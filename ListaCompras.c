#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ListaCompras.h"

void agregarClienteCompras(struct Cliente *nuevoCliente,struct Cliente *ListaCompras){
    if(ListaCompras->sig==NULL){
        //lista vacia
        ListaCompras->sig = nuevoCliente;
    }else{
        //lista con elementos
        struct Cliente *tmp = ListaCompras->sig;
        if(tmp->sig == NULL){
            tmp->sig = nuevoCliente;
            nuevoCliente->sig = tmp;
        }else{
            struct Cliente *aux = tmp->sig;
            tmp->sig = nuevoCliente;
            nuevoCliente->sig = aux;
        }
    }
    printf("El cliente %d entra a realizar compras\n",nuevoCliente->id);
    ListaCompras->cantidad++;
}

void mostrarListaCompras(struct Cliente *ListaCompras){
    struct Cliente *cliente = ListaCompras;
    if(cliente->sig!=NULL){
        //imprimiendo clientes en compras
        cliente=cliente->sig;
        printf("Cliente: %d\n",cliente->id);
        if(cliente->sig!=NULL){
            cliente=cliente->sig;
            while(cliente->id!=ListaCompras->sig->id){
            printf("Cliente: %d\n",cliente->id);
            cliente=cliente->sig;
            }
        }        
    }
}

struct Cliente* sacarClienteListaCompras(struct Cliente *ListaCompras,int idCliente){
    struct Cliente *cliente = buscarClienteListaCompras(ListaCompras,idCliente);
    struct Cliente *tmp;
    struct Cliente *aux;
    if(cliente==NULL){
        return NULL;
    }else if(cliente->sig == cliente->sig->sig){
        //es el ultimo elemento
        tmp = cliente->sig;
        ListaCompras->sig = NULL;
        ListaCompras->cantidad--;
        return tmp;
    }else{
        //hay mas de 1 elemento
        if(cliente->sig == ListaCompras->sig){
            //cliente principal a sacar

            //buscando ultimo elemento
            tmp=buscarUltimoClienteListaCompras(ListaCompras);
            //almacenando cliente a sacar
            aux = cliente->sig;
            //enlazando ultimo con el nuevo principal
            ListaCompras->sig = cliente->sig->sig;
            tmp->sig=ListaCompras->sig;
            ListaCompras->cantidad--;
            return aux;
        }else{
            //el cliente a sacar no es el principal
            tmp = cliente->sig;
            cliente->sig = cliente->sig->sig;
            ListaCompras->cantidad--;
            return tmp;
        }
    }
}

//devuelve el cliente anterior al que se eliminara
struct Cliente* buscarClienteListaCompras(struct Cliente *ListaCompras,int idCliente){
    struct Cliente *cliente = ListaCompras;
    if(cliente->sig!=NULL){        
        //validando si es el buscado
        if(cliente->sig->id==idCliente){
            return cliente;
        }
        cliente=cliente->sig;
        if(cliente->sig!=NULL){
            cliente=cliente->sig;
            while(cliente->id!=ListaCompras->sig->id){
                //validando si es el buscado
                if(cliente->sig->id==idCliente){
                    return cliente;
                }
                cliente=cliente->sig;                
            }
            //validando si es el buscado
            if(cliente->sig->id==idCliente){
                return cliente;
            }
        }
        //validando si es el buscado
            if(cliente->sig->id==idCliente){
                return cliente;
            }    
        //retornar null si no se encontro
        return NULL;
    }else{
        return NULL;
    }
}

struct Cliente* buscarUltimoClienteListaCompras(struct Cliente *ListaCompras){
    struct Cliente *cliente = ListaCompras;
    if(cliente->sig!=NULL){
        //imprimiendo clientes en compras
        cliente=cliente->sig;
        if(cliente->sig!=NULL){
            cliente=cliente->sig;
            while(cliente->sig->id!=ListaCompras->sig->id){
                cliente=cliente->sig;                
            }
            
        }
        return cliente;
    }else{
        return NULL;
    }
}

int contarListaCompras(struct Cliente *ListaCompras){
    return ListaCompras->cantidad;
}
/*Este Metodo que sobreescribe en el texto de salida para el archivo .dot*/
void graficarListaCompras(struct Cliente *ListaCompras,char salida[]){
    struct Cliente *cliente = ListaCompras;
    char subCodigo[20]="";
    strcat(salida,"subgraph cluster_1 {label = \"Lista_Compras\";");
    if(cliente->sig!=NULL){
        cliente=cliente->sig;
        strcat(salida," Cliente");
        sprintf(subCodigo,"%d",cliente->id);
        strcat(salida,subCodigo);
        strcat(salida,"__Carreta");
        sprintf(subCodigo,"%d",cliente->carretaID->id);
        strcat(salida,subCodigo);
        strcat(salida," ");
        if(cliente->sig!=NULL){
            strcat(salida,"->");
            strcat(salida," Cliente");
            sprintf(subCodigo,"%d",cliente->sig->id);
            strcat(salida,subCodigo);
            strcat(salida,"__Carreta");
            sprintf(subCodigo,"%d",cliente->sig->carretaID->id);
            strcat(salida,subCodigo);
            strcat(salida," ");
        }
        if(cliente->sig!=NULL){
            cliente=cliente->sig;
            while(cliente->id!=ListaCompras->sig->id){
            strcat(salida," Cliente");
            sprintf(subCodigo,"%d",cliente->id);
            strcat(salida,subCodigo);
            strcat(salida,"__Carreta");
            sprintf(subCodigo,"%d",cliente->carretaID->id);
            strcat(salida,subCodigo);
            strcat(salida," ");
            strcat(salida,"->");
            strcat(salida," Cliente");
            sprintf(subCodigo,"%d",cliente->sig->id);
            strcat(salida,subCodigo);
            strcat(salida,"__Carreta");
            sprintf(subCodigo,"%d",cliente->sig->carretaID->id);
            strcat(salida,subCodigo);
            strcat(salida," ");
            cliente=cliente->sig;
            }
        }        
    }
    strcat(salida,"}");
}