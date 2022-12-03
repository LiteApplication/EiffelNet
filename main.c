#include <stdio.h>
#include <stdlib.h>
#include "eiffelnet.h"
#include "output.h"
#include "test.h"

int main(void)
{
    struct lycee **lycees = lecture_lycees("../data/lycees.csv");
    struct eleve **eleves = lecture_eleves("../data/voeux.csv");
#ifdef PRETTY_PRINT
    printf("Informations:\n\n");
    printf("Nombre d'eleves: %d\n", NB_ELEVES);
    printf("Nombre de lycees: %d\n", NB_LYCEES);

    // Uncomment this line to print the list of students
    /* printf("Eleves :\n");
    for (int i = 0; i < NB_ELEVES; i = i + 1)
    {
        print_eleve(eleves[i]);
    }
    printf("\n");
 */
    printf("Une seule zone:\n\n");
#endif
    struct couple_el *el = oarea_algorithm(eleves, lycees, eleve_comparator);
    if (el == NULL)
    {
        printf("Erreur lors du traitement des donnees\n");
        return 1;
    }
#ifdef PRETTY_PRINT

    printf("Lycees :\n");
    for (int i = 0; i < NB_LYCEES; i = i + 1)
    {
        print_lycee(lycees[i]);
    }

    printf("Sans lycées:\n");
    for (int i = 0; i < NB_ELEVES; i++)
    {
        if (el[i].lycee == NULL)
        {
            print_eleve(el[i].eleve);
        }
    }
    printf("\n");
#else
    format_result(lycees);

#endif
    free(el);
    free_eleves(eleves, NB_ELEVES);
    free_lycees(lycees, NB_LYCEES);
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
