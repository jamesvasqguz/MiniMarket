#include "Cliente.h"
//Metodos que se usaran en la cola que reciben Cliente como referencia y no por valor.
void aggClienteCola(struct Cliente *ColaEspera,struct Cliente *nuevoCliente);
void mostrarCola(struct Cliente *ColaEspera);
int contar(struct Cliente *ColaEspera);
struct Cliente* moverCliente(struct Cliente *ColaEspera);