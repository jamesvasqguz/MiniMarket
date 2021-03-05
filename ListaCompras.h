#include "Cliente.h"
#include "Carreta.h"
/*Metodos que se usaran en la "clase" de compras.*/
void agregarClienteCompras(struct Cliente *nuevoCliente,struct Cliente *ListaCompras);
void mostrarListaCompras(struct Cliente *ListaCompras);
struct Cliente* sacarClienteListaCompras(struct Cliente *ListaCompras,int idCliente);
struct Cliente* buscarClienteListaCompras(struct Cliente *ListaCompras,int idCliente);
struct Cliente* buscarUltimoClienteListaCompras(struct Cliente *ListaCompras);
int contarListaCompras(struct Cliente *ListaCompras);
//Metodo que grafica la lista de compras
void graficarListaCompras(struct Cliente *ListaCompras,char salida[]);