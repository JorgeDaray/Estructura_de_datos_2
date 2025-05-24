#ifndef FUNSCADS_H_INCLUDED
#define FUNSCADS_H_INCLUDED
#include "Arches.h"
int cadespac(char cad[])
{
    int i;

    for(i = strlen(cad) - 1; i >=0 && cad[i] == ' '; i--)
        ;

    cad[++i] = '\0';
    return (i);
}

void mayusculas(char cadent[], char cadsal[])
    {
        //0x5F Quita el 32 a nivel bits para hacer mayusculas
        while (*cadsal++ = (cadent >= 'a' && *cadent <= 'z')? *cadent & 0x5F : *cadent)//cadena de entrada rango, entonces hace un if corto
        {
            cadent++;
        }
    }

#endif // FUNSCADS_H_INCLUDED
