#include <iostream>
#include <fstream>
#include <list>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>
using namespace std;

int main() {
   char cadena[128];
   //int numero;
  // char val[];
   //char matriz[128][128];

   ifstream fe("tabla.csv");

  // while(!fe.eof()) {
	   fe.getline(cadena, 128, '\n');
	   string std(cadena);
	   //char numPtr[2] = std.length();
	   //numero = atoi(numPtr);
	   for(int i=0;i<std.length();i++){
		   cout << std[i]<< endl;
	   }

	  /* for(int i=0;i<=5;i++){
		   for(int j=0;j<=5;j++){

		   }
	   }*/
	   //for(int i=0;i<cadena2.length();i++){

	   //}
   //}
   fe.close();
   return 0;
}
