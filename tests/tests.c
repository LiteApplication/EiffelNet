#include <assert.h>
#include <stdbool.h>

#include "eiffelnet.h"
#include "output.h"

int main()
{
    void *test_fail;
    /*
    int voeux1[NB_VOEUX] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int scores1[NB_VOEUX] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 15};
    int voeux2[NB_VOEUX] = {1, 2, 0, 13, 29, 3, 5, 7, 9, 1};
    int scores2[NB_VOEUX] = {9, 12, 20, 30, 40, 50, 60, 70, 80, 9};
    struct eleve *eleve1 = eleve_new(1, scores1, voeux1);
    struct eleve *eleve2 = eleve_new(2, scores2, voeux2);
    test_fail = eleve_new(-1, scores1, voeux1);
    assert(test_fail == NULL);

    assert(eleve1->id == 1);
    assert(eleve1->_raw_scores[0] == 10);
    assert(eleve2->id == 2);
    assert(eleve2->_raw_scores[0] == 20);
    for (int i = 0; i < NB_VOEUX; i++)
    {
        assert(eleve1->voeux[i] == voeux1[i]);
        assert(eleve2->voeux[i] == voeux2[i]);
    }

    struct lycee *lycee1 = lycee_new(1, 1);
    struct lycee *lycee0 = lycee_new(0, 1);

    struct lycee **lycees = (struct lycee **)malloc(sizeof(struct lycee *) * NB_LYCEES);

    lycees[0] = lycee1; // Force it to be full
    lycees[1] = lycee0; // They are not in the right order

    for (int i = 2; i < NB_LYCEES; i++)
        lycees[i] = lycee_new(i, (i + 1));

    test_fail = lycee_new(-1, 10);
    assert(test_fail == NULL);
    test_fail = lycee_new(1, -1);
    assert(test_fail == NULL);

    // Use find_lycee using both fast and slow method (O(n) and O(1))
    assert(find_lycee(0, lycees) == lycee0);
    assert(find_lycee(1, lycees) == lycee1);
    assert(find_lycee(3, lycees) == lycees[3]);

    assert(lycee1->id == 1);
    assert(lycee1->effectif == 1);
    assert(lycee1->effectif_actuel == 0);
    assert(lycees[2]->id == 2);
    assert(lycees[2]->effectif == 3);
    assert(lycees[2]->effectif_actuel == 0);
    affecte_eleve(eleve2, lycees[2]);
    assert(lycees[2]->eleves[0] == eleve1);
    assert(lycees[2]->eleves[1] == eleve2);
    assert(lycees[2]->effectif_actuel == 2);
    assert(lycee1->eleves[0] == eleve1);
    assert(lycee1->effectif_actuel == 1);

    lycee1->eleves[0] = NULL;
    lycee1->effectif_actuel = 0;
    lycees[2]->eleves[0] = NULL;
    lycees[2]->eleves[1] = NULL;
    lycees[2]->effectif_actuel = 0;

    assert(eleve_comparator(&eleve1, &eleve2) == 10);
    assert(eleve_comparator(&eleve1, &eleve1) == 0);

    // Create a useless list of students
    struct eleve **eleves = (struct eleve **)malloc(sizeof(struct eleve *) * NB_ELEVES);
    int voeux[NB_VOEUX] = {0};
    for (int i = 0; i < NB_ELEVES; i++)
        eleves[i] = eleve_new(i, 0, voeux);

    free(eleves[1]);
    free(eleves[2]);

    eleves[1] = eleve1;
    eleves[2] = eleve2;


    struct couple_el *result = oarea_algorithm(eleves, lycees, eleve_comparator);

    assert(lycee1->eleves[0] == eleve2);
    assert(lycees[2]->eleves[0] == eleve1);
    assert(lycees[2]->eleves[1] != eleve1 && lycees[2]->eleves[1] != eleve2);

    for (int i = 0; i < NB_ELEVES; i++)
    {
        if (result[i].eleve == eleve1)
            assert(result[i].lycee->id == 2);
        else if (result[i].eleve == eleve2)
            assert(result[i].lycee->id == 1);
    }

    free_lycees(lycees, NB_LYCEES);
    free_eleves(eleves, NB_ELEVES);
    free(result);
    */
}
