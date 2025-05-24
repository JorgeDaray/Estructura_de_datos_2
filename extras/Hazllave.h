#ifndef HAZLLAVE_H_INCLUDED
#define HAZLLAVE_H_INCLUDED
#include "Arches.h"

int hazllave(char cad1[], char cad2[])
{
    int longap, longap2;
    longap = cadespac(cad1); //quita espacios del apellido
    longap2 = cadespac(cad2);
    cad1[longap++] = ' ';
    cad1[longap] = '\0';
    cad2[longap2++] = ' ';
    cad2[longap2] = '\0';
    mayusculas(cad1,cad2);
    strcat(cad1,cad2);
    return longap+longap2;
}

#endif // HAZLLAVE_H_INCLUDED
