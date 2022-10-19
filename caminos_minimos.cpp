#include <iostream>
#include "caminos_minimos.h"
using namespace std;
CaminosMinimos::CaminosMinimos(Grafo &grafo)
{
	this->peso_etiquetado = 0;
	this->matriz_de_pesos = grafo.matrizPesos();
	this->tamanio = grafo.tamano();
	this->vector_caminos = new long int[tamanio];
	this->vector_caminos_minimos = new long int[tamanio-1];
	this->etiquetados = new bool[tamanio];
	this->matriz_de_adyacencia = new adyacencia*[tamanio];
	for (int j = 0;j<tamanio;j++)
		this->matriz_de_adyacencia[j] = new adyacencia;
}
void CaminosMinimos::dijkstra(string origen,string destino)
{
	int j = 0;
	for (int i = 0;i<this->tamanio;i++)
	{
		this->vector_caminos[i] = this->matriz_de_pesos[0][j];
		this->etiquetados[i] = false;
		j++;
	}
	this->matriz_de_adyacencia[0][0].vertice_iata_fila = origen;
	this->matriz_de_adyacencia[0][0].vertice_iata_columna = origen;
	for (int fila = 0;fila<tamanio;fila++)
	{
		for (int columna = 0;columna<tamanio;columna++)
			this->matriz_de_adyacencia[fila][columna].costo = this->matriz_de_pesos[fila][columna];
	}
	this->etiquetados[0] = true;
	for (int i = 0;i<tamanio-1;i++)
		this->vector_caminos_minimos[i] = 0;
	int posicion;
	int contador_pasadas = 1;
	int posicion_minimo = 0,fila;
	fila = 1;
	while ((contador_pasadas <= tamanio - 1))
	{
		posicion = elMinimo(); //posicion del numero etiquetado
		if (posicion == -1)
			cout<<"no hay nada"<<endl;
		else
		{
			this->etiquetados[posicion] = true;
			this->vector_caminos_minimos[posicion_minimo] = this->vector_caminos[posicion];
			posicion_minimo++;
		}
		fila++;
		contador_pasadas++;
	}
}
void CaminosMinimos::imprimirMinimos()
{
	cout<<"Los caminos minimos son: "<<endl;
	for (int i = 0;i<this->tamanio - 1;i++)
		cout<<this->vector_caminos_minimos[i]<<" ";
}
CaminosMinimos::~CaminosMinimos()
{
	if (tamanio>0)
	{
		delete []etiquetados;
		delete []this->vector_caminos;
		delete []this->vector_caminos_minimos;
		for (int i = 0;i<tamanio;i++)
		{
			delete []matriz_de_pesos[i];
			delete []matriz_de_adyacencia[i];
		}
		delete []matriz_de_pesos;
		delete []matriz_de_adyacencia;
	}
}
int CaminosMinimos::elMinimo()
{
	long int el_minimo = INFINITO;
	int pos;
	for (int i = 0;i<tamanio;i++)
	{
			if ((el_minimo>vector_caminos[i]) && (etiquetados[i] == false))
			{
				el_minimo = vector_caminos[i];
				pos = i;
			}
	}
	if (el_minimo == INFINITO)
		return(-1);
	else
	{
		verificarYModificarAdyacencia(pos);
		return(pos);
	}
}
void CaminosMinimos::verificarYModificarAdyacencia(int pos)
{
	for (int i = 0;i<tamanio;i++)
	{
		if ((this->matriz_de_pesos[pos][i] != INFINITO) && (this->matriz_de_pesos[pos][i] != 0)) //verifico adyacentes al dicho nodo
		{
			if (this->vector_caminos[i]>(this->vector_caminos[pos] + this->matriz_de_pesos[pos][i]))
				this->vector_caminos[i] = this->vector_caminos[pos] + this->matriz_de_pesos[pos][i];
		}
	}
}
