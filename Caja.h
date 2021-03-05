#ifndef CAJA_H
#define CAJA_H

#include <stdbool.h>
/*Definimos la estructura de Caja.*/
struct Caja
{
    int id;
    int tiempo;
    bool estado;
    struct Cliente *clienteID;
    struct Carreta *carretaCliente;
    struct Caja *sig;
    struct Caja *ant;
    int cantidad;
};

#endif