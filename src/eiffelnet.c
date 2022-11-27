#include "eiffelnet.h"


//Une seule zone
struct couple_el* oarea_algorithm(struct eleve** eleves, int nb_eleves, struct lycee** lycees, int nb_lycees) {
	qsort(eleves, nb_eleves, sizeof(struct eleve*), eleve_comparator);
	
	struct couple_el* el = malloc(sizeof(struct couple_el)*nb_eleves);
	for(int i = 0; i < nb_eleves; i++) {
		int j = 0;
		int lycee_id = eleves[i]->voeux[0];
		struct lycee* lycee = find_lycee(lycee_id, lycees, nb_lycees);
		while(lycee->effectif_actuel == lycee->effectif && j < NB_VOEUX) {
			lycee_id = eleves[i]->voeux[++j];
			lycee = find_lycee(lycee_id, lycees, nb_lycees);
		}
		if(j == NB_VOEUX) {
			lycee = NULL;
		}else{
			lycee->effectif_actuel++;
		}
		el[i].lycee = lycee;
		el[i].eleve = eleves[i];
	}
	return el;
}
