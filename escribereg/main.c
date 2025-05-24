#include "../Actividad1/include/arches.h"
#define campo_a_buffreg(br,cad) strcat(br,cad); strcat(br,DELIM_CAD);

char buffreg[TAM_MAX_REG + 1];
char *solicitud[] = {//Matriz de punteros. arreglo de apuntadores a caracter.
 "Digite apellido, o <CR> para salir: ",
 "                            nombre: ",
 "                         direccion: ",
 "                            ciudad: ",
 "                            Estado: ",
 "                        Cod. Post.: ",
 ""  //cadena nula para terminar la solicitud
};


int main()
{
    char respuesta[50];
    char nomarch[15];
    int fd,i;
    int long_reg;

    printf("Proporciona el nombre del archivo que quiera crear: ");
    gets(nomarch);

    if ((fd = creat(nomarch,PMODE)) < 0)
    {
        printf("Error en la apertura del archivo - fin de programa\n");
        exit(1);
    }
    printf("\n\n%s", solicitud[0]);
    gets(respuesta);
    while (strlen(respuesta) > 0)
    {
        fflush(stdin);
        buffreg[0] = '\0';
        campo_a_buffreg(buffreg,respuesta);
        for (i=1; *solicitud[i] != '\0' ; i++)
        {
            printf("%s", solicitud[i]);
            gets(respuesta);
            campo_a_buffreg(buffreg,respuesta);
        }

    //Escribe la longitud del registro y el contenido del buffer *
    long_reg = strlen(buffreg);
    write(fd,&long_reg,2);
    write(fd,buffreg,long_reg);
    //Se prepara para los siguientes datos
    printf("\n\n%s", solicitud[0]);
    gets(respuesta);
    }
    //cierra el archivo
    close(fd);

    return 0;
}
