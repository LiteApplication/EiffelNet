#include "eleve.h"
#include "voeux.h"
#include <stdlib.h>
#include <stdio.h>

struct eleve *eleve_new(int id, int scores[NB_VOEUX], int voeux[NB_VOEUX], struct lycee **lycees)
{
    if (id < 0)
    {
        return NULL;
    }
    struct eleve *eleve = (struct eleve *)malloc(sizeof(struct eleve));
    if (eleve == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }
    eleve->id = id;
    eleve->voeux = malloc(sizeof(struct voeu)*NB_VOEUX);
    for(int i = 0; i < NB_VOEUX; i++) {
	    struct lycee* lycee = find_lycee(voeux[i], lycees);
	    struct voeu* voeu = create_voeu(scores[i], eleve, lycee);
	    eleve->voeux[i] = voeu;
    }
    return eleve;	
}

struct eleve **lecture_eleves(char *filename, struct lycee **lycees)
{
    int eleve;
    int scores[NB_VOEUX];
    int voeux[NB_VOEUX];

    FILE *f = debut_lecture(filename);
    if (f == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    struct eleve **eleves = (struct eleve **)malloc(NB_ELEVES * sizeof(struct eleve *));
    if (eleves == NULL)
    {
        fprintf(stderr, "Impossible d'allouer la mémoire pour les élèves\n");
        return NULL;
    }

    int i = 0;
    while (lecture_eleve_suivant_zones(f, &eleve, scores, voeux) != EOF && i < NB_ELEVES)
    {
        eleves[i] = eleve_new(eleve, scores, voeux, lycees);
        if (eleves[i] == NULL)
        {
            free_eleves(eleves, i);
            fin_lecture(f);
            return NULL;
        }
        i++;
    }
    fin_lecture(f);
    return eleves;
}

void free_eleves(struct eleve **eleves, int nb_eleves)
{
    for (int i = 0; i < nb_eleves; i++)
    {	
	struct eleve* eleve = eleves[i];
	for(int j = 0; j < NB_VOEUX; j++) {
		free(eleve->voeux[j]);
	}
	free(eleve->voeux);
        free(eleve);
    }
    free(eleves);
}

void inverse_voeux(struct eleve **eleves)
{
	for(int j = 0; j < NB_ELEVES; j++) {
		struct voeu** voeux = eleves[j]->voeux;
		for(int i = 0; i < NB_VOEUX/2; i++) {
			struct voeu* voeu = voeux[NB_VOEUX-i-1];
			voeux[NB_VOEUX-i-1] = voeux[i];
			voeux[i] = voeu;
		}
	}
	
}
