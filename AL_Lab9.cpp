#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;

void colisionDobleHash(int* keyarr, int valor, int key, int size, int &dx){
    dx = ((key+1) % size); // formula distinta del doble hash
    // se aplica hasta que no existan colisiones
    cout << "CLAVE INICIAL: " << key << " + 1 % "<< size << endl;
        while (keyarr[dx] != -5 && keyarr[dx] != valor && dx!=key){
        if (dx == size || dx == size+1){
            dx = 0;
        } else {
            cout << "CLAVE: " << dx << " + 1 % " << size << endl;
            dx = ((dx+1)%size); // %size para que no se pase del tamano del arreglo
            cout << " = " << dx << endl;
        }
    }
        if (keyarr[dx]==valor){
        cout << "Valor encontrado\n";
    } else if (keyarr[dx]==-5){
        cout << "Se agrega " << valor << " en " << dx << endl;
        keyarr[dx] = valor;
    } else {
        cout << "Ha ocurrido un error...\n";
    }

}

void colisionCuadratica(int* keyarr, int valor, int key, int size, int &dx){
    /* se modificaron ciertos detalles en comparacion
    al pseudocodigo porque siempre habian errores en caso
    de que la clave donde hay colision es = 0, tambien
    cuando los numeros se mantenian haciendo bucle seguido,
    asignando los mismos numeros debajo de size */
    int i = 1;
    dx = (key + (i*i));
    if (dx > size){
        dx = dx - size;
        // esto para la primera asignacion, asegurarse
        // que no sobrepase el limite
    }
    while (keyarr[dx] != -5 && keyarr[dx] != valor) {
        dx = (dx + (i*i));

        if (dx >= size){ // en caso que dx se pase del limite
        // se reasigna con modulo sin modificar i o key
        // ya que ahi existiria un bucle infinito
            cout << "SE REASIGNAN\n";
            dx = dx%size;
        } 

        cout << "CONTROL" << dx << endl;
        cout << "dx : " << dx << "\n i : " << i << "\n";
        i++;
    }
    if (keyarr[dx]==valor){
        cout << "Valor encontrado\n";
    } else if (keyarr[dx]==-5){
        cout << "Se agrega " << valor << " en " << dx << endl;
        keyarr[dx] = valor;
    } else {
        cout << "Ha ocurrido un error...\n";
    }

}

// colision lineal, recorre el arreglo de forma circular hasta que
// encuentra un sitio adecuado
void colisionLineal(int* keyarr, int valor, int key, int size, int &dx){
    dx = key + 1;
    while (keyarr[dx] != -5 && keyarr[dx] != valor && dx!=key){
        cout << "Se intenta en la posicion " << dx << endl;
        if (dx == size || dx == size+1){
            dx = 0;
        } else {
            dx ++;
        }
    }
    if (keyarr[dx]==valor){
        cout << "Valor encontrado\n";
    } else if (keyarr[dx]==-5){
        cout << "Se agrega " << valor << " en " << dx << endl;
        keyarr[dx] = valor;
    } else {
        cout << "Ha ocurrido un error...\n";
    }
}

// aqui se evalua si el sitio keyarr[key] esta vacio (=-5) o
// ya contiene algo. desde ahi se agrega o se trata la colision
// devolviendo true o false
bool colision(int* keyarr, int valor, int key, int size){

    if (keyarr[key] == -5){
        return true;
    } else { // colision
        cout << "Se ha encontrado una colision \n";
        return false;
    }
}


//funcion hash con modulo
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

void buscar(int* keyarr, int valor, int size, char argumento){
    int dx;

    int key = hashKey(valor,size);
    if (valor != keyarr[key]){ // se reconoce si fue por colision y se usan los metodos para buscar con dx
        cout << "Este valor fue asignado por colision, buscando...\n";
        if (argumento == 'L'){
            colisionLineal(keyarr,valor,key,size,dx);
            cout << "Por reasignacion Lineal fue asignado en posicion " <<
            dx << "\n";
        } else if (argumento == 'C'){
            colisionCuadratica(keyarr,valor,key,size,dx);
            cout << "Por reasignacion Cuadratica fue asignado en posicion " <<
            dx << "\n";
        } else if (argumento == 'D'){
            colisionDobleHash(keyarr,valor,key,size,dx);
            cout << "Por reasignacion Cuadratica fue asignado en posicion " <<
            dx << "\n";

        }
    } else if (valor == keyarr[key]){ // si no existio colision, se encuentra valor
        cout << "El valor fue asignado en la posicion " << key << endl;
    }
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
    argumento = toupper(argv[1][0]);
    // comprobar que el argumento sea valido 
    while (argumento != 'L' && argumento != 'C' && argumento != 'D'){
        cout << "Opcion no valida. Escoja L, C o D\n";
        cin >> argumento;
        argumento = toupper(argumento);
    }

    cout << "Ingrese tamano de arreglo\n";
    int size = validarIn();
    // 99 maximo
    int arr[99];
    int keyarr[99];
    int dx; // este se usara para las busquedas
    
    //arregloNULL(keyarr,size); 
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
                    colisionLineal(keyarr,arr[i],key,size, dx);

                } else if (argumento == 'C'){
                    colisionCuadratica(keyarr,arr[i],key,size,dx);

                } else if (argumento == 'D'){
                    colisionDobleHash(keyarr,arr[i],key,size,dx);
                } // encadenamiento debe ser distinta al usar clases
            };
        }
        mostrarArreglo(keyarr,size);

        cout << "Arreglo ordenado \nEscoja el valor que desea buscar...\n";
        int busqueda = validarIn(); // busqueda
        buscar(keyarr,busqueda,size,argumento);
    }