#include <iostream>
#include <string>

using namespace std;

// Estructura para representar un contenedor
struct Contenedor {
    int numero;          
    string empresa;      
};

// Crear una pila con un tamaño máximo
Contenedor** crear_pila(int m, int n, int* &topes) {
    Contenedor** pilas = new Contenedor*[m];
    for (int i = 0; i < m; ++i) {
        pilas[i] = new Contenedor[n];
    }

    topes = new int[m];
    for (int i = 0; i < m; ++i) {
        topes[i] = -1;  
    }

    return pilas;  
}

// Verificar si la pila está llena
bool pila_llena(int tope, int max) {
    return tope == max - 1;
}

// Verificar si la pila está vacía
bool pila_vacia(int tope) {
    return tope == -1;
}

// Insertar un contenedor en la pila
bool push(Contenedor* pila, int& tope, int max, Contenedor contenedor) {
    if (pila_llena(tope, max)) {
        return false;  
    } else {
        pila[++tope] = contenedor;  
        return true;
    }
}

// Remover un contenedor de la pila
Contenedor pop(Contenedor* pila, int& tope) {
    if (pila_vacia(tope)) {
        return { -1, "" };  
    } else {
        return pila[tope--];  
    }
}

// Mostrar los contenedores en la pila
void ver_pila(Contenedor* pila, int tope) {
    if (pila_vacia(tope)) {
        cout << "La pila está vacía." << endl;
    } else {
        for (int i = tope; i >= 0; --i) {
            cout << i + 1 << " | " << pila[i].numero << " - " << pila[i].empresa << endl;
        }
    }
}

// Liberar la memoria de la pila
void destruir_pila(Contenedor** pilas, int* topes, int m) {
    for (int i = 0; i < m; ++i) {
        delete[] pilas[i]; 
    }
    delete[] pilas;  
    delete[] topes;  
}

// Mostrar el estado de todas las pilas
void ver_estado(Contenedor** pilas, int* topes, int m) {
    for (int i = 0; i < m; ++i) {
        cout << "Pila " << i + 1 << ":" << endl;
        ver_pila(pilas[i], topes[i]);
        cout << endl;
    }
}

// Agregar un contenedor a una pila específica
void agregar_contenedor(Contenedor** pilas, int* topes, int m, int n) {
    int pilaIndex;
    Contenedor contenedor;

    cout << "Ingrese el número del contenedor: ";
    cin >> contenedor.numero;
    cout << "Ingrese la empresa del contenedor: ";
    cin >> contenedor.empresa;

    cout << "Ingrese el número de pila (1 - " << m << "): ";
    cin >> pilaIndex;

    if (pilaIndex < 1 || pilaIndex > m) {
        cout << "Número de pila inválido." << endl;
        return;
    }
    pilaIndex--;  

    if (!push(pilas[pilaIndex], topes[pilaIndex], n, contenedor)) {
        cout << "La pila " << pilaIndex + 1 << " está llena." << endl;
    } else {
        cout << "Contenedor " << contenedor.numero << " de " << contenedor.empresa << " agregado a la pila " << pilaIndex + 1 << "." << endl;
    }
}

// Retirar un contenedor 
void retirar_contenedor(Contenedor** pilas, int* topes, int m, int numero, const string& empresa) {
    for (int i = 0; i < m; ++i) {
        Contenedor* tempPila = new Contenedor[topes[i] + 1]; 
        int tempTope = -1;
        bool encontrado = false;
        while (!pila_vacia(topes[i])) {
            Contenedor top = pop(pilas[i], topes[i]);

            if (top.numero == numero && top.empresa == empresa) {
                cout << "Contenedor " << numero << " de " << empresa << " retirado." << endl;
                encontrado = true;
                break;
            } else {
                push(tempPila, tempTope, topes[i] + 1, top);
            }
        }

        while (!pila_vacia(tempTope)) {
            push(pilas[i], topes[i], topes[i] + 1, pop(tempPila, tempTope));
        }

        delete[] tempPila;

        if (encontrado) return;
    }
    cout << "Contenedor " << numero << " de " << empresa << " no encontrado." << endl;
}

// Función principal para ejecutar el programa
int main() {
    int n, m, opcion;
    int* topes;

    cout << "Ingrese la capacidad máxima de contenedores por pila (n): ";
    cin >> n;
    cout << "Ingrese el número de pilas disponibles (m): ";
    cin >> m;
    Contenedor** pilas = crear_pila(m, n, topes); 

    do {
        cout << "\n1. Agregar contenedor" << endl;
        cout << "2. Retirar contenedor" << endl;
        cout << "3. Ver estado de las pilas" << endl;
        cout << "0. Salir" << endl;
        cout << "Opción: ";
        cin >> opcion;

        if (opcion == 1) {
            agregar_contenedor(pilas, topes, m, n);
        } else if (opcion == 2) {
            int numero;
            string empresa;
            cout << "Ingrese el número del contenedor a retirar: ";
            cin >> numero;
            cout << "Ingrese la empresa del contenedor a retirar: ";
            cin >> empresa;
            retirar_contenedor(pilas, topes, m, numero, empresa);
        } else if (opcion == 3) {
            ver_estado(pilas, topes, m);
        } else if (opcion != 0) {
            cout << "Opción no válida." << endl;
        }
    } while (opcion != 0);

    cout << "..." << endl;

    destruir_pila(pilas, topes, m);  

    return 0;
}
