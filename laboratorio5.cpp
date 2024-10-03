#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

#define TRUE 1
#define FALSE 0

enum {IZQUIERDO, DERECHO};

struct Nodo {
    int dato;
    int FE;
    Nodo* derecho;
    Nodo* izquierdo;
    Nodo* padre;
};

typedef Nodo* pNodo;
typedef Nodo* Arbol;

/* Insertar en arbol ordenado: */
void Insertar(Arbol* a, int dat);
/* Borrar un elemento: */
void Borrar(Arbol* a, int dat);
/* Funcion de busqueda: */
pNodo Buscar(Arbol a, int dat);
/* modificar */
void Modificar(Arbol* a, int dat);
/* Comprobar si es un nodo hoja: */
// cambiado a bool debido a que true: es hoja
// false: no es hoja
bool EsHoja(pNodo r);
/* Contar numero de nodos: */
int NumeroNodos(Arbol a);
/* Calcular la altura de un arbol: */
int AlturaArbol(Arbol a);
/* Calcular altura de un dato: */
int Altura(Arbol a, int c);
/* Generar salida para Graphiz */
void PreOrden(Arbol, std::ofstream &fp);

// Funciones de equilibrado:
void Equilibrar(Arbol* raiz, pNodo nodo, int, int);
void RotaDerechaDerecha(Arbol* raiz, pNodo nodo);
void RotaIzquierdaIzquierda(Arbol* raiz, pNodo nodo);
void RotaDerechaIzquierda(Arbol* raiz, pNodo nodo);
void RotaIzquierdaDerecha(Arbol* raiz, pNodo nodo);

/* Funciones auxiliares: */
void Podar(Arbol* a);
void auxContador(Arbol a, int*);
void auxAltura(Arbol a, int, int*);

void MenuPrincipal();
void GenerarGrafo(Arbol);

int main() {
    Arbol ArbolInt = NULL;
    int opcion = -1;
    int valor;
    int altura;
    int nodos;

    while (opcion != 0) {
        MenuPrincipal();
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese su numero: ";
                cin >> valor;
                Insertar(&ArbolInt, valor);
                break;
            case 2:
                cout << "Ingrese valor a buscar: ";
                cin >> valor;
                if (Buscar(ArbolInt, valor)){
                    cout << "Se encontro valor \n";
                } else {
                    cout << "No se encontro valor \n";
                }
                break;
            case 3:
                cout << "Ingrese numero a eliminar: ";
                cin >> valor;
                Borrar(&ArbolInt,valor);
                break;
            case 4:
                cout << "Ingrese numero a modificar: ";
                cin >> valor;
                Modificar(&ArbolInt,valor);
                //
                break;
            case 5:
                GenerarGrafo(ArbolInt);
                break;

            case 6:
            altura = AlturaArbol(ArbolInt);
            cout << "La altura del arbol es de: "<< altura << "\n";
            nodos = NumeroNodos(ArbolInt); 
            // usa * porque el valor se modifica
            cout << "El numero de nodos en el arbol es de: " << nodos << "\n";
            break;
            case 7:
            cout << "Ingrese el nodo del cual quiere saber informacion\n";
            cin >> valor;
            altura=Altura(ArbolInt,valor);
            cout <<altura << "\n";
            if (EsHoja(Buscar(ArbolInt,valor))){
                cout << "El nodo introducido es hoja\n";
            } else {
                cout << "El nodo introducido no es hoja\n";
            }
            break;
        }
    }

    /* Liberar memoria asociada al arbol. */
    Podar(&ArbolInt);
    return 0;
}

void GenerarGrafo(Arbol ArbolInt) {
    std::ofstream fp("grafo.txt");

    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=yellow];\n";

    fp << "nullraiz [shape=point];\n";
    fp << "nullraiz->" << ArbolInt->dato << " [label=" << ArbolInt->FE << "];\n";
    PreOrden(ArbolInt, fp);

    fp << "}\n";
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");
    system("start grafo.png &");
}

void MenuPrincipal() {
    cout << "\n";
    cout << "<1> Ingresar numero\n";
    cout << "<2> Busqueda numero\n";
    cout << "<3> Eliminar numero\n";
    cout << "<4> Modificar elemento ingresado\n";
    cout << "<5> Generar Grafo\n";
    cout << "<6> Informacion del arbol\n";
    cout << "<7> Informacion de un nodo\n";
    cout << "<0> Salir\n";
    cout << "\n";
}

void Podar(Arbol* a) {
    if (*a) {
        Podar(&(*a)->izquierdo);
        Podar(&(*a)->derecho);
        free(*a);
        *a = NULL;
    }
}

void Insertar(Arbol* a, int dat) {
    pNodo padre = NULL;
    pNodo actual = *a;

    while (actual != NULL && dat != actual->dato) {
        padre = actual;

        if (dat < actual->dato)
            actual = actual->izquierdo;
        else if (dat > actual->dato)
            actual = actual->derecho;
    }

    if (actual != NULL)
        return;

    if (padre == NULL) {
        *a = new Nodo{dat, 0, NULL, NULL, NULL};
    } else if (dat < padre->dato) {
        actual = new Nodo{dat, 0, NULL, NULL, padre};
        padre->izquierdo = actual;
        Equilibrar(a, padre, IZQUIERDO, TRUE);
    } else if (dat > padre->dato) {
        actual = new Nodo{dat, 0, NULL, NULL, padre};
        padre->derecho = actual;
        Equilibrar(a, padre, DERECHO, TRUE);
    }
}

void Borrar(Arbol* a, int dat){
    pNodo padre = NULL;
    pNodo actual = *a;

    if (actual != NULL){
        if (dat < actual->dato){
            Borrar(&(actual->izquierdo), dat);

        } else if (dat > actual->dato) {
            Borrar(&(actual->derecho),dat);
        } else {
            pNodo otro = actual;
            if (otro->derecho == NULL){
                pNodo temp = actual;
                *a = actual-> izquierdo;
            } else if (otro->izquierdo == NULL){
                pNodo temp = actual;
                *a = actual -> derecho;
            } else {
                pNodo auxiliar = actual -> izquierdo;
                pNodo auxiliar1;
                while (auxiliar -> derecho != NULL){
                    auxiliar1 = auxiliar;
                    auxiliar = auxiliar->derecho;
                };
                actual->dato = auxiliar->dato;

                if (auxiliar1 == auxiliar){
                    auxiliar1->derecho = auxiliar ->izquierdo;
                } else {
                    auxiliar1->izquierdo = auxiliar->izquierdo;
                }
                Podar(&auxiliar);
            }
        } 

    } else {
        cout << "No se consiguió en el arbol\n";
    }
}

pNodo Buscar(Arbol a, int dat){
    pNodo actual = a;
    pNodo padre = NULL; 
    while (actual != NULL && dat != actual->dato) {
        padre = actual;

        if (dat < actual->dato)
            actual = actual->izquierdo;
        else if (dat > actual->dato)
            actual = actual->derecho;
    }

    if (actual == NULL){
        return nullptr;
    } else {
        return actual;
    }
}

void Modificar(Arbol* a, int dat){
    Borrar(a,dat);
    cout << "Ingrese numero por el cual reemplazar: ";
    int nuevoNum;
    cin >> nuevoNum;
    Insertar(a,nuevoNum);
};

void Equilibrar(Arbol* a, pNodo nodo, int rama, int nuevo) {
    int salir = FALSE;

    while (nodo && !salir) {
        if (nuevo){
            if (rama == IZQUIERDO){
                nodo->FE -= 1;
            } else {
                nodo->FE += 1;
            }
        }
        else{
            if (rama == IZQUIERDO){
                nodo->FE += 1;
            } 
            else {
                nodo->FE -= 1;
            }
        }

        if (nodo->FE == 0)
            salir = TRUE;
        else if (nodo->FE == -2) {
            if (nodo->izquierdo->FE == 1)
                RotaIzquierdaDerecha(a, nodo);
            else
                RotaIzquierdaIzquierda(a, nodo);
            salir = TRUE;
        } else if (nodo->FE == 2) {
            if (nodo->derecho->FE == -1)
                RotaDerechaIzquierda(a, nodo);
            else
                RotaDerechaDerecha(a, nodo);
            salir = TRUE;
        }

        if (nodo->padre) {
            if (nodo->padre->derecho == nodo) {
                rama = DERECHO;
            } else {
                rama = IZQUIERDO;
            }
        }
        nodo = nodo->padre;
    }
}

void RotaIzquierdaDerecha(Arbol* raiz, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo R = Q->derecho;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre){
        if (Padre->derecho == nodo){
            Padre->derecho = R;
        }
        else {
            Padre->izquierdo = R;
        }
    }
    else
        *raiz = R;

    Q->derecho = B;
    P->izquierdo = C;
    R->izquierdo = Q;
    R->derecho = P;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = Q;
    if (C) C->padre = P;

    switch (R->FE) {
        case -1: Q->FE = 0; P->FE = 1; break;
        case 0: Q->FE = 0; P->FE = 0; break;
        case 1: Q->FE = -1; P->FE = 0; break;
    }

    R->FE = 0;
}

void RotaDerechaIzquierda(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo R = Q->izquierdo;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre){
        if (Padre->derecho == nodo){
            Padre->derecho = R;
        } else {
            Padre->izquierdo = R;
        }
    }
    else
        *a = R;

    P->derecho = B;
    Q->izquierdo = C;
    R->izquierdo = P;
    R->derecho = Q;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = P;
    if (C) C->padre = Q;

    switch (R->FE) {
        case -1: P->FE = 0; Q->FE = 1; break;
        case 0: P->FE = 0; Q->FE = 0; break;
        case 1: P->FE = -1; Q->FE = 0; break;
    }
    R->FE = 0;
}

void RotaIzquierdaIzquierda(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo B = Q->derecho;

    if (Padre){
        if (Padre->derecho == P){
            Padre->derecho = Q;
        }
        else {
            Padre->izquierdo = Q;
        }
    }
    else
        *a = Q;

    P->izquierdo = B;
    Q->derecho = P;

    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}

void RotaDerechaDerecha(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo B = Q->izquierdo;

    if (Padre){
        if (Padre->derecho == P){
            Padre->derecho = Q;
        }
        else {
            Padre->izquierdo = Q;
        }
    }
    else
        *a = Q;

    P->derecho = B;
    Q->izquierdo = P;

    P->padre = Q;
    
    if (B){
        B->padre = P;
    } 
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}

void PreOrden(Arbol a, std::ofstream &fp) {
    if (a) {
        fp << a->dato << ";\n";
        if (a->izquierdo) {
            fp << a->dato << "->" << a->izquierdo->dato << "[label="<< a->izquierdo->FE << "];\n";
            PreOrden(a->izquierdo, fp);
        }
        if (a->derecho) {
            fp << a->dato << "->" << a->derecho->dato << "[label=" << a->derecho->FE << "];\n";
            PreOrden(a->derecho, fp);
        }
    }
}

bool EsHoja(pNodo a){
    if (a->izquierdo == NULL && a->derecho == NULL){
        // ambos lados son null, significa que es hoja
        return TRUE;
    } else {
        return FALSE;
    }

};

int NumeroNodos(Arbol a){
    /* usando logica de recorrer en pre orden
    contar los nodos del inicio hasta que sea null*/
    pNodo root = a;
        if (root==nullptr){
            return 0;
        };
        return 1 + NumeroNodos(root->izquierdo) + NumeroNodos(root->derecho);
}

int AlturaArbol(Arbol a){
    pNodo root = a;
    if (root == nullptr){
        return -1;
        // en ese caso la altura se devuelve -1, ya que no hay nodos
    }
    // recursividad para sumar cada lado
    int alturaIzquierda = AlturaArbol(root->izquierdo);
    int alturaDerecha = AlturaArbol(root->derecho);

    // compara el mayor para recibir la altura
    if (alturaIzquierda >= alturaDerecha){
        return alturaIzquierda + 1;
    } else {
        return alturaDerecha +1;
    }
}

int Altura(Arbol a, int dat){
    cout << "Altura del nodo:\n";
    int altura;
    pNodo actual = a;
    pNodo padre = NULL; 
    while (actual != NULL && dat != actual->dato) {
        padre = actual;

        if (dat < actual->dato)
            actual = actual->izquierdo;
        else if (dat > actual->dato)
            actual = actual->derecho;
    }
    if (actual == NULL){
        return -1;
    } else { // dato encontrado
        altura = AlturaArbol(actual);
    }    
}