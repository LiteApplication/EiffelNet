#include <stdio.h>
#include "lecture.h"

FILE *debut_lecture(const char *fic)
{
  return fopen(fic, "r");
}

void fin_lecture(FILE *f)
{
  fclose(f);
}

int lecture_eleve_suivant(FILE *f, int *eleve, int *score, int *lycees)
{
  int n;
  int lyc = 0;

  n = fscanf(f, "%d,%d,", eleve, score);
  if (n == EOF)
  {
    return EOF;
  }
  for (int v = 0; v < NB_VOEUX; v = v + 1)
  {
    fscanf(f, "%d,", &lycees[lyc]);
    lyc = lyc + 1;
  }

  return 0;
}

int lecture_eleve_suivant_zones(FILE *f, int *eleve, int *scores, int *lycees)
{
  int n;
  int lyc = 0;

  n = fscanf(f, "%d,", eleve);
  if (n == EOF)
  {
    return EOF;
  }
  for (int v = 0; v < NB_VOEUX; v = v + 1)
  {
    fscanf(f, "%d,%d,", &lycees[lyc], &scores[lyc]);
    lyc = lyc + 1;
  }

  return 0;
}

int lecture_lycee_suivant(FILE *f, int *lycee, int *capacite)
{
  return fscanf(f, "%d,%d", lycee, capacite);
}

int compte_lignes(FILE *f)
{
  int c;
  int nb_lignes = 0;

  while ((c = fgetc(f)) != EOF)
  {
    if (c == '\n')
    {
      nb_lignes = nb_lignes + 1;
    }
  }
  rewind(f);
  return nb_lignes + 1; // +1 car on compte la dernière ligne
}
