#include <assert.h>
#include <stdbool.h>

#include "eiffelnet.h"
#include "output.h"

int main()
{
    void *fail_ptr; // Pour les tests qui doivent échouer

    // Test 1: Création d'un lycée
    struct lycee *lycee = lycee_new(1, 100);
    assert(lycee != NULL);
    assert(lycee->id == 1);
    assert(lycee->capacite == 100);
    assert(lycee->candidats == NULL);
    fail_ptr = lycee_new(-1, 100);
    assert(fail_ptr == NULL);
    fail_ptr = lycee_new(1, -100);
    assert(fail_ptr == NULL);

    // Test 2: Creation d'un élève
    int voeux[NB_VOEUX] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int scores[NB_VOEUX] = {100, 90, 80, 70, 60, 50, 40, 30, 20, 10};
    struct eleve *eleve = eleve_new(1, scores, voeux);
    assert(eleve != NULL);
    assert(eleve->id == 1);
    assert(eleve->demandes == NULL); // Pas encore rempli
    assert(eleve->lmaillon[0] == NULL);
    assert(eleve->lmaillon[1] == NULL);
    assert(eleve->_raw_scores[0] == 100);
    assert(eleve->_raw_scores[1] == 90);
    assert(eleve->_raw_voeux[0] == 1);
    assert(eleve->_raw_voeux[1] == 2);
    fail_ptr = eleve_new(-1, scores, voeux);
    assert(fail_ptr == NULL);

    // Preparation : Création d'une liste de lycées
    struct lycee *lycees[NB_LYCEES];
    for (int i = 0; i < NB_LYCEES; i++)
    {
        lycees[i] = lycee_new(i, i);
        assert(lycees[i] != NULL);
    }

    // Preparation : Création d'une liste d'élèves
    struct eleve *eleves[NB_ELEVES];
    for (int i = 0; i < NB_ELEVES; i++)
    {
        eleves[i] = eleve_new(i, scores, voeux);
        assert(eleves[i] != NULL);
    }
    // Preparation : conflit entre les élèves 0 et 1 sur le lycée 0
    eleves[0]->_raw_voeux[0] = 0;
    eleves[1]->_raw_voeux[0] = 0;
    eleves[0]->_raw_scores[0] = 100;
    eleves[1]->_raw_scores[0] = 50;
    lycees[0]->capacite = 1;

    place_eleves(eleves, lycees);

    // Test 3: Placement des élèves
    assert(eleves[0]->demandes != NULL);
    assert(eleves[0]->demandes->voeu->lycee->id == 0);
    assert(eleves[0]->demandes->voeu->score == 100);
    assert(eleves[0]->demandes->suiv != NULL);
    assert(eleves[1]->demandes != NULL);
    assert(eleves[1]->demandes->voeu->lycee->id == 0);
    assert(eleves[1]->demandes->voeu->score == 50);
    assert(eleves[1]->demandes->suiv != NULL);

    // Test 4: Placement des élèves dans les lycées
    assert(lycees[0]->capacite == 1);
    assert(lycees[0]->candidats != NULL);
    assert(lycees[0]->candidats->voeu->eleve == eleves[0]);
    assert(lycees[0]->candidats->voeu->score == 100);
    assert(lycees[0]->candidats->suiv != NULL);
    assert(lycees[0]->candidats->suiv->voeu->eleve == eleves[1]);
    assert(lycees[0]->candidats->suiv->voeu->score == 50);
    assert(lycees[0]->candidats->suiv->suiv == NULL);

    // Test 5: Algorithmes de répartition
    marea_algorithm(lycees);
    assert(lycees[0]->candidats->voeu->eleve == eleves[0]);
    assert(lycees[0]->candidats->voeu->score == 100);
    assert(eleves[0]->demandes != NULL);
    assert(eleves[0]->demandes->voeu->lycee == lycees[0]);
    assert(eleves[0]->demandes->suiv == NULL); // Plus de 2e voeu : accepté dans le premier
    assert(eleves[1]->demandes != NULL);
    assert(eleves[1]->demandes->suiv != NULL); // 2e voeu existe encore

    // Nettoyage
    free_eleves(eleves, NB_ELEVES);
    free_lycees(lycees, NB_LYCEES);
    free_lycees(&lycee, 1);
    free_eleves(&eleve, 1);

    return 0;
}
