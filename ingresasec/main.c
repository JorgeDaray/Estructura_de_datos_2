#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arches.h"
#define saca_cad(fd, cad)  write((fd), (cad), strlen(cad));\
                                        write ((fd), DELIM_CAD, 1);

/* escribesec.c
Crea el archivo de nombres y direcciones que es, en forma estricta, una secuencia de bytes
(sin delimitadores, contadores, u otra información que ayude a distinguir campos y registros).
Una modificación simple a la macro saca_cad:

#define saca_cad (fd, cad) write((fd), (cad), strlen (cad)); \

write ((fd), DELIM CAD, 1);

cambia el programa de tal forma que crea campos delimitados.
*/

int main()
{
     char nombre[30], apellido[30], direccion[30], ciudad[20];

    char estado[15], cp[9];

    char nomarch [15];

    int fd;

    printf("Proporcione el nombre del archivo que quiera crear: ");
    gets (nomarch);

    if ((fd = creat (nomarch, PMODE)) < 0) {
        printf("Error en la apertura del archivo --- Fin de programa\n"); exit(1);
    }

    printf("\n\nDigite un apellido, o <CR> para salir\n>>>");
    gets (apellido);

    while (strlen (apellido) > 0)
    {
        printf("\n Nombre:");
        gets (nombre);

        printf(" Dirección:");
        gets (direccion);

        printf("   ciudad:");
        gets (ciudad);

        printf("   Estado:");
        gets(estado);

        printf("Cod. Post. :");
        gets (cp);
    }


    /* Traslada las cadenas al buffer y después al archivo */

        saca_cad (fd, apellido);
        saca_cad (fd, nombre);
        saca_cad (fd, direccion);
        saca_cad (fd, ciudad);
        saca_cad (fd, estado);
        saca_cad (fd, cp);
    /* se prepara para los siguientes datos */

    printf("\n\nDigite un apellido, o <CR> para salir\n>>>");
    gets (apellido);
    /* cierra el archivo antes de terminar*/
    close (fd);
    return 0;
}

