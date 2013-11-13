/*
 * File:   main.cpp
 * Author: Erika
 *
 * Created on 9 de noviembre de 2013, 08:49 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;
//codigo de Cecibel Chamba
const int numeroEstados = 11;
const int numeroEventos = 12;
static char alfabeto[10] = {'+', '-', '*', '/', 'd', 'o', 'u', 'b', 'l', 'e'};
int final[6] = {2, 3, 4, 5, 7, 11};
static int transicion[numeroEstados][numeroEventos];
int contEs = 0;
static int val = 0;
static int tabla1[numeroEstados][3];
int tabla2[80][3];
static int indice[50];

//leer el archivo de Cecibel Chamba

void leerArchivo() {
    FILE *archivo;
    char linea[200];
    char *token;
    char separador[] = ";";
    archivo = fopen("C:\\Users\\jhymer\\Documents\\NetBeansProjects\\AnalizadorLexicoPrueba\\matriz.csv", "r");
    if (archivo == NULL) {
        printf("\nError de apertura del archivo. \n\n");
    } else {
        printf("\nTABLA DE TRANSICIÓN\n");
        while (fscanf(archivo, " %[^\n]", &linea) == 1) {
            token = strtok(linea, separador);
            int contColumnas = 0;
            while (token != NULL) {
                val = atoi(token);
                transicion[contEs][contColumnas] = val;
                printf("%d\t", transicion[contEs][contColumnas]);
                contColumnas++;
                token = strtok(NULL, separador);
            }
            contEs++;
            printf("\n");
        }
    }
    fclose(archivo);
}

//codigo de Erika Masache
void generarTabla1() {
    // columna 3
    int contadorElementos;
    for (int j = 0; j < numeroEstados; j++) {
        contadorElementos = 0;
        for (int k = 0; k < numeroEventos; k++) {
            if (transicion[j][k] != 0) {
                contadorElementos++;
            }
        }
        tabla1[j][2] = contadorElementos;
        //cout << contadorElementos<<endl;
    }
    // columna 1 y columna 2
    int estados = 1;
    tabla1[0][1] = 1;
    tabla1[0][0] = estados;
    for (int j = 1; j < numeroEstados; j++) {
        tabla1[j][0] = estados + 1;
        estados++;
        tabla1[j][1] = tabla1[j - 1][1] + tabla1[j - 1][2];
        //            cout<<estados<<tabla1[j][1]<<endl;
    }

    ////    presentacion tabla1
    cout << "\n Tabla 1" << endl;
    for (int i = 0; i < numeroEstados; i++) {
        for (int j = 0; j < 3; j++) {
            cout << tabla1[i][j] << "\t";
        }
        cout << "\n";
    }
}

// Codigo de Erika Masache   tabla2
int totalElementos;

void generarTabla2() {
    //    columna 1    
    totalElementos = (tabla1[numeroEstados-1][1] + tabla1[numeroEstados-1][2]) - 1;

    //    cout<<totalElementos<<endl;  nuemro total de elementos
    //    columna 1
    for (int i = 1; i < totalElementos + 1; i++) {
        tabla2[i - 1][0] = i;
    }
    //    columna 2 y columna 3
    int pos = 0;
    for (int j = 0; j < numeroEstados; j++) {
        for (int k = 0; k < numeroEventos; k++) {
            if (transicion[j][k] != 0) {
                tabla2[pos][1] = transicion[j][k];
                tabla2[pos][2] = k + 1;
                //                cout << tabla2[pos][1] << endl;
                pos++;
            }
        }
    }
    //    presentacion tabla2
    cout << "\n Tabla 2" << endl;
    for (int i = 0; i < totalElementos; i++) {
        for (int j = 0; j < 3; j++) {
            cout << tabla2[i][j] << "\t";
        }
        cout << "\n";
    }
}
int contadorFrase = 0;


// Codigo de Veronica Chimbo
void obtenerIndice(char linea[200]) {
    for (int j = 0; j < strlen(linea); j++) {
        for (int h = 0; h < strlen(alfabeto); h++) {
            if (linea[j] == alfabeto[h]) {
                indice[j] = h + 1;
                //                cout << h + 1 << "\t \n";
                contadorFrase++;
            }
        }
//       codigo de Richar Leon
        if (linea[j] == 32) {
            indice[j] = 11;
            //            cout << 11 << "\t \n";
            contadorFrase++;
        }
        if (linea[j] == 9) {
            indice[j] = 12;
            //            cout << 12 << "\t \n";
            contadorFrase++;
        }
    }
    //        cout<<"\n"<<cont<<endl;
}
// una vez obtenidos los indices verifico la cadena


//Codigo de Erika Masache y Richar Leon
void validarFrase() {
    totalElementos = (tabla1[10][1] + tabla1[10][2]) - 1;
    int t1c1 = tabla1[0][0];
    int t1c2 = tabla1[0][1];
    int t1c3 = tabla1[0][2];
    int t2c1 = 0;
    int t2c2 = 0;
    int t2c3 = 0;
    int intentos = 0;
    for (int i = 0; i < contadorFrase; i++) {
                      //  cout << "\t" << t1c1 << "\t" << t1c2 << "\t" << t1c3 << endl;
        //                cout << "\t" << t2c1 << "\t" << t2c2 << "\t" << t2c3 << endl;
        t2c1 = t1c2;
        intentos = t1c3;
        for (int j = t2c1 - 1; j < (t2c1 + intentos); j++) {
            t2c1 = t1c2;
            t2c2 = tabla2[j - 1][1];
            t2c3 = tabla2[j - 1][2];
            if (indice[i] == t2c3) {
                t1c1 = t2c2;
                ;
                t1c2 = tabla1[t2c2 - 1][1];
                t1c3 = tabla1[t2c2 - 1][2];
                break;
            }

        }
        if (t2c2 < 0) {
            t1c1 = tabla1[0][0];
            t1c2 = tabla1[0][1];
            t1c3 = tabla1[0][2];
            cout << "Token " << t2c2 << endl;
        }

    }
}

int main() {
    leerArchivo();
    cout << "\n" << endl;
    generarTabla1();
    cout << "\n" << endl;
    generarTabla2();
    char linea[200];
    cout << " Ingrese la frase " << endl;
    cin.getline((char*) linea, 256);
    obtenerIndice(linea);
    validarFrase();
    return 0;
}

