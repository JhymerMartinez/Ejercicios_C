/*
 * CLASE 1 
#include<iostream>
using namespace std;
inline float cubo(const float s){return s*s*s;}
int main(){
    cout << "Introduce la longitud de un cubo: ";
    float lado;
    cin >> lado;
    cout <<"el volumen de "<<lado<<" es "<<cubo(lado)<<"\n";
    return 0;
}*/
#include<iostream>
using namespace std;
float v;
int main(){
    int v=7;
    ::v = 10.5;//utilizar variable global v
    cout << "variable local v = "<<v<<"\n";
    cout << "variable global v = "<<::v<<"\n";
    return 0;
}
