#include "lycee.h"
#include "lecture.h"
#include "voeux.h"
#include <stdlib.h>

struct lycee *lycee_new(int id, int capacite)
{
    if (capacite < 0 || id < 0)
    {
        return NULL;
    }
    struct lycee *lycee = (struct lycee *)malloc(sizeof(struct lycee));
    if (lycee == NULL)
        return NULL;

    lycee->id = id;
    lycee->capacite = capacite;
    lycee->candidats = NULL;
    lycee->candidats_top = NULL;
    return lycee;
}

struct lycee **lecture_lycees(char *filename)
{
    int id, effectif;
    struct lycee **lycees;

    FILE *f = debut_lecture(filename);
    if (f == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", filename);
        return NULL;
    }

    lycees = (struct lycee **)malloc(NB_LYCEES * sizeof(struct lycee *));
    if (lycees == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire pour les lycées\n");
        return NULL;
    }
    int i = 0;
    while (lecture_lycee_suivant(f, &id, &effectif) != EOF && i < NB_LYCEES)
    {
        lycees[i] = lycee_new(id, effectif);
        if (lycees[i] == NULL)
        {
            fprintf(stderr, "Erreur lors de l'initialisation du lycee %d.", id);
            free_lycees(lycees, i);
            fin_lecture(f);
            return NULL;
        }
        i++;
    }
    fin_lecture(f);
    return lycees;
}

void free_lycees(struct lycee **lycee, int nb_lycees)
{
    for (int i = 0; i < nb_lycees; i++)
    {
        free_lvoeux(lycee[i]->candidats);
        free(lycee[i]);
    }
    free(lycee);
}

struct lycee *find_lycee(int id, struct lycee **lycees)
{

    struct lycee *lycee = NULL;
    // Il est probable que la liste des lycees soit triée par id
    if (id < NB_LYCEES && lycees[id]->id == id)
        lycee = lycees[id];
    else
    { // On prévoit quand même le cas ou elle ne l'est pas
        for (int j = 0; j < NB_LYCEES; j++)
        {
            if (lycees[j]->id == id)
            {
                lycee = lycees[j];
                break;
            }
        }
    }
    if (lycee == NULL)
    {
        fprintf(stderr, "Erreur lors de la recherche du lycée %d\n", id);
        return NULL;
    }
    return lycee;
}

void inverse_candidats(struct eleve **eleves) {
	for(int i = 0; i < NB_ELEVES; i++) {
		for(int j = 0; j < NB_VOEUX; j++) {
			struct voeu *voeu = eleves[i]->voeux[j];
			struct lycee *lycee = voeu->lycee;
			if(lycee->candidats == NULL) {
				lycee->candidats = create_lvoeux(voeu);
				lycee->candidats_top = lycee->candidats;
				continue;
			}
			struct lvoeux *top = lycee->candidats_top;
			struct lvoeux *top_alt = top;
			while(top != NULL && voeu->score > top->voeu->score) {
				top_alt = top;
				top = top->prec;
			}
			struct lvoeux *n_lvoeux = malloc(sizeof(struct lvoeux));
			n_lvoeux->voeu = voeu;
			if(top == NULL) {
				top_alt->prec = n_lvoeux;
				n_lvoeux->suiv = top_alt;
				lycee->candidats = n_lvoeux;
			} else {
				top->suiv = n_lvoeux;
				n_lvoeux->prec = top;
				n_lvoeux->suiv = top_alt;
				top_alt->prec = n_lvoeux;
			}
			if(top != lycee->candidats_top) {
				lycee->candidats_top = n_lvoeux;
			}
		}
	}
}
