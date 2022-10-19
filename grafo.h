#ifndef GRAFO_H_
#define GRAFO_H_
#include "datos_de_aeropuerto.h"
#include <string>

using namespace std;

const int INFINITO = 999999999;

class Vertice;
class Arista;

class Vertice
{
    string              codigoIata;
    DatosAeropuerto*    datosAeropuerto;
    Vertice*            siguienteVertice; // Lista de nodos
    Arista*             aristaAdyacente;
    friend class Grafo;
};

class Arista
{
    Arista*     siguienteArista; // Lista de aristas
    Vertice*    verticeAdyacente;
    long int         peso;
    friend class Grafo;
};

class Grafo
{
    private:
        Vertice* ptrPrimerVertice;
    public:
        Grafo();
        bool vacio();
        int tamano();
        Vertice* getPtrVertice(string);
        string obtener_iata();
        void insertarArista(Vertice*, Vertice*,long int);
        void insertarVertice(DatosAeropuerto*);
        void eliminarArista(Vertice*, Vertice*);
        void eliminarVertice(Vertice*);
        void sacarNodo(Vertice*);
        void informacionAeropuerto(string);
        void mostrarAeropuertosEntrantes(Vertice*);
        void mostrarAeropuertosSalientes(Arista*);
        void imprimirDatosAeropuerto(DatosAeropuerto*);
        void listaAeropuertos();
        long int** matrizPesos();
        void cargarMatriz(long int**);
        int getNumeroVertice(Vertice*);
        long int obtenerPeso(Vertice*, Vertice*);
        void imprimirMatrizPesos();
    private:

};
#endif /* GRAFO_H_ */
