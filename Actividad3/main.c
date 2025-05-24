/*
Alumno: Padilla Perez Jorge Daray
Codigo: 216584703
Materia: Estructura de datos 2
seccion: D09
Profesor: Miguel Angel Guerrero Segura Ramirez
*/
#include "../extras/Arches.h"
#include "../extras/Tomarc.h"
#define campo_a_buffreg(br,cad) strcat(br,cad); strcat(br,DELIM_CAD);

//seccion de prototipos de funciones.
void menu();
void escriberreg();
void leerreg();

//seccion de variables
    char respuesta[50];
    char nomarch[15];
    int fd, cont_reg, cont_campos, i;
    int pos_bus, long_reg;
    char campo[TAM_MAX_REG + 1];
    char buffreg[TAM_MAX_REG + 1];
char *solicitud[] = {//Matriz de punteros. arreglo de apuntadores a caracter.
 " Titulo de pelicula: o <CR> para salir:",
 "                          protagonista: ",
 "                              director: ",
 "              Estudio, o distribuidora: ",
 "                                genero: ",
 "                        año de estreno: ",
 "           numero de premios obtenidos: ",
 "      calificacion otorgada a la cinta: ",
 ""  //cadena nula para terminar la solicitud
};

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
    printf("Abierto correctamente\n");
    system("pause");
    while (opc!=3)
    {
        system("cls");
        menu();
        printf("Continuar 1 salir 3:\n");scanf("%d", &opc);
   }
    return 0;
}

//escribereg
void escriberreg()
{
    fflush(stdin);
    printf("\n\n%s", solicitud[0]);
    gets(respuesta);
    while (strlen(respuesta) > 0)
    {
        fflush(stdin);
        buffreg[0] = '\0';
        lseek(fd,0L,2);
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
}

//leereg
void leerreg()
{
    cont_reg = 0;
    pos_bus = 0;
    lseek(fd,0L,0);//Traslada el puntero al inicio.
    while ((long_reg = toma_reg(fd,buffreg)) > 0)
    {
        printf("Registro %d\n", ++cont_reg);
        cont_campos = 0;
        while((pos_bus = toma_campo(campo,buffreg,pos_bus,long_reg)) > 0)
        {
            printf("\tCampo %d: %s\n", ++cont_campos, campo);
        }
    }
}

void menu()
{
    int opc = 0;
    printf("1) Ingresar pelicula\n");
	printf("2) Leer pelicula\n");
	printf("3) Salir\n");
    scanf("%d", &opc);
	switch(opc){

		case 1: {
                    escriberreg();
                }break;
        case 2: {
                    leerreg();
                }break;
        case 3: {
                    printf("Saliendo\n");
                     close (fd);//Cierre del archivo.
                }break;
	}
}

