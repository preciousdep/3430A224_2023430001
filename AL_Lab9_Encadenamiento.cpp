#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;

// se hace un documento aparte debido a que se necesita una estructura distinta
// para este metodo de reordenamiento


struct nodo{
    int info;
    nodo* next = nullptr;
};

void encadenamiento(nodo*& keyarr, int valor, int key, int size, int &pointer){
    
    nodo* newNode = new nodo;
    newNode->info = valor; 
    newNode->next = nullptr; 


    if (keyarr[key].next == nullptr) {
        keyarr[key].next = newNode; 
    } else {
        nodo* q = keyarr[key].next;
        while (q->next != nullptr) {
            q = q->next;
            pointer++;
        }
        q->next = newNode;
    }
}

//funcion hash con modulo
int hashKey(int valor, int size){
    // hash por modulo
    int key;
    key = (valor % size);
    return key;
}

void buscar(nodo* keyarr, int valor, int size){
    int pointer = 0;

    int key = hashKey(valor,size);
    if (valor != keyarr[key].info && keyarr[key].info != -5){ // se reconoce si fue por colision y se usan los metodos para buscar con dx
        encadenamiento(keyarr,valor,key,size,pointer);
        cout << "El valor se encuentra encadenado como numero " << pointer+2 << " en la posicion " <<
        key << " del arreglo \n";
    } else if (valor == keyarr[key].info){ // si no existio colision, se encuentra valor
        cout << "El valor fue asignado en la posicion " << key << endl;
    } else {
        cout << "No se encontro \n";
    }
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

void mostrarArregloNodo(nodo* arr, int size) {
    // mostrar los valores del arreglo
    for (int i = 0; i < size; ++i) {
        if (arr[i].info == -5){
            cout << "Vacio";
        } else {
            cout << arr[i].info;
            if (arr[i].next != nullptr){
                nodo* temp = arr[i].next;
                while (temp != nullptr){
                    cout << " -> "<< temp -> info ;
                    temp = temp->next;
                }
            } 
        }
        cout << "\n" ;
    }
    cout << endl;
}


bool colisionEnc(nodo* keyarr, int valor, int key, int size){
    if (keyarr[key].info == -5){
        return true;
    } else { // colision
        cout << "Se ha encontrado una colision \n";
        return false;
    }
}

nodo* crearArregloNodos(int size){
    nodo* arrnodo = new nodo[99];
    for (int i = 0; i<size;i++){
        arrnodo[i].info = rand() % 100 + 1;;
    }

    return arrnodo;
}

nodo* crearArregloNull(int size){
    nodo* arrnodo = new nodo[99];
    for (int i = 0; i<size;i++){
        arrnodo[i].info = -5;
    }

    return arrnodo;
}


int main() {

    cout << "Ingrese tamano de arreglo\n";
    int size = validarIn();
    // 99 maximo
    nodo* arr = crearArregloNodos(size);
    nodo* keyarr = crearArregloNull(size);
    int pointer; // este se usara para las busquedas
    
    //arregloNULL(keyarr,size); 
    mostrarArregloNodo(arr,size);

    // recorre arreglo para asignar keys
        for (int i=0; i<size; i++){
            // asigna una key inicial
            int key = hashKey(arr[i].info, size);
            cout << arr[i].info <<" CLAVE: " << key << endl; 
            // aqui se dirige a colision con la key
            if (colisionEnc(keyarr,arr[i].info,key,size)){
                keyarr[key] = arr[i];
            } else { // manejo de colisiones
            cout << "Se consiguio una colision para el valor " << arr[i].info << " en el lugar " << key << endl;
                encadenamiento(keyarr,arr[i].info,key,size,pointer);
            };
        }
        mostrarArregloNodo(keyarr,size);
        cout << "----------------------\n";
        cout << "Arreglo ordenado \nEscoja el valor que desea buscar...\n";
        int busqueda = validarIn(); // busqueda
        buscar(keyarr,busqueda,size);
}