#include "output.h"

void format_result(struct lycee **lycee)
{
    for (int l = 0; l < NB_LYCEES; l++)
    {
        printf("%d", lycee[l]->id);
        for (int e = 0; e < lycee[l]->effectif_actuel; e++)
        {
            printf(" %d", lycee[l]->eleves[e]->id);
        }
        printf("\n");
    }
}

void print_lycee(struct lycee *lycee)
{
    printf("Lycée %d\n\tEffectif actuel:\t%d / %d\n", lycee->id, lycee->effectif_actuel, lycee->effectif);
    printf("\tÉlèves:\n");
    for (int i = 0; i < lycee->effectif_actuel; i++)
    {
        print_eleve(lycee->eleves[i]);
    }
}

void print_eleve(struct eleve *eleve)
{
    printf("\t\tEleve %d:\tScore: %d\tVoeux: ", eleve->id, eleve->score);
    for (int i = 0; i < NB_VOEUX; i++)
    {
        printf("%d ", eleve->voeux[i]);
    }
    printf("\n");
}