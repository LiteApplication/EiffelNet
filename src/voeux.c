#include "voeux.h"
#include <stdlib.h>

struct lvoeux* create_lvoeux(struct voeu* voeu) {
	struct lvoeux* lvoeux = malloc(sizeof(struct lvoeux));
	lvoeux->voeu = voeu;
	lvoeux->prec = NULL;
	lvoeux->suiv = NULL;
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
}

void free_lvoeux(struct lvoeux *lv)
{
    if (lv == NULL) return;
    free_lvoeux(lv->suiv);
    free(lv);
}
