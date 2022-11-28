#ifndef _OUTPUT_H
#define _OUTPUT_H

#include "lycee.h"
#include "eleve.h"

/**
 * @brief Affiche les résultats de l'algorithme sous forme brute comme indiqué
 * dans la consigne
 * @param lycee La liste des lycees une fois l'algorithme terminé
 */
void format_result(struct lycee **lycees);

/**
 * @brief Affiche un élève (ainsi que son score et ses voeux)
 * @param eleve L'élève à afficher
 */
void print_eleve(struct eleve *eleve);

/**
 * @brief Affiche un lycée et la liste de ses élèves
 * @param lycee Le lycée à afficher
 */
void print_lycee(struct lycee *lycee);
#endif // _OUTPUT_H