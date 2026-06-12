#ifndef PILA_H
#define PILA_H

#include "tablero.h"

typedef struct Nodo {
  Tablero estado;
  struct Nodo *sig;
} Nodo;

typedef struct {
  Nodo *tope;
} Pila;

Pila crearPila();

int pilaVacia(Pila *p);

void apilar(Pila *p, Tablero t);

Tablero desapilar(Pila *p);

int deshacerMovimiento(Pila *historial, Tablero *tablero);

#endif
