#include <stdlib.h>
#include <stdio.h>

int inferieur(const void *a, const void *b)
{
  int na = *(int *)a, nb = *(int *)b;
  return nb - na;
}

int main(void)
{
  int tab[6] = {17, 3, 5, -2, 15, 20};
  qsort(tab, 6, sizeof(int), inferieur);
  printf("nouvel ordre : ");
  for (int i = 0; i < 6; i = i + 1)
  {
    printf("%d ", tab[i]);
  }
  printf("\n");
}
