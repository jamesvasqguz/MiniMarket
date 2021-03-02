#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ListaCajas.h"

//metodo para inicializar una cantidad n de cajas
void agregarCaja(struct Caja *ListaCaja,struct Caja *nuevaCaja){
    //------------agregar a lista doblemente enlazada-----------
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
void asignarCaja(int *cajasDisponibles,struct Caja *cajaPrincipal,struct Cliente *clientePrincipalColaPagar,int *clientesEnEsperaDePagar,int paso,struct Carreta *carretaPrincipalPila1,struct Carreta *carretaPrincipalPila2,int *carretasDisponiblesPila1,int *carretasDisponiblesPila2,int numeroAleatorio){
    //struct Cliente *cliente = sacarClienteColaPagar(clientePrincipalColaPagar,clientesEnEsperaDePagar);
    struct Cliente *cliente;
    struct Caja *caja = cajaPrincipal->siguiente;
    int residuo;
    for (int i = 0; i < *cajasDisponibles; i++)
    {
        if(caja!=NULL){
            if(caja->ocupado){
                //caja ocupada -> verificando si sale cliente
                residuo = paso % caja->tiempoServicio;
                if(residuo == 0){
                    //turno de liberar caja
                    finalizarCliente(caja->clienteAtendido,caja,carretaPrincipalPila1,carretaPrincipalPila2,carretasDisponiblesPila1,carretasDisponiblesPila2,numeroAleatorio);
                } 
                //caja = caja->siguiente;
            }else{
                //caja libre -> asignando valores a la caja
                cliente = sacarClienteColaPagar(clientePrincipalColaPagar,clientesEnEsperaDePagar);
                if(cliente != NULL){
                    caja->clienteAtendido = cliente;
                    caja->carretaDelCliente = cliente->carreta;
                    caja->ocupado = true;
                    printf("El cliente %d está siendo atendido por la caja %d.\n",caja->clienteAtendido->id,caja->numero);
                }    
                //caja = caja->siguiente;
            }
            caja = caja->siguiente;
        }//else{
            //caja = caja->siguiente;
        //}
    }
    
    //regresarClienteColaPagar(cliente,clientePrincipalColaPagar,clientesEnEsperaDePagar);
}

/*Este metodo obtiene al primer cliente que se encuentre en la cola de pagos y lo trae para asignarlo a caja.*/
struct Cliente* obtenerCliente(struct Cliente *ColaPagos,int *clientesEnEsperaDePagar){
    struct Cliente *tmp;
    if(ColaPagos->sig!=NULL){
        //if(clientePrincipalColaPagar->siguiente->siguiente == NULL){
            //struct Cliente *clienteTemporal = clientePrincipalColaPagar->siguiente;
            //clientePrincipalColaPagar->siguiente = NULL;
            //*clientesEnEsperaDePagar = *clientesEnEsperaDePagar-1;
            //return clienteTemporal;
        //}else{
            tmp= ColaPagos->sig;
            ColaPagos->sig = ColaPagos->sig->sig;
            colaDePagos->cantidad--;
            return tmp;
        //}
    }else{
        return NULL;
    }
}


/*Metodo que despacha al cliente y libera la caja*/
void despachar(struct Cliente *cliente,struct Caja *caja,struct Carreta *carretaPrincipalPila1,struct Carreta *carretaPrincipalPila2,int *carretasDisponiblesPila1,int *carretasDisponiblesPila2,int numeroAleatorio){
    printf("El cliente %d sale del sistema.\n",cliente->id);
    //liberando carreta
    if(numeroAleatorio == 1){
        agregarPilaCarretas(cliente->carreta,carretaPrincipalPila1,carretaPrincipalPila1,carretasDisponiblesPila1,carretasDisponiblesPila2);
    }else{
        agregarPilaCarretas(cliente->carreta,carretaPrincipalPila2,carretaPrincipalPila1,carretasDisponiblesPila1,carretasDisponiblesPila2);
    }
    printf("Se libera la carreta %d\n",cliente->carreta->id);
    //liberando caja
    caja->clienteAtendido = NULL;
    caja->carretaDelCliente = NULL;
    caja->ocupado = false;
    printf("Se libera la caja %d\n",caja->numero);
    //sacando al cliente del sistema
    free(cliente);
}