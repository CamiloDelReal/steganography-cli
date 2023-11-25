#ifndef WAVE_FILE
#include "WAV.h"
#endif

#ifndef EXCEPTION_TYPES
#include "ExceptionTypes.h"
#endif

#include <iostream>
using namespace std;

WAV::WAV(const string &_path)
{
	raf = new RandomAccessFile(_path, BINARY_MODE_UPDATE_READ);

	chunkCommonID = new uint8_t[4];
	memset(chunkCommonID, 0, 5);	//Inicializamos en cero todos los caracteres de chunkCommonID
									//son cinco bloques de 1 byte pues se tiene en cuenta
									//el caracter EOF
	format = new uint8_t[4];
	memset(format, 0, 5);			//Lo mismo para los restantes arreglos de bytes

	chunkFormatID = new uint8_t[4];
	memset(chunkFormatID, 0, 5);

	chunkDataID = new uint8_t[4];
	memset(chunkDataID, 0, 5);


	uint32_t lenght = 0;
	uint8_t tmp[5] = {0};

	raf->read(chunkCommonID, 4);
	//Validar que sea RIFF o RIFX

	if(strcmp((const char*)chunkCommonID, "RIFF") == 0)
	{
		info[CHUNK_COMMON_ID] = 0;

		chunkCommonSize = raf->readUnsignedInt32();
		info[CHUNK_COMMON_SIZE] = 4;

		raf->read(format, 4);
		info[FORMAT] = 8;

		if(strcmp((const char*)format, "WAVE") != 0)
		{
			IncorrectFileType ex = *(new IncorrectFileType("El fichero no es de tipo WAVE"));
			throw ex;
		}

		lenght = chunkCommonSize + 8;
	}
	else
	{
		IncorrectFileType ex = *(new IncorrectFileType("El fichero no contiene el formato RIFF"));
		throw ex;
	}

	//Procedemos a leer todos los chunk restantes
	uint32_t pos = 0;
	while(raf->bytePosition() < lenght && lenght - raf->bytePosition() >= 4)
	{
		memset(tmp, 0, 4);
		raf->read(tmp, 4);

		//Comprobar si es el chunk formato
		if(strcmp((const char*)tmp, "fmt ") == 0)
		{
			memcpy(chunkFormatID, tmp, 4);
			pos = raf->bytePosition();
			info[CHUNK_FORMAT_ID] = pos - 4;

			chunkFormatSize = raf->readUnsignedInt32();
			info[CHUNK_FORMAT_SIZE] = pos;

			audioFormat = raf->readUnsignedInt16();
			info[AUDIO_FORMAT] = (pos += 4);

			numberChannels = raf->readUnsignedInt16();
			info[NUMBER_CHANNELS] = (pos += 2);

			sampleRate = raf->readUnsignedInt32();
			info[SAMPLE_RATE] = (pos += 2);

			byteRate = raf->readUnsignedInt32();
			info[BYTE_RATE] =(pos += 4);

			blockAlign = raf->readUnsignedInt16();
			info[BLOCK_ALIGN] = (pos += 4);

			bitsPerSample = raf->readUnsignedInt16();
			info[BITS_PER_SAMPLE] = (pos += 2);

			//Validar los campos calculables de este chunk
			if(byteRate != (sampleRate * numberChannels * bitsPerSample / 8))
			{
				InconsistentData ex = *(new InconsistentData("Inconsistencia en los datos del fichero\nByte-rate no correcto"));
				throw ex;
			}
			if(blockAlign != (numberChannels * bitsPerSample / 8))
			{
				InconsistentData ex = *(new InconsistentData("Inconsistencia en los datos del fichero\nAlineación de los bloques del campo de datos no correcta"));
				throw ex;
			}
		}
		else if(strcmp((const char*)tmp, "data") == 0)
		{
			memcpy(chunkDataID, tmp, 4);
			pos = raf->bytePosition();
			info[CHUNK_DATA_ID] = pos - 4;

			chunkDataSize = raf->readUnsignedInt32();
			info[CHUNK_DATA_SIZE] = pos;

			info[DATA_AUDIO] = (pos += 4);
			//Desplazamiento hasta el final del flujo de bytes
			raf->skipBytes(chunkDataSize);
			
			//Validar el campo calculable de este chunk no lo podemos validar
			//de momento pues no tenemos los segundos de duracion
			
		}
		else
		{
			//Como no es ninguno de los anteriores lo saltamos
			uint32_t size = raf->readUnsignedInt32();
			raf->skipBytes(size);
		}
		
		  //Aqui se anidarían los esle restantes para los chunk que faltan (son desconocidos para mi)
	}

	//Validar que se hayan encontrado los chunk de formato y datos en el fichero WAVE
	if(info[CHUNK_FORMAT_ID] == 0)
	{
		InconsistentData ex = *(new InconsistentData("Inconsistencia en los datos del fichero\nNo se encontró en chunk de formato"));
		throw ex;
	}
	if(info[CHUNK_DATA_ID] == 0)
	{
		InconsistentData ex = *(new InconsistentData("Inconsistencia en los datos del fichero\nNo se encontró en chunk de datos"));
		throw ex;
	}

}


WAV::~WAV(void)
{
}


bool WAV::setChunkCommonSize(const uint32_t &_chunkCommonSize)
{
	chunkCommonSize = _chunkCommonSize;
	return raf->write(chunkCommonSize, info[CHUNK_COMMON_SIZE]);
}
bool WAV::setChunkFormatSize(const uint32_t &_chunkFormatSize)
{
	chunkFormatSize = _chunkFormatSize;
	return raf->write(chunkFormatSize, info[CHUNK_FORMAT_SIZE]);
}
bool WAV::setAudioFormat(const uint16_t &_audioFormat)
{
	audioFormat =_audioFormat;
	return raf->write(audioFormat, info[AUDIO_FORMAT]);
}
bool WAV::setNumberChannels(const uint16_t &_numberChannels)
{
	numberChannels = _numberChannels;
	return raf->write(numberChannels, info[NUMBER_CHANNELS]);
}
bool WAV::setSampleRate(const uint32_t &_sampleRate)
{
	sampleRate = _sampleRate;
	return raf->write(sampleRate, info[SAMPLE_RATE]);
}
bool WAV::setBitsPerSample(const uint16_t &_bitsPerSample)
{
	bitsPerSample = _bitsPerSample;
	return raf->write(bitsPerSample, info[BITS_PER_SAMPLE]);
}
bool WAV::setChunkDataSize(const uint32_t &secondRemain)
{
	chunkDataSize = secondRemain * sampleRate * numberChannels * bitsPerSample / 8;
	return raf->write(chunkDataSize, info[CHUNK_DATA_SIZE]);
}

string WAV::getChunkCommonID()
{
	return (char*)chunkCommonID;
}
uint32_t WAV::getChunkCommonSize()
{
	return chunkCommonSize;
}
string WAV::getFormat()
{
	return (char*)format;
}
string WAV::getChunkFormatID()
{
	return (char*)chunkFormatID;
}
uint32_t WAV::getChunkFormatSize()
{
	return chunkFormatSize;
}
uint16_t WAV::getAudioFormat()
{
	return audioFormat;
}
uint16_t WAV::getNumberChannels()
{
	return numberChannels;
}
uint32_t WAV::getSampleRate()
{
	return sampleRate;
}
uint32_t WAV::getByteRate()
{
	return byteRate;
}
uint16_t WAV::getBlockAlign()
{
	return blockAlign;
}
uint16_t WAV::getBitsPerSample()
{
	return bitsPerSample;
}
string WAV::getChunkDataID()
{
	return (char*)chunkDataID;
}
uint32_t WAV::getChunkDataSize()
{
	return chunkDataSize;
}


uint32_t WAV::secondDuration()
{
	return ((chunkDataSize * 8) / (sampleRate * numberChannels * bitsPerSample) );
}

uint32_t WAV::fileSize()
{
	uint32_t pos = raf->bytePosition();
	raf->end();
	uint32_t size = raf->bytePosition();
	raf->seek(pos);
	return size;
}

void WAV::gotoSamples()
{
	raf->seek(info[DATA_AUDIO]);
}
uint8_t WAV::getSample_8()
{
	if(bitsPerSample != 8)
	{
		SampleSizeDifferent ex = *(new SampleSizeDifferent("Ha solicitado una muestra de 8 bits, pero estas son de un tamaño diferente"));
		throw ex;
	}
	uint32_t pos = raf->bytePosition();
	if(fileSize() - pos < 1)
	{
		NoBytes ex = *(new NoBytes("No hay mas bytes para leer, posible EOF"));
		throw ex;
	}
	uint8_t bits = raf->readUnsignedInt8();
	return bits;
}
uint8_t WAV::getSample_8(const uint32_t &index)
{
	if(bitsPerSample != 8)
	{
		SampleSizeDifferent ex = *(new SampleSizeDifferent("Ha solicitado una muestra de 8 bits, pero estas son de un tamaño diferente"));
		throw ex;
	}
	uint32_t pos = raf->bytePosition();
	if(fileSize() - pos < 1)
	{
		NoBytes ex = *(new NoBytes("No hay mas bytes para leer, posible EOF"));
		throw ex;
	}
	//Posicionarnos en la posicion indicada
	gotoSamples();
	raf->skipBytes(index);	//las muestras son de 8 bits, por tanto, moverme una posicion es moverme 8 bits
	
	uint8_t bits = raf->readUnsignedInt8();
	return bits;
}
int16_t WAV::getSample_16()
{
	if(bitsPerSample != 16)
	{
		SampleSizeDifferent ex = *(new SampleSizeDifferent("Ha solicitado una muestra de 16 bits, pero estas son de un tamaño diferente"));
		throw ex;
	}
	uint32_t pos = raf->bytePosition();
	if(fileSize() - pos < 2)
	{
		NoBytes ex = *(new NoBytes("No hay mas bytes para leer, posible EOF"));
		throw ex;
	}
	int16_t bits = raf->readInt16();
	return bits;
}

uint16_t WAV::getSample_16(const uint32_t &index)
{
	if(bitsPerSample != 16)
	{
		SampleSizeDifferent ex = *(new SampleSizeDifferent("Ha solicitado una muestra de 16 bits, pero estas son de un tamaño diferente"));
		throw ex;
	}
	uint32_t pos = raf->bytePosition();
	if(fileSize() - pos < 2)
	{
		NoBytes ex = *(new NoBytes("No hay mas bytes para leer, posible EOF"));
		throw ex;
	}
	//Posicionarnos en la posicion indicada
	gotoSamples();
	raf->skipBytes(index * 2);	//

	int16_t bits = raf->readInt16();
	return bits;
}

bool WAV::close()
{
	return raf->close();
}

RandomAccessFile * WAV::getRAF()
{
	return raf;
}