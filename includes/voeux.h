#ifndef _VOEUX_H
#define _VOEUX_H

#include "eleve.h"
#include "lycee.h"

struct voeu
{
    int score;
    struct eleve *eleve;
    struct lycee *lycee;
};

struct lvoeux
{
    struct voeu *v;
    struct lvoeux *prec, *suiv;
};

/**
 * @brief Crée et alloue un voeu
 * @param score Le score du voeu
 * @param eleve L'élève du voeu
 * @param lycee Le lycée du voeu
 * @return Un pointeur vers le voeu créé
 */
struct voeu *voeu_new(int score, struct eleve *eleve, struct lycee *lycee);

/**
 * @brief Free une liste de voeux (dans le sens de suiv)
 * @param lv La liste de voeux à free
 */
void free_lvoeux(struct lvoeux *lv);

#endif // _VOEUX_H