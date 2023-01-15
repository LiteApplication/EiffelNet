#ifndef _ELEVE_H
#define _ELEVE_H

#include "lycee.h"
#include "lecture.h"
#include <stdbool.h>

#define NB_ELEVES 1327
#define NB_LYCEES 28

struct lycee; // forward declaration

/**
 * @brief Structure représentant un élève
 */
struct eleve
{
    int id;
    int _raw_scores[NB_VOEUX];          // Utilisé pour la lecture des fichiers
    int _raw_voeux[NB_VOEUX];           // pareil
    struct lvoeux *demandes;            // liste des voeux de l'eleve par ordre decroissant de preference
    struct lvoeux *lmaillon[NB_LYCEES]; // acces direct au maillon de chaque lycee demande dans la liste du lycee;
    struct lvoeux *emaillon[NB_LYCEES]; // acces direct au maillon de chaque lycee demande dans la liste de l'eleve
};

/**
 * @brief Crée et alloue un élève
 * @param id L'identifiant de l'élève
 * @param scores Les scores de l'élève
 * @param voeux Les voeux de l'élève dans un tableau de taille NB_VOEUX
 * @return Un pointeur vers l'élève créé
 */
struct eleve *eleve_new(int id, int scores[NB_VOEUX], int voeux[NB_VOEUX]);

/**
 * @brief la liste des élèves dans un fichier
 * @param filename Le nom du fichier à lire
 * @return Un tableau de pointeurs vers les élèves lus
 */
struct eleve **lecture_eleves(char *filename);

/**
 * @brief Ajoute un élève à un lycée
 * @param eleve L'élève
 * @param lycees La liste des lycées
 * @param position Position du voeu dans la liste des voeux de l'élève
 */
void affecte_eleve(struct eleve *eleve, struct lycee **lycees, int position);

/**
 * @brief Place tous les élèves dans les lycées demandés et organise les voeux.
 * @param eleves La liste des élèves
 * @param lycees La liste des lycées
 */
void place_eleves(struct eleve **eleves, struct lycee **lycees);

/**
 * @brief Supprime les voeux à partir d'un lycée et retire l'élève des lycées suivants
 * @param eleve L'élève
 * @param lycee Le lycée
 */
bool supprime_voeux_after(struct eleve *eleve, struct lycee *lycee);

/**
 * @brief Libère la mémoire allouée pour les élèves
 * @param eleves Le tableau d'élèves à libérer
 * @param nb_eleves Le nombre d'élèves dans le tableau
 * @note Cette fonction se charge de libérer la mémoire allouée pour les voeux dans la liste des voeux
 * Le pointeur vers le tableau d'élèves n'est pas libéré.
 */
void free_eleves(struct eleve **eleves, int nb_eleves);

#endif // _ELEVE_H
