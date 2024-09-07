#include <iostream>
#include <string>

using namespace std;

// crea la estructura de un nodo
struct Stack{
    int data;
    Stack* next;
};

//revisa si la pila esta vacia con el
// contador de counter y comparando si es == 0
bool emptyStack(Stack* head,int counter){
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
bool fullStack(Stack* head,int max, int counter){
    bool result;
    if (max==counter){
        //pila llena
        result = true;
    } else {
        //pila no llena
        result = false;
    };
    return result;
}

bool push(Stack*& head, int& counter, int max, int dato){

    if (fullStack(head,max,counter)) {
        return false;
    } else {
        Stack* newStack = new Stack();
        newStack -> data = dato;
        counter += 1;
        newStack->next = head;
        head = newStack;
        return true;
    };
    
}

//elimina el ultimo dato
bool pop(Stack*& head, int counter) {
    if (emptyStack(head,counter)) {
        return true;
    } else {
        Stack* top = head;
        head = head->next;
        counter = counter - 1;
        return false;
    };
}

// muestra datos en orden de pila
void printStack(Stack* head){
    Stack* current = head;
    while (current != nullptr){
        cout << "|"<< current->data << "|" << "\n";
        current = current -> next;
    };
};

int main() {
    Stack* head = nullptr;
    int max; // definir numero maximo de la pila, por ejemplo 5
    max = 5;
    int counter = 0;

    // menu
    int menuChoice = -1;
    while (menuChoice != 0){
        cout << "Administrador de pila. . .\n";
        cout << "El máximo de la pila ahora es: " << max << "\n" <<
        "Agregar/push [1]\n" << "Remover/pop [2]\n" << "Ver pila [3]\n"
        << "Salir [0]\n";
        cout << "-------------------\n";
        cin >> menuChoice;

        if (menuChoice == 1){
            int pushData;
            cout << "Ingrese el dato a agregar\n";
            cin >> pushData;
            if (push(head,counter,max,pushData)){
                cout << "Dato agregado con exito\n";
            } else {
                cout << "Pila llena. No agregado\n";
            }
        } else if (menuChoice == 2){
            if (!pop(head,counter)){
                cout << "Ultimo dato eliminado con exito\n";
            } else {
                cout << "Pila vacía. Agregue datos primero\n";
            }
        } else if (menuChoice == 3){
            printStack(head);
        } else {
            break;
        }
    }
}