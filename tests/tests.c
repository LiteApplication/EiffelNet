#include <assert.h>
#include "eiffelnet.h"

int main()
{
    void *test_fail;

    /* eleve_new */
    int voeux1[NB_VOEUX] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int voeux2[NB_VOEUX] = {2, 4, 0, 13, 29, 3, 5, 7, 9, 1};
    struct eleve *eleve1 = eleve_new(1, 10, voeux1);
    struct eleve *eleve2 = eleve_new(2, 20, voeux2);
    test_fail = eleve_new(-1, 10, voeux1);
    assert(test_fail == NULL);
    test_fail = eleve_new(1, -1, voeux1);
    assert(test_fail == NULL);

    assert(eleve1->id == 1);
    assert(eleve1->score == 10);
    assert(eleve2->id == 2);
    assert(eleve2->score == 20);
    for (int i = 0; i < NB_VOEUX; i++)
    {
        assert(eleve1->voeux[i] == voeux1[i]);
        assert(eleve2->voeux[i] == voeux2[i]);
    }

    /* lycee_new */
    struct lycee *lycee1 = lycee_new(1, 10);
    struct lycee *lycee2 = lycee_new(2, 20);
    test_fail = lycee_new(-1, 10);
    assert(test_fail == NULL);
    test_fail = lycee_new(1, -1);
    assert(test_fail == NULL);

    assert(lycee1->id == 1);
    assert(lycee1->effectif == 10);
    assert(lycee1->effectif_actuel == 0);
    assert(lycee2->id == 2);
    assert(lycee2->effectif == 20);
    assert(lycee2->effectif_actuel == 0);

    /* add_voeu */
    add_voeu(eleve1, lycee2, 1);
    add_voeu(eleve1, lycee1, 0);
    add_voeu(eleve2, lycee2, 0);
    assert(lycee1->eleves[0] == eleve1);
    assert(lycee2->eleves[1] == eleve2);
    assert(lycee2->eleves[0] == eleve1);
    assert(lycee1->effectif_actuel == 1);
    assert(lycee2->effectif_actuel == 2);

    /* eleve_comparator */
    assert(eleve_comparator(eleve1, eleve2) == 10);
    assert(eleve_comparator(eleve1, eleve1) == 0);

    /*  */
}
