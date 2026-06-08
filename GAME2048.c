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

  Tablero tablero = crearTablero(n);

  agregarCasillaAleatoria(tablero, n);
  agregarCasillaAleatoria(tablero, n);

  char opcion;
  
  printf("\nControles:\n");
  printf("  a - Mover izquierda\n");
  printf("  d - Mover derecha\n");
  printf("  w - Mover arriba\n");
  printf("  s - Mover abajo\n");
  printf("  q - Salir\n\n");

  while (1) {
    mostrarTablero(tablero);
    
    // Verificar victoria
    if (verificarVictoria(tablero)) {
      printf("\n¡¡¡ GANASTE :) !!!\n");
      destruirTablero(tablero);
      return 0;
    }
    
    // Verificar derrota
    if (verificarDerrota(tablero)) {
      printf("\n¡¡¡ PERDISTE :( !!! \n");
      destruirTablero(tablero);
      return 0;
    }
    
    printf("Ingrese su movimiento (a/d/w/s/q): ");
    scanf(" %c", &opcion);
    
    switch (opcion) {

      case 'a':
        moverIzquierda(tablero);
        agregarCasillaAleatoria(tablero, n);
        agregarCasillaAleatoria(tablero, n);
        break;

      case 'd':
        moverDerecha(tablero);
        agregarCasillaAleatoria(tablero, n);
        agregarCasillaAleatoria(tablero, n);
        break;

      case 'w':
        moverArriba(tablero);
        agregarCasillaAleatoria(tablero, n);
        agregarCasillaAleatoria(tablero, n);
        break;

      case 's':
        moverAbajo(tablero);
        agregarCasillaAleatoria(tablero, n);
        agregarCasillaAleatoria(tablero, n);
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
