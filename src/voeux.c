#include "voeux.h"

void free_lvoeux(struct lvoeux *lv)
{
    if (lv == NULL)
        return;

    free_lvoeux(lv->suiv);
    free(lv);
}