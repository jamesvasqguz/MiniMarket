#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "PilasCarretas.h"
#include "ListaCajas.h"
#include "ColaEsperaCliente.h"
#include "ColaPagos.h"
#include "ListaCompras.h"

/*Se declaran las funciones que se ejecutaran en el programa.*/
void simulacion();
void graficar();
void Opciones();
void start(int nuevosClientes);
int salirLCompras();
int destinoCarreta();
void iniciarCajas(int cantCajas);
void iniciarColaCarretas(int clientes);
void iniciarPilasCarretas(int cantCarretas);
void iniciarColaPagos(int cantCPagos);
void iniciarListaCompras(int cantLCompras);
void ingresarClientes();


/*Declaramos las variables globales*/
struct Cliente ColaEspera;
struct Cliente ColaDePagos;
struct Cliente ListaCompras;
struct Carreta Pila1;
struct Carreta Pila2;
struct Caja ListaCajas;

//Variables de los id de los objetos.
int idCliente, idCaja, idCarreta, idPila;

//Variables iniciales para el sistema.
int cantCarretas, cantCajas, cantColaCarretas, nuevosClientes, cantCPagos, cantLCompras;

//Variable para contar los clientes en la cola de carretas.
int clientesEnCola;
int carretasEnPila;
int carretasPila;
int carretasDisponibles;
int carretasPila1;
int carretasPila2;
int clientesComprando;
int clientesPagando;

//Variable que indica el numero de paso de la simulacion que se esta llevando a cabo.
int paso;

//Variable de tipo char que sera las instrucciones que recibira graphviz
char salida[3072]="";

/*Metodo main principal.*/
int main()
{
    simulacion();
    return 0;
}

/*Metodo que inicia la simulacion inicializando los valores y llamando a los metodos que estaran usando en la simulacion.*/
void simulacion(){
    paso = 1;

    idCliente = 1;
    idCaja = 1;
    idCarreta = 1;
    idPila = 1;

    printf("\n********¡Bienvenidos al MiniMarket!********\n");
    printf("\n********¡Tu tienda de confianza!********\n\n");

    printf("\n********¡Ingrese el número de carretas para la pila 1.!********\n");
    scanf("%i", &cantCarretas);
    iniciarPilasCarretas(cantCarretas);
    mostrarPila(&Pila1);
    carretasEnPila = contarPila(&Pila1);
    printf("Carretas en la pila 1:  %d\n", carretasEnPila);

    printf("\n********¡Ingrese el número de carretas para la pila 2.!********\n");
    scanf("%i", &cantCarretas);
    iniciarPilasCarretas(cantCarretas);
    mostrarPila(&Pila2);
    carretasEnPila = contarPila(&Pila2);
    printf("Carretas en la pila 2:  %d\n", carretasEnPila);

    printf("\n********¡Ingrese el número de cajas disponibles en la tienda.!********\n");
    scanf("%i", &cantCajas);
    iniciarCajas(cantCajas);
    mostrarCajas(&ListaCajas);

    printf("\n********¡Ingrese el número de Clientes en la Cola de espera de Carretas.!********\n");
    scanf("%i", &cantColaCarretas);
    iniciarColaCarretas(cantColaCarretas);
    mostrarCola(&ColaEspera);
    clientesEnCola = contarClienteCarreta(&ColaEspera);
    printf("Clientes en cola:  %d\n", clientesEnCola);

    printf("\n********¡Ingrese el número de Clientes en la cola de pagos.!********\n");
    scanf("%d", &cantCPagos);
    //agregando la cantidad de clientes a la cola de espera para pagar
    iniciarColaPagos(cantCPagos);
    mostrarColaPagos(&ColaDePagos);

    printf("\n********¡Ingrese el número de Clientes que se encuentran comprando.!********\n");
    scanf("%d", &cantLCompras);
    iniciarListaCompras(cantLCompras);
    mostrarListaCompras(&ListaCompras);

    /*int numDestino;
    numDestino = destinoCarreta();
    printf("Destino de la carreta es: %d\n", numDestino);

    int numSalirCompras;
    numSalirCompras = salirLCompras();
    printf("El indice del cliente con el que sale es: %d\n", numSalirCompras);
    */
};

/*Este metodo permite realizar las acciones del sistema*/
void Opciones()
{
    int opcion;

    do
    {
        printf("\n   Opciones del Sistema.");
        printf("\n   1. Siguiente Paso.");
        printf("\n   2. Graficar Paso.");
        printf("\n   3. Salir.");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            printf("\nIngrese la cantidad de clientes que entran : ");
            scanf("%d", &nuevosClientes);
            start(nuevosClientes);
            break;
        case 2:
            graficar();
            break;
        }
    } while (opcion != 3);
}

/*Metodo que empieza y ejecuta cada simulacion.*/
void start(int nuevosClientes)
{
    printf("\n********************************* Paso #%d *********************************\n", paso);
    //Vemos si hay clientes en la cola de espera y si hay carretas disponibles para despacharlos a compras.
    int carretasP1 = contarPila(&Pila1);
    int carretasP2 =contarPila(&Pila2);
    ;
    carretasDisponibles = carretasP1 + carretasP2;
    //Si hay carretas disponibles operamos los clientes que ya estan en la cola de espera.
    for (int i = 0; i < carretasDisponibles; i++)
    {
        moverClientesACompras();
    }
    //Se ingresan cada uno de los nuevos clientes al sistema.
    for (int i = 0; i < nuevosClientes; i++)
    {
        ingresarClientes();
    }

    clientesComprando = contarListaCompras(&ListaCompras);
    //Verificamos que la lista de compras no esta vacia y asi poder despachar a los clientes a pagos.
    if (clientesComprando > 0)
    {
        int numAleatorio = salirLCompras();
        printf("Numero aleatorio: %d\n", numAleatorio);
        struct Cliente *tmp = sacarClienteListaCompras(&ListaCompras, numAleatorio);
        if (tmp != NULL)
        {
            tmp->sig = NULL;
            agregarClienteColaPagar(tmp, &ColaDePagos);
        }
    }
    //verificando si hay cajas disponibles para ingresar a clientes y clientes listos para salir
    asignarCaja(&ListaCajas,&ColaDePagos,&Pila1,&Pila2,paso);

    //Sumamos 1 a cada paso que indica que el numero de simulacion que se llevara acabo.
    paso++;
    Opciones();
}

/*Metodo que inicia las cajas que el usuario a indicado al principio*/
void iniciarCajas(int cantCajas)
{
    //Creamos nuevas cajas a raiz del numero que ingreso el cliente.
    struct Caja *nuevaCaja;
    for (int i = 0; i < cantCajas; i++)
    {
        nuevaCaja = (struct Caja *)malloc(sizeof(struct Caja));
        nuevaCaja->id = idCaja;
        idCaja++;
        printf("Ingrese el numero de turnos: ");
        scanf("%d", &nuevaCaja->tiempo);
        agregarCaja(nuevaCaja, &ListaCajas);
    }
}

/*Metodo para agregar la cantidad de clientes en la cola de carretas dado po el usuario.*/
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

/*Metodo que ingresa la cantidad de carretas a cada pila antes de iniciar la simulacion.*/
void iniciarPilasCarretas(int carretas)
{
    if (idPila == 1)
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
    else if (idPila == 2)
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
    idPila++;
}

/*Este metodo inicia la cola de pagos con los clientes ingresados con sus respectivas carretas.*/
void iniciarColaPagos(int cantCPagos)
{
    for (int i = 0; i < cantCPagos; i++)
    {
        struct Carreta *nuevaCarreta = (struct Carreta *)malloc(sizeof(struct Carreta));
        nuevaCarreta->id = idCarreta;
        idCarreta++;
        struct Cliente *nuevoCliente = (struct Cliente *)malloc(sizeof(struct Cliente));
        nuevoCliente->id = idCliente;
        nuevoCliente->carretaID = nuevaCarreta;
        idCliente++;
        encolarCliente(&ColaDePagos,nuevoCliente);
    }
}

/*Este metodo inicia la lista de compras con los clientes ingresados con sus respectivas carretas.*/
void iniciarListaCompras(int cantLCompras)
{
    //Crea los clientes con sus carretas en la lista de compras.
    for (int i = 0; i < cantLCompras; i++)
    {
        struct Carreta *nuevaCarreta = (struct Carreta *)malloc(sizeof(struct Carreta));
        nuevaCarreta->id = idCarreta;
        idCarreta++;
        struct Cliente *cliente = (struct Cliente *)malloc(sizeof(struct Cliente));
        cliente->id = idCliente;
        idCliente++;
        cliente->carretaID = nuevaCarreta;
        agregarClienteCompras(cliente, &ListaCompras);
    }
}

/*Este metodo ingresa nuevos clientes en el sistema*/
void ingresarClientes()
{
    struct Cliente *nuevoCliente = (struct Cliente *)malloc(sizeof(struct Cliente));
    nuevoCliente->id = idCliente;
    idCliente++;
    printf("Ingreso del nuevo cliente %d\n", nuevoCliente->id);

    //Obtenemos la cantida de carretas en la pila 1 y 2.
    carretasPila1 = contarPila(&Pila1);
    carretasPila2 = contarPila(&Pila2);
    printf("Carretas disponibles en la pila 1: %d y pila 2: %d\n", carretasPila1, carretasPila2);
    //Verificamos que las pilas 1 y 2 tengan disponibles carretas.
    if (carretasPila1 > 0)
    {
        //Si la pila 1 tiene disponibles carretas le asigamos carreta al cliente nuevo.
        nuevoCliente->carretaID = moverCarreta(&Pila1);
        //Luego de obtener su carreta ingresamos al cliente nuevo a la lista de compras con su carreta.
        agregarClienteListaCompras(nuevoCliente, &ListaCompras);
    }
    else if (carretasPila2 > 0)
    {
        //Si la pila 1 tiene disponibles carretas le asigamos carreta al cliente nuevo.
        nuevoCliente->carretaID = moverCarreta(&Pila2);
        //Luego de obtener su carreta ingresamos al cliente nuevo a la lista de compras con su carreta.
        agregarClienteListaCompras(nuevoCliente, &ListaCompras);
    }
    else
    {
        ////Si la pila 1 y 2 no tiene disponibles carretas agregamos al cliente nuevo a la cola de espera de carretas.
        aggClienteCola(&ColaEspera, nuevoCliente);
    }
}

//metodo para verificar los clientes de la cola en espera de carretas
void moverClientesACompras()
{
    //Obtenemos lo clientes que se encuentran en la cola de espera de carreta y la cantidad de carretas disponibles en las pilas.
    int cantClientes = contarClienteCarreta(&ColaEspera);
    int carretasP1 = contarPila(&Pila1);
    int carretasP2 = contarPila(&Pila2);

    if (cantClientes > 0)
    {
        if (carretasP1 > 0)
        {
            struct Cliente *cliente = moverCliente(&ColaEspera);
            cliente->carretaID = moverCarreta(&Pila1);
            agregarClienteListaCompras(cliente, &ListaCompras);
        }
        else if (carretasP2 > 0)
        {
            struct Cliente *cliente = moverCliente(&ColaEspera);
            cliente->carretaID = moverCarreta(&Pila2);
            agregarClienteListaCompras(cliente, &ListaCompras);
        }
    }
}
/*Metodo que devuelve la cantidad disponible de carretas en la pila que se le pase por parametro.*/

/*Este metodo grafica cada lista, cola, pila que se encuentre en el sistema*/
void graficar()
{
    int p1=1;
    int p2=2;
    char numPaso[4] = "";
    printf("Graficando el paso del Sistema.");
    strcat(salida, "echo \"digraph Paso{");

    graficarCajas(&ListaCajas, salida);
    graficarColaClientesPagar(&ColaDePagos, salida);
    graficarListaCompras(&ListaCompras, salida);
    graficarPilaCarretas(&Pila1, p1, salida);
    graficarPilaCarretas(&Pila2, p2, salida);
    graficarColaClientesCarretas(&ColaEspera, salida);

    strcat(salida, "}\" | dot -Tpng > grafica/Paso");
    sprintf(numPaso, "%d", (paso - 1));
    strcat(salida, numPaso);
    strcat(salida, ".png");
    system(salida);
    memset(salida, 0, 1000);
    Opciones();
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