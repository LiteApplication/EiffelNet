#include "eiffelnet.h"
#include <assert.h>

void marea_algorithm(struct lycee **lycees)
{
	// struct couple_el *el = (struct couple_el *)malloc(sizeof(struct couple_el) * NB_ELEVES);
	char change = 0;
	do
	{
		change = 0;
		for (int i = 0; i < NB_LYCEES; i++)
		{
			struct lycee *lycee = lycees[i];
			struct lvoeux *can = lycee->candidats;
			int capacite = lycee->capacite;
			int n = 0;
			while (can != NULL && n < capacite)
			{
				struct eleve *eleve = can->voeu->eleve;
				char delete = 0;
				for (int j = 0; j < NB_VOEUX; j++)
				{
					if (delete)
					{
						struct lvoeux *lvoeux = eleve->voeux[j]->lycee->candidats;
						while (lvoeux != NULL && lvoeux->voeu != can->voeu)
						{
							lvoeux = lvoeux->suiv;
						}
						if (lvoeux == NULL)
							continue;
						change = 1;
						if (lvoeux->prec == NULL && lvoeux->suiv != NULL)
						{
							lvoeux->suiv->prec = NULL;
						}
						else if (lvoeux->prec != NULL && lvoeux->suiv == NULL)
						{
							lvoeux->prec->suiv = NULL;
						}
						else
						{
							lvoeux->prec->suiv = lvoeux->suiv;
							lvoeux->suiv->prec = lvoeux->prec;
						}
						// free lvoeux to add
						// free voeu to add
						eleve->voeux[j] = NULL;
						continue;
					}
					if (eleve->voeux[j] == can->voeu)
					{
						delete = 1;
					}
				}
				n++;
			}
		}
	} while (change);
}
