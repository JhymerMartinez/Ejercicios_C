#include <stdio.h>
#include <stdlib.h>

int main()
{
char numPtr[5] = "1234";

printf( "Convirtiendo la cadena \"%s\" en un numero: %d\n", numPtr, atoi(numPtr) );

return 0;
}
