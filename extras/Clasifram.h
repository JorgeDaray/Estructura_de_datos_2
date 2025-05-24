#ifndef CLASIFRAM_H_INCLUDED
#define CLASIFRAM_H_INCLUDED
#include "Arches.h"

char nombre_archivo[15] = "Indice";
char nomarch[15];

strcat(nomarch,nombre_archivo);
 if((indice = open(nomarch,LECTESCRIT))<0)
    {
        indice=creat(nomarch,PMODE);//si no existe, lo crea
        encabezado.cont_reg = 0; //inicializa el encabezado
        write(indice, &encabezado,sizeof(encabezado));//escribe el registro del encabezado
    }
    else // se abre el archivo existente y lee el encabezado
    {
        read(indice,&encabezado,sizeof(encabezado));
    }


#endif // CLASIFRAM_H_INCLUDED
