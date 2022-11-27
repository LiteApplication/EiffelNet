#include <stdio.h>
#include <stdlib.h>
#include "eiffelnet.h"
#include "eiffelnet_debug.h"
#include "test.h"

int main(void)
{
    int nb_eleves, nb_lycees;
    struct lycee **lycees = lecture_lycees("../data/lycees.csv", &nb_lycees);
    struct eleve **eleves = lecture_eleves("../data/voeux.csv", &nb_eleves);
    printf("Informations:\n\n");
    printf("Nombre d'eleves: %d\n", nb_eleves);
    printf("Nombre de lycees: %d\n", nb_lycees);
    printf("Eleves :\n");
    for (int i = 0; i < nb_eleves; i = i + 1)
    {
        print_eleve(eleves[i]);
    }
    printf("Lycees :\n");
    for (int i = 0; i < nb_lycees; i = i + 1)
    {
        print_lycee(lycees[i]);
    }
    printf("\n");

    printf("Une seule zone:\n\n");
    struct couple_el *el = oarea_algorithm(eleves, nb_eleves, lycees, nb_lycees, eleve_comparator);
    int i = 0;
    for(int h = 0; h < nb_eleves; h++) {
	printf("%d\n", el[h].eleve->id);
    }
    int *already_seen = malloc(sizeof(int) * nb_lycees);
    int g = 0;
    while (i < nb_eleves)
    {
        struct lycee *lycee = el[i].lycee;
        if (lycee == NULL)
        {
            i++;
            continue;
        }
        char in_it = 0;
        for (int j = 0; j < nb_lycees; j++)
        {
            if (already_seen[j] == lycee->id)
            {
                in_it = 1;
                break;
            }
        }
        if (in_it)
        {
            i++;
            continue;
        }
        already_seen[g] = lycee->id;
        g++;
        char is_not = 0;
        printf("Lycée n°%d\n", lycee->id);
        printf(" -%d\n", el[i].eleve->id);
        for (int j = i + 1; j < nb_eleves; j++)
        {
            if (el[j].lycee == lycee)
            {
                printf(" -%d\n", el[j].eleve->id);
            }
            else
            {
                if (!is_not)
                {
                    i = j;
                    is_not = 1;
                }
            }
        }
    }
    free(already_seen);
    free_eleves(eleves, nb_eleves);
    free_lycees(lycees, nb_lycees);
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
