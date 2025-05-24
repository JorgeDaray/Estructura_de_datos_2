#include "../extras/Arches.h"
#include "../extras/Funscads.h"
#include "../extras/Tomarc.h"
#include "../extras/Hazllave.h"
#define EXITO 1
#define FRACASO 0

int fd, long_reg, pos_bus;
int encontro;
char llave_bus[30], llave_enc[30], pelicula[30], protagonista[30];
char nomarch[15];
char buffreg[TAM_MAX_REG+1], campo[TAM_MAX_REG + 1];

int main()
{
    printf("Proporciona el nombre del archivo en donde buscar: ");
    gets(nomarch);

    if ((fd = open(nomarch,SOLOLECT)) < 0)
    {
        printf("Error en la apertura del archivo - fin de programa\n");
        exit(1);
    }
    printf("\n\nDigite el pelicula: "); // Toma la llave de busqueda
    gets(pelicula);
    printf("Ingrese el protagonista: ");
    gets(protagonista);
    hazllave(pelicula,protagonista,llave_bus);

    encontro = FRACASO;
    while (!encontro && (long_reg = toma_reg(fd,buffreg)) > 0)
    {
        pos_bus = 0;
        pos_bus = toma_campo(pelicula,buffreg,pos_bus,long_reg);
        pos_bus = toma_campo(protagonista,buffreg,pos_bus,long_reg);
        hazllave(pelicula,protagonista, llave_enc);
        if(strcmp(llave_enc,llave_bus) == 0)
            encontro = EXITO;
    }

    if (encontro)
    {
        printf("se encontro el registro\n");
        pos_bus = 0;

        while ((pos_bus = toma_campo(campo,buffreg,pos_bus,long_reg)) > 0)
            printf("\t%s\n",campo);
    }
    else{
        printf("no se encontro");
    }

    return 0;
}
