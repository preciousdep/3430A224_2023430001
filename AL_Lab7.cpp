#include <stdlib.h>
#include <iostream>
using namespace std;

/* inicializa un vector. recibe el vector como un puntero.
void inicializar_vector_caracter (char *vector, int n) {
    int col;
    // recorre el vector.
    for (col=0; col<n; col++) {
        vector[col] = '';
    }
}*/

// imprime un vector. recibe el vector como un puntero.
void imprimir_vector_caracter(char *vector, int n) {
    cout << endl;
    for (int i=0; i<n; i++) {
        cout << "vector[" << i << "]: " << vector[i] << " ";
    }
    cout << endl;
}

// imprime matriz.
void imprimir_matriz(int **matriz, int n) {
    cout << endl;
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
            cout << matriz[fila][col] << " ";
        }
        cout << endl;
    }
}

// inicializa matriz nxn. recibe puntero a la matriz.
void inicializar_matriz_enteros (int** matriz, int n) {
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
            matriz[fila][col] = 0 ;
        }
    }
    imprimir_matriz(matriz,n);

    // rellenar con valores ahora
    for (int fila = 0; fila<n; fila++){
        for (int col = 0; col < n; col++){
            if (fila == col){
                matriz[fila][col]=0;
            } else {
                cout << "Ingrese peso de conexion entre " <<
                fila << " y " << col << ":";
                cin >> matriz[fila][col];
                if (matriz[fila][col] == 0 || matriz[fila][col] < 0){
                    // elimina la conexion para evitar errores
                    matriz[fila][col] = -1;
                }
                // no se tngo que pensar mejor la logica
                matriz[col][fila] = matriz[fila][col];

            }
        }
        cout << endl;
    }
}

void prim(int** matriz, int n, char* vector){

}

//
int main(int argc, char **argv) {
    // número de elementos.
    int n;

    // valida cantidad de parámetros mínimos.
    if (argc<2) {
        cout << "Uso: \n./matriz n" << endl;
        return -1;
    }

    // convierte string a entero.
    n = atoi(argv[1]);

    char vector[40];

    // inicializa e imprime vectores.
        int col;
    // recorre el vector.
    for (col=0; col<n; col++) {
        vector[col] = ' ';
    }
    cout << "CONTROL";
    imprimir_vector_caracter(vector, n);

    // crea matriz nxn de enteros.
    int **matriz;
    matriz = new int*[n];
    for(int i=0; i<n; i++) {
        matriz[i] = new int[n];
    };
    
    inicializar_matriz_enteros(matriz, n);
    imprimir_matriz(matriz, n);
}