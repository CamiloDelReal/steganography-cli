#pragma once

#ifndef RANDOM_ACCESS_FILE
#define RANDOM_ACCESS_FILE
#endif

#include <xstring>
#include <stdint.h>

typedef unsigned char uchar;

using namespace std;

//Posibles modos de abrir el fichero
const string READ = "r";							//Abre un fichero de texto para lectura
const string WRITE = "w";							//Trunca, a longitud cero o crea un fichero de texto para escribir
const string WRITE_END = "a";						//Añade; abre o crea un fichero de texto para escribir al final del fichero (EOF)
const string BINARY_MODE_READ = "rb";				//Abre un fichero en modo binario para lectura
const string BINARY_MODE_WRITE = "wb";				//Trunca, a longitud cero o crea un fichero en modo binario para escribir
const string BINARY_MODE_WRITE_END = "ab";			//Añade; abre o crea un fichero en modo binario para escribir al final del fichero (EOF)
const string UPDATE_READ = "r+";					//Abre un fichero de texto para actualización (lectura y escritura)
const string UPDATE_WRITE = "w+";					//Trunca, a longitud cero o crea un fichero de texto para actualización
const string UPDATE_WRITE_END = "a+";				//Añade, abre o crea un fichero de texto para actualización, escribiendo al final del fichero (EOF)
const string BINARY_MODE_UPDATE_READ = "r+b";		//Abre un fichero en modo binario para actualización (lectura y escritura) -- rb+ | r+b
const string BINARY_MODE_UPDATE_WRITE = "w+b";		//Trunca, a longitud cero o crea un fichero en modo binario para actualización -- wb+ | w+b
const string BINARY_MODE_UPDATE_WRITE_END = "a+b";	//Añade, abre o crea un fichero en modo binario para actualización, escribiendo al final del fichero (EOF) -- ab+ | a+b

//Posibles modos de establecer el buffer de redireccionamiento
const int IOFBF = _IOFBF;
const int IOLBF = _IOLBF;
const int IONBF = _IONBF;

class RandomAccessFile
{
	public:
		//Constructor
		//El tipo de dato string esta preparado para coger en una asignacion un char array
		//es por eso que no es necesario un constructor para recoger un char array
		__declspec(dllexport) RandomAccessFile(const string &_path, const string &mode = READ);

		//Destructor
		virtual __declspec(dllexport) ~RandomAccessFile(void);

		//Read data types
		/*
		En estos metodos deben de validarse los valores de salida de fread,
		si devuelven un valor menor que 1 que es la cantidad de bloques de n-bytes
		que leeran es porque hubo un error en la lectura, y por la caracteristica
		de los valores que devuelven no se pueden indicar errores en el parametro
		de salida
		*/
		__declspec(dllexport) int8_t readInt8();
		__declspec(dllexport) int8_t readInt8(const uint32_t &index);
		__declspec(dllexport) uint8_t readUnsignedInt8();
		__declspec(dllexport) uint8_t readUnsignedInt8(const uint32_t &index);
		__declspec(dllexport) int16_t readInt16();
		__declspec(dllexport) int16_t readInt16(const uint32_t &index);
		__declspec(dllexport) uint16_t readUnsignedInt16();
		__declspec(dllexport) uint16_t readUnsignedInt16(const uint32_t &index);
		__declspec(dllexport) int32_t readInt32();
		__declspec(dllexport) int32_t readInt32(const uint32_t &index);
		__declspec(dllexport) uint32_t readUnsignedInt32();
		__declspec(dllexport) uint32_t readUnsignedInt32(const uint32_t &index);
		__declspec(dllexport) int64_t readInt64();
		__declspec(dllexport) int64_t readInt64(const uint32_t &index);
		__declspec(dllexport) uint64_t readUnsignedInt64();
		__declspec(dllexport) uint64_t readUnsignedInt64(const uint32_t &index);
		__declspec(dllexport) float readFloat();
		__declspec(dllexport) float readFloat(const uint32_t &index);
		__declspec(dllexport) double readDouble();
		__declspec(dllexport) double readDouble(const uint32_t &index);
		__declspec(dllexport) char readChar();
		__declspec(dllexport) char readChar(const uint32_t &index);
		__declspec(dllexport) uchar readUnsignedChar();
		__declspec(dllexport) uchar readUnsignedChar(const uint32_t &index);

		//Read bytes
		__declspec(dllexport) bool read(uint8_t bytes[], const uint32_t &size);								//TRUE en caso de poder leer todos los bytes solicitados
		__declspec(dllexport) bool read(uint8_t bytes[], const uint32_t &index, const uint32_t &size);		//Idem
		__declspec(dllexport) bool read(int8_t bytes[], const uint32_t &size);
		__declspec(dllexport) bool read(int8_t bytes[], const uint32_t &index, const uint32_t &size);

		//Write data types
		__declspec(dllexport) bool write(const int8_t &value);							//TRUE en caso de escribir todo sin problema, para todos los casos de write
		__declspec(dllexport) bool write(const int8_t &value, const uint32_t &index);
		__declspec(dllexport) bool write(const uint8_t &value);
		__declspec(dllexport) bool write(const uint8_t &value, const uint32_t &index);
		__declspec(dllexport) bool write(const int16_t &value);
		__declspec(dllexport) bool write(const int16_t &value, const uint32_t &index);
		__declspec(dllexport) bool write(const uint16_t &value);
		__declspec(dllexport) bool write(const uint16_t &value, const uint32_t &index);
		__declspec(dllexport) bool write(const int32_t &value);
		__declspec(dllexport) bool write(const int32_t &value, const uint32_t &index);
		__declspec(dllexport) bool write(const uint32_t &value);
		__declspec(dllexport) bool write(const uint32_t &value, const uint32_t &index);
		__declspec(dllexport) bool write(const int64_t &value);
		__declspec(dllexport) bool write(const int64_t &value, const uint32_t &index);
		__declspec(dllexport) bool write(const uint64_t &value);
		__declspec(dllexport) bool write(const uint64_t &value, const uint32_t &index);
		__declspec(dllexport) bool write(const float &value);
		__declspec(dllexport) bool write(const float &value, const uint32_t &index);
		__declspec(dllexport) bool write(const double &value);
		__declspec(dllexport) bool write(const double &value, const uint32_t &index);
		__declspec(dllexport) bool write(const char &value);
		__declspec(dllexport) bool write(const char &value, const uint32_t &index);

		//Write bytes
		__declspec(dllexport) bool write(uint8_t bytes[], const uint32_t &size);							//TRUE en caso de poder escribir todos los bytes correctamente
		__declspec(dllexport) bool write(uint8_t bytes[], const uint32_t &index, const uint32_t &size);		//Idem
		__declspec(dllexport) bool write(int8_t bytes[], const uint32_t &size);
		__declspec(dllexport) bool write(int8_t bytes[], const uint32_t &index, const uint32_t &size);

		//Movement
		__declspec(dllexport) bool isEOF();											//TRUE en caso de ser fin de fichero
		__declspec(dllexport) bool seek(const uint32_t &byte);						//FALSE en caso de error
		__declspec(dllexport) bool skipBytes(const uint32_t &bytes);				//FALSE en caso de error
		__declspec(dllexport) uint32_t bytePosition();								//Devuelve la posicion actual en el fichero, en bytes. En caso de error devuelve < 0
		__declspec(dllexport) void begin();											//FALSE en caso de error
		__declspec(dllexport) bool end();											//FALSE en caso de error
		__declspec(dllexport) bool lessMovementFromCursor(const uint32_t &index);	//FALSE en caso de error

		//Errors
		__declspec(dllexport) bool haveErrors();				//TRUE en caso de haber error/es

		//Redireccion
		__declspec(dllexport) void setBuffer(char data[], const uint32_t &size, const uint32_t &mode = _IOFBF);		//Preferiblemente iniciar data como: "char data[BUFSIZ] = {0};"
		__declspec(dllexport) bool flush();						//TRUE en caso de despejar correctamente la entrada de bytes al fichero

		//Endding
		__declspec(dllexport) bool close();						//TRUE al cerrarse correctamente

	private:
		string path;
		FILE *raf;
};