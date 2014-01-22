#include <iostream>
#include <string>
#include <string.h>      /* printf, fgets */
#include <stdlib.h>

using namespace std;

bool simular_af(char *c) {
     int pos = 0; //posicion del caracter a evaluar en la cadena
     int state = 0; //estado del automata
     int longitud = strlen(c);

     while(pos < longitud) {
            switch(state) {
//-----------------------------------------------------------------------------
                          case 0://estado 0
                          switch(c[pos]) {
                                         case 'i':
                                              state = 1;
                                              break;
                                         case 'p':
                                              state = 4;
                                              break;
                                         case '-':
                                              state = 16;
                                              break;
                                         case '=':
                                              state = 18;
                                              break;
                                         default:
                                              return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 1://estado 1
                          switch(c[pos]){
                                          case 'n':
                                               state = 2;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 2://estado 2
                          switch(c[pos]){
                                          case 't':
                                               cout << " -1 "<<endl;
                                               state = 3;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 3://estado 3
                          switch(c[pos]){
                                          case ' ':
                                               state = 0;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 4://estado 4
                          switch(c[pos]){
                                          case 'u':
                                               state = 5;
                                               break;
                                          case 'r':
                                               state = 10;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 5://estado 5
                          switch(c[pos]){
                                          case 'b':
                                               state = 6;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 6://estado 6
                          switch(c[pos]){
                                          case 'l':
                                               state = 7;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 7://estado 7
                          switch(c[pos]){
                                          case 'i':
                                               state = 8;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 8://estado 8
                          switch(c[pos]){
                                          case 'c':
                                               cout <<" -2 "<<endl;
                                               state = 9;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 9://estado 9
                          switch(c[pos]){
                                          case ' ':
                                               state = 0;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 10://estado 10
                          switch(c[pos]){
                                          case 'i':
                                               state = 11;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 11://estado 11
                          switch(c[pos]){
                                          case 'v':
                                               state = 12;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 12://estado 12
                          switch(c[pos]){
                                          case 'a':
                                               state = 13;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 13://estado 13
                          switch(c[pos]){
                                          case 't':
                                               state = 14;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 14://estado 14
                          switch(c[pos]){
                                          case 'e':
                                               cout << " -3  "<<endl;
                                               state = 15;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 15://estado 15
                          switch(c[pos]){
                                          case ' ':
                                               state = 0;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 16://estado 16
                          switch(c[pos]){
                                          case '-':
                                               state = 17;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 17://estado 17
                          switch(c[pos]){
                                          case ' ':
                                               cout << " -4  "<<endl;
                                               state = 0;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------
                          case 18://estado 12
                          switch(c[pos]){
                                          case ' ':
                                               cout << " -5  "<<endl;
                                               state = 0;
                                               break;
                                          default:
                                                return false;
                          };
                          break;
//-----------------------------------------------------------------------------

                          default:
                                   return false; //error, el estado solo puede ser 0||1

                          };
                          pos++;
            };
            if(state == 3 || state == 9 || state == 15  || state == 17 || state == 18)//estado de aceptacion
                     return true;
            else
                     return false;
            }


int main(){
    char cadena[80];
    cout<<"Ingrese la cadena a analizar: ";
    cin.getline(cadena,80);
    if(!simular_af(cadena))
        cout<<"Error: Identificador no valido"<<endl;
    else
        cout<<"La cadena '"<<cadena<<"' es un identificador valido"<<endl;

    return 0;
}



