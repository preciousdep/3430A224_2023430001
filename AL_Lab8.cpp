#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

void intercambio(int* a, int* b){
    // intercambia a con b
    int t = *a;
    *a = *b;
    *b = t;
}

//---------------------------------------- quicksort 
// divide la funcion en 2 utilizando el pivote
int dividir(int arr[], int low, int high){
    // pivote es el numero en la ultima posicion del arreglo (high)
    // y low es el limite inferior
    int pivote = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++){
        if (arr[j] <= pivote){ // al ser menor o igual se hace intercambio
        // para poder separar entre los menores y mayores que el pivote
            i++;
            intercambio(&arr[i], &arr[j]);
        }
    }
    intercambio(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high){
    if (low < high){
        // primero se divide el arreglo 
        int pivote = dividir(arr, low, high);

        // se hace un sort sobre el pivote y
        // debajo del pivote
        quickSort(arr, low, pivote - 1);
        quickSort(arr, pivote + 1, high);
    }
}

// ------------------------- selection

void selectionSort(int arr[], int n) {
    int min_idx;
    //inicialmente se define al primer elemento
    // del arreglo como el menor (min_idx), el cual luego
    // sera reemplazado si se encuentra uno menor
    // mientras se itera por todo el arreglo en un
    // bucle interno y externo

    for (int i = 0; i < n-1; i++){
        min_idx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        intercambio(&arr[min_idx], &arr[i]);
    }
}

void llenarArreglo(int* arr, int size) {
    // llenar el arreglo con numeros aleatorios entre 1 y 100
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100 + 1; // genera un numero entre 1 y 100
    }
}

void mostrarArreglo(int* arr, int size) {
    // mostrar los valores del arreglo
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){
    const int SIZE_tmp = 10000 ;
    int arr[SIZE_tmp];
    int arr2[SIZE_tmp];

    int SIZE;
    cout << "Ingrese tamano de su arreglo: ";
    cin >> SIZE;
    
    // ---- para el selection sort
    cout << "Generando arreglo 1 ...\n";
    llenarArreglo(arr,SIZE);
    mostrarArreglo(arr,SIZE);

    cout << "Generando arreglo 2 ...\n";
    // ----- para el quick sort
    llenarArreglo(arr2,SIZE);
    mostrarArreglo(arr2,SIZE);
    
    // ------ arreglo 1 con selection sort
    auto start = std::chrono::high_resolution_clock::now();
    selectionSort(arr,SIZE);    
    auto end=std::chrono::high_resolution_clock::now();
    mostrarArreglo(arr,SIZE);
    std::chrono::duration<double> duration = (end - start)*1000;
    cout << " * SELECTION SORT * \n";
    cout << "Tiempo de ejecucion: " << duration.count() << " milisegundos " << endl;

    // ------------- arreglo 2 con quicksort
    // se definen otras variables de tiempo para medir ambos procesos
    // por separado
    auto start2 = std::chrono::high_resolution_clock::now();
    quickSort(arr2,0,SIZE);
    auto end2=std::chrono::high_resolution_clock::now();
    mostrarArreglo(arr2,SIZE);
    std::chrono::duration<double> duration2 = (end2 - start2)*1000;
    cout << " * QUICK SORT * \n";
    cout << "Tiempo de ejecucion: " << duration2.count() << " milisegundos " << endl;

}
