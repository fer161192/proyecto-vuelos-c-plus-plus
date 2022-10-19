#ifndef PARSER_H_
#define PARSER_H_
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include "datos_de_aeropuerto.h"
using namespace std;
class Parser
{
private:
	DatosAeropuerto registro_aeropuerto;
	string codigo_aeropuerto;
	string linea;
	fstream archivo;
	long int costo_viaje;
public:
	//pre:-
	//post:el parser fue creado
	Parser();
	//pre: el parser debe existir
	//post: Devuelve el costo del viaje de un aeropuerto a otro
	long int obtenerCostoViaje();
	string obtenerCodigoAeropuerto();
	//pre: el parser debe existir
	 //post: devuelve un dato
	DatosAeropuerto* obtenerDatosDelAeropuerto();
private:
	//pre: recibe un bolleano
	//post: se cargo la linea en el archivo
	void leerLinea(bool &es_fin);
	 //pre: recibe una cadena
	//post: carga el registro registro_aeropuerto
	DatosAeropuerto* parseoGeneral();
	//Pre: recibe una cadena y un vector de caracteres
	//Post: extrae el codigo iata de una respectiva linea del archivo
	void pasarCodigo(char codigo[4],string auxiliar);
	 //pre: recibe un entero
	 //post: Extrae las cadenas de los datos del aeropuerto que se encuentran en las lineas del archivo
	string pasarCadenas(int &pos1);
	//pre:recibe un enteros
	//post: Se utiliza para extraer el dato que se encuentra al final de las lineas del archivo
	string pasarCadenasFinal(int &pos1);
	//Pre: Recibe un costo de viaje
	//Post: Setea el costo de viaje
	void setCostoViaje(long int costo);
	void setCodigoAeropuerto(string iata);
};
#endif /* PARSER_H_ */
