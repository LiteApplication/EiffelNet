/*
    Ce fichier contient les fonctions utilisées pour debugger
    Elles affichent un lycee et ses élèves ou simplement un élève
*/
#ifndef _EIFFELNET_DEBUG
#define _EIFFELNET_DEBUG
#include <stdio.h>
#include "lycee.h"
#include "eleve.h"
#ifndef NDEBUG

/** Affiche un élève
 * @param e L'élève à afficher
 */
void print_eleve(struct eleve *e)
{
    printf("\t\tEleve %d:\tScore: %d\tVoeux: ", e->id, e->score);
    for (int i = 0; i < NB_VOEUX; i++)
    {
        printf("%d ", e->voeux[i]);
    }
    printf("\n");
}

void print_lycee(struct lycee *l)
{
    printf("Lycée %d\n\tEffectif actuel:\t%d / %d\n", l->id, l->effectif_actuel, l->effectif);
    printf("\tÉlèves:\n");
    for (int i = 0; i < l->effectif_actuel; i++)
    {
        print_eleve(l->eleves[i]);
    }
}

#else

void print_lycee(struct lycee *l) { (void)l; }
void print_eleve(struct eleve *e) { (void)e; }

#endif // NDEBUG
#endif // _EIFFELNET_DEBUG