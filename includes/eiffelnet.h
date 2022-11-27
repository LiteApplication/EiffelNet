#ifndef _EIFFELNET_H
#define _EIFFELNET_H

#include "lycee.h"
#include "eleve.h"
#include <stdlib.h>

struct couple_el
{
	struct eleve *eleve;
	struct lycee *lycee;
};

/** eleves: tableau d'élèves
 * nb_eleves: nombre d'élèves dans le tableau
 * lycees: tableau de lycées
 * nb_lycees: nombre de lycées dans le tableau
 * eleve_comparator: fonction de comparaison des élèves entre eux
 */
struct couple_el *oarea_algorithm(struct eleve **eleves, int nb_eleves, struct lycee **lycees, int nb_lycees, int (*eleve_comparator)(const void *, const void *));

#endif // _EIFFELNET_H