#include <stdlib.h>
#include <iostream>
using namespace std;

// imprime un vector. recibe el vector como un puntero.
void imprimir_vector_caracter(char *vector, int n) {

    cout << endl;
    char alfabeto;
    for (int i=0; i<n; i++) {
        cout << "vector[" << i << "]: " << vector[i] << " ";
    }
    cout << endl;
}

// imprime matriz.
void imprimir_matriz(int **matriz, int n) {
    for (int i = 0; i<n; i++){
        cout << "    " << i << "   ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << i;
        for (int j = 0; j < n; j++) {
            //cout << "matriz[" << i << "," << j << "]: " << matriz[i][j] << " ";
            cout << "   " << matriz[i][j] << "   ";
        }
        cout << endl;
    }
}

// inicializa matriz nxn. recibe puntero a la matriz.
void inicializar_matriz_enteros (int** matriz, int n) {
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
            matriz[fila][col] = -1 ;
        }
    }
    imprimir_matriz(matriz,n);

    // rellenar con valores ahora
    for (int fila = 0; fila<n; fila++){
        for (int col = 0; col < n; col++){
            if (fila == col){
                matriz[fila][col]=0;
            } else if (fila < col) { // de esta forma solo se llena [0][1] y no [1][0]
                cout << "Ingrese peso de conexion entre " <<
                fila << " y " << col << ":";
                cin >> matriz[fila][col];
                if (matriz[fila][col] == 0 || matriz[fila][col] < 0){
                    // elimina la conexion para evitar errores
                    matriz[fila][col] = -1;
                }

            }
        }
        cout << endl;
    }
}

void menorCosto(int** matriz, int n){
    // definir menor (indice)
    // definir menor costo
    // pasar por cada columna o fila ACLARAR
    // comparar si costo < menor costo
    // si se cumple definir menor indice
    // actualizar menor costo

    // retornar menor indice y menor costo
}

void prim(int** matriz, int n, char* vector){
    // inicializar V con vector
    // inicializar U vacio
    // inicializar L vacio
    
    for (int i = 1; i<n; i++){
        // escoger menor arista (u,v) (funcion menorCosto)

        // que v aun pertenezca a U
        // agregar (u,v) a L
        // agregar v a U
    }
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

    //inicializa un arreglo alfabetico de n elementos
    char letters[27];
    for (int i = 0; i < 27; ++i) {
        letters[i] = 'A' + i; 
    }

    // convierte string a entero.
    n = atoi(argv[1]);

    char vector[40];
    // inicializa e imprime vectores.
    int col;
    // recorre el vector.
    for (col=0; col<n; col++) {
        vector[col] = letters[col];
    }

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