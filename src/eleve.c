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
        struct eleve *eleve = eleves[i];
        struct lvoeux *lvoeux = eleve->demandes;
        struct lvoeux *lvoeux_prev;
        while (lvoeux != NULL)
        {
            lvoeux_prev = lvoeux;
            lvoeux = lvoeux->suiv;
            free(lvoeux_prev->voeu);
            free(lvoeux_prev);
        }
        free(eleve);
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

    struct lvoeux *lvoeu_lycee = (struct lvoeux *)malloc(sizeof(struct lvoeux));
    struct lvoeux *lvoeu_eleve = (struct lvoeux *)malloc(sizeof(struct lvoeux));

    if (lvoeu_lycee == NULL || lvoeu_eleve == NULL)
    {
        fprintf(stderr, "Erreur lors de l'affectation de l'élève %d au lycée %d\n", eleve->id, eleve->_raw_voeux[position]);
        return;
    }
    lvoeu_lycee->voeu = voeu;
    lvoeu_eleve->voeu = voeu;
    eleve->lmaillon[position] = lvoeu_lycee;
    eleve->emaillon[position] = lvoeu_eleve;

    // On insère le voeu dans la liste des voeux du lycée, de sorte à ce que la liste soit triée par score décroissant
    if (lycee_eleve->candidats == NULL || lycee_eleve->candidats->voeu->score < score)
    { // cas particulier : la liste est vide ou le voeu est le plus grand
        lvoeu_lycee->suiv = lycee_eleve->candidats;
        lycee_eleve->candidats = lvoeu_lycee;
        lvoeu_lycee->prec = NULL;
        return;
    }

    struct lvoeux *lvoeux = lycee_eleve->candidats;
    while (lvoeux->suiv != NULL && lvoeux->suiv->voeu->score > score)
    {
        lvoeux = lvoeux->suiv;
    }
    lvoeu_lycee->suiv = lvoeux->suiv;
    lvoeux->suiv = lvoeu_lycee;
    lvoeu_lycee->prec = lvoeux;
    if (lvoeu_lycee->suiv != NULL)
        lvoeu_lycee->suiv->prec = lvoeu_lycee;

    // On ajoute le voeu à la liste des voeux de l'élève
    if (eleve->emaillon[position - 1] != NULL)
    { // Cas rapide, les voeux sont ajoutés dans l'ordre
        eleve->emaillon[position - 1]->suiv = lvoeu_eleve;
        lvoeu_eleve->prec = eleve->emaillon[position - 1];
        return;
    }

    // Cas général, on doit parcourir la liste des voeux de l'élève
    struct lvoeux *ptr = eleve->demandes;
    if (ptr == NULL)
    { // Cas particulier : la liste est vide
        eleve->demandes = lvoeu_eleve;
        lvoeu_eleve->prec = NULL;
        return;
    }
    while (ptr->suiv != NULL)
    {
        ptr = ptr->suiv;
    }
    ptr->suiv = lvoeu_eleve;
    lvoeu_eleve->prec = ptr;
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

bool supprime_voeux_after(struct eleve *eleve, struct lycee *lycee)
{
    struct lvoeux *lvoeu = eleve->demandes;
    // Itération sur la liste des voeux de l'élève jusqu'à trouver le voeu correspondant au lycée
    while (lvoeu != NULL && lvoeu->voeu->lycee != lycee)
    {
        lvoeu = lvoeu->suiv;
    }
    if (lvoeu == NULL)
    {
        fprintf(stderr, "Erreur lors de la suppression: L'élève %d n'a pas de voeu pour le lycée %d\n", eleve->id, lycee->id);
        return false;
    }

    if (lvoeu->suiv == NULL)
        return false;

    lvoeu = lvoeu->suiv;

    bool suppression = false;

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
        suppression = supprime_eleve(eleve, lvoeu->voeu->lycee) || suppression;

        // Free stuff
        free(lvoeu->voeu);
        free(lvoeu);
    }
    return suppression;
}
