#include "eleve.h"
#include <stdlib.h>
#include <stdio.h>

struct eleve *eleve_new(int id, int scores[NB_VOEUX], int voeux[NB_VOEUX])
{
    if (id < 0)
    {
        return NULL;
    }
    struct eleve *eleve = (struct eleve *)malloc(sizeof(struct eleve));
    if (eleve == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }
    eleve->id = id;
    eleve->demandes = NULL;
    for (int i = 0; i < NB_LYCEES; i++)
    {
        eleve->lmaillon[i] = NULL;
        eleve->emaillon[i] = NULL;
    }

    for (int i = 0; i < NB_VOEUX; i++)
    {
        eleve->_raw_scores[i] = scores[i];
        eleve->_raw_voeux[i] = voeux[i];
    }

    return eleve;
}

struct eleve **lecture_eleves(char *filename)
{
    int eleve;
    int scores[NB_VOEUX];
    int voeux[NB_VOEUX];

    FILE *f = debut_lecture(filename);
    if (f == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    struct eleve **eleves = (struct eleve **)malloc(NB_ELEVES * sizeof(struct eleve *));
    if (eleves == NULL)
    {
        fprintf(stderr, "Impossible d'allouer la mémoire pour les élèves\n");
        return NULL;
    }

    int i = 0;
    while (lecture_eleve_suivant_zones(f, &eleve, &scores, voeux) != EOF && i < NB_ELEVES)
    {
        eleves[i] = eleve_new(eleve, scores, voeux);
        if (eleves[i] == NULL)
        {
            free_eleves(eleves, i);
            fin_lecture(f);
            return NULL;
        }
        i++;
    }
    fin_lecture(f);
    return eleves;
}

void free_eleves(struct eleve **eleves, int nb_eleves)
{
    for (int i = 0; i < nb_eleves; i++)
    {
        free(eleves[i]);
    }
    free(eleves);
}

void affecte_eleve(struct eleve *eleve, struct lycee *lycee)
{
}

void inverse_voeux(struct eleve *eleve)
{
}
