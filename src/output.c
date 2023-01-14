#include "output.h"
#include "voeux.h"

void format_result(struct lycee **lycees)
{
    for (int i = 0; i < NB_LYCEES; i++)
    {
        struct lycee *lycee = lycees[i];
        printf("%d ", lycee->id);
        struct lvoeux *voeu = lycee->candidats;
        int n = 0;
        while (voeu != NULL && n < lycee->capacite)
        {
            printf("%d ", voeu->voeu->eleve->id);
            voeu = voeu->suiv;
            n++;
        }
        printf("\n");
    }
}
