#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main() {
   char cadena[128];
   string prueba[10];
   int index=0;

   ifstream fe("tabla.csv");

  // while(!fe.eof()) {
	   fe.getline(cadena, 128, '\n');

	   for(int i=0;i<(int) strlen(cadena);i++){
		   if(cadena[i] != ';' ){
				   prueba[index] = cadena[i];
				   index++;

			  // cout << cadena[i]<< endl;
		   }
	   }
	 // for(int i=0;i<(int)sizeof(prueba);i++){
		cout << sizeof(prueba)<< endl;
	   //}
	   //for(int i=0;i<cadena2.length();i++){

	   //}
   //}
   fe.close();
   return 0;
}

/*int tamanio(string cadena[]){
	string i;
	int contador=0;
	while(i != ""){
		i = cadena[contador];
		contador++;
	}*/

