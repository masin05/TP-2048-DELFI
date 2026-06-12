#include <stdio.h>
#include <stdlib.h>

#include "pila.h"

Pila crearPila (){
  Pila p;
  p.tope = NULL;
  return p;
}

int pilaVacia(Pila *p){
  return p->tope == NULL;
}

void apilar(Pila *p, Tablero t){
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo == NULL){
        printf("Error al reservar memoria\n");
        exit(1);
    }
    nuevo->estado = copiarTablero(t);
    nuevo->sig = p->tope;
    p->tope = nuevo;
}

Tablero desapilar(Pila *p){
    if (pilaVacia(p)){
        printf("La pila esta vacia\n");
        exit(1);
    }
    Nodo *aux = p->tope;
    Tablero t = aux->estado;
    p->tope = aux->sig;
    free(aux);
    return t;
}
