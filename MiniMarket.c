#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "PilasCarretas.h"

/*Se declaran las funciones que se ejecutaran en el programa.*/
int salirLCompras();
int destinoCarreta();
void iniciarColaCarretas(int clientes);
void iniciarPilasCarretas(int cantCarretas);

/*Declaramos las variables globales*/
struct Cliente ColaEspera;
struct Carreta Pila1;
struct Carreta Pila2;
struct Carreta eliminar;
//Variables de los id de los objetos.
int idCliente, idCaja, idCarreta, idPila;
//Variables iniciales para el sistema.
int cantCarretas, cantCajas, cantColaCarretas;
//Variable para contar los clientes en la cola de carretas.
int clientesEnCola;
int carretasPila;
int pilas;
/*Metodo main principal.*/
int main()
{
    idCliente = 1;
    idCaja = 1;
    idCarreta = 1;
    idPila=1;
    pilas=1;
    printf("\n********¡Bienvenidos al MiniMarket!********\n");
    printf("\n********¡Tu tienda de confianza!********\n\n");

    printf("\n********¡Ingrese el número de carretas para la pila 1.!********\n");
    scanf("%i", &cantCarretas);
    iniciarPilasCarretas(cantCarretas);
    mostrarPila(&Pila1);
    clientesEnCola = contar(&Pila1);
    /*moverCarreta(&Pila1,&eliminar);
    mostrarPila(&Pila1);
    clientesEnCola = contar(&Pila1);*/
    printf("Carretas en la pila 1:  %d\n", clientesEnCola);

    printf("\n********¡Ingrese el número de carretas para la pila 2.!********\n");
    scanf("%i", &cantCarretas);
    iniciarPilasCarretas(cantCarretas);
    mostrarPila(&Pila2);
    clientesEnCola = contar(&Pila2);
    printf("Carretas en la pila 2:  %d\n", clientesEnCola);

    printf("\n********¡Ingrese el número de cajas disponibles en la tienda.!********\n");
    scanf("%i", &cantCajas);

    printf("\n********¡Ingrese el número de Clientes en la Cola de Espera.!********\n");
    scanf("%i", &cantColaCarretas);
    printf("\nCantidad de Carretas: %d , Cantidad de Cajas: %d , Cantidad de Clientes en la ColaEspera: %d\n\n", cantCarretas, cantCajas, cantColaCarretas);
    iniciarColaCarretas(cantColaCarretas);
    mostrarCola(&ColaEspera);
    clientesEnCola = contar(&ColaEspera);
    printf("Clientes en cola:  %d\n", clientesEnCola);
    /*
    ColaEspera = moverClienteCompras(ColaEspera);
    mostrar(ColaEspera);*/

    /*int numDestino;
    numDestino = destinoCarreta();
    printf("Destino de la carreta es: %d\n", numDestino);

    int numSalirCompras;
    numSalirCompras = salirLCompras();
    printf("El indice del cliente con el que sale es: %d\n", numSalirCompras);
    return 0;*/
}

/*Metodo para agregar la cantidad de clientes en la cola de carretas dado po el usuario*/
void iniciarColaCarretas(int clientes)
{
    for (int i = 0; i < clientes; i++)
    {
        struct Cliente *nuevoCliente = (struct Cliente *)malloc(sizeof(struct Cliente));
        nuevoCliente->id = idCliente;
        printf("Cliente # %d agregado a la cola de carretas. ", nuevoCliente->id);
        idCliente++;
        aggClienteCola(&ColaEspera, nuevoCliente);
    }
}

void iniciarPilasCarretas(int carretas)
{
    if (pilas == 1)
    {
        for (int i = 0; i < cantCarretas; i++)
        {
            struct Carreta *nuevaCarreta = (struct Carreta *)malloc(sizeof(struct Carreta));
            nuevaCarreta->id = idCarreta;
            printf("Carreta # %d agregado a la Pila 1 de carretas. ", nuevaCarreta->id);
            idCarreta++;
            
            apilar(&Pila1, nuevaCarreta);
        }
    }
    else if (pilas == 2)
    {
        for (int i = 0; i < cantCarretas; i++)
        {
            struct Carreta *nuevaCarreta = (struct Carreta *)malloc(sizeof(struct Carreta));
            nuevaCarreta->id = idCarreta;
            printf("Carreta # %d agregado a la Pila 2 de carretas. ", nuevaCarreta->id);
            idCarreta++;
            apilar(&Pila2, nuevaCarreta);
        }
    }

    pilas++;
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