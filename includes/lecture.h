#ifndef _LECTURE_H
#define _LECTURE_H

#include <stdio.h>

#define NB_VOEUX 10

/**
 * @brief a lancer avant de lire le contenu d'un fichier
 * @param fic nom d'un fichier suppose au bon format
 * @return un pointeur sur le fichier ouvert
 */
FILE *debut_lecture(const char *fic);

/** @param f valeur récupérée grace a debut_lecture
 * @brief À lancer quand on a fini de lire le contenu d'un fichier
 */
void fin_lecture(FILE *f);

/** @param f valeur récupérée grace a debut_lecture
 * @brief lit les donnees d'une ligne dans un fichier de voeux et les stocke
 * dans les adresses fournies en argument, avec l'hypothèse qu'il y
 * a NB_VOEUX voeux
 * @return le nombre d'arguments lus, ou EOF si la fin du fichier
 * est atteinte (EOF est défini dans stdio.h)
 * POUR LE PREMIER RENDU
 */
int lecture_eleve_suivant(FILE *f, int *eleve, int *score, int *lycees);

/** @param f valeur récupérée grace a debut_lecture
 * @brief lit les donnees d'une ligne dans un fichier de lycees et les stocke
 * dans les adresses fournies en argument
 * @return le nombre d'arguments lus, ou EOF si la fin du fichier
 * est atteinte (EOF est défini dans stdio.h)
 */
int lecture_lycee_suivant(FILE *f, int *lycee, int *capacite);

/** @param f valeur récupérée grace a debut_lecture
 * @brief lit les donnees d'une ligne dans un fichier de voeux et les stocke
 * dans les adresses fournies en argument, avec l'hypothèse qu'il y
 * a NB_VOEUX voeux
 * @return le nombre d'arguments lus, ou EOF si la fin du fichier
 * est atteinte (EOF est défini dans stdio.h)
 * POUR LE DEUXIÈME RENDU
 */
int lecture_eleve_suivant_zones(FILE *f, int *eleve, int *scores, int *lycees);
#endif
