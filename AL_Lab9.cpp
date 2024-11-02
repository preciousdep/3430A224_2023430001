#include <iostream>
#include <cstdlib>
using namespace std;

// buscar implementando el hash

// colision lineal, recorre el arreglo de forma circular hasta que
// encuentra un sitio adecuado
void colisionLineal(int* keyarr, int valor, int key, int size){
    int i = key + 1;
    while (keyarr[i] != -5 && keyarr[i] != valor && i!=key){
        if (i == size || i == size+1){
            i = 0;
        } else {
            i ++;
        }
    }
    keyarr[i] = valor;
}

// aqui se evalua si el sitio keyarr[key] esta vacio (=-5) o
// ya contiene algo. desde ahi se agrega o se trata la colision
bool colision(int* keyarr, int valor, int key, int size){
    if (keyarr[key] == -5){
        keyarr[key] = valor;
    } else { // colision
        cout << "Se ha encontrado una colision \n";
        colisionLineal(keyarr,valor,key,size);
    }
}

//funcion hash
int hashKey(int valor, int size){
    // hash por modulo
    int key;
    key = (valor % size);
    return key;
}

int validarIn(){
    int a;
    while(1){
        cin>>a;
        if(cin.fail()){
            cin.clear();
            cout<<"Valor no valido"<<endl;
            cin.ignore();
        } else if(!cin.fail()){
            break;
            }
    }
    return a;
}

void llenarArreglo(int* arr, int size) {
    // llenar el arreglo con numeros aleatorios entre 1 y 100
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100 + 1; // genera un numero entre 1 y 100
    }
}

void arregloNULL(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = -5;
    }
}

void mostrarArreglo(int* arr, int size) {
    // mostrar los valores del arreglo
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " - ";
    }
    cout << endl;
}

int main(int argc,char **argv) {

    if (argc < 2){
        return -1;
    }

    cout << "Ingrese tamano de arreglo\n";
    int size = validarIn();
    // 99 maximo
    int arr[99];
    int keyarr[99];
    
    arregloNULL(keyarr,size);
    llenarArreglo(arr,size);
    mostrarArreglo(arr,size);

    // recorre arreglo para asignar keys
    for (int i=0; i<size; i++){
        // asigna una key inicial
        int key = hashKey(arr[i],size);
        cout << arr[i] <<" CLAVE: " << key << endl; 
        // aqui se dirige a colision con la key
        colision(keyarr,arr[i],key,size);
        mostrarArreglo(keyarr,size);
    }
}