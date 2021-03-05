#include "Caja.h"
#include "Carreta.h"
#include "Cliente.h"
#include "PilasCarretas.h"
/*Declaramos los metodos que usaremos en la lista cajas.*/
void agregarCaja(struct Caja *ListaCaja,struct Caja *nuevaCaja);
void mostrarCajas(struct Caja *ListaCaja);
void asignarCaja(struct Caja *ListaCaja,struct Cliente *ColaPagos,int paso,struct Carreta *Pila1,struct Carreta *Pila2);

struct Cliente* obtenerCliente(struct Cliente *ColaPagos);
void despachar(struct Cliente *cliente,struct Caja *caja,struct Carreta *Pila1,struct Carreta *Pila2,int destCarreta);
int contarListaCajas(struct Caja *ListaCaja);
int destinoCarreta();
//Metodo que graficara la lista de cajas.
void graficarCajas(struct Caja *ListaCaja,char salida[]);