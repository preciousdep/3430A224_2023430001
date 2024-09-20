#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct Node {
    int info;
    Node* left;
    Node* right;
};


// crear un nodo en base a una informacion
Node* createNode(const int& data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

class Arbol {
private:
    Node*& root;

public:
    // se asigna el root(node) a la clase arbol para
    // construirla
    Arbol(Node*& node) : root(node) {}

    // escribe en el archivo
    void recorrer(Node* root, ofstream& fp) {
        if (root != nullptr){
            if (root->left != nullptr){
                fp << root->info << " -> " << root->left->info << ";" << endl;
            } else {
                // se usa el \" para agregar comillas dobles al numero,
                // si no estuvieran presentes existen problemas de
                // ambiguedad con el entero
                string cadena = "\"" + to_string(root->info) + "i\"";
                fp << cadena << "[shape=point];" << endl;
                fp << root->info << " -> " << cadena << ";" << endl;
            }
            if (root->right!=nullptr){
                fp << root->info << " -> " << root->right->info << ";" << endl;
            } else {
                string cadena = "\"" + to_string(root->info) + "d\"";
                fp << cadena << "[shape=point];" << endl;
                fp << root->info << " -> " << cadena << ";" << endl;
            }
            recorrer(root->left,fp);
            recorrer(root->right,fp);
        }
    }

    // genera el grafico con el archivo de texto y agrega su encabezado/final
    void visualize() {
        ofstream fp("arbol.txt");

        if (!fp.is_open()) {
            cerr << "Error al abrir el archivo arbol.txt" << endl;
            return;
        }

        fp << "digraph G {" << endl;
        fp << "node [style=filled fillcolor=yellow];" << endl;

        recorrer(root, fp);

        fp << "}" << endl;
        
        fp.close();

        // aqui se genera la imagen, luego se abre el archivo
        system("dot -Tpng -o arbol.png arbol.txt");
        cout << "Imagen generada con exito\n";
        // utiliza este comando en windows para poder abrir
        // la imagen generada
        system("start arbol.png");
    }


    // insertar un nuevo nodo considerando
    // mayor o menor al root, usando recursividad
    // hasta encontrar su lugar adecuado
    // en caso de que el usuario quiera agregar
    // datos de forma manual (igualmente ya hay datos
    //previamente agregados en el main)
    Node* insertNode(Node*& root, int info){
        if (root == NULL){
            root = createNode(info);
        } else if (info == root-> info){
            // en caso de que ya existiera, se omite
            cout << "El dato ya existe en el arbol\n";
        } else if (info <= root->info) {
            root->left = insertNode(root->left, info);
        } else {
            root->right = insertNode(root->right,info);
        }
        return root;
    }

    // elimina el nodo que se busca con la informacion
    // que contiene
    Node* deleteNode(Node*& root, int search){
        if (root==NULL){
            return root;
        }
        if (search < root -> info) {
            root -> left = deleteNode(root->left,search);
        } else if (search > root -> info) {
            root -> right = deleteNode(root->right,search);
        } else { // intercambio con un temp para poder eliminar
            if (root->left == NULL) {
                Node* temp = root -> right;
                delete root;
                return temp;
            } else if (root->right==NULL){
                Node* temp = root -> left;
                delete root;
                return temp;
            }
            Node* temp = root -> right;
            while (temp->left != NULL) {
                temp = temp-> left;
            }
            root -> info = temp -> info;
            root -> right = deleteNode(root->right, temp->info);
        }
        return root;

    }
    
    // se busca el nodo con recursividad y
    // se modifica su informacion contenida
    // con input del usuario
    bool modifyNode(Node*& root, int info){
        if (root==NULL) {
            return false;
        } else if (root-> info == info){
            // modify here
            cout << "Ingrese nueva informacion para el nodo (ENTERO)\n";
            int newNode;
            cin >> newNode;
            root-> info = newNode;
            return true;
        } else if (info <= root -> info){
            return modifyNode(root->left, info);
        } else {
            return modifyNode(root->right, info);
        }
    }

//root izq derecha print
    void preOrderPrint(Node* root){
        if (root==nullptr){
            return;
        }
        cout << root-> info << " | ";
        preOrderPrint(root->left);
        preOrderPrint(root->right);
    }

// izq root derecha
    void inOrderPrint(Node* root){
        if (root==nullptr){
            return;
        }
        inOrderPrint(root->left);
        cout << root-> info << " | ";
        inOrderPrint(root->right);
    }

// izq derecha root
    void postOrderPrint(Node* root){
        if (root==nullptr){
            return;
        }
        postOrderPrint(root->left);
        postOrderPrint(root->right);
        cout << root-> info << " | ";
    }
};

int main() {
    Node *root = NULL;
    Arbol arbol(root);

    // agregar datos
    arbol.insertNode(root,120);
    arbol.insertNode(root,87);
    arbol.insertNode(root,140);
    arbol.insertNode(root,43);
    arbol.insertNode(root,99);
    arbol.insertNode(root,130);
    arbol.insertNode(root,22);
    arbol.insertNode(root,65);
    arbol.insertNode(root,93);
    arbol.insertNode(root,135);
    arbol.insertNode(root,56);

    int menuChoice = -1;
    while (menuChoice != 0){
        cout << "A R B O L\n";
        cout << "Escoja lo que quiere hacer:" << "\n" <<
        "Agregar al arbol [1]\n" << "Mostrar arbol[2]\n" <<
        "Eliminar un nodo [3]\n" << "Modificar un nodo [4]\n"
        << "Salir [0]\n";
        cout << "-------------------\n";
        cin >> menuChoice;

        // utilizacion de menu que habia usado
        // en guias anteriores para un aspecto
        // mas interactivo
        if (menuChoice == 1){
            // lo dejo por si se desea agregar datos
            // desde la terminal, igualmente ya se tienen datos ya
            // predeterminados
            cout << "Ingrese numero a agregar\n";
            int addNode;
            cin >> addNode;
            cout << "Agregando nodo. . .\n";
            arbol.insertNode(root,addNode);
        } else if (menuChoice == 2){
            cout << "Mostrar en Pre Orden [1]\n" <<
            "Mostrar en In Orden [2]\n" << "Mostrar en Post Orden [3]\n" <<
            "Generar imagen del arbol [4]\n";
            int printChoice;
            cin >> printChoice;
            if (printChoice == 1){
                arbol.preOrderPrint(root);
            } else if (printChoice == 2){
                arbol.inOrderPrint(root);
            } else if (printChoice == 3){
                arbol.postOrderPrint(root);
            } else if (printChoice==4){
                // generar imagen
                arbol.visualize();
            } else {
                 cout << "Opcion invalida\n";
            };
            cout << "\n";            

        } else if (menuChoice == 3){
            cout << "Ingrese el valor del nodo que quiere eliminar\n";
            int search;
            cin >> search;
            if (arbol.deleteNode(root,search) != NULL){
                cout << "No se ha eliminado nada, no se encontro\n";
            } else {
                cout << "Eliminado con exito\n";
            };
        } else if (menuChoice == 4){
            cout << "Ingrese el valor del nodo que quiere modificar\n";
            int search;
            cin >> search;
            if (arbol.modifyNode(root,search) == true) {
                cout <<"Se encontro y se modifico con exito \n";
            } else {
                cout << "No se encontro\n";
            }
        } else {
            break;
        }
    }

    return 0;
}