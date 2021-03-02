#ifndef CARRETA_H
#define CARRETA_H

/*Definimos la estructra basica de carreta.*/
struct Carreta
{
    int id;
    int cantidad;
    struct Carreta *sig;
    struct Carreta *ant;
};

#endif