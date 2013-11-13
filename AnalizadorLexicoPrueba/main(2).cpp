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

using namespace std;

const int numeroEstados = 11;
const int numeroEventos = 12;
static char alfabeto[10]={'+','-','*','/','d','o','u','b','l','e'};
int final[6]={2,3,4,5,7,11};
static int transicion[numeroEstados][numeroEventos];
int contEs=0;
static int val=0;
static int tabla1[numeroEstados][3];


//leer el archivo
void leerArchivo(){
    FILE *archivo;
    char linea[200];
    char *token;
    char separador[]=";";
    archivo = fopen("C:\\Users\\Erika\\Documents\\NetBeansProjects\\AnalizadorLexicoPrueba\\matriz.csv","r");
    if (archivo == NULL){
            printf("\nError de apertura del archivo. \n\n");
    }else{
        printf("\nTABLA DE TRANSICIÓN\n");
        while (fscanf(archivo," %[^\n]",&linea)==1){
            token= strtok(linea,separador);
                int contColumnas=0;
                while(token != NULL){
                    val=atoi(token);
                    transicion[contEs][contColumnas]=val;
                    printf("%d\t",transicion[contEs][contColumnas]);
                    contColumnas++;
                    token = strtok(NULL, separador);
                }
            contEs++;
            printf("\n");
        }
    }
    fclose(archivo);
}

void generarTabla1(){
// columna 3
    int contadorElementos;
    for (int j = 0; j < numeroEstados; j++) {
        contadorElementos = 0;
        for (int k = 0; k < numeroEventos; k++) {
            if (transicion[j][k]!= 0){
                contadorElementos++;
            }
        }
        tabla1[j][2] = contadorElementos;
        //cout << contadorElementos<<endl;
    }
// columna 1 y columna 2
    int estados=1;
    tabla1[0][1] = 1;
    tabla1[0][0] = estados;
    for (int j = 1; j < numeroEstados; j++) {
        tabla1[j][0] = estados+1;
        estados++;
        tabla1[j][1] = tabla1[j-1][1]+tabla1[j-1][2];
//            cout<<estados<<tabla1[j][1]<<endl;
    }

////    presentacion tabla1
    cout << "\n Tabla 1"<< endl;
    for (int i = 0; i < numeroEstados; i++) {
        for (int j = 0; j < 3; j++) {
            cout<<tabla1[i][j]<< "\t";
        }
        cout << "\n";
    }
}

//    tabla2
void generarTabla2(){
//    columna 1
    int totalElementos;
    totalElementos = (tabla1[10][1]+tabla1[10][2])-1;
    int tabla2[80][3];
//    cout<<totalElementos<<endl;  nuemro total de elementos
//    columna 1
    for (int i = 1; i < totalElementos+1; i++) {
        tabla2[i-1][0] = i;
    }
//    columna 2 y columna 3
    int pos =0;
    for (int j = 0; j < numeroEstados; j++) {
        for (int k = 0; k < numeroEventos; k++) {
            if (transicion[j][k]!=0) {
                tabla2[pos][1] = transicion[j][k];
                tabla2[pos][2] = k+1;
//                cout << tabla2[pos][1] << endl;
                pos++;
            }
        }
    }

//    presentacion tabla1
    cout<<"\n Tabla 2"<<endl;
    for (int i = 0; i < totalElementos; i++) {
        for (int j = 0; j < 3; j++) {
            cout<<tabla2[i][j]<< "\t";
        }
        cout << "\n";
    }
}

void validarFrase(char* linea){
    string cade[strlen(linea)];
    for(int i = 0; i < strlen(linea); i++){
        if(linea[i] == 32){
            cade[i] = "32";
        }else if(linea[i] == 9){
            cade[i] = "9";
        }else{
            cade[i] = linea[i];
        }
    }
//   obtener indice
    int indice=0;
    int cadena_buscar[strlen(linea)];
    cout<<strlen(linea)<<endl;
    for(int d = 0; d < strlen(linea); d++){
        for(int i = 0; i < 12; i++){            
            cout << "alf "<< alfabeto[i] << "    letra\t "<<cade[d]<< "\n";
            if (alfabeto[i]==cade[d]){   
            cout << "alfabeto "<< alfabeto[i] << "    letra\t "<<cade[d]<< "\n";   
                cadena_buscar[indice] = i+1;
//                cout<<"indice "<<cadena_buscar[indice]<<" i + 1 "<< (i+1) <<endl;
                indice++;
            }
        }
    }
    
}

int main() {
    leerArchivo();
    cout<<"\n"<<endl;
    generarTabla1();
    cout<<"\n"<<endl;
    generarTabla2();
    char linea[200];
    cout<<" Ingrese la frase "<<endl;
    cin.getline((char*)linea, 256);
    validarFrase(linea);
    return 0;
}

