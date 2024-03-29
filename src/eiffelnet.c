#include "eiffelnet.h"
#include <assert.h>
#include <stdbool.h>

void marea_algorithm(struct lycee **lycees)
{
	bool change = true;
	while (change)
	{
		change = false;
		for (int i = 0; i < NB_LYCEES; i++) // pour chaque lycee
		{
			struct lycee *lycee = lycees[i];
			struct lvoeux *can = lycee->candidats;
			int capacite = lycee->capacite;
			int n = 0;
			while (can != NULL && n < capacite)
			{
				struct eleve *eleve = can->voeu->eleve;
				change = supprime_voeux_after(eleve, lycee) || change;
				can = can->suiv;
				n++;
			}
		}
	}
}
