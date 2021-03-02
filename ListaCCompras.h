#include "Cliente.h"
#include "Carreta.h"
/*Metodos que se usaran en la "clase" de compras.*/
void agregarClienteListaCompras(struct Cliente *clienteAAgregar,struct Cliente *clientePrincipalListaCompras,int *clientesEnCompras);
void verListaCompras(struct Cliente *clientePrincipalListaCompras);
struct Cliente* sacarClienteListaCompras(struct Cliente *clientePrincipalListaCompras,int idCliente,int *clientesEnCompras);
struct Cliente* buscarClienteListaCompras(struct Cliente *clientePrincipalListaCompras,int idCliente);
struct Cliente* buscarUltimoClienteListaCompras(struct Cliente *clientePrincipalListaCompras);