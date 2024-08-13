#include <iostream>
#include <string>
using namespace std; 

int numero()
{
    std::cout << "Ingrese un numero\n";
    int x;
    // leer desde estandar
    std::cin >> x;
    // imprimir con estandar
    std::cout << x <<"\n";
    return x;
}

int par_o_no(int x)
// determinar si es par o no
{
    if ( x % 2 == 0) {
        std::cout << x << " es un numero par\n";
    } else {
        std::cout << x << " no es un numero par\n";
    }

}

int cuenta_string()
{
    std::string texto;
    int contador = 0;
    std::getline(std::cin, texto);
    for (auto i=0; i< texto.length(); ++i) {
        contador ++;
    };
    std::cout << contador;
}

int main()
{
    int numerouser = numero();
    par_o_no(numerouser);
    for (int i = 1; i <= 10; i++) {
        par_o_no(i);
    };
    cuenta_string();

}