#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

using namespace std;
// Configuraciones de tabla de transiciones
/*const int fila = 30;
const int columna = 72;
const int filas_tabla2 = 259;*/
const int FILA = 43;
const int COLUMNA = 70;
const int FILAS_TABLA2 = 2281;

void lee_guarda_datos(string tabla[][COLUMNA]){
    int f = 0;
    ifstream  data("tabla.csv");
    string line;
    while(getline(data,line)){
        int c = 0;
        stringstream  lineStream(line);
        string cell;
        while(getline(lineStream,cell,',')){
            tabla[f][c] = cell;
            c++;
        }
        f++;
    }
}

void presenta_matriz(string tabla[][COLUMNA]){
    cout << "--- TABLA DE TRANSICIONES ---" << endl;
    for (int f=0; f<FILA; f++){
        for(int c = 0; c<COLUMNA; c++){
            cout << tabla[f][c] << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

void presenta_matriz2(int tabla1[][3]){
    cout << "---- TABLA 1 ----" << endl;
    int temp = 0;
    for (int f=0; f<FILA-1; f++){
        for(int c = 0; c<3; c++){
            cout << tabla1[f][c] << "\t";
        }
        /*temp = temp + tabla1[f][2];
        cout << temp;*/
        cout << "\n";
    }
    cout << "\n";
}

void presenta_matriz3(int tabla2[][3]){
    cout << "---- TABLA 2 ----" << endl;
    for (int f=0; f<FILAS_TABLA2; f++){
        for(int c = 0; c<3; c++){
            cout << tabla2[f][c] << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

void crea_tabla_compacta(string tabla[][COLUMNA], int tabla1[][3], int tabla2[][3]){
    tabla1[0][1] = 1; //asigna valor inicial de 1 a C2_tabla1
    int i2 = 0; //contador de 0 - 24 que servira para filas de tabla2
    for(int f2 = 1; f2 < FILA; f2++){ //recorre las filas de tabla
        int i = 0; //contador que servira para sumar el valor de las celdas validas de tabla
        tabla1[f2-1][0] = atoi(tabla[f2][0].c_str()); //asigna valor a celda de C1 de tabla1
        for(int c2 = 1; c2 < COLUMNA; c2++){ //recorre las columnas de tabla
            if(tabla[f2][c2] != "~"){ //condiciona a que sean diferentes de 'a'
                tabla2[i2][0] = i2+1; //asigna valores secuenciales (1-24) a celda C1 de tabla2
                tabla2[i2][1] = atoi(tabla[f2][c2].c_str()); //asigna celdas validas de tabla a C2 de tabla2
                tabla2[i2][2] = c2; //asigna la posicion de la columna del elemento C2 de tabla2
                i++;
                i2++;
            }
        }
        tabla1[f2-1][2] = i; //asigna valor de celdas validas en C3 de tabla1
        if(f2 < FILA-1){ //control para sobrecarga en indice de C2 en tabla1
            tabla1[f2][1] = tabla1[f2-1][1] + tabla1[f2-1][2]; //asigna valor a C2 en tabla1
        }
    }
}

void cambia_tabla(int tabla1[][3], int tabla2[][3], int c2_tabla1, int c3_tabla1, int cadena_buscar[], int cont_indice, int length){
    int cuenta_intentos = 0;

    for(int f2 = 0; f2 < FILAS_TABLA2; f2++){
        if(c2_tabla1 == tabla2[f2][0]){
            if(cadena_buscar[cont_indice] == tabla2[f2][2]){
                if(tabla2[f2][1] < 0){
                    cout << "(Estados)";
                    cout << "\nCADENA ACEPTADA" << "\n(Token: " << tabla2[f2][1] << ")\n" << endl;
                    if (length == cont_indice+1){
                        exit(0);
                    }else{
                        cambia_tabla(tabla1, tabla2, tabla1[0][1], tabla1[0][2], cadena_buscar, cont_indice, length);
                    }
                }else{
                    for(int f1 = 0; f1 < FILA-1; f1++){
                        if(tabla2[f2][1] == tabla1[f1][0]){
                            cout << tabla1[f1][0] << " ";
                            cont_indice++;
                            cambia_tabla(tabla1, tabla2, tabla1[f1][1], tabla1[f1][2], cadena_buscar, cont_indice, length);
                        }
                    }
                }
            }else{
                c2_tabla1++;
                cuenta_intentos++;
                if(cuenta_intentos == c3_tabla1){
                    cout << "CADENA RECHAZADA" <<  endl;
                }
            }
        }
    }
}

void verifica_cadena(string tabla[][COLUMNA], int tabla1[][3], int tabla2[][3]){
    //codigo para extraer indices de la tabla
    string str;
    cout << "Ingresa tu cadena: ";
    cin.getline((char*)str.c_str(), 256);

    string cade[strlen(str.c_str())];
    for(int i = 0; i < strlen(str.c_str()); i++){
        if(str[i] == 32){
            cade[i] = "32";
        }else if(str[i] == 9){
            cade[i] = "9";
        }else{
            cade[i] = str[i];
        }
    }
    int indice=0;
    int cadena_buscar[strlen(str.c_str())];
    for(int c = 0; c < strlen(str.c_str()); c++){
        for(int i = 1; i < COLUMNA; i++){
            if (tabla[0][i] == cade[c]){
                cadena_buscar[indice] = i;
                indice++;
            }
        }
    }
    //fin de codigo para extraer indices de tabla

    int cont_indice = 0;
    int length = sizeof cadena_buscar / sizeof *cadena_buscar;
    cout << "0 ";
    cambia_tabla(tabla1, tabla2, tabla1[0][1], tabla1[0][2], cadena_buscar, cont_indice, length);
}

int main(){
    string tabla[FILA][COLUMNA];
    int tabla1[FILA-1][3];
    int tabla2[FILAS_TABLA2][3];
    lee_guarda_datos(tabla);
    crea_tabla_compacta(tabla, tabla1, tabla2);
    presenta_matriz(tabla);
    presenta_matriz2(tabla1);
    presenta_matriz3(tabla2);
    verifica_cadena(tabla, tabla1, tabla2);
 }
