#include <string>
#include <iostream>
#include <windows.h>

using namespace std;

string elim_espacios_finales(string cadena)
{
int p_ini=0;
int longitud;
int a_p = 0;


a_p = cadena.size() - 1;
while(cadena[a_p] == ' ')
{
a_p --;
}
longitud = a_p - p_ini + 1;

return cadena.substr(p_ini, longitud);
}

int main()
{
cout << "Cadena con espacios al final "; // ponle espacios ya que yahoo los elimina 
cout <<"otra cadena de prueba";


cout<<"\n\nElimando espacios al final de la cadena\n\n"; 
cout << elim_espacios_finales("Cadena con espacios al final  "); /* ponle espacios ya que yahoo los elimina */
cout <<"otra cadena de prueba";


cout<<"\n\n";
system("pause");
return 0;

}