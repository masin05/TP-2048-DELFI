#ifndef TABLERO_H
#define TABLERO_H

typedef struct {
    int **celdas;
    int dimension;
} Tablero;

int *crearTablero(int n);
void liberarTablero(int *tablero);

void mostrarTablero(int *tablero, int n);

void agregarFichaAleatoria(int *tablero, int n);
int contarCasillasLibres(int *tablero, int n);

void moverIzquierda(int *tablero, int n);
void moverDerecha(int *tablero, int n);
void moverArriba(int *tablero, int n);
void moverAbajo(int *tablero, int n);
