#include "eleve.h"
#include "voeux.h"
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
    while (lecture_eleve_suivant_zones(f, &eleve, scores, voeux) != EOF && i < NB_ELEVES)
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

void affecte_eleve(struct eleve *eleve, struct lycee **lycees, int position)
{
    struct lycee *lycee_eleve = find_lycee(eleve->_raw_voeux[position], lycees);
    if (lycee_eleve == NULL)
    {
        fprintf(stderr, "Erreur lors de l'affectation de l'élève %d au lycée %d\n", eleve->id, eleve->_raw_voeux[position]);
        return;
    }

    int score = eleve->_raw_scores[position];

    struct voeu *voeu = voeu_new(score, eleve, lycee_eleve);
    if (voeu == NULL)
    {
        fprintf(stderr, "Erreur lors de l'affectation de l'élève %d au lycée %d\n", eleve->id, eleve->_raw_voeux[position]);
        return;
    }

    struct lvoeux *lvoeu = (struct lvoeux *)malloc(sizeof(struct lvoeux));
    if (lvoeu == NULL)
    {
        fprintf(stderr, "Erreur lors de l'affectation de l'élève %d au lycée %d\n", eleve->id, eleve->_raw_voeux[position]);
        return;
    }
    lvoeu->v = voeu;
    eleve->emaillon[position] = lvoeu;

    // On insère le voeu dans la liste des voeux du lycée, de sorte à ce que la liste soit triée par score décroissant
    if (lycee_eleve->candidats == NULL || lycee_eleve->candidats->v->score < score)
    { // cas particulier : la liste est vide ou le voeu est le plus grand
        lvoeu->suiv = lycee_eleve->candidats;
        lycee_eleve->candidats = lvoeu;
        lvoeu->prec = NULL;
        return;
    }

    struct lvoeux *lvoeux = lycee_eleve->candidats;
    while (lvoeux->suiv != NULL && lvoeux->suiv->v->score > score)
    {
        lvoeux = lvoeux->suiv;
    }
    lvoeu->suiv = lvoeux->suiv;
    lvoeux->suiv = lvoeu;
    lvoeu->prec = lvoeux;
    if (lvoeu->suiv != NULL)
        lvoeu->suiv->prec = lvoeu;
}

void place_eleves(struct eleve **eleves, struct lycee **lycees)
{
    for (int i = 0; i < NB_ELEVES; i++)
    {
        for (int j = 0; j < NB_VOEUX; j++)
        {
            affecte_eleve(eleves[i], lycees, j);
        }
    }
}

void supprime_voeux(struct eleve *eleve, struct lycee *lycee)
{
    struct lvoeux *lvoeu = eleve->demandes;
    // Itération sur la liste des voeux de l'élève jusqu'à trouver le voeu correspondant au lycée
    while (lvoeu != NULL && lvoeu->v->lycee != lycee)
    {
        lvoeu = lvoeu->suiv;
    }
    if (lvoeu == NULL)
    {
        fprintf(stderr, "Erreur lors de la suppression: L'élève %d n'a pas de voeu pour le lycée %d\n", eleve->id, lycee->id);
        return;
    }

    while (lvoeu != NULL)
    {
        // On supprime le voeu de la liste des voeux de l'élève
        if (lvoeu->prec != NULL)
            lvoeu->prec->suiv = lvoeu->suiv;
        else
            eleve->demandes = lvoeu->suiv;
        if (lvoeu->suiv != NULL)
            lvoeu->suiv->prec = lvoeu->prec;

        // On supprime le voeu de la liste des voeux du lycée
        supprime_eleve(eleve, lycee);

        // Free stuff
        free(lvoeu->v);
        free(lvoeu);
        }
}

void inverse_voeux(struct eleve *eleve)
{
}
