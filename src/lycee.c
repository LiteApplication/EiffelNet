#include "lycee.h"
#include "lecture.h"
#include <stdlib.h>

struct lycee *lycee_new(int id, int effectif)
{
    struct lycee *lycee = malloc(sizeof(struct lycee));
    if (lycee == NULL)
        return NULL;

    lycee->id = id;
    lycee->effectif = effectif;
    lycee->effectif_actuel = 0;
    lycee->eleves = (struct eleve **)malloc(effectif * sizeof(struct eleve *));
    if (lycee->eleves == NULL)
    {
        free(lycee);
        return NULL;
    }
    return lycee;
}

struct lycee **lecture_lycees(char *filename, int *nb_lycees)
{
    int id, effectif;
    struct lycee **lycees;

    *nb_lycees = 0;
    FILE *f = debut_lecture(filename);
    if (f == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", filename);
        return NULL;
    }

    *nb_lycees = compte_lignes(f);

    lycees = (struct lycee **)malloc(*nb_lycees * sizeof(struct lycee *));
    if (lycees == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire pour les lycées\n");
        return NULL;
    }

    int i = 0;
    while (lecture_lycee_suivant(f, &id, &effectif) != EOF && i < *nb_lycees)
    {
        lycees[i] = lycee_new(id, effectif);
        if (lycees[i] == NULL)
        {
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
        free(lycee[i]->eleves);
        free(lycee[i]);
    }
    free(lycee);
}

struct lycee *find_lycee(int id, struct lycee **lycees, int nb_lycees)
{

    struct lycee *lycee = NULL;
    // Il est probable que la liste des lycees soit triee par id
    if (id < nb_lycees && lycee[id].id == id)
        lycee = lycees[id];
    else
    {
        for (int j = 0; j < nb_lycees; j++)
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