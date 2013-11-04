#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int *devuelve_arreglo() {
    int *arreglo; // declaramos en apuntador 
    //int tamano = 4; // asignamos el tamaño del vector 
    arreglo = (int*) malloc(4); // se crea el arreglo 
    arreglo[0] = 1; // asignamos valores 
    arreglo[1] = 2; // asignamos valores 
    arreglo[2] = 3; // asignamos valores 
    arreglo[3] = 4; // asignamos valores 
    return arreglo;
}

int main() {
    int *arreglo; // declaramos el arreglo 
    arreglo = devuelve_arreglo(); // llamamos a la funcion 
    cout<<arreglo[0]<<endl;
    cout<<arreglo[1]<<endl;
    cout<<arreglo[2]<<endl;
    // aquí puedes usar los elementos del arreglo
}