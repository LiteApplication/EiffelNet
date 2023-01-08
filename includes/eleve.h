#ifndef _ELEVE_H
#define _ELEVE_H

#include "lycee.h"
#include "lecture.h"

#define NB_ELEVES 1327
#define NB_LYCEES 28

struct lycee; // forward declaration

/**
 * @brief Structure représentant un élève
 */
struct eleve
{
    int id;
    struct voeu** voeux;
    /*
    int _raw_scores[NB_VOEUX];
    int _raw_voeux[NB_VOEUX];
    struct lvoeux *demandes;            // liste des voeux de l'eleve par ordre decroissant de preference
    struct lvoeux *lmaillon[NB_LYCEES]; // acces direct au maillon de chaque lycee demande dans la liste du lycee;
    struct lvoeux *emaillon[NB_LYCEES]; // acces direct au maillon de chaque lycee demande dans la liste de l'eleve
    */
};

/**
 * @brief Crée et alloue un élève
 * @param id L'identifiant de l'élève
 * @param score Le score de l'élève
 * @param voeux Les voeux de l'élève dans un tableau de taille NB_VOEUX
 * @return Un pointeur vers l'élève créé
 */
struct eleve *eleve_new(int id, int scores[NB_VOEUX], int voeux[NB_VOEUX], struct lycee **lycees);

/**
 * @brief la liste des élèves dans un fichier
 * @param filename Le nom du fichier à lire
 * @return Un tableau de pointeurs vers les élèves lus
 */
struct eleve **lecture_eleves(char *filename, struct lycee **lycees);

/**
 * @brief Libère la mémoire allouée pour un élève
 * @param eleves Le tableau d'élèves à libérer
 * @param nb_eleves Le nombre d'élèves dans le tableau
 */
void free_eleves(struct eleve **eleves, int nb_eleves);
/**
 * @brief Ajoute un élève à un lycée
 * @param eleve L'élève
 * @param lycee Le lycée
 */
void affecte_eleve(struct eleve *eleve, struct lycee *lycee);

void inverse_voeux(struct eleve **eleves);

#endif // _ELEVE_H
