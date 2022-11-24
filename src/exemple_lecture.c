#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lecture.h"

// exemple d'utilisation des fonctions de lecture.c
// gcc -g -Wall -Wno-unused -pedantic -Wextra -std=c11 -Wreturn-type lecture.c exemple_lecture.c -o exemple_lecture
//#lecture.c
//#libs: -I../includes
void exemple_lecture_voeux()
{
  FILE *f = debut_lecture("../data/voeux.csv");

  if (f == NULL)
  {
    fprintf(stderr, "fichier inexistant dans exemple_lecture_voeux\n");
    return;
  }

  while (true)
  {
    int eleve, score;
    int lycees[NB_VOEUX];
    int fin = lecture_eleve_suivant(f, &eleve, &score, lycees);
    if (fin == EOF)
    {
      break;
    }
    printf("L'eleve %d obtient le score %d, les lycees demandes dans l'ordre de preference: ", eleve, score);
    for (int i = 0; i < NB_VOEUX; i = i + 1)
    {
      printf("%d ", lycees[i]);
    }
    printf("\n");
  }

  fin_lecture(f);
}

void exemple_lecture_lycees()
{
  FILE *f = debut_lecture("../data/lycees.csv");

  if (f == NULL)
  {
    fprintf(stderr, "fichier inexistant dans exemple_lecture_lycees\n");
    return;
  }

  while (true)
  {
    int lycee, effectif;
    int fin = lecture_lycee_suivant(f, &lycee, &effectif);
    if (fin == EOF)
    {
      break;
    }
    printf("effectif du lycee %d : %d\n", lycee, effectif);
  }
  fin_lecture(f);
}

int main(void)
{
  exemple_lecture_voeux();
  printf("------------------\n");
  exemple_lecture_lycees();
  return 0;
}
