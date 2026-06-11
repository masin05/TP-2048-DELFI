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

// Funciones de control de juego
int verificarVictoria(Tablero t); 
int verificarDerrota(Tablero t);  
int tableroLleno(Tablero t);     

Tablero copiarTablero(Tablero original);
#endif
