#include "eiffelnet.h"
#include <assert.h>

// Une seule zone
struct couple_el *marea_algorithm(struct eleve **eleves, struct lycee **lycees)
{
	struct couple_el *el = (struct couple_el *)malloc(sizeof(struct couple_el) * NB_ELEVES);
	return el;
}
