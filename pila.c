Pila crearPila (){
  Pila p;
  p.tope = NULL;
  return p;
}

int pilaVacia (Pila p){
  return p.tope == NULL;
}

