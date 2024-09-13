// README
/* para poder eliminar un dato de una pila que no esta
al final de la misma hay que mover todos los datos anteriores
con el elemento [3] del menu, verificando que efectivamente
se consigue el elemento por eliminar al extremo final de alguna
pila. de ahi solo hay que utilizar la opcion [2]
los contenedores deben ingresarse de forma manual, al igual
que el tamaño y cantidad de pilas */

#include <iostream>
#include <string>

using namespace std;

// crea la estructura de un nodo
struct Stack{
    // nombre del contenedor
    string data;
    Stack* next;
};

// revisa si la pila esta vacia con el
// contador de counter y comparando si es == 0
bool emptyStack(Stack*& head, int& counter){
    bool result;
    if (counter==0){
        //pila vacia
        result = true;
    } else {
        //pila tiene algo
        result = false;
    };
    return result;
}

//revisa si la pila esta en su maximo
//comparando si el contador counter es igual
//al maximo
bool fullStack(Stack*& head,int max, int& counter){
    bool result;

    if (counter >= max){
        //pila llena
        cout << "control\n";
        result = true;
    } else {
        //pila no llena
        result = false;
    };
    return result;
}

bool push(Stack*& head, int max, string dato, int& counter){
    if (fullStack(head,max,counter)) {
        return false;
    } else {
        counter++;
        Stack* newStack = new Stack();
        newStack -> data = dato;
        newStack->next = head;
        head = newStack;
        return true;
    };
    
}

//elimina el ultimo dato
bool pop(Stack*& head, int& counter) {
    if (emptyStack(head, counter)) {
        return true;
    } else {
        counter --;
        Stack* top = head;
        head = head->next;
        return false;
    };
}

// muestra datos en orden de pila
void printStack(Stack*& head){
    Stack* current = head;
    while (current != nullptr){
        cout << "|"<< current->data << "|" << "\n";
        current = current -> next;
    };
};

int main() {
    
    cout << "LEER README AL INICIO DEL CODIGO ANTES DE USAR\n";
    int maxPuerto;
    cout << "Ingrese cantidad de pilas que habra en" <<
    " el puerto seco: (max 40) ";
    cin >> maxPuerto;
    
    int maxPila;
    cout << "\nIngrese tamano maximo de las pilas: (max 40) ";
    cin >> maxPila;
    cout << "\n";

    // definiendo un numero grande, ya que
    // de igual forma el tamaño del arreglo
    // esta definido por m
    Stack* puertoSeco[40] = {nullptr};
    int counterList[40];
    for (int i = 0; i < maxPuerto ; ++i){
        puertoSeco[i] = new Stack();
        counterList[i] = 0;
    }


    // menu
    int menuChoice = -1;
    while (menuChoice != 0){
        cout << "Administrador de puerto. . .\n";
        cout << "El maximo de la pila ahora es: " << maxPila << "\n" <<
        "Agregar/push [1]\n" << "Remover/pop [2]\n" << "Mover datos [3]\n"
    << "Visualizar contenedores [4]\n" << "Salir [0]\n";
        cout << "-------------------\n";
        cin >> menuChoice;

        if (menuChoice == 1){
            int pushStack;
            cout << "Ingrese pila donde desea agregar\n";
            cin >> pushStack;
            string pushData;
            cout << "Ingrese el dato a agregar\n";
            cin >> pushData;

            if (push(puertoSeco[pushStack - 1], maxPila, pushData, counterList[pushStack-1])) {
                cout << "Dato agregado\n";
            } else {
                cout << "Pila llena. No se puede agregar el dato.\n";
            };

            // agregar datos en una pila
        } else if (menuChoice == 2){
            // eliminar el ultimo dato de la pila con eliminacion
            // del puntero
            cout << "Escoja pila para borrar su ultimo elemento\n";
            int popChoice;
            cin >> popChoice;
            if (!pop(puertoSeco[popChoice-1], counterList[popChoice-1])){
                cout << "Dato eliminado con exito\n";
            } else {
                cout << "Pila vacia, no se ha eliminado ningun dato\n";
            }; 

        } else if (menuChoice == 3){
            cout << "Escoja pila de la cual va a mover el elemento\n";

            // se recibe el numero de la pila de la cual se va a mover el elemento, el "origen"
            // si se escoge 1, se sabe que el indice de la pila dentro del arreglo es 1-1= 0
            int originStack;
            cin >> originStack;
            // mismo caso, es la pila en la que va a hacerse funcion de push
            // con los datos del elemento que se desea. la modificacion se basa en
            // agregar un nuevo contenedor con la misma info (que en este caso es el string)
            cout << "Escoja pila a la cual lo va a mover\n";
            int endStack;
            cin >> endStack;
            // se guarda la informacion del string para crear uno nuevo
            string tempData = puertoSeco[originStack-1]-> data;

            // se elimina el dato de la pila de origen
            if (!pop(puertoSeco[originStack-1], counterList[originStack-1])){
                cout << "Dato eliminado con exito\n";
            } else {
                cout << "Pila vacia, no se ha eliminado ningun dato\n";
            }; 

            // se agrega el dato 'nuevo' a la nueva pila con el
            // push, utilizando tempData como la informacion del struct
            if (push(puertoSeco[endStack - 1], maxPila, tempData, counterList[endStack-1])) {
                cout << "Dato agregado\n";
            } else {
                cout << "Pila llena. No se puede agregar el dato.\n";
            };

        } else if (menuChoice == 4){
            for (int i = 0; i < maxPuerto; i++){
                cout << "- Pila " << i+1 << "\n";
                printStack(puertoSeco[i]);
            }
        } else {
            break;
        }
    }
}