#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;

struct MST{ // arbol ya ordenado
    int pesos[27]; // los pesos de cada arista van aca
    string aristas[27]; // aristas en forma de a->b van aca
    char claves[27]; // aca van las claves
    
    void imprimirMST(int* pesos, string* aristas, int n){
        cout << "Creando MST \n";
        ofstream fp("mst.txt");
        fp << "graph G {" << endl;
        fp << "graph [rankdir=LR]" << endl;
        fp << "node [style=filled fillcolor=green];" << endl;

        for (int i = 0; i<n-1;i++){
            fp << aristas[i] << " [label=" << pesos[i] << "];" << endl;
        }

        fp << "}" << endl;
        fp.close();

    system("dot -Tpng -omst.png mst.txt");
    system("Start mst.png &"); // windows 
    }
};

// pa despues
void imprimir_grafo(int **matriz, char *vector, int n) {

    cout << "Creando grafo \n";
    ofstream fp("grafo.txt");
    fp << "graph G {" << endl;
    fp << "graph [rankdir=LR]" << endl;
    fp << "node [style=filled fillcolor=green];" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && i<j && matriz[i][j] > 0) {
                fp << vector[i] << "--" << vector[j] << " [label=" << matriz[i][j] << "];" << endl;
            } 
        }
    }

    fp << "}" << endl;
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");
    system("Start grafo.png &"); // windows 
}

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
void imprimir_matriz(int **matriz, char *vector, int n) {
    for (int i = 0; i<n; i++){
        cout << "    " << vector[i] << "   ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << vector[i];
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

    // rellenar con valores ahora
    for (int fila = 0; fila<n; fila++){
        for (int col = 0; col < n; col++){
            if (fila == col){
                matriz[fila][col]=0;
            } else if (fila < col) { // de esta forma solo se llena [0][1] y no [1][0]
                cout << "Ingrese peso de conexion entre " <<
                fila << " y " << col << ":";
                cin >> matriz[fila][col];
                matriz[col][fila] = matriz[fila][col]; // ya que no es dirigido
                if (matriz[fila][col] == 0 || matriz[fila][col] < 0){
                    // elimina la conexion para evitar errores
                    matriz[fila][col] = -1;
                }

            }
        }
        cout << endl;
    }
}

bool isIn(char carac1, char* vector2, int n){
    for (int i=0; i<n; i++){ //
            if (carac1 == vector2[i]){
                return true;

            }
    }
    return false;
};

// encuentra el arista de menor costo para ese nodo (vector fila)
int menorCosto(int vector[27], int n, int &weight){ // DRAFT
    int menorIndice=0; // el indice del menor arista
    weight = 10;
    for (int i = 0; i<n; i++){
        if (vector[i] <= weight && vector[i] > 0){
            menorIndice = i;
            weight = vector[i];
        } 
    }       
    // al terminar se ha encontrado el menor costo del vector
    //cout << menorIndice << ", PESO A RETORNO: " << vector[menorIndice] << endl;
    return menorIndice;
}

// algoritmo de prim draft
void prim(int** matriz, int n, char* vector){

    bool alcanzado[27] = {false};

    // inicializar V con vector
    int counter = 0;
    int weight = 10;
    MST mst;
    mst.claves[0] = vector[0];
    alcanzado[0] = true;
    int i = 0;

    while (counter < n){ // hago vector de la columna
        int vecQ[27];
        for (int j= 0 ; j<n; j++){
            vecQ[j] = matriz[i][j];
        }

        int indiceMenor = menorCosto(vecQ,n,weight);
    
        if (!alcanzado[indiceMenor]){
            mst.aristas[counter] = string(1,vector[i]) + "--" + string(1,vector[indiceMenor]);
            mst.claves[counter] = vector[i];
            mst.pesos[counter] = weight;
            
            alcanzado[indiceMenor] = true;
            cout << mst.claves[counter] << "--" << mst.aristas[counter] << " - " << mst.pesos[counter] << endl;
        } else {
            int internoCounter= 0;
            while (alcanzado[indiceMenor]){
                cout << "Ya existe: " << vector[indiceMenor] << endl;

                vecQ[indiceMenor] = -1;
                indiceMenor = menorCosto(vecQ,n,weight);

                cout << "Se toma " << vector[indiceMenor] << endl;
                internoCounter++;
                if (internoCounter == n || !alcanzado[indiceMenor]){
                    break;
                }
            }

            mst.aristas[counter] = string(1,vector[i]) + "--" + string(1,vector[indiceMenor]);
            mst.claves[counter] = vector[i];
            mst.pesos[counter] = weight;
            alcanzado[indiceMenor] = true;
            cout << mst.claves[counter] << " -- " << mst.aristas[counter] << " - " << mst.pesos[counter] << endl;
        }
        
        i = indiceMenor;
        counter++;

    }
    cout << "Menor camino encontrado . . . \n";

    imprimir_vector_caracter(mst.claves, n);
    mst.imprimirMST(mst.pesos, mst.aristas,n);
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

    if (atoi(argv[1]) > 27){
        /* para simplificar, el tamaño maximo que se va a poder trabajarr
        es el 27 debido a que se esta usando el alfabeto como indices.
        ademas de eso, tambien se arregla el problema de las constantes
        al momento de declarar vectores o matrices */
        cout << "El numero usado es mayor que el soportado. Asignado: 27\n";  
        n = 27;
    }else {
        // convierte string a entero mientras n sea menor que 27
        n = atoi(argv[1]);
    };

    char vector[27];
    // inicializa. largo maximo 27 por alfabeto usado
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
    imprimir_matriz(matriz, vector, n);
    imprimir_grafo(matriz,vector,n);

    prim(matriz,n,vector);
    
}