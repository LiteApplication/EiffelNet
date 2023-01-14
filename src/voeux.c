#include "voeux.h"
#include <stdlib.h>

struct voeu *voeu_new(int score, struct eleve *eleve, struct lycee *lycee)
{
    if (score < 0 || eleve == NULL || lycee == NULL)
        return NULL;

    struct voeu *v = (struct voeu *)malloc(sizeof(struct voeu));
    if (v == NULL)
        return NULL;

    v->score = score;
    v->eleve = eleve;
    v->lycee = lycee;
    return v;
}

struct lvoeux *lvoeux_new(struct voeu *voeu)
{
    struct lvoeux *lvoeux = malloc(sizeof(struct lvoeux));
    lvoeux->voeu = voeu;
    lvoeux->prec = NULL;
    lvoeux->suiv = NULL;
    return lvoeux;
}

void free_lvoeux(struct lvoeux *lv)
{
    if (lv == NULL)
        return;
    free_lvoeux(lv->suiv);
    free(lv);
}
