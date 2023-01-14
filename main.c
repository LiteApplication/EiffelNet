#include <stdio.h>
#include <stdlib.h>
#include "eiffelnet.h"
#include "output.h"
#include "test.h"

int main(void)
{
	struct lycee **lycees = lecture_lycees("../data/lycees.csv");
	struct eleve **eleves = lecture_eleves("../data/voeux_zones.csv");

	place_eleves(eleves, lycees); // place les eleves dans listes des lycees

	marea_algorithm(lycees); // Algorithme principal
	format_result(lycees);

	// Libération de la mémoire
	free_eleves(eleves, NB_ELEVES);
	free_lycees(lycees, NB_LYCEES);

	return EXIT_SUCCESS;
}