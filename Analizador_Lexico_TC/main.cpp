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

}

void obtener_tablas(string matriz[50][50], string matriz_tabla1[50][50], string matriz_tabla2[50][50], int rango[3]) {
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
    rango[2] = cont2;
}

string leer_palabra() {
    string palabra;
    string palabra2;

    cin.getline((char*) palabra.c_str(), 256);
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

int recuperar_valor(int valor, int verificador, int retorno, string matriz_tabla1[50][50], string matriz_tabla2[50][50], int rango[3]) {


    if (verificador == 0) {
        //int c1 = atoi(matriz_tabla1[0][0].c_str());
        //int c2 = atoi(matriz_tabla1[0][1].c_str());
        int c3 = atoi(matriz_tabla1[0][2].c_str());
        //int d1 = atoi(matriz_tabla2[0][0].c_str());
        //int d2 = atoi(matriz_tabla2[0][1].c_str());
        //int d3 = atoi(matriz_tabla2[0][2].c_str());
        for (int i = 0; i < c3; i++) {
            if (valor == atoi(matriz_tabla2[i][2].c_str())) {
                return atoi(matriz_tabla2[i][1].c_str());
                break;
            }
        }
    } else {
        int c1 = retorno;
        int c2;
        int c3;
        for (int i = 0; i < rango[1]; i++) {
            if (c1 == atoi(matriz_tabla1[i][0].c_str())) {
                c2 = atoi(matriz_tabla1[i][1].c_str());
                c3 = atoi(matriz_tabla1[i][2].c_str());
                break;
            }
        }
        int aux = c2;

        for (int i = 0; i < c3; i++) {
            if (valor == atoi(matriz_tabla2[aux - 1][2].c_str())) {
                return atoi(matriz_tabla2[aux - 1][1].c_str());
            }
            aux++;
        }

    }
}

void algoritmo_validar(string matriz[50][50], string matriz_tabla1[50][50], string matriz_tabla2[50][50], int rango[3], string palabra) {

    string valores_palabra[50];
    int val;
    int contFinal = 1;
    int resultados[30];
    if (palabra == "" || palabra == " " || palabra == "\t") {
        cout << "No se ha ingresado ninguna palabra" << endl;
        exit(0);
    }
    for (int i = 0; i < palabra.size(); i++) {
        stringstream stream;
        stream << palabra[i];
        val = retornar_posicion(stream.str(), matriz, rango);

        if (val != 0) {
            stringstream valStr;
            valStr << val;
            valores_palabra[i] = valStr.str();
            contFinal++;
        } else {
            cout << "Sintaxis incorrecta" << endl;
            exit(0);
            break;
        }
    }
    //contFinal guarda extension de la palabra
    //valores_palabra[i] contiene la lista de numeros de cada caracter de la palbra ingresada
    int retorno = 0;
    int verificador = 0;
    int cont = 0;
    bool band = false;
    for (int i = 0; i < contFinal; i++) {
        int valor = atoi(valores_palabra[i].c_str());
        resultados[cont] = recuperar_valor(valor, verificador, retorno, matriz_tabla1, matriz_tabla2, rango);
        verificador++;
        if (resultados[cont] > 0) {
            retorno = resultados[cont];
        }
        if (resultados[cont] < 0) {
            retorno = resultados[cont];
            verificador = 0;
            retorno = 0;
        }
        if (resultados[cont] == 0) {
            
            break;
        }
        cont++;

    }
    
    //en caso de existir un cero al final del arreglo
    if (resultados[cont - 1] < 0) {
        //para evaluar si existe algun valor con cero
        //entonces se presenta mensaje y finaliza el programa
         for (int i = 0; i < cont; i++) {
            if (resultados[i] == 0) {
                cout << "Sintaxis incorrecta" << endl;
                exit(0);
            }
        }
        
        //si se supera el for anterior entonces se extraen 
         //los token obtenidos
        for (int i = 0; i < cont; i++) {
            if (resultados[i] < 0) {
                cout << "Token =  " << resultados[i] << endl;
            }
        }
    } else {
        cout << "Sintaxis incorrecta" << endl;
        exit(0);
    }


}

void presentar_tablas(string matriz[50][50], string matriz_tabla1[50][50], string matriz_tabla2[50][50], int rango[3]) {
    cout << "***** TABLA GENERAL *****" << endl;
    for (int i = 1; i < rango[0]; i++) {
        for (int j = 1; j < rango[1]; j++) {
            printf("%s   ", matriz[i][j].c_str());
        }
        printf("\n");
    }

    printf("\n");
    cout << "***** TABLA 1 *****" << endl;
    for (int i = 1; i < rango[0] - 1; i++) {
        printf("%s      %s      %s\n", matriz_tabla1[i][0].c_str(), matriz_tabla1[i][1].c_str(), matriz_tabla1[i][2].c_str());
    }
    cout << "\n" << endl;
    cout << "***** TABLA 2 *****" << endl;
    for (int i = 0; i < rango[2]; i++) {
        printf("%s      %s      %s\n", matriz_tabla2[i][0].c_str(), matriz_tabla2[i][1].c_str(), matriz_tabla2[i][2].c_str());

    }
    printf("\n");
}

int main() {
    string matriz[50][50];
    string matriz_tabla1[50][50];
    string matriz_tabla2[50][50];
    string palabra;
    int rango[3];

    obtener_matriz(matriz, rango);
    obtener_tablas(matriz, matriz_tabla1, matriz_tabla2, rango);
    presentar_tablas(matriz, matriz_tabla1, matriz_tabla2, rango);

    cout << "Ingrese una palabra o frase:" << endl;
    palabra = leer_palabra();
    
    //en caso de q no se ingrese un espacio o tabulador al final
    char aux = palabra[palabra.size()-1];
    stringstream s1;
    s1 << aux;
    if (s1.str() != " " && s1.str() != "        ") {
        stringstream ss;
        ss << palabra.c_str() << " ";
        palabra = ss.str();
        algoritmo_validar(matriz, matriz_tabla1, matriz_tabla2, rango, palabra);
    } else {
        algoritmo_validar(matriz, matriz_tabla1, matriz_tabla2, rango, palabra);
    }
}






