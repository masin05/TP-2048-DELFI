#ifndef TABLERO_H
#define TABLERO_H

typedef struct {
    int **celdas;
    int dimension;
} Tablero;

Tablero crearTablero(int n);
void destruirTablero(Tablero t);
void mostrarTablero(Tablero t);

void agregarCasillaAleatoria(Tablero t, int n);

void moverIzquierda(Tablero t);
void moverDerecha(Tablero t);
void moverArriba(Tablero t);
void moverAbajo(Tablero t);
Tablero deshacerMovimiento(Tablero t);

// Funciones de control de juego
int verificarVictoria(Tablero t);  // Retorna 1 si hay un 2048, 0 si no
int verificarDerrota(Tablero t);   // Retorna 1 si no hay movimientos posibles, 0 si hay
int tableroLleno(Tablero t);       // Retorna 1 si todas las celdas están ocupadas, 0 si hay celdas vacías

#endif
