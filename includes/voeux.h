#ifndef _VOEUX_H
#define _VOEUX_H

#include "eleve.h"
#include "lycee.h"

/**
 * @brief Structure représentant un voeu (partagé entre un élève et un lycée)
 */
struct voeu
{
    int score;
    struct eleve *eleve;
    struct lycee *lycee;
};

/**
 * @brief Structure représentant un maillon de liste de voeux
 */
struct lvoeux
{
    struct voeu *voeu;
    struct lvoeux *prec, *suiv;
};

/**
 * @brief Crée et alloue un maillon de liste de voeux
 * @param voeu Le voeu du maillon
 * @return Un pointeur vers le maillon créé
 */
struct lvoeux *lvoeux_new(struct voeu *voeu);

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
