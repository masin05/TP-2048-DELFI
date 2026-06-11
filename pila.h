typedef struct Nodo {
  Tablero estado;
  struct Nodo *sig;
} Nodo;

Typedef struct {
  Nodo *tope;
} Pila

Pila crearPila();

int pilaVacia(Pila p);

void apilar(Pila *p, Tablero t);

Tablero desapilar(Pila *p);
