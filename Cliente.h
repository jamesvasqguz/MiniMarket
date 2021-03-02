#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdbool.h>
/*Definimos la estructura de cliente.*/
struct Cliente
{
    int id;
    int cantidad;
    struct Cliente *sig;
    struct Carreta *carretaID;
};

#endif