#include <iostream>
#include <fstream>
using namespace std;

int main() {
   char cadena[128];
   // Crea un fichero de salida

   ofstream fs("nombre.txt");

   // Enviamos una cadena al fichero de salida:
   fs << "Hola, mundo" << endl;
   fs << "hola denuevo" << endl;

   // Cerrar el fichero,
   // para luego poder abrirlo para lectura:
   fs.close();

   // Abre un fichero de entrada

   ifstream fe("nombre.txt");

   while(!fe.eof()) {
	   fe.getline(cadena, 128);
	   cout << cadena << endl;
   }
   fe.close();


   return 0;
}

 *
 *  Created on: 29/10/2013
 *      Author: Jhymer
 */




