/*
Alumno: Padilla Perez Jorge Daray
Codigo: 216584703
Materia: Estructura de datos 2
seccion: D09
Profesor: Miguel Angel Guerrero Segura Ramirez
*/
#include "../extras/Arches.h"
#include "../extras/Tomarc.h"
#include "../extras/Funscads.h"
#define LONG_REG 64
#define campo_a_buffreg(br,cad) strcat(br,cad); strcat(br,DELIM_CAD);
#define campo_a_sin_deli(br,cad) strcat(br,cad);

static char *solicitud[]={
    "\t Número de participación: ",
    "\t Tiempo de clasificación: [H:MM:SS]",
    "\t Nombre de atleta: ",
    "\t Ciudad: ",
    "\t Nacionalidad: ",
    "\t Dirección del atleta: ",
    ""
};

static int fd;
static struct
{
    short cont_reg;
    char relleno[30];
}encabezado;

int main()
{
    int i, menu_elec, nrr,byte_pos;
    char nomarch[15];
    long lseek();
    char buffreg[TAM_MAX_REG + 1];
    printf("Proporcione el nombre del archivo: ");
    gets(nomarch);

    if((fd=open(nomarch,LECTESCRIT))<0)
    {
        fd=creat(nomarch,PMODE);//si no existe, lo crea
        encabezado.cont_reg = 0; //inicializa el encabezado
        write(fd, &encabezado,sizeof(encabezado));//escribe el registro del encabezado
    }
    else // se abre el archivo existente y lee el encabezado
    {
        read(fd,&encabezado,sizeof(encabezado));
    }
    //ciclo del programa principal llama al menu y salta las opciones
    while((menu_elec = menu()) < 3)
    {
        switch(menu_elec)
        {
        case 1: //agrega un registro nuevo
            {
                printf("Proporcione la informacion del registro nuevo: \n\n");
                pide_info(buffreg);
                byte_pos = encabezado.cont_reg * LONG_REG + sizeof(encabezado);
                lseek(fd,(long) byte_pos, 0);
                write(fd,buffreg,LONG_REG);
                encabezado.cont_reg++;
                break;
            }
        case 2://actualiza un registro existente
            {
                nrr = pide_nrr();
                //si el NRR es muy grande, imprime mensaje de error
                if (nrr >= encabezado.cont_reg)
                {
                    printf("El numero de registro es demasiado grande");
                    printf("...se vuelve al menu...");
                    break;
                }

                //En caso contrario, se coloca el registro...
                byte_pos = nrr * LONG_REG + sizeof(encabezado);
                lseek(fd, (long) byte_pos, 0);

                //lo despliega y pide cambios
                lee_y_muestra();
                if (cambio())
                {
                    printf("\n\n proporcione los valores revisados: \n\n");
                    pide_info(buffreg);
                    lseek(fd, (long) byte_pos, 0);
                    write(fd,buffreg,LONG_REG);
                }
                break;
            }
        }
    }
    //reescribe la suma de registros correcta en el encabezado
    //antes de terminar
    lseek(fd,0L,0);
    write(fd,&encabezado,sizeof(encabezado));
    close(fd);
    return 0;
}

int menu()
{
    int eleccion;
    char respuesta[10];
    printf("\n\n\n\n\t Programa de actualizacion del archivo\n");
    printf("\n Encabezado: \n");
    printf("NRR (Registros disponibles): %i\n",encabezado.cont_reg);
    printf("\n\n Puede elegir: \n\n");
    printf("\n 1) Agregar un registro al final del archivo\n");
    printf("\n 2) Extraer un registro para actualizarlo\n");
    printf("\n 3) Salir del programa\n\n");
    printf("Proporcione el numero de su eleccion: ");
    gets(respuesta);
    eleccion = atoi(respuesta);
    return(eleccion);
};

void pide_info(char buffreg[])
{
    char c;
    int cont_campos, i, nc = 0;
    char respuesta[50];
    char tiempo[50];
    //limpia el buffer del registro
    for (i = 0; i < LONG_REG; buffreg[i++] = '\0')
        ;
    //fflush(stdin);
    for (i = 0; *solicitud[i] != '\0';i++)
    {
        if(i == 0)
        {
            printf("%s",solicitud[i]);
            gets(respuesta);
            campo_a_sin_deli(buffreg,respuesta);
        }
        else if(i == 1)
        {
            printf("%s",solicitud[i]);
                while ((c = getchar()) != '\n')
                {
                    if(c != ' ' && c != ':')
                    {
                        tiempo[nc] = c;
                        nc++;
                    }
                }
            campo_a_sin_deli(buffreg,tiempo);
        }
        else
        {
            printf("%s",solicitud[i]);
            gets(respuesta);
            campo_a_buffreg(buffreg,respuesta);
        }
        cont_campos = LONG_REG - strlen(buffreg);
        printf("Te quedan %i caracteres para la info \n",cont_campos);
    }
}

int pide_nrr()
{
    int nrr;
    char respuesta[10];

    printf("\n\n Digite el numero relativo del registro\n");
    printf("\t que desee actualizar: ");
    gets(respuesta);
    nrr = atoi(respuesta);
    return(nrr);
}

void lee_y_muestra()
{
    char buffreg[TAM_MAX_REG + 1], campo[TAM_MAX_REG + 1], otro_campo[TAM_MAX_REG + 1];
    int pos_bus = 9, long_datos, i = 0;
    read(fd, buffreg, LONG_REG);
    printf("\n\n\n\n Contenido del registro existente\n");
    buffreg[LONG_REG] = '\0';//se asegura que el registro termine en nulo
    long_datos = strlen(buffreg);
        for (i = 0; i < 9; i++)
        {
            otro_campo[i] = buffreg[i];
            if (i == 3)
            {
                printf("\t%c%c%c%c\n",buffreg[0],buffreg[1],buffreg[2],buffreg[3]);
            }
        }
        printf("\t%c",buffreg[4]);
        printf(":");
        printf("%c%c",buffreg[5],buffreg[6]);
        printf(":");
        printf("%c%c\n",buffreg[7],buffreg[8]);

    while((pos_bus = toma_campo(campo, buffreg, pos_bus, long_datos)) > 0)
    {
            if (pos_bus > 9)
            {
                printf("\t%s\n",campo);
            }
    }
}

int cambio()
{
    char respuesta[10];
    printf("\n\n Desea modificar este registro?\n");
    printf("Conteste S o N, seguido por <ENTER> ==>");
    gets(respuesta);
    mayusculas(respuesta,respuesta);
    return((respuesta[0] == 'S') ? 1:0);
}
