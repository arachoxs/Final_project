#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct
{
    bool segunda_vuelta;
}segunda_votacion_usuarios;

int main(int argc, char const *argv[])
{
    //abre el archivo y ponle la estrucutura segunda_votacion_usuarios con el bool en false
    FILE *archivo = fopen("segunda_vuelta.txt", "w");
    fwrite(&segunda_votacion_usuarios, sizeof(segunda_votacion_usuarios), 1, archivo);
    fclose(archivo);

    
    return 0;
}
