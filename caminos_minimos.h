#ifndef CAMINOS_MINIMOS_H_
#define CAMINOS_MINIMOS_H_
#include "grafo.h"
#include <string>
typedef struct
{
	string vertice_iata_fila;
	long int costo;
	string vertice_iata_columna;
}adyacencia;
class CaminosMinimos
{
private:
	int tamanio;
	long int* vector_caminos;
	long int* vector_caminos_minimos;
	long int** matriz_de_pesos;
	adyacencia** matriz_de_adyacencia;
	bool* etiquetados;
	long int peso_etiquetado;
public:
	CaminosMinimos(Grafo &grafo);
	void dijkstra(string origen,string destino);
	void imprimirMinimos();
	~CaminosMinimos();
private:
	void verificarYModificarAdyacencia(int pos);
	int elMinimo();
};
#endif /* CAMINO_MINIMO_H_ */
