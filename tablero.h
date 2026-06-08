#ifndef TABLERO_H
#define TABLERO_H

typedef struct {
    int **celdas;
    int dimension;
} Tablero;

Tablero *crearTablero(int n);
void destruirTablero(Tablero *t);

void mostrarTablero(Tablero *t);

void moverIzquierda(Tablero *t);
void moverDerecha(Tablero *t);
void moverArriba(Tablero *t);
void moverAbajo(Tablero *t);
