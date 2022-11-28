#include "eleve.h"
#include <stdlib.h>
#include <stdio.h>

struct eleve *eleve_new(int id, int score, int *voeux)
{
    if (id < 0 || score < 0)
    {
        return NULL;
    }
    struct eleve *eleve = malloc(sizeof(struct eleve));
    if (eleve == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }
    eleve->id = id;
    eleve->score = score;
    for (int i = 0; i < NB_VOEUX; i++)
    {
        eleve->voeux[i] = voeux[i];
    }
    return eleve;
}

struct eleve **lecture_eleves(char *filename, int *nb_eleves)
{
    int eleve, score;
    int voeux[NB_VOEUX];

    *nb_eleves = 0;
    FILE *f = debut_lecture(filename);
    if (f == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    *nb_eleves = compte_lignes(f);
    struct eleve **eleves = malloc(*nb_eleves * sizeof(struct eleve *));
    if (eleves == NULL)
    {
        fprintf(stderr, "Impossible d'allouer la mémoire pour les élèves\n");
        return NULL;
    }

    int i = 0;
    while (lecture_eleve_suivant(f, &eleve, &score, voeux) != EOF && i < *nb_eleves)
    {
        eleves[i] = eleve_new(eleve, score, voeux);
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

void add_voeu(struct eleve *eleve, struct lycee *lycee, int rang)
{
    eleve->voeux[rang] = lycee->id;
    lycee->eleves[lycee->effectif_actuel] = eleve;
    lycee->effectif_actuel++;
}

int eleve_comparator(const void *first, const void *second)
{
    return ((struct eleve *)second)->score - ((struct eleve *)first)->score;
}

void inverse_voeux(struct eleve *eleve)
{
    int middle = NB_VOEUX / 2;
    for (int i = 0; i <= middle; i++)
    {
        int tmp = eleve->voeux[i];
        eleve->voeux[i] = eleve->voeux[NB_VOEUX - i - 1];
        eleve->voeux[NB_VOEUX - i - 1] = tmp;
    }
}
