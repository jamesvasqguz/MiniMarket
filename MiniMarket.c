#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#define true 1
#define false 0

/*Se declaran las funciones que se ejecutaran en el programa.*/
int salirLCompras();
int destinoCarreta();

/*Declaramos las estructuras de los objetos partes del programa.*/
typedef struct Cliente
{
    int *idC;
    struct Cliente *sig;
} NodoCliente;

typedef struct Carreta
{
    int *idCarreta;
    struct Carreta *sig;
} NodoCarreta;

typedef struct Caja
{
    int *idCaja;
    bool estado : true;
    int refCliente;
    int refCarreta;
    struct Caja *sig;
} NodoCaja;

/*Iniciamos la cola de espera de los clientes*/
NodoCliente *iniciarCola(NodoCliente *ColaEspera)
{
    ColaEspera = NULL;
}

/*Agregar Cliente a la cola de Espera*/
NodoCliente *aggClienteCola(NodoCliente *ColaEspera, int *idC)
{
    /*Creamos el nodo de cliente con el parametro ID que recibe.*/
    NodoCliente *nuevoCliente;
    NodoCliente *tmp;
    nuevoCliente = (NodoCliente *)malloc(sizeof(NodoCliente));
    /*Verificamos si hay espacio en la memoria para crear el nuevo cliente*/
    if (nuevoCliente != NULL)
    {
        nuevoCliente->idC = idC;
        nuevoCliente->sig = NULL;
        /*Insertamos el cliente a la Cola de espera de las carretas, en el caso de que no haya carretas disponibles.*/
        /*Verificamos si la cola esta vacia.*/
        if (ColaEspera == NULL)
        {
            /*Si la cola esta vacia y no hay carretas disponibles el nuevo cliente sera el primer nodo en la cola.*/
            ColaEspera = nuevoCliente;
        }
        else
        {
            /*Si la cola no esta vacia el nuevo cliente que se crea sera el ultimo.*/
            tmp = ColaEspera;
            while (tmp->sig != NULL)
            {
                tmp = tmp->sig;
            }
            tmp->sig = nuevoCliente;
        }
        /*Si hay carretas disponibles el cliente pasa por su carreta, y se va directo a pagos.*/
    }
    else
    {
        printf("\nMemoria llena no se puede crear el cliente.\n");
    }
    return ColaEspera;
}

/*Muestra la cola de espera.*/
void mostrar(NodoCliente *ColaEspera)
{
    while (ColaEspera != NULL)
    {
        printf("\n\n Cola de espera ID del Cliente %d puntero de ref %p y su siguiente es: %p \n\n", ColaEspera->idC, ColaEspera, ColaEspera->sig);
        ColaEspera = ColaEspera->sig;
    }else
    {
        printf("Cola vacia");
    }
    
}

/*Movemos al Cliente a compras su hay carretas disponibles.*/
NodoCliente *moverClienteCompras(NodoCliente *ColaEspera)
{
    if (ColaEspera != NULL)
    {
        //Eliminar el primero de la cola.
        NodoCliente *tmp;
        tmp = ColaEspera;

        ColaEspera = ColaEspera->sig;

        free(tmp);
        /*
        if (tmp->sig!=NULL)
        {
            while ((tmp->sig)->sig != NULL)
            {
                tmp = tmp->sig;
            }
            free(tmp->sig);
            tmp->sig = NULL;
        }
        else
        {
            ColaEspera= iniciarCola(ColaEspera);
        }*/
    }
    else
    {
        printf("No se puede eliminar por no hay nada en la Cola");
    }
    return ColaEspera;
}

/*Metodo main principal.*/
int main()
{
    NodoCliente *ColaEspera = iniciarCola(ColaEspera);
    printf("%p \n", ColaEspera);

    ColaEspera = aggClienteCola(ColaEspera, (int *)8);
    ColaEspera = aggClienteCola(ColaEspera, (int *)15);
    ColaEspera = aggClienteCola(ColaEspera, (int *)25);

    mostrar(ColaEspera);
    printf("\n\n Eliminando\n\n");
    
    ColaEspera = moverClienteCompras(ColaEspera);
    mostrar(ColaEspera);

    int numDestino;
    numDestino = destinoCarreta();
    printf("Destino de la carreta es: %d\n", numDestino);

    int numSalirCompras;
    numSalirCompras = salirLCompras();
    printf("El indice del cliente con el que sale es: %d\n", numSalirCompras);
    return 0;
}

/*Esta funcion devuelve un numero aleatorio entre 1 y 2 para ver a que pila va la carreta despues de que el cliente paga.*/
int destinoCarreta()
{
    int numero;
    srand((unsigned)time(0));
    numero = (rand() % 2) + 1;
    return numero;
}

/*Este funcion devuelve un numero aleatorio entre 0 y 100 para salir de la lista circular de compras.*/
int salirLCompras()
{
    int numero;
    srand((unsigned)time(0));
    numero = rand() % 101;
    return numero;
}