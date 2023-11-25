#pragma once

#ifndef EXCEPTION_TYPES
#define EXCEPTION_TYPES
#endif

#include <exception>
#include <xstring>

using namespace std;

/*
  Se definen en este fichero todas las excepciones que pueden ser lanzadas
  por las clases para manipular el acceso a los ficheros establecidos en este
  proyecto
*/


//Excepcion cuando no se encuantra el fichero
class NotFoundFile : public exception
{
	public:
		NotFoundFile(string msg) : exception(msg.c_str()) {};
};

//Excepcion destinada a ficheros que no sean del tipo esperado
class IncorrectFileType : public exception
{
	public:
		IncorrectFileType(string msg) : exception(msg.c_str()) {};
};


//Excepcion destinada cuando la informacion dentro de un fichero no es realmente la que debe ser
class InconsistentData : public exception
{
	public:
		InconsistentData(string msg) : exception(msg.c_str()) {};
};

//Excepcion destinada cuando al solicitar una muestra de un tipo en el fichero WAVE este las posee de un tamaño distinto
class SampleSizeDifferent : public exception
{
	public:
		SampleSizeDifferent(string msg) : exception(msg.c_str()) {};
};

//Excepcion destinada a indices fuera de rango
class IndexOutOfRange : public exception
{
	public:
		IndexOutOfRange(string msg) : exception(msg.c_str()) {};
};

//Excepcion destinada cuando no hay bytes disponibles para leer o escribir
class NoBytes : public exception
{
	public:
		NoBytes(string msg) : exception(msg.c_str()) {};
};

//Excepcion cuando no es fichero con texto oculto
class NoLSB : public exception
{
	public:
		NoLSB(string msg) : exception(msg.c_str()) {};
};

class NoSignature : public exception
{
public:
	NoSignature(string msg) : exception(msg.c_str()) {};
};