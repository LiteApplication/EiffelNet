#ifndef _ELEVE_H
#define _ELEVE_H

#include "lecture.h"
#include "lycee.h"

struct lycee; // forward declaration

struct eleve
{
    int id;
    int score;
    int voeux[NB_VOEUX];
};

struct eleve *eleve_new(int id, int score, int *voeux);
struct eleve **lecture_eleves(char *filename, int *nb_eleves);
void free_eleves(struct eleve **eleves, int nb_eleves);
void add_voeu(struct eleve *eleve, struct lycee *lycee, int rang);
int eleve_comparator(const void *e1, const void *e2);

#endif // _ELEVE_H