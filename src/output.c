#include "output.h"
#include "voeux.h"
#include "eiffelnet.h" // PRETTY_PRINT

void format_result(struct lycee **lycees)
{
#ifndef PRETTY_PRINT
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
#else
    /*
    Lycée <id>
        Effectif actuel:    <effectif actuel> / <effectif max>
        Élèves:
            Eleve <id>:    Score: <score>   Voeux: <liste des voeux>
            Eleve <id>:    Score: <score>   Voeux: <liste des voeux>
            */
    for (int i = 0; i < NB_LYCEES; i++)
    {
        int effectif = 0;
        struct lvoeux *voeu = lycees[i]->candidats;
        while (voeu != NULL && effectif < lycees[i]->capacite)
        {
            effectif++;
            voeu = voeu->suiv;
        }
        struct lycee *lycee = lycees[i];
        printf("Lycée %d\n", lycee->id);

        printf("\tEffectif actuel:\t%d / %d\n", effectif, lycee->capacite);
        printf("\tÉlèves:\n");
        voeu = lycee->candidats;
        effectif = 0;
        while (voeu != NULL && effectif < lycee->capacite)
        {
            printf("\t\tEleve %d:\tScore: %d\tVoeux: ", voeu->voeu->eleve->id, voeu->voeu->score);
            for (int j = 0; j < NB_VOEUX; j++)
            {
                printf("%d ", voeu->voeu->eleve->_raw_voeux[j]);
            }
            printf("\n");
            voeu = voeu->suiv;
            effectif++;
        }
    }
#endif
}
