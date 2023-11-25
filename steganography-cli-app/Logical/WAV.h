#pragma once

#ifndef WAVE_FILE
#define WAVE_FILE
#endif

#ifndef RANDOM_ACCESS_FILE
#include "RandomAccessFile.h"
#endif

#include <xstring>
#include <map>

using namespace std;

//La clase WAV solo tendrá disponible por el momento 3 bloques chunk: el común que identifica el fichero RIFF/RIFX,
//el de formato y el de datos

//No se establecen constantes a los índices de los bloques de información en el fichero
//pues como pueden haber varios bloques chunk el valor de los indices puede cambiar
//En su lugar guardaremos en un mapa los indices a la informacion que puede ser conocida
//y manipulada por esta clase que serán los valores de los chunk posibles
typedef enum
{
	//Common chunk
	CHUNK_COMMON_ID = 0,
	CHUNK_COMMON_SIZE,
	FORMAT,
	//Format chunk
	CHUNK_FORMAT_ID,
	CHUNK_FORMAT_SIZE,
	AUDIO_FORMAT,
	NUMBER_CHANNELS,
	SAMPLE_RATE,
	BYTE_RATE,
	BLOCK_ALIGN,
	BITS_PER_SAMPLE,
	//Chunk data audio
	CHUNK_DATA_ID,
	CHUNK_DATA_SIZE,
	DATA_AUDIO
}Index;

/*
  Excepciones que lanza esta clase
      IncorrectFileType
	  InconsistentData
	  SampleSizeDifferent
*/

class WAV
{
	public:
		__declspec(dllexport) WAV(const string &_path);

		virtual __declspec(dllexport) ~WAV(void);

		//Métodos getters y setters para los datos de todo el fichero
		/*
		  Las variables chunkID, format, chunkFormatID y chunkDataID
		  no son modificables
		  Tampoco lo son byteRate y blockAlign
		  El valor de chunkDataSize es un caso particular que se modifica a partir de la duración en segundos
		*/
		__declspec(dllexport) bool setChunkCommonSize(const uint32_t &_chunkCommonSize);
		__declspec(dllexport) bool setChunkFormatSize(const uint32_t &_chunkFormatSize);
		__declspec(dllexport) bool setAudioFormat(const uint16_t &_audioFormat);
		__declspec(dllexport) bool setNumberChannels(const uint16_t &_numberChannels);
		__declspec(dllexport) bool setSampleRate(const uint32_t &_sampleRate);
		__declspec(dllexport) bool setBitsPerSample(const uint16_t &_bitsPerSample);
		__declspec(dllexport) bool setChunkDataSize(const uint32_t &secondRemain);

		__declspec(dllexport) string getChunkCommonID();
		__declspec(dllexport) uint32_t getChunkCommonSize();
		__declspec(dllexport) string getFormat();
		__declspec(dllexport) string getChunkFormatID();
		__declspec(dllexport) uint32_t getChunkFormatSize();
		__declspec(dllexport) uint16_t getAudioFormat();
		__declspec(dllexport) uint16_t getNumberChannels();
		__declspec(dllexport) uint32_t getSampleRate();
		__declspec(dllexport) uint32_t getByteRate();
		__declspec(dllexport) uint16_t getBlockAlign();
		__declspec(dllexport) uint16_t getBitsPerSample();
		__declspec(dllexport) string getChunkDataID();
		__declspec(dllexport) uint32_t getChunkDataSize();

		//Otros metodos importantes
		__declspec(dllexport) uint32_t secondDuration();
		__declspec(dllexport) uint32_t fileSize();

		//Manipulacion de las muestras/samples
		//Estos metodos lanzan excepciones en caso de que el fichero wav no posea las muestras del tipo que se desee
		__declspec(dllexport) void gotoSamples();

		__declspec(dllexport) uint8_t getSample_8();
		__declspec(dllexport) uint8_t getSample_8(const uint32_t &index);
		__declspec(dllexport) int16_t getSample_16();
		__declspec(dllexport) uint16_t getSample_16(const uint32_t &index);


		//Metodos propios de file
		__declspec(dllexport) bool close();

		__declspec(dllexport) RandomAccessFile *getRAF();
		__declspec(dllexport) map<Index, uint32_t> getMap(){
			return info;
		}

	private:
		RandomAccessFile *raf;

		//Mapa para guardar los indices donde se encuentran los datos que puede manipular esta clase
		map<Index, uint32_t> info;

		/*
		NOTAS:
			1. El tiempo de duración en segundos se puede obtener mediante la ecuación chunkDataSize = duracionEnSegundos * sampleRate * numChannels * bitsPerSample/8
			2. La única forma de comprobar que sea correcto el tamaño en bytes de la información de audio es colocándose al final del encabezado del segundo
			   sub-bloque chunk, pedir la posición dentro del fichero, ir hasta el final del fichero, pedir la posición y la diferencia dará = chunkDataSize
		*/
		
		//Chunk common header
		uint8_t *chunkCommonID;	//Identifica el fichero, debe ser 'RIFF', no es modificable
		uint32_t chunkCommonSize;	//Es el tamaño del fichero menos los 8 primeros bytes(los dos primeros campos)
		uint8_t *format;			//Identifica el tipo de fichero y por consiguiente la estructura de los chunk siguientes, no es modificable
		//WAV format chunk header
		uint8_t *chunkFormatID;	//Identifica el sub-bloque chunk, debe ser 'fmt', no es modificable
		uint32_t chunkFormatSize;	//Son los restantes bytes del sub-bloque, estos + los 8 bytes anterios suman el tamaño del sub-bloque
		uint16_t audioFormat;		//Categoría de formato del fichero WAV
		uint16_t numberChannels;	//Numero de canales en el segmento de datos, mono=1, stereo=2
		uint32_t sampleRate;		//Frecuencia de muestreo (11.025, 22.050 ó 44.100)
		uint32_t byteRate;			//Numero de bytes que se deben reproducir por segundo, = sampleRate * numberChannels * bitsPerSample/8
		uint16_t blockAlign;		//Alineación de los bloques del campo de datos, = numberChannels * bitsPerSample/8
		uint16_t bitsPerSample;		//Bits por muestra. 8 bits = 8, 16 bits = 16, etc.
		//WAV data chunk header
		uint8_t *chunkDataID;		//Identifica el sub-bloque chunk, debe ser 'data', no es modificable
		uint32_t chunkDataSize;		//Tamaño en bytes de los datos de audio, son los restantes bytes del bloque, = duracionEnSegundos * sampleRate * numberChannels * bitsPerSample/8
		//Después solo quedan los bytes de la información sonora

		//Validaciones de los campos en los chunk queson calculables
		bool validateByteRate();
		bool validateBlockAlign();
};

