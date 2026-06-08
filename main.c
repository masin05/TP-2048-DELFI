#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tablero.h"
int main()
{
  int n;

  printf("Ingrese el tamaño del tablero: ");
  scanf("%d", &n);

  srand(time(NULL));

  int *tablero;
  //tablero = malloc(n * n * sizeof(int));
  //tablero[i * n + j]; para entrar a las posiciones
  tablero = crearTablero(n);

  agregarFichaAleatoria(tablero, n);
  agregarFichaAleatoria(tablero, n);

  char opcion;
}
