#ifndef _LYCEE_H
#define _LYCEE_H

#include "eleve.h"

struct lycee
{
    int id;
    int effectif;
    struct eleve **eleves;
    int effectif_actuel; // Nombre d'élèves dans le tableau
};

struct lycee *lycee_new(int id, int effectif);
struct lycee **lecture_lycees(char *filename, int *nb_lycees);
void free_lycees(struct lycee **lycee, int nb_lycees);
struct lycee *find_lycee(int id, struct lycee **lycees, int nb_lycees);

#endif // _LYCEE_H