#include <fstream>
#include <iostream>
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
    // Constructor de la clase Arbol
    Arbol(Node*& node) : root(node) {}

    // escribe en el archivo
    void generateGraphic(Node* root, ofstream& fp) {
        if (root != NULL){
            if (root->left != NULL){
                fp << root->info << " -> " << root->left->info << ";" << endl;
                generateGraphic(root->left,fp);
            }
            if (root->right!=NULL){
                fp << root->info << " -> " << root->right->info << ";" << endl;
                generateGraphic(root->right,fp);
            }
        }
    }

    // Generar y mostrar la visualizacion del arbol
    void visualize() {
        ofstream fp("arbol.txt");

        if (!fp.is_open()) {
            cerr << "Error al abrir el archivo arbol.txt" << endl;
            return;
        }

        fp << "digraph G {" << endl;
        fp << "node [style=filled fillcolor=yellow];" << endl;

        generateGraphic(root, fp);

        fp << "}" << endl;
        
        fp.close();

        // Generar y mostrar la imagen del arbol
        system("dot -Tpng -o arbol.png arbol.txt");
        cout << "Imagen generada con exito\n";
    }


    // insertar un nuevo nodo considerando
    // mayor o menor al root
    Node* insertNode(Node*& root, int info){
        if (root == NULL){
            root = createNode(info);
        } else if (info == root-> info){
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
        } else {
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
    
    // se busca el nodo y se modifica su informacion
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

    int menuChoice = -1;
    while (menuChoice != 0){
        cout << "A R B O L\n";
        cout << "Escoja lo que quiere hacer:" << "\n" <<
        "Agregar al arbol [1]\n" << "Mostrar arbol[2]\n" <<
        "Eliminar un nodo [3]\n" << "Modificar un nodo [4]\n"
        << "Salir [0]\n";
        cout << "-------------------\n";
        cin >> menuChoice;

        if (menuChoice == 1){
            cout << "Ingrese numero a agregar\n";
            int addNode;
            if (cin >> addNode){
                cout << "Agregando nodo. . .\n";
                arbol.insertNode(root,addNode);
            } else if (cin.bad()){
                cout << "Dato invalido. Debe ser entero\n";
            } // ARREGLAR ESTO AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        } else if (menuChoice == 2){
            cout << "Mostrar en Pre Orden [1]\n" <<
            "Mostrar en In Orden [2]\n" << "Mostrar en Post Orden [3]\n" <<
            "Generar imagen del arbol [4]\n";
            int printChoice;
            cin >> printChoice;
            // arreglar loop infinito cuando se muestra tras vaciar arbol
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