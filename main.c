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
    printf("\n");

    printf("Une seule zone:\n\n");
    struct couple_el *el = oarea_algorithm(eleves, nb_eleves, lycees, nb_lycees, eleve_comparator);

    printf("Lycees :\n");
    for (int i = 0; i < nb_lycees; i = i + 1)
    {
        print_lycee(lycees[i]);
    }

    printf("Sans lycées: ");
    for (int i = 0; i < nb_eleves; i++)
    {
        if (el[i].lycee == NULL)
        {
            printf("%d ", el[i].eleve->id);
        }
    }
    printf("\n\n");
    free(el);
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
