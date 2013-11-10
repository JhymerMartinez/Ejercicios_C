#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <sstream> 
#include <string> 
#include<stdio.h>

using namespace std;

void obtener_matriz(string matriz[50][50], int rango[3]) {

    char cadena[128];
    char cadenaAUX[128];
    int column = 0;
    int fila = 0;
    int x = 0;
    int y = 0;
    int count = 0;

    ifstream archivo_tabla("tabla.csv");

    while (!archivo_tabla.eof()) {

        archivo_tabla.getline(cadena, 128, '\n');
        ofstream archivo_aux("auxtt.txt");
        archivo_aux << cadena << endl;
        archivo_aux.close();

        ifstream archivo_aux_lec("auxtt.txt");

        while (!archivo_aux_lec.eof()) {
            archivo_aux_lec.getline(cadenaAUX, 128, ';');
            string cadenaSTR(cadenaAUX);
            matriz[fila][column] = cadenaSTR;
            column++;
        }
        if (count == 0) {
            y = column - 1;
        }
        x = fila;
        fila++;
        count++;
        column = 0;
        archivo_aux_lec.close();
    }
    archivo_tabla.close();
    rango[0] = x;
    rango[1] = y;
    //cout <<"x= "<<x<<"y= "<<y<<endl;
    /**x = 19 
     *y = 17
     * para recorrerlos hasta x=18 y=16*/
    /*for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cout << "[" << i << "]" << "[" << j << "] => " << matriz[i][j] << "..." << endl;
        }
    }*/

}

void obtener_tablas(string matriz[50][50], string matriz_tabla1[50][50], string matriz_tabla2[50][50], int rango[3]) {
    //string matriz_tabla1[50][50];
    //string matriz_tabla2[50][50];
    string valoresC3[50];
    int cont = 0;


    for (int i = 1; i < rango[0]; i++) {
        stringstream stream;
        stream << i;
        matriz_tabla1[i - 1][0] = stream.str();
    }

    for (int i = 1; i < rango[0]; i++) {
        for (int j = 1; j < rango[1]; j++) {
            if (matriz[i][j] != "0") {
                cont++;
            }
        }
        stringstream stream;
        stream << cont;
        valoresC3[i - 1] = stream.str();
        cont = 0;
    }

    for (int i = 0; i < rango[0] - 1; i++) {

        matriz_tabla1[i][2] = valoresC3[i];
        if (i == 0) {
            matriz_tabla1[i][1] = "1";
        } else {
            int aux1 = atoi(matriz_tabla1[i - 1][1].c_str());
            int aux2 = atoi(matriz_tabla1[i - 1][2].c_str());
            int suma = aux1 + aux2;
            stringstream stream;
            stream << suma;
            matriz_tabla1[i][1] = stream.str();
        }
        //matriz_tabla1 completa  

        //cout << matriz_tabla1[i][0] << "    " << matriz_tabla1[i][1] << "    " << matriz_tabla1[i][2] << endl;
    }
    int cont2 = 0;
    for (int i = 1; i < rango[0]; i++) {
        for (int j = 1; j < rango[1]; j++) {
            if (matriz[i][j] != "0") {
                stringstream stream;
                stringstream stream2;
                stream << cont2 + 1;
                matriz_tabla2[cont2][0] = stream.str();
                matriz_tabla2[cont2][1] = matriz[i][j];
                stream2 << j;
                matriz_tabla2[cont2][2] = stream2.str();
                cont2++;
            }


        }
    }
    //
    rango[2] = cont2;
    /*for (int i = 0; i < rango[2]; i++) {
        cout << matriz_tabla2[i][0]<<"  "<<matriz_tabla2[i][1] <<"  "<< matriz_tabla2[i][2]<< endl;
    }*/

}

string leer_palabra() {
    string palabra;
    string palabra2;
    cin.getline((char*) palabra.c_str(), 256);
    //cout << palabra.c_str() << endl;
    palabra2 = palabra.c_str();
    return palabra2.c_str();
}

int retornar_posicion(string letra, string matriz[50][50], int rango[3]) {

    for (int j = 1; j < rango[1]; j++) {
        if (letra == matriz[0][j]) {
            return j;
            break;
        }
    }
}

void algoritmo_validar(string matriz[50][50], string matriz_tabla1[50][50], string matriz_tabla2[50][50], int rango[3], string palabra) {
    
    string valores_palabra[50];
    int val;
    if (palabra == "") {
        cout << "No se ha ingresado ninguna palabra" << endl;
        
    }
    for (int i = 0; i < palabra.size(); i++) {
        stringstream stream;
        stream << palabra[i];
        val = retornar_posicion(stream.str(), matriz, rango);

        if (val != 0) {
            stringstream valStr;
            valStr << val;
            valores_palabra[i] = valStr.str();
        } else {
            cout << "Palabra incorrecta" << endl;
            break;
        }
    }

}

int main() {
    string matriz[50][50];
    string matriz_tabla1[50][50];
    string matriz_tabla2[50][50];
    string palabra;
    int rango[3];
    
    obtener_matriz(matriz, rango);
    obtener_tablas(matriz, matriz_tabla1, matriz_tabla2, rango);

    cout << "Ingrese una palabra o frase:" << endl;
    //string palabra(leer_palabra());
    palabra = leer_palabra();

    //cout << palabra.size()<<endl;
    /*
    for(int i=0;i<palabra.size();i++){
        cout <<palabra[i]<<endl;
    }*/

    algoritmo_validar(matriz, matriz_tabla1, matriz_tabla2, rango, palabra);


    for (int i = 0; i < rango[0]; i++) {
        cout << matriz_tabla1[i][0]<<"  "<<matriz_tabla1[i][1] <<"  "
                << matriz_tabla1[i][2]<< endl;
    }
    
      for (int i = 0; i < rango[2]; i++) {
        cout << matriz_tabla2[i][0]<<"  "<<matriz_tabla2[i][1] <<"  "
                << matriz_tabla2[i][2]<< endl;
    }
    //cout <<"x= "<<rango[0]<<"y= "<<rango[1]<<endl;
    /*for (int i = 0; i < rango[0]; i++) {
         for (int j = 0; j < rango[1]; j++) {
             cout << "[" << i << "]" << "[" << j << "] => " << matriz[i][j] << "..." << endl;
         }
     }*/
}






