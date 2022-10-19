#include <iostream>
#include "parser.h"
Parser::Parser()
{
	this->codigo_aeropuerto = " ";
	this->registro_aeropuerto.codigoIata = " ";
	this->registro_aeropuerto.cuidad = " ";
	this->registro_aeropuerto.nombreAeropuerto = " ";
	this->registro_aeropuerto.pais = " ";
	this->linea = " ";
	this->costo_viaje = 0;
	this->archivo.open("vuelos.txt",ios::in);
}
long int Parser::obtenerCostoViaje()
{
	return(this->costo_viaje);
}
string Parser::obtenerCodigoAeropuerto()
{
	return(this->codigo_aeropuerto);
}
DatosAeropuerto* Parser::obtenerDatosDelAeropuerto()
{
	DatosAeropuerto* ptrAeropuerto = 0;
	string aux2;
	char codigo[4];
	bool es_fin_de_archivo = true;
	setCodigoAeropuerto("0");
	this->registro_aeropuerto.codigoIata = " ";
	this->registro_aeropuerto.cuidad = " ";
	this->registro_aeropuerto.nombreAeropuerto = " ";
	this->registro_aeropuerto.pais = " ";
	setCostoViaje(0);
	leerLinea(es_fin_de_archivo);
	if (es_fin_de_archivo == false)
	{
		pasarCodigo(codigo,this->linea);
		registro_aeropuerto.codigoIata = codigo;
		this->codigo_aeropuerto = codigo;
		ptrAeropuerto = parseoGeneral();
	}
	return(ptrAeropuerto);
}
void Parser::leerLinea(bool &es_fin)
{
	if (this->archivo.is_open() == true)
	{
		es_fin = this->archivo.eof();
		if (this->archivo.eof() == false)
		{
			getline(this->archivo,this->linea);
			cout<<"Linea leida"<<endl;
		}
		else
		{
			cout<<"Fin del archivo!"<<endl;
			this->archivo.close();
		}
	}
	else
	{
		cout<<"No existe dicho archivo."<<endl;
		this->linea = " ";
	}
}
DatosAeropuerto* Parser::parseoGeneral()
{
	DatosAeropuerto* aux;
	aux = new DatosAeropuerto[2];
	int i;
	i = 4;
	registro_aeropuerto.nombreAeropuerto = pasarCadenas(i);
	i++;
	registro_aeropuerto.cuidad = pasarCadenas(i);
	i++;
	registro_aeropuerto.pais = pasarCadenas(i);
	aux[0] = registro_aeropuerto;
	i++;
	registro_aeropuerto.codigoIata = pasarCadenas(i);
	i++;
	registro_aeropuerto.nombreAeropuerto = pasarCadenas(i);
	i++;
	registro_aeropuerto.cuidad = pasarCadenas(i);
	i++;
	registro_aeropuerto.pais = pasarCadenas(i);
	aux[1] = registro_aeropuerto;
	i++;
	string auxiliar_numeros;
	auxiliar_numeros = pasarCadenasFinal(i);
	this->costo_viaje = atol(auxiliar_numeros.c_str());
	cout<<this->costo_viaje<<endl;
	return(aux);
}
void Parser::pasarCodigo(char codigo[4],string auxiliar)
{
	int i = 0;
	while (auxiliar[i] != ' ')
	{
		codigo[i] = auxiliar[i];
		i++;
	}
}
string Parser::pasarCadenas(int &pos1)
{
	string auxiliar;
	int contador = 0;
	int j = pos1,i;
	while (linea[pos1] != ' ')
	{
		contador++;
	    pos1++;
	}
	contador++;
	char cadena[contador];
	i = 0;
	while (linea[j] != ' ')
	{
		cadena[i] = linea[j];
		i++;
		j++;
	 }
	cadena[i] = '\0';
	auxiliar = cadena;
	return(auxiliar);
}
string Parser::pasarCadenasFinal(int &pos1)
{
	string auxiliar;
	char auxiliar2[7];
	int i = 0;
	while (this->linea[pos1] != '\0')
	{
		auxiliar2[i] = this->linea[pos1];
		pos1++;
		i++;
	}
	auxiliar2[i] = '\0';
	auxiliar = auxiliar2;
	return(auxiliar);
}
void Parser::setCostoViaje(long int costo)
{
	this->costo_viaje = costo;
}
void Parser::setCodigoAeropuerto(string iata)
{
	this->codigo_aeropuerto = iata;
}
