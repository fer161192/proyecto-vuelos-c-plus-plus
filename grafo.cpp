#include <iostream>
#include "grafo.h"
Grafo::Grafo()
{
    ptrPrimerVertice = NULL;
}

bool Grafo::vacio()
{
    return ( ptrPrimerVertice == NULL );
}

int Grafo::tamano()
{
    int contador = 0;
    Vertice* verticeAuxiliar;
    verticeAuxiliar = ptrPrimerVertice;
    while (verticeAuxiliar != NULL)
    {
        contador++;
        verticeAuxiliar = verticeAuxiliar->siguienteVertice;
    }
    return contador;
}

Vertice* Grafo::getPtrVertice(string codigoIata)
{
    Vertice* actual;
    actual = ptrPrimerVertice;
    while(actual != NULL)
    {
        if ( actual->codigoIata == codigoIata )
            return actual;
        actual = actual->siguienteVertice;
    }
    return NULL;
}
void Grafo::insertarVertice(DatosAeropuerto* datos)
{
    Vertice* nuevoVertice = new Vertice();
    nuevoVertice->codigoIata = datos->codigoIata;
    nuevoVertice->datosAeropuerto = datos;
    nuevoVertice->siguienteVertice = NULL;
    nuevoVertice->aristaAdyacente = NULL;

    if ( vacio() )
        ptrPrimerVertice = nuevoVertice;
    else
    {
        Vertice* verticeAuxiliar;
        verticeAuxiliar = ptrPrimerVertice;
        while(verticeAuxiliar->siguienteVertice != NULL)
            verticeAuxiliar = verticeAuxiliar->siguienteVertice;
        verticeAuxiliar->siguienteVertice = nuevoVertice;
    }
}

void Grafo::insertarArista( Vertice* origen, Vertice* destino, long int peso)
{
    Arista* nuevaArista = new Arista();
    nuevaArista->peso = peso;
    nuevaArista->siguienteArista = NULL;
    nuevaArista->verticeAdyacente = NULL;

    Arista* aristaAuxiliar; // crea una arista auxiliar para recorrer la lista de aristas
    aristaAuxiliar = origen->aristaAdyacente; // la posiciona en la primera posicion de la lista

    if (aristaAuxiliar == NULL)// si el vertice no tenia ninguna arista, nuevaArista pasa a ser la primera
        origen->aristaAdyacente = nuevaArista;
    else// si no pega la ultima arista al final de la lista de aristas
    {
        while ( aristaAuxiliar->siguienteArista != NULL)
            aristaAuxiliar = aristaAuxiliar->siguienteArista;
        aristaAuxiliar->siguienteArista = nuevaArista;
    }
    nuevaArista->verticeAdyacente = destino;
}

void Grafo::eliminarArista(Vertice* origen, Vertice* destino)
{
    Arista* actual;

    actual = origen->aristaAdyacente; // "actual" es la primera arista de la lista de aristas de un vertice

    if (actual == NULL) // Caso en que el vertice origen no tiene aristas
        return;
    else
    {
        if (actual->verticeAdyacente == destino) // Caso en que la primera arista de la lista (de aristas) conecta al vertice de destino
        {
            origen->aristaAdyacente = actual->siguienteArista; // Conecta al vertice de origen directamente con la segunda arista de la lista
            delete actual; // Y borra la arista que los conectaba
        }
        else // Caso en que la arista a borrar se encuentra entre medio de de lista de aristas
        {
            bool encontrado = false;
            Arista* anterior;

            while (actual != NULL && encontrado == false) // si llego al final de la lista de aristas o encuentro la arista que busco, salgo del bucle
            {
                if (actual->verticeAdyacente == destino)
                {
                    anterior->siguienteArista = actual->siguienteArista;
                    delete actual;
                    encontrado = true;
                }
                anterior = actual;
                actual = actual->siguienteArista;
            }
        }// si no encontre la arista que une esos 2 nodos, es porque no existe
    }
}

void Grafo::eliminarVertice(Vertice* verticeEliminar)
{
    /*Recorro la lista de vertices, por cada uno accedo a sus aristas adyacentes, cuando encuentro una que lo conecte con el nodo
    a eliminar elimino esa arista, asi con todos los vertices. Cuando toca revisar la lista de aristas del vertice a eliminar, salto
    ese ciclo y avanzo al siguiente vertice.*/

    Vertice* actual;
    Arista* aristaAuxiliar;
    bool encontrado = false;

    actual = ptrPrimerVertice;

    while (actual != NULL) // mientras no llege al final de la lista de nodos
    {
        if (actual != verticeEliminar)
        {
            encontrado = false;
            aristaAuxiliar = actual->aristaAdyacente; // toma la primera arista de la lista de aristas
            while(aristaAuxiliar != NULL && encontrado == false) // mientras no llege al final de la lista de aristas y no se haya encontrado el vertice a eliminar
            {
                if (aristaAuxiliar->verticeAdyacente == verticeEliminar)
                {
                    eliminarArista(actual, verticeEliminar);
                    encontrado = true; // salgo del ciclo porque no va a haber otra arista que conecte a esos nodos
                }
                aristaAuxiliar = aristaAuxiliar->siguienteArista;
            }
        }
        actual = actual->siguienteVertice;
    }
    // Una vez elimine todas las aristas que llegan al vertice a eliminar, elimino las aristas que salen del vertice
    while(verticeEliminar->aristaAdyacente != NULL)
        eliminarArista(verticeEliminar, verticeEliminar->aristaAdyacente->verticeAdyacente);//borra siempre la primera arista

    sacarNodo(verticeEliminar);
}

void Grafo::sacarNodo(Vertice* verticeEliminar)
{
    Vertice* actual;
    actual = ptrPrimerVertice; // lo vuelvo a iniciar en el primer nodo del grafo
    if (verticeEliminar == actual) // Caso en que el vertice a eliminar sea el primer vertice que ingrese
    {
        actual = actual->siguienteVertice;
        delete(actual);
    }
    else
    {
        Vertice* anterior;
        while(actual != verticeEliminar) // se detiene cuando actual es el vertice a eliminar
        {
            anterior = actual;
            actual = actual->siguienteVertice;
        }
        anterior->siguienteVertice = actual->siguienteVertice;
        delete(actual);
    }
}

void Grafo::informacionAeropuerto(string codigoIata)
{
    Vertice* aeropuerto;
    Arista* auxArista;
    aeropuerto = getPtrVertice(codigoIata);
    if (aeropuerto)
    {
        auxArista = aeropuerto->aristaAdyacente;
        cout << "Vuelos entrantes a " << aeropuerto->datosAeropuerto->nombreAeropuerto << "(" << aeropuerto->codigoIata << ")" << ", ";
        cout << aeropuerto->datosAeropuerto->cuidad << ", " << aeropuerto->datosAeropuerto->pais << ": " << endl << endl;
        mostrarAeropuertosEntrantes(aeropuerto);
        cout << endl;
        cout << "Vuelos salientes de " << aeropuerto->datosAeropuerto->nombreAeropuerto << "(" << aeropuerto->codigoIata << ")" << ", ";
        cout << aeropuerto->datosAeropuerto->cuidad << ", " << aeropuerto->datosAeropuerto->pais << ": " << endl << endl;
        mostrarAeropuertosSalientes(auxArista);
        cout << endl;
    }
    else
    {
        cout << "No existe ese aeropuerto " << endl;
    }

}

void Grafo::mostrarAeropuertosEntrantes(Vertice* aeropuerto)
{
    Vertice* actual;
    Arista* aristaAuxiliar;
    bool encontrado;
    int contador =1;

    actual = ptrPrimerVertice;

    while (actual) // mientras no llege al final de la lista de nodos
    {
        encontrado = false;
        if (actual != aeropuerto) // asi, si es igual salta al siguiente vertice
        {
            aristaAuxiliar = actual->aristaAdyacente; // toma la primera arista de la lista de aristas
            while(aristaAuxiliar != NULL && encontrado == false) // mientras no llege al final de la lista de aristas y no se haya encontrado el aeropuerto
            {
                if (aristaAuxiliar->verticeAdyacente == aeropuerto)
                {
                    cout << contador << ") ";
                    imprimirDatosAeropuerto(actual->datosAeropuerto);
                    encontrado = true; // salgo del ciclo porque no va a haber otra arista que conecte a esos aeropuertos
                    contador++;
                }
                aristaAuxiliar = aristaAuxiliar->siguienteArista;
            }
        }
        actual = actual->siguienteVertice;
    }
}

void Grafo::mostrarAeropuertosSalientes(Arista* auxiliar)
{
    DatosAeropuerto* datos;
    int contador = 1;
    while (auxiliar != NULL)
    {
        datos = auxiliar->verticeAdyacente->datosAeropuerto;
        cout << contador << ") ";
        imprimirDatosAeropuerto(datos);
        cout << "Precio: " << auxiliar->peso << " ARS" << endl;
        auxiliar = auxiliar->siguienteArista;
        contador++;
    }
}

void Grafo::imprimirDatosAeropuerto(DatosAeropuerto* datos)
{
    cout << datos->cuidad << ", " << datos->pais << endl;
    cout << "Aeropuerto : " << datos->nombreAeropuerto << ", (" << datos->codigoIata << ") " << endl;
}

void Grafo::listaAeropuertos()
{
    Vertice* actual;
    actual = ptrPrimerVertice;
    cout << "Aeropuertos agregados: " << endl << endl;
    while (actual != NULL)
    {
        cout << actual->codigoIata <<  ", " << actual->datosAeropuerto->nombreAeropuerto << ", " << actual->datosAeropuerto->pais << endl;
        actual = actual->siguienteVertice;
    }
}
long int** Grafo::matrizPesos()
{
    int dimension;
    long int** matriz;
    dimension = tamano();
    matriz = new long int* [dimension];
    for  (int i = 0; i < dimension; i++)
        matriz[i] = new long int [dimension];
    cargarMatriz(matriz);
    return matriz;
}
void Grafo::cargarMatriz(long int** matriz)
{
    Vertice *vertice1, *vertice2;
    int fila = 0, columna = 0;

    vertice1 = ptrPrimerVertice;

    while (vertice1 != NULL)
    {
        vertice2 = ptrPrimerVertice;
        columna = 0;
        while(vertice2 != NULL)
        {
            if (vertice1 == vertice2)
                matriz[fila][columna] = 0;
            else
                matriz[fila][columna] = obtenerPeso(vertice1, vertice2);
            columna++;
            vertice2 = vertice2->siguienteVertice;
        }
        vertice1 = vertice1->siguienteVertice;
        fila++;
    }
}
int Grafo::getNumeroVertice(Vertice* vertice)
{
    Vertice* actual;
    int contador = 1;

    actual = ptrPrimerVertice;

    while(actual != vertice)
    {
        contador++;
        actual = actual->siguienteVertice;
    }
    return contador;
}
long int Grafo::obtenerPeso(Vertice* origen, Vertice* destino)
{
    Arista* aristaActual;
    aristaActual = origen->aristaAdyacente;

    while(aristaActual != 0)
    {
        if (aristaActual->verticeAdyacente == destino)
            return(aristaActual->peso);
        aristaActual = aristaActual->siguienteArista;
    }
    return(INFINITO);
}
void Grafo::imprimirMatrizPesos()
{
    long int** matriz;
    matriz = matrizPesos();
    for (int i = 0; i < tamano(); i++)
    {
        for (int j = 0; j < tamano()-1; j++)
            cout << matriz[i][j] << "-";
        cout << matriz[i][tamano()-1];
        cout << endl;
    }
}
