#include "../extras/Arches.h"
#include "../extras/Tomarc.h"

int main()
{
    int fd, cont_reg, cont_campos;
    int pos_bus, long_reg;
    char nomarch[15];
    char buffreg[TAM_MAX_REG + 1];
    char campo[TAM_MAX_REG + 1];

    printf("Proporcione el nombre del archivo a leer: ");
    gets(nomarch);
    if ((fd = open(nomarch,SOLOLECT)) < 0)
    {
        printf("Error en la apertura del archivo - fin del programa\n");
        exit(1);
    }
    cont_reg = 0;
    pos_bus = 0;
    while ((long_reg = toma_reg(fd,buffreg)) > 0)
    {
        printf("Registro %d\n", ++cont_reg);
        cont_campos = 0;
        while((pos_bus = toma_campo(campo,buffreg,pos_bus,long_reg)) > 0)
        {
            printf("\tCampo %d: %s\n", ++cont_campos, campo);
        }
    }
    close(fd);
}

/*//Tomar.c
int toma_reg(int fd,char buffreg[])
{
    int long_reg;
    if (read(fd, &long_reg, 2) == 0)
    {
        return(0);
    }
    long_reg = read(fd, buffreg, long_reg);
    return(long_reg);
}

int toma_campo(char campo[], char buffreg[], int pos_bus, int long_reg)
{
    int cpos = 0;
    if (pos_bus == long_reg)
    {
        return(0);
    }
    while (pos_bus < long_reg && (campo[cpos++] = buffreg[pos_bus++]) != DELIM_CAR)
        ;

        if (campo[cpos - 1] == DELIM_CAR)
            campo[--cpos] = '\0';
        else
            campo[cpos] = '\0';
    return(pos_bus);
}*/
