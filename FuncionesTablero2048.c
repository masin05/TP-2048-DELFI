#include "tablero.h"
#include <stdio.h>
#include <stdlib.h>

// Creo un tablero de n x n
Tablero crearTablero(int n) {
    Tablero t;
    t.dimension = n;
    t.celdas = (int **)malloc(n * sizeof(int *));
    
    for (int i = 0; i < n; i++) {
        t.celdas[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            t.celdas[i][j] = 0;
        }
    }
    return t;
}

// Destruir el tablero y libera espacio en memoria
void destruirTablero(Tablero t) {
    for (int i = 0; i < t.dimension; i++) {
        free(t.celdas[i]);
    }
    free(t.celdas);
}

// Mostrar el tablero en pantalla
void mostrarTablero(Tablero t) {
    printf("\n");
    for (int i = 0; i < t.dimension; i++) {
        for (int j = 0; j < t.dimension; j++) {
            printf("%5d", t.celdas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Agregar una casilla (2 o 4) aleatoria en una posicion aleatoria
void agregarCasillaAleatoria(Tablero t, int n) {
    int fila, columna;
    int encontrado = 0;
    
    // Buscar una celda vacía
    while (!encontrado) {
        fila = rand() % n;
        columna = rand() % n;
        if (t.celdas[fila][columna] == 0) {
            encontrado = 1;
        }
    }
    
    // Agregar 2 o 4 (75% de probabilidad 2, 25% de probabilidad 4)
    int valor = (rand() % 4 == 0) ? 4 : 2;
    t.celdas[fila][columna] = valor;
}

// elimina los 0 de la fila 

void invertirLinea(int *linea, int n) {
    for (int i = 0; i < n / 2; i++) {
        int temp = linea[i];
        linea[i] = linea[n - 1 - i];
        linea[n - 1 - i] = temp;
    }
}

void comprimirLinea(int *linea, int n) {
    int indice = 0;
    for (int i = 0; i < n; i++) {
        if (linea[i] != 0) {
            linea[indice] = linea[i];
            indice++;
        }
    }
    while (indice < n) {
        linea[indice] = 0;
        indice++;
    }
}

void fusionarLinea(int *linea, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (linea[i] != 0 && linea[i] == linea[i + 1]) {
            linea[i] *= 2;
            linea[i + 1] = 0;
        }
    }
}

//MOVER HORIZONTAL: dir = Izquierda -1, derecha 1

void moverHorizontal(Tablero t, int direccion) {
    for (int i = 0; i < t.dimension; i++) {
        int *fila = t.celdas[i];
        
        // Si vamos a la derecha, invertimos para tratarlo como si fuera izquierda
        if (direccion == 1) invertirLinea(fila, t.dimension);
        
        // La secuencia magica de 2048
        comprimirLinea(fila, t.dimension);
        fusionarLinea(fila, t.dimension);
        comprimirLinea(fila, t.dimension); // Comprimir de nuevo por si la fusion dejo huecos
        
        // Devolvemos la fila a su orientacion original si fuimos a la derecha
        if (direccion == 1) invertirLinea(fila, t.dimension);
    }
}
//MOVER VERTICAL: dir = abajo 1, arriba -1

void moverVertical(Tablero t, int direccion) {
    int *columna = (int *)malloc(t.dimension * sizeof(int));
    
    for (int j = 0; j < t.dimension; j++) {
        // Extraer la columna
        for (int i = 0; i < t.dimension; i++) {
            columna[i] = t.celdas[i][j];
        }
        if (direccion == 1) invertirLinea(columna, t.dimension);
        
        comprimirLinea(columna, t.dimension);
        fusionarLinea(columna, t.dimension);
        comprimirLinea(columna, t.dimension);
        
        if (direccion == 1) invertirLinea(columna, t.dimension);
        // Volver a guardar la columna en el tablero
        for (int i = 0; i < t.dimension; i++) {
            t.celdas[i][j] = columna[i];
        }
    }
    free(columna);
}

// VERIFICAR VICTORIA, Busca si existe un 2048 en el tablero

int verificarVictoria(Tablero t) {
    for (int i = 0; i < t.dimension; i++) {
        for (int j = 0; j < t.dimension; j++) {
            if (t.celdas[i][j] == 2048) {
                return 1; 
            }
        }
    }
    return 0;  
}

// VERIFICAR TABLERO LLENO 
int tableroLleno(Tablero t) {
    for (int i = 0; i < t.dimension; i++) {
        for (int j = 0; j < t.dimension; j++) {
            if (t.celdas[i][j] == 0) {
                return 0;  
            }
        }
    }
    return 1; 
}

// VERIFICAR DERROTA 
int verificarDerrota(Tablero t)
{
    if (!tableroLleno(t))
    {
        return 0;
    }
    for (int i = 0; i < t.dimension; i++){
        for (int j = 0; j < t.dimension; j++){
            if (j < t.dimension - 1 &&
                t.celdas[i][j] == t.celdas[i][j + 1])
            {
                return 0;
            }
            if (i < t.dimension - 1 &&
                t.celdas[i][j] == t.celdas[i + 1][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

Tablero copiarTablero(Tablero original){
    Tablero copia;
    copia.dimension = original.dimension;
    copia.celdas = malloc(original.dimension * sizeof(int*));
    for (int i = 0; i < copia.dimension; i++){
        copia.celdas[i] = malloc(original.dimension * sizeof(int));
        for(int j = 0; j < copia.dimension; j++){
            copia.celdas[i][j] = original.celdas [i][j];
        }
    }
    return copia;
}

int deshacerMovimiento(Pila *historial, Tablero *tablero){
    if(pilaVacia(historial))
    {
        printf("No hay movimientos para deshacer\n");
        return 0;
    }
    destruirTablero(*tablero);
    *tablero = desapilar(historial);
    return 1;
}
