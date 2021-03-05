#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ColaPagos.h"

/*Metodo que agrega un cliente a la cola de pagos.*/
void encolarCliente(struct Cliente *ColaPagos,struct Cliente *cliente){
    //Si la cola esta vacia el cliente a encolar sera el primero.
        if(ColaPagos->sig==NULL){
            ColaPagos->sig=cliente;
            printf("El cliente %d se agrega a la cola de pagos con la carreta %d\n",cliente->id,cliente->carretaID->id);
        }else{
            //Como la cola no esta vacia se agrega al ultimo
            struct Cliente *tmp =ColaPagos->sig;
            while(tmp->sig!=NULL){
                tmp=tmp->sig;
            }
            tmp->sig=cliente;
            printf("El cliente %d se agrega a la cola de pagos con la carreta %d\n",cliente->id,cliente->carretaID->id);
        }
        ColaPagos->cantidad++;
}

/*Metodo que muestra los clientes que se encuentran en la cola pagos.*/
void mostrarColaPagos(struct Cliente *ColaPagos){
    struct Cliente *tmp = ColaPagos;
    if(tmp->sig!=NULL){
        tmp=tmp->sig;
        while(tmp!=NULL){
            printf("Cliente: %d con carreta %d\n",tmp->id,tmp->carretaID->id);
            tmp=tmp->sig;
        }
    }
}
/*Cuenta cuantos clientes estan en la cola de pagos.*/
int contarCP(struct Cliente *ColaPagos){
    return ColaPagos->cantidad;
}

void graficarColaClientesPagar(struct Cliente *ColaDePagos,char salida[]){
    struct Cliente *cliente = ColaDePagos;
    strcat(salida,"subgraph cluster_6{label=\"Cola_De_Pagos\"");
    char subCodigo[4]="";
    if(cliente->sig!=NULL){
        cliente=cliente->sig;
        while(cliente!=NULL){
            strcat(salida," Cliente_");
            sprintf(subCodigo,"%d",cliente->id);
            strcat(salida,subCodigo);
            strcat(salida," ");
            if(cliente->sig!=NULL){
                strcat(salida,"-> Cliente_");
                sprintf(subCodigo,"%d",cliente->sig->id);
                strcat(salida,subCodigo);
                strcat(salida," ");
            }
            cliente=cliente->sig;
        }
    }
    strcat(salida,"}");
}