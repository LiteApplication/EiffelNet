#include <stdio.h>
#include <stdlib.h>
#include "eiffelnet.h"
#include "output.h"
#include "test.h"

int main(void)
{
	struct lycee **lycees = lecture_lycees("../data/lycees.csv");
	struct eleve **eleves = lecture_eleves("../data/voeux_zones.csv");

	place_eleves(eleves, lycees);

	struct voeu *voeu = malloc(sizeof(voeu));
	create_lvoeux(voeu);
	printf("\n\n");
	for (int i = 0; i < NB_LYCEES; i++)
	{
		struct lycee *lycee = lycees[i];
		printf("- %d\n", lycee->id);
		struct lvoeux *voeu = lycee->candidats;
		while (voeu != NULL)
		{
			printf("\t%d\n", voeu->voeu->score);
			voeu = voeu->suiv;
		}
	}

	marea_algorithm(lycees);
	for (int i = 0; i < NB_LYCEES; i++)
	{
		struct lycee *lycee = lycees[i];
		printf("- %d\n", lycee->id);
		struct lvoeux *voeu = lycee->candidats;
		while (voeu != NULL)
		{
			printf("\t%d\n", voeu->voeu->eleve->id);
			voeu = voeu->suiv;
		}
	}

	return EXIT_SUCCESS;
}

/* Main de exemple_tri */
/* int main()
{
	int tab[6] = {17, 3, 5, -2, 15, 20};
	qsort(tab, 6, sizeof(int), inferieur);
	printf("nouvel ordre : ");
	for (int i = 0; i < 6; i = i + 1)
	{
		printf("%d ", tab[i]);
	}
	printf("\n");
	return 0;
} */

/* Main de exemple_lecture */
/* int main(void)
{
	exemple_lecture_voeux();
	printf("------------------\n");
	exemple_lecture_lycees();
	return 0;
} */
