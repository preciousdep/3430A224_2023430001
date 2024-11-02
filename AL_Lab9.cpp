#include <iostream>
#include <cstdlib>
using namespace std;


void colisionDobleHash(int* keyarr, int valor, int key, int size){
    int dx = ((key+1) % size); // formula distinta del doble hash
    cout << "CLAVE INICIAL: " << key << " + 1 % "<< size << endl;
        while (keyarr[dx] != -5 && keyarr[dx] != valor && dx!=key){
        if (dx == size || dx == size+1){
            dx = 0;
        } else {
            cout << "CLAVE: " << dx << " + 1 % " << size << endl;
            dx = ((dx+1)%size);
            cout << " = " << dx << endl;
        }
    }
    keyarr[dx] = valor;

}

void colisionCuadratica(int* keyarr, int valor, int key, int size){
    int i = 1;
    int dx = (key + (i*i)) % size;
    while (keyarr[key] != -5 && dx != key) {
        i++;
        dx = (key + (i*i)) % size;

        if (dx > size){
            i = 0;
            dx = 1;
            key = 1;
        }
    }
    if (keyarr[key]== -5){
        keyarr[dx] = valor;
    }

}

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
        return true;
    } else { // colision
        cout << "Se ha encontrado una colision \n";
        return false;
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

    char argumento;
    cin >> argumento;

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
            if (colision(keyarr,arr[i],key,size)){
                keyarr[key] = arr[i];
            } else { // manejo de colisiones
                if (argumento == 'L'){
                    colisionLineal(keyarr,arr[i],key,size);

                } else if (argumento == 'C'){
                    colisionCuadratica(keyarr,arr[i],key,size);

                } else if (argumento == 'D'){
                    colisionDobleHash(keyarr,arr[i],key,size);
                }
            };
        }
        mostrarArreglo(keyarr,size);
    }