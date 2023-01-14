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

	// format_result(lycees);
	marea_algorithm(lycees);
	format_result(lycees);

	return EXIT_SUCCESS;
}