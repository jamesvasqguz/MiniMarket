//Incluimos las "clases" de cliente y Carreta
#include "Cliente.h"
#include "Carreta.h"
/*Declamos los metodos que usaremos en la cola de pagos.*/
void encolarCliente(struct Cliente *ColaPagos,struct Cliente *cliente);
void mostrarColaPagos(struct Cliente *ColaPagos);
int contarCP(struct Cliente *ColaPagos);
void graficarColaClientesPagar(struct Cliente *ColaDePagos, char salida[]);