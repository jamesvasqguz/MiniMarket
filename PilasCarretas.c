#include <stdio.h>
#include <stdlib.h>

#include "PilasCarretas.h"

//metodo para agregar una carreta a la pila de carretas
void apilar(struct Carreta *Pila, struct Carreta *nuevaCarreta){            
    if(Pila->sig==NULL){
        //Si la pila esta vacia la nueva carreta sera la pila.
        Pila->sig=nuevaCarreta;
    }else{
        //Si la pila no esta vacia se agrega al final.
        nuevaCarreta->sig = Pila->sig;
        Pila->sig = nuevaCarreta;
    }
    //Contador de cuantas carretas estan en la pila
    Pila->cantidad++;
}

void mostrarPila(struct Carreta *Pila){
    struct Carreta *tmp = Pila;
    printf("Carretas en la Pila: \n");
    //Se verifica que la pila no este vacia.
    if(tmp->sig!=NULL){
        tmp=tmp->sig;
        //Se recorre la pila mientras no apunte a null
        while(tmp!=NULL){
            printf("Carreta: %d\n",tmp->id);
            tmp=tmp->sig;
        }
    }
}

struct Carreta* moverCarreta(struct Carreta *Pila,struct Carreta *carreta){
    struct Carreta *tmp = Pila->sig;
    Pila->sig=tmp->sig; 

    //validando cantidad de carretas disponibles en las pilas
    Pila->cantidad--;
    return tmp;
}

int contarPila(struct Carreta *Pila){
    return Pila->cantidad;
}