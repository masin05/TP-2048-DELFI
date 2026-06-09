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

// Destruir el tablero y liberar espacio en memoria
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

// Función auxiliar para comprimir una fila (eliminar ceros)
void comprimirFila(int *fila, int n) {
    int temp[n];
    int indice = 0;
    

    for (int i = 0; i < n; i++) {
        if (fila[i] != 0) {
            temp[indice++] = fila[i];
        }
    }
    

    while (indice < n) {
        temp[indice++] = 0;
    }
    

    for (int i = 0; i < n; i++) {
        fila[i] = temp[i];
    }
}

// Función auxiliar para fusionar valores iguales en una fila
void fusionarFila(int *fila, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (fila[i] != 0 && fila[i] == fila[i + 1]) {
            fila[i] *= 2;
            fila[i + 1] = 0;
        }
    }
}

// MOVER A LA IZQUIERDA
void moverIzquierda(Tablero t) {
    for (int i = 0; i < t.dimension; i++) {
        // Comprimir la fila (eliminar ceros)
        comprimirFila(t.celdas[i], t.dimension);
        // Fusionar valores iguales
        fusionarFila(t.celdas[i], t.dimension);
        // Comprimir nuevamente después de fusionar
        comprimirFila(t.celdas[i], t.dimension);
    }
}

// MOVER A LA DERECHA
void moverDerecha(Tablero t) {
    for (int i = 0; i < t.dimension; i++) {
        // Invertir la fila
        for (int j = 0; j < t.dimension / 2; j++) {
            int temp = t.celdas[i][j];
            t.celdas[i][j] = t.celdas[i][t.dimension - 1 - j];
            t.celdas[i][t.dimension - 1 - j] = temp;
        }
        // Comprimir
        comprimirFila(t.celdas[i], t.dimension);
        // Fusionar
        fusionarFila(t.celdas[i], t.dimension);
        // Comprimir 
        comprimirFila(t.celdas[i], t.dimension);
        // Invertir 
        for (int j = 0; j < t.dimension / 2; j++) {
            int temp = t.celdas[i][j];
            t.celdas[i][j] = t.celdas[i][t.dimension - 1 - j];
            t.celdas[i][t.dimension - 1 - j] = temp;
        }
    }
}

// MOVER ARRIBA
void moverArriba(Tablero t) {
    // Trabajar por columnas
    for (int j = 0; j < t.dimension; j++) {
        int columna[t.dimension];
        
        // Extraer columna
        for (int i = 0; i < t.dimension; i++) {
            columna[i] = t.celdas[i][j];
        }
        
        // Comprimir
        comprimirFila(columna, t.dimension);
        // Fusionar
        fusionarFila(columna, t.dimension);
        // Comprimir nuevamente
        comprimirFila(columna, t.dimension);
        
        // Poner columna de vuelta
        for (int i = 0; i < t.dimension; i++) {
            t.celdas[i][j] = columna[i];
        }
    }
}

// MOVER ABAJO
void moverAbajo(Tablero t) {
    // Trabajar por columnas
    for (int j = 0; j < t.dimension; j++) {
        int columna[t.dimension];
        
        // Extraer columna
        for (int i = 0; i < t.dimension; i++) {
            columna[i] = t.celdas[i][j];
        }
        
        // Invertir columna
        for (int i = 0; i < t.dimension / 2; i++) {
            int temp = columna[i];
            columna[i] = columna[t.dimension - 1 - i];
            columna[t.dimension - 1 - i] = temp;
        }
        
        // Comprimir
        comprimirFila(columna, t.dimension);
        // Fusionar
        fusionarFila(columna, t.dimension);
        // Comprimir denuevo
        comprimirFila(columna, t.dimension);
        
        // Invertir columna 
        for (int i = 0; i < t.dimension / 2; i++) {
            int temp = columna[i];
            columna[i] = columna[t.dimension - 1 - i];
            columna[t.dimension - 1 - i] = temp;
        }
        
        // Poner columna 
        for (int i = 0; i < t.dimension; i++) {
            t.celdas[i][j] = columna[i];
        }
    }
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
