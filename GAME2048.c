#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tablero.h"
#include "pila.h"
#include "FuncionesTablero2048.c"

int main(){
  int n;

  printf("---- 2048 GAME ----\n");
  printf("Ingrese el tamaño del tablero : ");
  scanf("%d", &n);

  srand(time(NULL));

  Tablero tablero = crearTablero(n);
  Pila historial = crearPila();

  agregarCasillaAleatoria(tablero, n);
  agregarCasillaAleatoria(tablero, n);

  char opcion;
  
  printf("\nControles:\n");
  printf("  a - Mover izquierda\n");
  printf("  d - Mover derecha\n");
  printf("  w - Mover arriba\n");
  printf("  s - Mover abajo\n");
  printf("  u - Retrocedes\n\n");

  while (1) {
    mostrarTablero(tablero);
    printf("Ingrese su movimiento (a/d/w/s/q): ");
    scanf(" %c", &opcion);

    if (opcion == 'a' || opcion == 'd' || opcion == 'w' || opcion == 's') {
        apilar(&historial, tablero);
    }
    
    switch (opcion) {

      case 'a':
        moverHorizontal(tablero, -1);
        agregarCasillaAleatoria(tablero, n);
        break;

      case 'd':
        moverHorizontal(tablero, 1);
        agregarCasillaAleatoria(tablero, n);
        break;

      case 'w':
        moverVertical(tablero, -1);
        agregarCasillaAleatoria(tablero, n);
        break;

      case 's':
        moverVertical(tablero, 1);
        agregarCasillaAleatoria(tablero, n);
        break;
      
      case 'u':
        deshacerMovimiento(&historial,&tablero);
        break;

      default:
        printf("Opcion no valida\n");
    }
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
  }
  return 0;
}
