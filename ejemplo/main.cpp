/*#include<iostream> 
#include<string> 
#include <stdlib.h>
using namespace std; */

/*int main () { 
int integer; 
string buffer = "123456789"; 
cout << "String:" << buffer << endl; 
integer=atoi(buffer.c_str()); 
cout << "Integer:" << integer << endl; 
return 0; 
}*/

/*
int main(){
string FileMeasure="Hello FILE!";
int TempNumOne=FileMeasure.size();
char Filename[100];
for (int a=0;a<TempNumOne;a++){
            //Filename[a]=FileMeasure[a];
            cout<<FileMeasure[a]<<endl;
        }
}*/
/*
 #include<string.h>
 #include<stdio.h>
main()
 {
   int a,l;
   char str[50],str1[50],str3[100];
   printf("\nEnter a string");
   scanf("%s",str);
   str3[0]='\0';
   printf("\nEnter the string which you want to concat with string one");
   scanf("%s",str1);
   strcat(str3,str);
   strcat(str3,str1);
   printf("\nThe strings is %s\n",str3);
 }
*/


#include<iostream> 
#include<string> 
#include <stdlib.h>
using namespace std; 
int main()
{

    string nombre;
    int edad;


    cout << "Introduzca el nombre: ";
    cin >> nombre;


    cout << "Introduzca la edad: ";
    cin >> edad;


    cout << "\nInfo: " << nombre << ',' << edad << endl;
}



   // cout << "x=" << x << "  y=" << y << endl;
    //cout <<x<<"   "<<y<<"..."<<endl;
    //cout << num<< endl;

    /*  for(int i=0;i<(int) strlen(cadena);i++){
              if(cadena[i] != ';'){
                  if(cadena[i+1] != ';' && (cadena[i+1] != ' ' || cadena[i+1] != '  ' )){
                       // prueba[fila][colum] = cadena[i]+cadena[i+1];
                        datos[0] = cadena[i];
                        datos[1] = cadena[i+1];
                        string num(datos);
                        prueba[fila][colum] = num;
                        colum++;
                  }else{
                       prueba[fila][colum] = cadena[i];
                        colum++;
                  }
                      // cout << cadena[i]<< endl;
               }
          //cout << cadena[i]<< endl;
    //   }
       fila++;
       colum=0;
    }
       
     for(int i=0;i<10;i++){
         for(int j=0;j<16;j++){
            cout <<"["<<i<<"]"<<"["<<j<<"] => "<<prueba[i][j]<<endl;
         }
       }*/
    //for(int i=0;i<cadena2.length();i++){

    //}
    //}