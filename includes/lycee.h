#ifndef _LYCEE_H
#define _LYCEE_H

#include "eleve.h"

struct lycee
{
    int id;
    int capacite;    // nombre de places
    int capacite_actuel;
    struct lvoeux *candidats; // liste des voeux sur ce lycee par ordre decroissant de score pour ce lycee
    struct lvoeux *candidats_top;
};

/**
 * @brief Crée un nouveau lycée
 * @param id L'identifiant du lycée
 * @param effectif L'effectif du lycée
 * @return Un pointeur vers le lycée créé
 */
struct lycee *lycee_new(int id, int effectif);

/**
 * @brief Lit la liste des lycées dans un fichier
 * @param filename Le nom du fichier à lire
 * @return Un tableau de pointeurs vers les lycées lus
 */
struct lycee **lecture_lycees(char *filename);

/**
 * @brief Libère la mémoire allouée pour un lycée
 * @param lycees Le tableau de lycées à libérer
 * @param nb_lycees Le nombre de lycées dans le tableau
 */
void free_lycees(struct lycee **lycee, int nb_lycees);

/**
 * @brief Trouve un lycée dans un tableau de lycées (complexité constante ou linéaire en fonction de l'organisation du tableau)
 * @param id Identifiant du lycée à trouver
 * @param lycees Tableau de lycées
 * @return Un pointeur vers le lycée trouvé, NULL si non trouvé
 */
struct lycee *find_lycee(int id, struct lycee **lycees);

void inverse_candidats(struct eleve **eleves);

#endif // _LYCEE_H
