#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <sstream>
#include <string>
#include<stdio.h>

using namespace std;

const long FILAS = 43;
const long COLUMNAS = 70;
const long FILAS_MATRIZ1 = 42;
const long COLUMNAS_MATRIZ1 = 3;
const long FILAS_MATRIZ2 = 2281;
const long COLUMNAS_MATRIZ2 = 3;
const long EXT_CADENA = 500;
const long EXT_RANGO = 3;
const long EXT_RESULTADOS = 500;

void obtener_matriz(string matriz[FILAS][COLUMNAS], int rango[EXT_RANGO]) {

    char cadena[EXT_CADENA];
    char cadenaAUX[EXT_CADENA];
    int column = 0;
    int fila = 0;
    int x = 0;
    int y = 0;
    int count = 0;

    ifstream archivo_tabla("tabla.csv");
    //lectura del csv
    while (!archivo_tabla.eof()) {
        archivo_tabla.getline(cadena, EXT_CADENA, '\n');
        ofstream archivo_aux("temp.txt");
        archivo_aux << cadena << endl;
        archivo_aux.close();
        ifstream archivo_aux_lec("temp.txt");
        while (!archivo_aux_lec.eof()) {
            archivo_aux_lec.getline(cadenaAUX, EXT_CADENA, ',');
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
    //se guardan los valores para los posteriores recorridos
    rango[0] = x;
    rango[1] = y;

}

void obtener_tablas(string matriz[FILAS][COLUMNAS], string matriz_tabla1[FILAS_MATRIZ1][COLUMNAS_MATRIZ1], string matriz_tabla2[FILAS_MATRIZ2][COLUMNAS_MATRIZ2], int rango[EXT_RANGO]) {
    string valoresC3[EXT_CADENA];
    int cont = 0;
    ////////////// TABLA 1 ///////////////////

    for (int i = 1; i < rango[0]; i++) {

        stringstream stream_para_c1;
        stream_para_c1 << i;
        matriz_tabla1[i - 1][0] = stream_para_c1.str();
    }

    for (int i = 1; i < rango[0]; i++) {
        for (int j = 1; j < rango[1]; j++) {
            if (matriz[i][j] != "~") {
                cont++;
            }
        }

        stringstream stream_para_c3;
        stream_para_c3 << cont;
        valoresC3[i - 1] = stream_para_c3.str();
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
            stringstream stream_para_c2;
            stream_para_c2 << suma;
            matriz_tabla1[i][1] = stream_para_c2.str();
        }
    }

    //////////////// TABLA 2 ///////////////////
    int cont2 = 0;
    for (int i = 1; i < rango[0]; i++) {
        for (int j = 1; j < rango[1]; j++) {

            if (matriz[i][j] != "~") {
                stringstream stream_para_d1;
                stringstream stream_para_d3;
                //conversion entero -> string
                stream_para_d1 << cont2 + 1;
                matriz_tabla2[cont2][0] = stream_para_d1.str();
                //valores de la matriz
                matriz_tabla2[cont2][1] = matriz[i][j];
                //conversion entero -> string
                stream_para_d3 << j;
                matriz_tabla2[cont2][2] = stream_para_d3.str();
                cont2++;
            }
        }
    }
    //se almacena el valor para posteriores recorridos
    rango[2] = cont2;
}

string leer_palabra() {
    string palabra;
    string palabra_retorno;

    cin.getline((char*) palabra.c_str(), 256);

    palabra_retorno = palabra.c_str();
    return palabra_retorno.c_str();
}

int retornar_posicion(string letra, string matriz[FILAS][COLUMNAS], int rango[EXT_RANGO]) {
    for (int j = 1; j < rango[1]; j++) {
        //solo recorre la fila 0 que es donde esta el alfabeto
        if (letra == matriz[0][j]) {
            return j;
            break;
        }
    }
}

int recuperar_valor(int valor, int verificador, int retorno, string matriz_tabla1[FILAS_MATRIZ1][COLUMNAS_MATRIZ1], string matriz_tabla2[FILAS_MATRIZ2][COLUMNAS_MATRIZ2], int rango[EXT_RANGO]) {


    if (verificador == 0) {

        int c3 = atoi(matriz_tabla1[0][2].c_str());
        for (int i = 0; i < c3; i++) {
            //valor es el numero del elemento encontrado en la matriz
            if (valor == atoi(matriz_tabla2[i][2].c_str())) {
                //se retorna un entero
                return atoi(matriz_tabla2[i][1].c_str());
                break;
            }
        }
    } else {
        //procedimiento similar con el resto de elementos de la palabra
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

void algoritmo_validar(string matriz[FILAS][COLUMNAS], string matriz_tabla1[FILAS_MATRIZ1][COLUMNAS_MATRIZ1], string matriz_tabla2[FILAS_MATRIZ2][COLUMNAS_MATRIZ2], int rango[EXT_RANGO], string palabra) {

    string valores_palabra[EXT_CADENA];
    int posicion;
    int contFinal = 0;
    int resultados[EXT_RESULTADOS];


    //En caso de q no se haya ingresado nada
    if (palabra == "" || palabra == " " || palabra == "\t") {
        cout << "\nError: No se ha ingresado ninguna cadena\n" << endl;
        exit(0);
    }

    for (int i = 0; i < palabra.size(); i++) {
        //conversion char -> string
        stringstream stream_caracter;
        stream_caracter << palabra[i];
        posicion = retornar_posicion(stream_caracter.str(), matriz, rango);

        //si se retorna una posicion distinta a cero
        if (posicion != 0) {
            //conversion int -> string
            stringstream stream_posicion;
            stream_posicion << posicion;
            valores_palabra[i] = stream_posicion.str();
            //este contador se usara para luego recorrer el arreglo
            contFinal++;


        } else {

            cout << "\nError: Cadena incorrecta\n" << endl;
            exit(0);
            break;
        }
    }


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

        for (int i = 0; i < cont; i++) {
            if (resultados[i] == 0) {
                cout << "\nError: Cadena incorrecta\n" << endl;
                exit(0);
            }
        }
        cout << "\n" << endl;

        int almacenador_tokens[50];
        int contador = 0;
        for (int i = 0; i < cont; i++) {
            if (resultados[i] == -1) {
                cout << "Token =  " << resultados[i] << " {TIPO DE DATO}" << endl;
                almacenador_tokens[contador] = resultados[i];
                contador++;
            }
            if (resultados[i] == -2) {
                cout << "Token =  " << resultados[i] << " {NOMBRE DE VARIABLE}" << endl;
                almacenador_tokens[contador] = resultados[i];
                contador++;
            }
            if (resultados[i] == -3) {
                cout << "Token =  " << resultados[i] << " {CARACTER}" << endl;
                almacenador_tokens[contador] = resultados[i];
                contador++;
            }
            if (resultados[i] == -4) {
                cout << "Token =  " << resultados[i] << " {DECIMAL}" << endl;
                almacenador_tokens[contador] = resultados[i];
                contador++;
            }
            if (resultados[i] == -5) {
                cout << "Token =  " << resultados[i] << " {ENTERO}" << endl;
                almacenador_tokens[contador] = resultados[i];
                contador++;
            }
            if (resultados[i] == -6) {
                cout << "Token =  " << resultados[i] << " {IGUAL}" << endl;
                almacenador_tokens[contador] = resultados[i];
                contador++;
            }
            if (resultados[i] == -7) {
                cout << "Token =  " << resultados[i] << " {PUNTO Y COMA}" << endl;
                almacenador_tokens[contador] = resultados[i];
                contador++;
            }

        }


        //################################### verificacion sintactica ###################################


        if ((almacenador_tokens[0] == -1 && almacenador_tokens[1] == -2 && almacenador_tokens[2] == -7) ||
                (almacenador_tokens[0] == -1 && almacenador_tokens[1] == -2 && almacenador_tokens[2] == -6 &&
                (almacenador_tokens[3] == -3 || almacenador_tokens[3] == -4 || almacenador_tokens[3] == -5) &&
                almacenador_tokens[4] == -7)) {

            cout << "\nLa sintaxis es correcta\n" << endl;

        } else {
            cout << "\nERROR de sintaxis\n" << endl;

        }
    } else {
        cout << "\n" << endl;
        cout << "\nError: Cadena incorrecta\n" << endl;
        exit(0);
    }

    //#######################################################################################################

}

string elim_espacios_finales(string cadena) {
    int pos_ini = 0;
    int longitud;
    int tam_cadena = 0;
    tam_cadena = cadena.size() - 1;
    while (cadena[tam_cadena] == ' ' || cadena[tam_cadena] == '\t') {
        tam_cadena--;
    }
    longitud = tam_cadena - pos_ini + 1;
    return cadena.substr(pos_ini, longitud);
}

void presentar_tablas(string matriz[FILAS][COLUMNAS], string matriz_tabla1[FILAS_MATRIZ1][COLUMNAS_MATRIZ1], string matriz_tabla2[FILAS_MATRIZ2][COLUMNAS_MATRIZ2], int rango[EXT_RANGO]) {
    cout << "********************************** TABLA DE TRANSICIONES **********************************\n" << endl;
    for (int i = 1; i < rango[0]; i++) {
        for (int j = 1; j < rango[1]; j++) {

            cout << matriz[i][j].c_str() << "\t";
        }
        printf("\n");
    }

    printf("\n");
    cout << "***** TABLA 1 *****\n" << endl;
    for (int i = 0; i < rango[0] - 1; i++) {
        cout << matriz_tabla1[i][0].c_str() << "\t" << matriz_tabla1[i][1].c_str() << "\t" << matriz_tabla1[i][2].c_str() << "\n";
    }
    cout << "\n" << endl;
    cout << "***** TABLA 2 *****\n" << endl;
    for (int i = 0; i < rango[2]; i++) {
        cout << matriz_tabla2[i][0].c_str() << "\t" << matriz_tabla2[i][1].c_str() << "\t" << matriz_tabla2[i][2].c_str() << "\n";
    }
    printf("\n");
}

int main() {
    string matriz[FILAS][COLUMNAS];
    string matriz_tabla1[FILAS_MATRIZ1][COLUMNAS_MATRIZ1];
    string matriz_tabla2[FILAS_MATRIZ2][COLUMNAS_MATRIZ2];
    string palabra;
    int rango[EXT_RANGO];

    obtener_matriz(matriz, rango);
    obtener_tablas(matriz, matriz_tabla1, matriz_tabla2, rango);
    presentar_tablas(matriz, matriz_tabla1, matriz_tabla2, rango);

    cout << "Ingrese una palabra o frase: \n\n>>  ";

    palabra = elim_espacios_finales(leer_palabra());

    //agregando un espacio en blanco al final
    // para ejecución correcta
    stringstream stream_concat;
    stream_concat << palabra.c_str() << " ";
    palabra = stream_concat.str();
    algoritmo_validar(matriz, matriz_tabla1, matriz_tabla2, rango, palabra);
}






