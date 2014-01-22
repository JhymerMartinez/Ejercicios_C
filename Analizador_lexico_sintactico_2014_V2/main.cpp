#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <sstream>
#include <string>
#include<stdio.h>

using namespace std;

const long I = 43;
const long J = 70;
const long EXT_CADENA = 500;
const long EXT_RANGO = 3;
const long EXT_RESULTADOS = 500;

void obtener_matriz(string matriz[I][J], int rango[EXT_RANGO]) {

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
        //para leer linea por linea se usa un archivo auxiliar
        //donde se escribe la linea leida del csv
        //y se la lle nuevamente para ser almacenada en una fila de
        // la matriz
        archivo_tabla.getline(cadena, EXT_CADENA, '\n');
        ofstream archivo_aux("temp.txt");
        archivo_aux << cadena << endl;
        archivo_aux.close();
        ifstream archivo_aux_lec("temp.txt");
        while (!archivo_aux_lec.eof()) {
            //hasta encontrar el ultimo ;
            archivo_aux_lec.getline(cadenaAUX, EXT_CADENA, ',');
            string cadenaSTR(cadenaAUX);
            //se va llenando la matriz con cada linea
            matriz[fila][column] = cadenaSTR;
            column++;
        }
        //almaceno la columna reducida en 1 para posteriores usos
        //se utiliza el if para almacenar el valor de column antes de que count 
        //incremente
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

//genera ambas tablas compactas a partir de la matriz inicial
void obtener_tablas(string matriz[I][J], string matriz_tabla1[42][3], string matriz_tabla2[2281][3], int rango[EXT_RANGO]) {
    string valoresC3[EXT_CADENA];
    int cont = 0;
    ////////////// TABLA 1 ///////////////////
    //se completa c1 con un contador desde 1
    for (int i = 1; i < rango[0]; i++) {
        //conversion entero->string
        stringstream stream_para_c1;
        stream_para_c1 << i;
        matriz_tabla1[i - 1][0] = stream_para_c1.str();
    }

    //recorrido de la matriz para conseguir el numero de valores
    //diferentes de cero
    for (int i = 1; i < rango[0]; i++) {
        for (int j = 1; j < rango[1]; j++) {
            if (matriz[i][j] != "~") {
                cont++;
            }
        }
        //conversion int a string
        stringstream stream_para_c3;
        stream_para_c3 << cont;
        valoresC3[i - 1] = stream_para_c3.str();
        //se regresa cont a cero y se continua con la 
        //siguiente fila
        cont = 0;
    }
    //se completa el resto de la tabla
    for (int i = 0; i < rango[0] - 1; i++) {
        //se pasan los valores almacenados anteriormente a C3
        matriz_tabla1[i][2] = valoresC3[i];
        //se pone en 1 el primer valor de C2
        //solo si es la primera vuelta
        if (i == 0) {
            matriz_tabla1[i][1] = "1";
        } else {
            //caso contrario se continua con el proceso normal
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
            //si el elemento es distinto de cero 
            //entonces lo almacena
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
    //obtiene la frase ingresada por teclado
    cin.getline((char*) palabra.c_str(), 256);
    //retorna el string
    palabra_retorno = palabra.c_str();
    return palabra_retorno.c_str();
}

//este metodo recibe una letra y mediante recorrido por el alfabeto
//que tambien se encuentra en la matriz principal,
//devuelve su ubicacion segun la columna donde se encuentre
int retornar_posicion(string letra, string matriz[I][J], int rango[EXT_RANGO]) {
    for (int j = 1; j < rango[1]; j++) {
        //solo recorre la fila 0 que es donde esta el alfabeto
        if (letra == matriz[0][j]) {
            return j;
            break;
        }
    }
}

//metodo que permite interacccion entre las dos tablas, teniendo como fin el retorno de un valor que se utilizara 
//en el proximo ciclo 
int recuperar_valor(int valor, int verificador, int retorno, string matriz_tabla1[42][3], string matriz_tabla2[2281][3], int rango[EXT_RANGO]) {

    //verificador indica si es la primera vuelta o si ya se han ejecutado otras anteriores
    //cero indica q es la primera
    if (verificador == 0) {
        //se define el numero de intentos para encontrar el elemento
        //buscado
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

void algoritmo_validar(string matriz[I][J], string matriz_tabla1[42][3], string matriz_tabla2[2281][3], int rango[EXT_RANGO], string palabra) {

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
            //en caso de retornar cero muestra mensaje de error y
            //termina el programa
            cout << "\nError: Cadena incorrecta\n" << endl;
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
                cout << "\nError: Cadena incorrecta\n" << endl;
                exit(0);
            }
        }
        cout << "\n" << endl;
        //si se supera el for anterior entonces se extraen 
        //los token obtenidos
        for (int i = 0; i < cont; i++) {
            if (resultados[i] < 0) {
                cout << "Token =  " << resultados[i] << endl;
            }
        }
        cout << "\n" << endl;
    } else {
        cout << "\nError: Cadena incorrecta\n" << endl;
        exit(0);
    }


}

string elim_espacios_finales(string cadena) {
    int pos_ini = 0;
    int longitud;
    int tam_cadena = 0;
    tam_cadena = cadena.size() - 1;
    while (cadena[tam_cadena] == ' '||cadena[tam_cadena] == '\t') {
        tam_cadena--;
    }
    longitud = tam_cadena - pos_ini + 1;
    return cadena.substr(pos_ini, longitud);
}

void presentar_tablas(string matriz[I][J], string matriz_tabla1[42][3], string matriz_tabla2[2281][3], int rango[EXT_RANGO]) {
    /*cout << "********************************** TABLA DE TRANSICIONES **********************************\n" << endl;
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
    }*/
    printf("\n");
}

int main() {
    string matriz[I][J];
    string matriz_tabla1[42][3];
    string matriz_tabla2[2281][3];
    string palabra;
    int rango[EXT_RANGO];

    obtener_matriz(matriz, rango);
    obtener_tablas(matriz, matriz_tabla1, matriz_tabla2, rango);
    presentar_tablas(matriz, matriz_tabla1, matriz_tabla2, rango);

    cout << "Ingrese una palabra o frase: \n\n>>  ";
    
    //quitamos el exceso de espacios finales en caso
    //de que hayan sido agregados
    palabra = elim_espacios_finales(leer_palabra());


    //agregando un espacio en blanco al final
    // para ejecución correcta
    stringstream stream_concat;
    stream_concat << palabra.c_str() << " ";
    palabra = stream_concat.str();
    algoritmo_validar(matriz, matriz_tabla1, matriz_tabla2, rango, palabra);
}






