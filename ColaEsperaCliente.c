#include <stdio.h>
#include <stdlib.h>

#include "ColaEsperaCliente.h"

/*Insertamos el cliente a la Cola de espera de las carretas, en el caso de que no haya carretas disponibles.*/
/*Metodo que agrega cliente a la cola de espera.*/
void aggClienteCola(struct Cliente *ColaEspera, struct Cliente *nuevoCliente){
    //Declaramos nuevos Clientes
    struct Cliente *tmp;
    
    if(ColaEspera->sig==NULL){
        //Si la inicial apunta a null esta vacia y por lo tanto la cola sera el cliente nuevo.
        ColaEspera->sig=nuevoCliente;  
    }else{
        //Ya que la cola tiene cliente se agrega el nuevo al final.
        tmp =ColaEspera->sig;
        while(tmp->sig!=NULL){
            tmp=tmp->sig;
        }
        tmp->sig=nuevoCliente;
    }
    printf("Cliente con el ID %d agregado a la cola en espera de carretas\n",nuevoCliente->id);
    ColaEspera->cantidad++;
}

/*Metodo que saca el cliente que se encuentre en el primer lugar.*/
struct Cliente* moverCliente(struct Cliente *ColaEspera){
    struct Cliente *tmp;
    //Se verifica si la cola tiene clientes.
    if(ColaEspera->sig!=NULL){
        tmp= ColaEspera->sig;
        ColaEspera->sig=ColaEspera->sig->sig;
        ColaEspera->cantidad--;
        return tmp;
    }else{
        //Si no tiene clientes retorna null.
        return NULL;
    }
}

/*Metodo que muestra los clientes que se encuentren en la cola de espera.*/
void  mostrarCola(struct Cliente *ColaEspera){
    struct Cliente *cola = ColaEspera;
    printf("Cola de Espera\n");
    if(cola->sig!=NULL){
        //Se recorre cada nodo de clientes.
        cola=cola->sig;
        //Mientras que el cola no apunte a null imprime todos los clientes.
        while(cola!=NULL){
            printf("Cliente: %d\n",cola->id);
            cola=cola->sig;
        }
    }
}

int contar(struct Cliente *ColaEspera){
    return ColaEspera->cantidad;
}