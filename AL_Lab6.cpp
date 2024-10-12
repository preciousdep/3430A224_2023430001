#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#define TRUE 0
#define FALSE 1

using namespace std;

void leer_nodos (char *vector, int n) {
    for (int i = 0; i < n; i++) {
        vector[i] = 'a' + i;
    }
}

int buscar_indice_caracter(char* V, char caracter, int n) {
    for (int i = 0; i < n; i++) {
        if (V[i] == caracter)
            return i;
    }
    return -1;
}

// imprime vector de caracteres. recibe vector y el nombre del vector
void imprimir_vector_caracter(char *vector, char g, int n) {
    cout << endl;
    for (int i=0; i<n; i++) {
        cout << "vector[" << i << "]: " << vector[i] << " ";
    }
    cout << endl;
}

// imprime vector de enteros
void imprimir_vector_entero(int *vector, int n) {
    for (int i = 0; i < n; i++) {
        cout << "D[" << i << "]: " << vector[i] << " ";
    }
    cout << endl;
}

void imprimir_matriz(int** matriz, int n) {
    cout << "   0   |   1   |   2   |   3   |   4   \n";
    for (int i = 0; i < n; i++) {
        cout << i;
        for (int j = 0; j < n; j++) {
            //cout << "matriz[" << i << "," << j << "]: " << matriz[i][j] << " ";
            cout << "   " << matriz[i][j] << "   ";
        }
        cout << endl;
    }
}

void imprimir_grafo(int **matriz, char *vector, int n) {

    cout << "Creando grafo \n";
    ofstream fp("grafo.txt");
    fp << "digraph G {" << endl;
    fp << "graph [rankdir=LR]" << endl;
    fp << "node [style=filled fillcolor=yellow];" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && matriz[i][j] > 0) {
                fp << vector[i] << "->" << vector[j] << " [label=" << matriz[i][j] << "];" << endl;
            } 
        }
    }

    fp << "}" << endl;
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");
    system("Start grafo.png &");
}

int calcular_minimo(int dw, int dv, int mvw) {
    int min = 0;
    if (dw == -1) {
        min = (dv != -1 && mvw != -1) ? dv + mvw : -1;
    } else {
        min = (dv != -1 && mvw != -1 && dw > (dv + mvw)) ? (dv + mvw) : dw;
    }
    cout << "dw: " << dw << " dv: " << dv << " mvw: " << mvw << " min: " << min << endl;
    return min;
}

void actualizar_pesos (int *D, char *VS, int **M, char *V, char v, int n) {
    cout << "\n> actualiza pesos en D[]" << endl;
    int indice_v = buscar_indice_caracter(V, v,n);
    for (int i = 0; VS[i] != ' '; i++) {
        if (VS[i] != v) {
            int indice_w = buscar_indice_caracter(V, VS[i],n);
            // para que no intente buscar minimo si hay un -1
            // ya que no existe un camino 
            if (M[indice_v][indice_w] != -1) {
            D[indice_w] = calcular_minimo(D[indice_w], D[indice_v], M[indice_v][indice_w]);
            };
        }
    }
}

void agrega_vertice_a_S(char* S, char vertice, int n) {
    for (int i = 0; i < n; i++) {
        if (S[i] == ' ') {
            S[i] = vertice;
            return;
        }
    }
}

int elegir_vertice(char* VS, int* D, char* V, int n) {
    int menor = -1, vertice = 0;
    for (int i = 0; VS[i] != ' '; i++) {
        int peso = D[buscar_indice_caracter(V, VS[i],n)];
        // modificado para que considere los pesos -1
        // que son una no conexion
        if (peso != -1 && peso != 0 && (menor == -1 || peso < menor)) {
            menor = peso;
            vertice = VS[i];
        }
    }
    cout << "\nvertice: " << vertice << endl << endl;
    return vertice;
}

int busca_caracter(char c, char* vector, int n) {
    for (int j = 0; j < n; j++) {
        if (c == vector[j]) {
            return TRUE;
        }
    }
    return FALSE;
}

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
            } else {
                cout << "Ingrese peso de conexion entre " <<
                fila << " y " << col << ":";
                cin >> matriz[fila][col];
            }
        }
        cout << endl;
    }
}

void inicializar_vector_caracter (char* vector, int n) {
    int col;
  
    // recorre el vector.
    for (col=0; col<n; col++) {
        vector[col] = ' ';
    }
}

void actualizar_VS(char* V, char* S, char* VS, int n) {
    inicializar_vector_caracter((char*)VS,n);
    for (int j = 0, k = 0; j < n; j++) {
        if (busca_caracter(V[j], (char*)S, n) != TRUE) {
            VS[k++] = V[j];
        }
    }
}

void inicializar_vector_D (int* D, int** M, int n) {
    for (int col = 0; col < n; col++) {
        D[col] = M[0][col];
    }
}


void aplicar_dijkstra (char* V, char* S, char* VS, int* D, int** M, int n) {
    inicializar_vector_D(D, M,n);

    cout << "---------Estados iniciales ---------------------------------------" << endl;
    imprimir_matriz(M,n);
    cout << endl;
    imprimir_vector_caracter(S, 'S',n);
    imprimir_vector_caracter(VS, 'V',n);
    imprimir_vector_entero(D,n);
    cout << "------------------------------------------------------------------" << endl << endl;
    
    cout << "> agrega primer valor V[0] a S[] y actualiza VS[]" << endl << endl;
    agrega_vertice_a_S(S, V[0],n);
    imprimir_vector_caracter(S, 'S',n);
    actualizar_VS(V, S, VS,n);
    imprimir_vector_caracter(VS, 'V',n);
    imprimir_vector_entero(D,n);

    for (int i = 1; i < n; i++) {
        cout << "\n> elige vertice menor en VS[] según valores en D[]" << endl;
        cout << "> lo agrega a S[] y actualiza VS[]" << endl;
        int v = elegir_vertice(VS, D, V,n);

        agrega_vertice_a_S(S, v,n);
        imprimir_vector_caracter(S, 'S',n);

        actualizar_VS(V, S, VS,n);
        imprimir_vector_caracter(VS, 'V',n);

        actualizar_pesos(D, VS, M, V, v,n);
        imprimir_vector_entero(D,n);
    }
}



int main(int argc, char **argv) {
    int const n = atoi(argv[1]);
    // pide valor constante
    char V[n], S[n], VS[n];
    int D[n];

    // valores de prueba1.
    /*int M[N][N] = {{ 0, 4, 11, -1, -1},
                   {-1, 0, -1,  6,  2},
                   {-1 ,3,  0,  6, -1},
                   {-1,-1, -1,  0, -1},
                   {-1,-1,  5,  3,  0}};*/

    // inicializa matriz de n arreglos de n tamaño
    int **M;
    M = new int*[n];
    for(int i=0; i<n; i++){
        M[i] = new int[n];
    }
    
    // inicializa matriz y la rellena
    // con los pesos 
    inicializar_matriz_enteros(M,n);

    inicializar_vector_caracter(V,n);
    inicializar_vector_caracter(S,n);
    inicializar_vector_caracter(VS,n);

    leer_nodos(V,n);
    aplicar_dijkstra(V, S, VS, D, (int**)M, n);
    imprimir_grafo((int**)M, V,n);

    return 0;
}