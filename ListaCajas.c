#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ListaCajas.h"

//Metodo agrega nuevas cajas al sistema
void agregarCaja(struct Caja *ListaCaja,struct Caja *nuevaCaja){
    if(ListaCaja->sig==NULL){
        ListaCaja->sig=nuevaCaja;
    }else{
        struct Caja *tmp = ListaCaja->sig;
        while (tmp->sig!=NULL)
        {
            tmp = tmp->sig;
        }
        tmp->sig = nuevaCaja;
        nuevaCaja->ant=tmp;   
    }
    ListaCaja->cantidad++;
}
/*Metodo que muestra las lista de cajas*/
void mostrarCajas(struct Caja *ListaCaja){
    struct Caja *tmp = ListaCaja->sig;
    while(tmp!=NULL){
        printf("Caja: %d",tmp->id);
        if(tmp->sig!=NULL){
            printf("Caja Siguiente: %d\n",tmp->sig->id);
        }
        if(tmp->ant!=NULL){
            printf("Caja Anterior: %d\n",tmp->ant->id);
        };        
        tmp=tmp->sig;
    }
}

/*Metodo que asigna clientes a las cajas disponibles.*/
void asignarCaja(struct Caja *ListaCajas,struct Cliente *ColaPagos,int paso,struct Carreta *Pila1,struct Carreta *Pila2){
    struct Cliente *cliente;
    struct Caja *tmp = ListaCajas->sig;
    int cajasDisponibles= contarListaCajas(ListaCajas);
    int residuo;
    for (int i = 0; i < cajasDisponibles; i++)
    {
        if(tmp!=NULL){
            if(tmp->estado){
                //caja ocupada -> verificando si sale cliente
                residuo = paso % tmp->tiempo;
                if(residuo == 0){
                    //turno de liberar caja
                    int destCarreta = destinoCarreta();
                    despachar(tmp->clienteID,tmp,Pila1,Pila2,destCarreta);
                } 
                //caja = caja->siguiente;
            }else{
                //caja libre -> asignando valores a la caja
                cliente = obtenerCliente(ColaPagos);
                if(cliente != NULL){
                    tmp->clienteID = cliente;
                    tmp->carretaCliente = cliente->carretaID;
                    tmp->estado = true;
                    ColaPagos->cantidad--;
                    printf("El cliente %d está siendo atendido por la caja %d.\n",tmp->clienteID->id,tmp->id);
                }    
            }
            tmp = tmp->sig;
        }
    }
}

int contarListaCajas(struct Caja *ListaCaja){
    return ListaCaja->cantidad;
}

/*Este metodo obtiene al primer cliente que se encuentre en la cola de pagos y lo trae para asignarlo a caja.*/
struct Cliente* obtenerCliente(struct Cliente *ColaPagos){
    struct Cliente *tmp;
    if(ColaPagos->sig!=NULL){
            tmp= ColaPagos->sig;
            ColaPagos->sig = ColaPagos->sig->sig;
            ColaPagos->cantidad--;
            tmp->sig=NULL;
            return tmp;
    }else{
        return NULL;
    }
}

/*Metodo que despacha al cliente y libera la caja*/
void despachar(struct Cliente *cliente,struct Caja *caja,struct Carreta *Pila1,struct Carreta *Pila2,int destCarreta){
    printf("El cliente %d sale del sistema.\n",cliente->id);
    //liberando carreta
    if(destCarreta == 1){
        apilar(Pila1,cliente->carretaID);
    }else{
        apilar(Pila2,cliente->carretaID);
    }
    printf("Se libera la carreta %d\n",cliente->carretaID->id);
    //liberando caja
    caja->clienteID = NULL;
    caja->carretaCliente = NULL;
    caja->estado = false;
    caja->cantidad++;
    printf("Se libera la caja %d\n",caja->id);
    //sacando al cliente del sistema
    free(cliente);
}

/*Metodo que sobreescribe en el texto de salida para el archivo .dot*/
void graficarCajas(struct Caja *ListaCajas,char salida[]){
    strcat(salida,"subgraph cajas{");
    struct Caja *tmp = ListaCajas->sig;
    char subGrafo[60]="";
    while (tmp!=NULL)
    {  
        //agregando codigo caja
        sprintf(subGrafo,"%d",tmp->id);        
        strcat(salida,subGrafo);
        strcat(salida," [shape=box,label=\"Caja"); 
        sprintf(subGrafo,"%d",tmp->id);    
        strcat(salida,subGrafo);
        strcat(salida,"_");
        sprintf(subGrafo,"%d",tmp->tiempo);        
        strcat(salida,subGrafo);
        if(tmp->estado){
            strcat(salida,"turnos_Ocupado\"]; ");
        }else{
            strcat(salida,"turnos_Libre\"]; ");
        }
        tmp = tmp->sig;
    }
    tmp = ListaCajas->sig;
    while(tmp!=NULL){
        if(tmp->sig!=NULL){
            sprintf(subGrafo,"%d",tmp->id);
            strcat(salida,subGrafo);
            strcat(salida,"->");
            sprintf(subGrafo,"%d",tmp->sig->id);
            strcat(salida,subGrafo);
            strcat(salida," ");
        }
        if(tmp->ant!=NULL){
            sprintf(subGrafo,"%d",tmp->id);
            strcat(salida,subGrafo);
            strcat(salida,"->");
            sprintf(subGrafo,"%d",tmp->ant->id);
            strcat(salida,subGrafo);
            strcat(salida," ");
        }       
        tmp=tmp->sig;
    }
    strcat(salida,"}");
}

int destinoCarreta()
{
    int numero;
    srand((unsigned)time(0));
    numero = (rand() % 2) + 1;
    return numero;
}
//sprintf convierte un numero a cadena de caracteres
//strcat concatena una cadena a otra