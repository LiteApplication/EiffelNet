#ifndef _LYCEE_H
#define _LYCEE_H

#include "eleve.h"
#include <stdbool.h>

/**
 * @brief Structure représentant un lycée
 * @note Les candidats sont triés par ordre décroissant de score pour ce lycée
 */
struct lycee
{
    int id;
    int capacite;             // nombre de places
    struct lvoeux *candidats; // liste des voeux sur ce lycee par ordre décroissant de score pour ce lycee
};

struct eleve; // forward declaration
/**
 * @brief Crée un nouveau lycée
 * @param id L'identifiant du lycée
 * @param capacite La capacité du lycée
 * @return Un pointeur vers le lycée créé
 */
struct lycee *lycee_new(int id, int capacite);

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
 * @note Le pointeur vers le tableau de lycées n'est pas libéré.
 */
void free_lycees(struct lycee **lycee, int nb_lycees);

/**
 * @brief Trouve un lycée dans un tableau de lycées
 * @param id Identifiant du lycée à trouver
 * @param lycees Tableau de lycées
 * @return Un pointeur vers le lycée trouvé, NULL si non trouvé
 * @note La complexité de cette fonction est constante si l'id du lycée
 * correspond à son indice dans le tableau. Sinon, la complexité est linéaire en
 * la taille du tableau.
 */
struct lycee *find_lycee(int id, struct lycee **lycees);

/**
 * @brief Supprime un élève d'un lycée
 * @param eleve L'élève à supprimer
 * @param lycee Le lycée
 * @return true si l'élève a été supprimé, false sinon
 */
bool supprime_eleve(struct eleve *eleve, struct lycee *lycee);

#endif // _LYCEE_H
