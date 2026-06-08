#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tablero.h"

int main()
{
  int n;

  printf("---- 2048 GAME ----\n");
  printf("Ingrese el tamaño del tablero : ");
  scanf("%d", &n);

  srand(time(NULL));

  Tablero *tablero = crearTablero(n);

  agregarFichaAleatoria(tablero, n);
  agregarFichaAleatoria(tablero, n);

  char opcion;
  
  printf("\nControles:\n");
  printf("  a - Mover izquierda\n");
  printf("  d - Mover derecha\n");
  printf("  w - Mover arriba\n");
  printf("  s - Mover abajo\n");
  printf("  q - Salir\n\n");

  while (1) {
    mostrarTablero(tablero);
    
    printf("Ingrese su movimiento (a/d/w/s/q): ");
    scanf(" %c", &opcion);
    
    switch (opcion) {

      case 'a':
        moverIzquierda(tablero);
        agregarFichaAleatoria(tablero, n);
        break;

      case 'd':
        moverDerecha(tablero);
        agregarFichaAleatoria(tablero, n);
        break;

      case 'w':
        moverArriba(tablero);
        agregarFichaAleatoria(tablero, n);
        break;

      case 's':
        moverAbajo(tablero);
        agregarFichaAleatoria(tablero, n);
        break;

      case 'q':
        printf("¡Gracias por jugar!\n");
        destruirTablero(tablero);
        return 0;

      default:
        printf("Opcion no valida\n");
    }
  }

  return 0;
}
