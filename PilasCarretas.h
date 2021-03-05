#ifndef PILAS_CARRETAS_H
#define PILAS_CARRETAS_H

#include "Carreta.h"
#include "Cliente.h"

////Metodos que se usaran en la pila que reciben Carreta como referencia y no por valor.
void apilar(struct Carreta *Pila, struct Carreta *nuevaCarreta);          
void mostrarPila(struct Carreta *Pila);
struct Carreta* moverCarreta(struct Carreta *Pila);
int contarPila(struct Carreta *Pila);
//Metodo para graficar la pila de carretas
void graficarPilaCarretas(struct Carreta *Pila,int numPila,char salida[]);
#endif