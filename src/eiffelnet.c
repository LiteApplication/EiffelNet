#include "eiffelnet.h"
#include <assert.h>

// Une seule zone
struct couple_el *oarea_algorithm(struct eleve **eleves, struct lycee **lycees, int (*eleve_comparator)(const void *, const void *))
{
	qsort(eleves, NB_ELEVES, sizeof(struct eleve *), eleve_comparator);

	struct couple_el *el = malloc(sizeof(struct couple_el) * NB_ELEVES);
	for (int i = 0; i < NB_ELEVES; i++)
	{
		int j = 0;
		int lycee_id = eleves[i]->voeux[0];
		struct lycee *lycee = NULL; // Cannot use do...while
		while (lycee == NULL ||
			   (lycee->effectif_actuel >= lycee->effectif && j < NB_VOEUX))
		{
			lycee_id = eleves[i]->voeux[j];
			lycee = find_lycee(lycee_id, lycees);
			if (lycee == NULL)
			{
				printf("Impossible de trouver un lycée pour l'élève %d\n", eleves[i]->id);
				return NULL;
			}
			j++;
		}
		if (j == NB_VOEUX)
		{
			lycee = NULL;
		}
		else
		{
			lycee->eleves[lycee->effectif_actuel] = eleves[i];
			lycee->effectif_actuel++;
		}
		el[i].lycee = lycee;
		el[i].eleve = eleves[i];
	}
	return el;
}
