#include <iostream>
#include "grafo.h"
#include "parser.h"
#include "datos_de_aeropuerto.h"
#include "caminos_minimos.h"
using namespace std;
void cargar_grafo(Grafo &grafo,Parser &parser)
{
	string auxiliar_codigo_iata;
	auxiliar_codigo_iata = "1"; //Valor para inicializar
	DatosAeropuerto *ptr_aeropuerto,*aeropuerto1,*aeropuerto2;
	Vertice *vertice1,*vertice2,*vertice_auxiliar;
	long int costo_viaje;
	while (auxiliar_codigo_iata != "0")
	{
		ptr_aeropuerto = parser.obtenerDatosDelAeropuerto();
		aeropuerto1 = ptr_aeropuerto;
		aeropuerto2 = (ptr_aeropuerto+1);
		auxiliar_codigo_iata = parser.obtenerCodigoAeropuerto();
		if (auxiliar_codigo_iata != "0")
		{
			costo_viaje = parser.obtenerCostoViaje();
			vertice_auxiliar = grafo.getPtrVertice(aeropuerto1->codigoIata);
			if (vertice_auxiliar == NULL)
				grafo.insertarVertice(aeropuerto1);
			vertice_auxiliar = grafo.getPtrVertice(aeropuerto2->codigoIata);
			if (vertice_auxiliar == NULL)
				grafo.insertarVertice(aeropuerto2);
			vertice1 = grafo.getPtrVertice(aeropuerto1->codigoIata);
			vertice2 = grafo.getPtrVertice(aeropuerto2->codigoIata);
			grafo.insertarArista(vertice1,vertice2,costo_viaje);
		}
	}
}
void cargar_partida_y_destino(string &partida,string &destino)
{
	cout<<"Ingrese el codigo iata de partida: "<<endl;
	cin>>partida;
	cout<<"Ingrese el codigo iata de destino: "<<endl;
	cin>>destino;
}
void mostrar_menu(Grafo &grafo)
{
	char respuesta = 's';
	int opcion;
	string iataIngresado;
	DatosAeropuerto *ptr_aeropuerto;
	Vertice *auxiliar_vertice;
	while (respuesta == 's')
	{
		cout<<"Ingrese una de las opciones que desea realizar: "<<endl;
		cout<<"1: Buscar la informacion de un aeropuerto."<<endl;
		cout<<"2: Listar todos los aeropuertos."<<endl;
		cout<<"3: Agregar un nuevo aeropuerto."<<endl;
		cout<<"4: Cantidad de aeropuertos."<<endl;
		cin>>opcion;
		switch (opcion)
		{
			case 1:
				cout<<"Ingrese el codigo iata de dicho aeropuerto a buscar: "<<endl;
				cin>>iataIngresado;
				grafo.informacionAeropuerto(iataIngresado);
				break;
			case 2:
				grafo.listaAeropuertos();
				break;
			case 3:
				ptr_aeropuerto = new DatosAeropuerto;
				cout<<"Ingrese el codigo iata del aeropuerto: "<<endl;
				cin>>ptr_aeropuerto->codigoIata;
				cout<<"Ingrese el nombre del aeropuerto (en los espacios poner '-'): "<<endl;
				cin>>ptr_aeropuerto->nombreAeropuerto;
				cout<<"Ingrese la ciudad donde se encuentra: "<<endl;
				cin>>ptr_aeropuerto->cuidad;
				cout<<"Ingrese el pais donde se encuentra: "<<endl;
				cin>>ptr_aeropuerto->pais;
				if (grafo.getPtrVertice(ptr_aeropuerto->codigoIata) != 0)
				{
					cout<<"Esta ciudad ya fue agregada."<<endl;
					delete ptr_aeropuerto;
				}
				else
					grafo.insertarVertice(ptr_aeropuerto);
				break;
			case 4:
				cout<<"La cantidad de aeropuertos que hay es de: "<<grafo.tamano()<<endl;
				break;
			default:
				cout<<"Opcion incorrecta."<<endl;
		}
		cout<<"Desea seguir realizando mas operaciones? (s para si/n para no): "<<endl;
		cin>>respuesta;
	}
}
int main()
{
	bool encontrado = false;
    Grafo objeto_grafo;
    Parser objeto_parser;
    cargar_grafo(objeto_grafo,objeto_parser);
    objeto_grafo.imprimirMatrizPesos();
    string iata_partida,iata_destino;
    while ((encontrado == false))
    {
    	cargar_partida_y_destino(iata_partida,iata_destino);
    	if ((objeto_grafo.getPtrVertice(iata_partida) != NULL) && (objeto_grafo.getPtrVertice(iata_destino) != NULL))
    	{
    		cout<<"Origen y destino encontrados."<<endl;
    		encontrado = true;
    	}
    	else
    		cout<<"No encontrados. Por favor, reingrese el origen y el destino"<<endl;
    }
    mostrar_menu(objeto_grafo);
    CaminosMinimos objeto_camino_minimo(objeto_grafo);
    objeto_camino_minimo.dijkstra(iata_partida,iata_destino);
    objeto_camino_minimo.imprimirMinimos();
    return 0;
}
