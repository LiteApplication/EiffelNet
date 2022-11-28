#ifndef _EIFFELNET_H
#define _EIFFELNET_H

#include "lycee.h"
#include "eleve.h"
#include <stdlib.h>

#undef PRETTY_PRINT

struct couple_el
{
	struct eleve *eleve;
	struct lycee *lycee;
};

/**
 * @brief Algorithme de répartition des élèves dans les lycées (une seule zone)
 * @param eleves: tableau d'élèves
 * @param nb_eleves: nombre d'élèves dans le tableau
 * @param lycees: tableau de lycées
 * @param nb_lycees: nombre de lycées dans le tableau
 * @param eleve_comparator: fonction de comparaison des élèves entre eux
 */
struct couple_el *oarea_algorithm(struct eleve **eleves, struct lycee **lycees, int (*eleve_comparator)(const void *, const void *));

#endif // _EIFFELNET_H