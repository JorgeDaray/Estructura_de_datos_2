/*
Alumno: Padilla Perez Jorge Daray
Codigo: 216584703
Materia: Estructura de datos 2
seccion: D09
Profesor: Miguel Angel Guerrero Segura Ramirez
*/
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

#define saca_cad (fd, cad) write((fd), (cad),       strlen (cad)); \

                                                    write ((fd), DELIM CAD, 1);

cambia el programa de tal forma que crea campos delimitados.
*/

void ingresar();
void leer();
void menu();

    char nombre[30], direccion[30], ciudad[20];
    char estado[15], cp[9], ramo[30];
    char nomarch [15];//Declaracion archivo fisico.
    int fd;//Declaracion archivo logico.

int main()
{
    int opc = 0;
    printf("Proporcione el nombre del archivo que quiera crear o leer: ");
    gets (nomarch);//Obtencion del nombre del archivo fisico.
    if ((fd = open(nomarch,LECTESCRIT)) < 0)//Apertura de archivo fisico, a traves del archivo logico. Escritura y Lectura.
    {
        fd = creat(nomarch,PMODE);//Creacion del archivo fisico, a traves del archivo logico. En PMODE 0755.
        printf("Creado correctamente\n");
        system("pause");
    }
    while (opc!=3)
    {
        system("cls");
        menu();
        printf("Continuar 1 salir 3:\n");scanf("%d", &opc);
   }
    return 0;
}

void ingresar()
{
    fflush(stdin);
    printf("\n\nDigite un nombre o razon social del cliente, o <CR> para salir\n>>>");
    gets (nombre);
    while (strlen(nombre) > 0)
    {
        printf(" Dirección de la empresa:");
        gets (direccion);

        printf(" ciudad:");
        gets (ciudad);

        printf(" Estado:");
        gets(estado);

        printf(" Cod. Post.:");
        gets (cp);

        printf(" Ramo a que se dedica:");
        gets (ramo);

    lseek(fd,0L,2);//Traslada el puntero al final del archivo, para no sobreescribir.
    /* Traslada las cadenas al buffer y después al archivo */

        saca_cad (fd, nombre);
        saca_cad (fd, direccion);
        saca_cad (fd, ciudad);
        saca_cad (fd, estado);
        saca_cad (fd, cp);
        saca_cad (fd, ramo);
    /* se prepara para los siguientes datos */

    system("pause");
    printf("\n\nDigite un nombre o razon social del cliente, o <CR> para salir\n>>>");
    gets (nombre);
    }
}


/*
leesec.c
lee una secuencia de campos delimitados
*/
void leer()
{
    int n;
    char cad[30];
    int cont_campos;

    /* Ciclo del programa principal llama a leecampo () hasta que se leen todos los campos */

    cont_campos = 0;
    lseek(fd,0L,0);//Traslada el puntero al inicio.
    while ((n = leecampo(fd, cad)) > 0)
        printf("\tCampo # %3d: %s\n", ++cont_campos, cad);
}

leecampo(int fd,char cad[])
{
    int i;
    char c;
    i = 0;

    while (read (fd, &c, 1) > 0 && c != DELIM_CAR)
    cad[i++] = c;

    cad[i] = '\0'; /*Agrega un caracter nulo al final de la cadena*/
    return (i);
}

void menu()
{
    int opc = 0;
    printf("1) Ingresar cliente\n");
	printf("2) Leer cliente\n");
	printf("3) Salir\n");
    scanf("%d", &opc);
	switch(opc){

		case 1: {
                    ingresar();
                }break;
        case 2: {
                    leer();
                }break;
        case 3: {
                    printf("Saliendo\n");
                     close (fd);//Cierre del archivo.
                }break;
	}
}
