#include <stdlib.h>
#include <stdio.h>

int inferieur(const void *a, const void *b)
{
  int na = *(int *)a, nb = *(int *)b;
  return nb - na;
}
