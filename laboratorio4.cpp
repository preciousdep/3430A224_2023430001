#include <fstream>
#include <iostream>
using namespace std;

struct Node {
    int info;
    Node* left;
    Node* right;
};

// Crear un nuevo nodo
Node* createNode(const int& data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

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

void preOrderPrint(Node* root){
    if (root==nullptr){
        return;
    }
    cout << root-> info << " | ";
    preOrderPrint(root->left);
    preOrderPrint(root->right);
}

void inOrderPrint(Node* root){
    if (root==nullptr){
        return;
    }
    inOrderPrint(root->left);
    cout << root-> info << " | ";
    inOrderPrint(root->right);
}

void postOrderPrint(Node* root){
    if (root==nullptr){
        return;
    }
    postOrderPrint(root->left);
    postOrderPrint(root->right);
    cout << root-> info << " | ";
}

class Arbol {
private:
    Node* root;

public:
    // Constructor de la clase Arbol
    Arbol(Node* node) : root(node) {}

    // escribe en el archivo
    void generateGraphic(Node* node, ofstream& fp) {
        if (node != NULL){
            if (node->left != NULL){
                fp << node->info << " -> " << node->left->info << ";" << endl;
                generateGraphic(node->left,fp);
            }
            if (node->right!=NULL){
                fp << node->info << " -> " << node->right->info << ";" << endl;
                generateGraphic(node->right,fp);
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
};

int main() {
    Node *root = NULL;

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
                insertNode(root,addNode);
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
                preOrderPrint(root);
            } else if (printChoice == 2){
                inOrderPrint(root);
            } else if (printChoice == 3){
                postOrderPrint(root);
            } else if (printChoice==4){
                // generar imagen
                Arbol arbol(root);
                arbol.visualize();
            } else {
                 cout << "Opcion invalida\n";
            };
            cout << "\n";            

        } else if (menuChoice == 3){
            cout << "Ingrese el valor del nodo que quiere eliminar\n";
            int search;
            cin >> search;
            if (deleteNode(root,search) != NULL){
                cout << "No se ha eliminado nada, no se encontro\n";
            } else {
                cout << "Eliminado con exito\n";
            };
        } else if (menuChoice == 4){
            cout << "Ingrese el valor del nodo que quiere modificar\n";
            int search;
            cin >> search;
            if (modifyNode(root,search) == true) {
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