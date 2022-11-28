#ifndef _ELEVE_H
#define _ELEVE_H

#include "lecture.h"
#include "lycee.h"

#define NB_ELEVES 1327

struct lycee; // forward declaration

/**
 * @brief Structure représentant un élève
 */
struct eleve
{
    int id;
    int score;
    int voeux[NB_VOEUX];
};

/**
 * @brief Crée et alloue un élève
 * @param id L'identifiant de l'élève
 * @param score Le score de l'élève
 * @param voeux Les voeux de l'élève dans un tableau de taille NB_VOEUX
 * @return Un pointeur vers l'élève créé
 */
struct eleve *eleve_new(int id, int score, int *voeux);

/**
 * @brief la liste des élèves dans un fichier
 * @param filename Le nom du fichier à lire
 * @return Un tableau de pointeurs vers les élèves lus
 */
struct eleve **lecture_eleves(char *filename);

/**
 * @brief Libère la mémoire allouée pour un élève
 * @param eleves Le tableau d'élèves à libérer
 * @param nb_eleves Le nombre d'élèves dans le tableau
 */
void free_eleves(struct eleve **eleves, int nb_eleves);
/**
 * @brief Ajoute le voeu d'un élève à un lycée donné
 * @param eleve L'élève
 * @param lycee Le lycée
 * @param rang Le rang du voeu de l'élève
 */
void add_voeu(struct eleve *eleve, struct lycee *lycee, int rang);

/**
 * @brief Compare deux élèves
 * @param first Un élève
 * @param second Un autre élève
 */
int eleve_comparator(const void *first, const void *second);

void inverse_voeux(struct eleve *eleve);

#endif // _ELEVE_H
