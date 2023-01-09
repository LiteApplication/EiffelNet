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

struct lvoeux* create_lvoeux(struct voeu* voeu) {
	struct lvoeux* lvoeux = malloc(sizeof(struct lvoeux));
	printf("slt");
	lvoeux->voeu = voeu;
	lvoeux->prec = NULL;
	lvoeux->suiv = NULL;
	return lvoeux;
}

struct lvoeux *add_lvoeux(struct lvoeux *lv, struct voeu *voeu) {
	if(lv == NULL) {
		struct lvoeux *lvoeux = malloc(sizeof(lvoeux));
		lvoeux->suiv = NULL;
		lvoeux->prec = NULL;
		lvoeux->voeu = voeu;
	}
	struct lvoeux *ptr = lv;
	struct lvoeux *ptra = lv;
	while(ptr != NULL) {
		ptra = ptr;
		ptr = ptr->suiv;
	}
	struct lvoeux *n_lvoeux = malloc(sizeof(struct lvoeux));
	n_lvoeux->voeu = voeu;
	n_lvoeux->prec = ptra;
	ptra->suiv = n_lvoeux;
	return ptr;
}

void free_lvoeux(struct lvoeux *lv)
{
    if (lv == NULL) return;
    free_lvoeux(lv->suiv);
    free(lv);
}
