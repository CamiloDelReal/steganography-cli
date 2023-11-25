// Testing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>

#ifndef BITMAP_FILE
#include "BMP.h"
#endif

#ifndef WAVE_FILE
#include "WAV.h"
#endif

#ifndef EXCEPTION_TYPES
#include "ExceptionTypes.h"
#endif

#ifndef ESTEGANOGRAFIA_LSB_H
#include "Esteganografia_LSB.h"
#endif

#include "ErrorC.h"
#include <stdexcept>
using namespace std;

string getExtension(string path)
{
	string ext;
	bool doit = false;
	int siz = path.size();
	int lon = 0;
	while(!doit && siz > 0)
	{
		if(path.at(siz - 1) != '.')
			lon++;
		else
			doit = true;
		siz--;
	}
	return path.substr(path.size() - lon, lon);
}

void read()
{
	string path,msg, ext;
	cout<<"Entre el nombre del fichero (tipo bmp/wav)"<<endl;
	cin>>path;

	try
	{
		ext = getExtension(path);
		if(ext == "bmp" || ext == "BMP")
		{
			BMP *bmp = new BMP(path.c_str());
			msg = Esteganografia_LSB::LSB_BMP_read(bmp);
			bmp->close();
		}
		else if(ext == "wav" || ext == "WAV")
		{
			WAV *wav = new WAV(path.c_str());
			msg = Esteganografia_LSB::LSB_WAV_read(wav);
			wav->close();
		}
		else
		{
			cout<<"No introdujo un tipo de fichero conocido"<<endl;
			system("pause");
			system("cls");
			return;
		}
		cout<<"Mensaje extraido"<<endl;
		cout<<msg.c_str()<<endl<<endl;
		system("pause");
		system("cls");
	}
	catch (exception ex)
	{
		cout<<"Error abriendo el fichero\nProbablemente no exista"<<endl<<endl;
		system("pause");
		system("cls");
	}
}

void write()
{
	string path, msg, ext;
	cout<<"Entre el nombre del fichero (tipo bmp/wav)"<<endl;
	cin>>path;

	//Se quito de aqui la entrada del texto a guardar puesto que en caso
	//de no existir el fichero el usuario se ahorraba la molestia de haber
	//escrito el texto con anterioridad
	/*cout<<"Entre el mensaje que desee guardar"<<endl;
	cin>>msg;*/

	try
	{
		ext = getExtension(path);		
		if(ext == "bmp" || ext == "BMP")
		{			
			BMP *bmp = new BMP(path.c_str());
			cout<<"Entre el mensaje que desee guardar"<<endl;
			cin>>msg;
			Esteganografia_LSB::LSB_BMP_write(bmp, msg);
			bmp->close();
		}
		else if(ext == "wav" || ext == "WAV")
		{
			WAV *wav = new WAV(path.c_str());
			cout<<"Entre el mensaje que desee guardar"<<endl;
			cin>>msg;
			Esteganografia_LSB::LSB_WAV_write(wav, msg);
			wav->close();
		}
		else
		{
			cout<<"No introdujo un tipo de fichero conocido"<<endl;
			system("pause");
			system("cls");
			return;
		}
		system("pause");
		system("cls");
	}
	catch (exception ex)
	{
		cout<<"Error abriendo el fichero\nProbablemente no exista"<<endl<<endl;
		system("pause");
		system("cls");
	}
}

int menu()
{
	cout<<"------Menu------"<<endl;
	cout<<"1. Leer texto de un fichero (bmp/wav)"<<endl;
	cout<<"2. Escribir texto en un fichero (bmp/wav)"<<endl;
	cout<<"3. Salir"<<endl;
	int option;
	cin>>option;
	return option;
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	//Testing BMP
	BMP *bmp = new BMP("road.bmp");

	cout<<"Encabezado BMP"<<endl;
	cout<<"Type                 "<<bmp->getFileType()<<endl;
	cout<<"Size file            "<<bmp->getFileSize()<<endl;
	cout<<"Reserved 1           "<<bmp->getReservedOne()<<endl;
	cout<<"Reserved 2           "<<bmp->getReservedTwo()<<endl;
	cout<<"Offset               "<<bmp->getOffset()<<endl;
	cout<<"Header size          "<<bmp->getHeaderSize()<<endl;
	cout<<"Pixel width          "<<bmp->getPixelsWidth()<<endl;
	cout<<"Pixel height         "<<bmp->getPixelsHeight()<<endl;
	cout<<"Planes number        "<<bmp->getPlanesNumber()<<endl;
	cout<<"Bits per pixel       "<<bmp->getBitsPerPixel()<<endl;
	cout<<"Compression          "<<bmp->getCompression()<<endl;
	cout<<"Size image           "<<bmp->getImageSize()<<endl;
	cout<<"Hor resolution       "<<bmp->getHorizontalResolution()<<endl;
	cout<<"Ver resolution       "<<bmp->getVerticalResolution()<<endl;
	cout<<"Table colors         "<<bmp->getColorsTable()<<endl;
	cout<<"Importants colors    "<<bmp->getImportantsColors()<<endl;
	cout<<endl<<endl;
	*/

	/*
	//Esteganografia en ficheros BMP
	//RandomAccessFile *raf = new RandomAccessFile("road.bmp", "rb+");	
	try{
		Esteganografia_LSB::LSB_BMP_write(bmp, string("Camilo Jose del Real Martell"));
		string str = Esteganografia_LSB::LSB_BMP_read(bmp);
		cout<<"Texto extraido"<<endl;
		cout<<str.c_str()<<endl;
	}
	catch(exception ex)
	{
		cout<<ex.what()<<endl;
	}
	//raf->close();

	//delete raf;
	bmp->close();
	*/



	/*
	//Testing WAV
	WAV *wav = new WAV("max_2.wav");

	cout<<"Encabezado WAV"<<endl;
	cout<<wav->getMap()[CHUNK_COMMON_ID]<<". chunkCommonID    "<<wav->getChunkCommonID()<<endl;
	cout<<wav->getMap()[CHUNK_COMMON_SIZE]<<". chunkCommonSize  "<<wav->getChunkCommonSize()<<endl;
	cout<<wav->getMap()[FORMAT]<<". format           "<<wav->getFormat()<<endl;
	cout<<wav->getMap()[CHUNK_FORMAT_ID]<<". chunkFormatID    "<<wav->getChunkFormatID()<<endl;
	cout<<wav->getMap()[CHUNK_FORMAT_SIZE]<<". chunkFormatSize  "<<wav->getChunkFormatSize()<<endl;
	cout<<wav->getMap()[AUDIO_FORMAT]<<". audioFormat      "<<wav->getAudioFormat()<<endl;
	cout<<wav->getMap()[NUMBER_CHANNELS]<<". numberChannels   "<<wav->getNumberChannels()<<endl;
	cout<<wav->getMap()[SAMPLE_RATE]<<". sampleRate       "<<wav->getSampleRate()<<endl;
	cout<<wav->getMap()[BYTE_RATE]<<". byteRate         "<<wav->getByteRate()<<endl;
	cout<<wav->getMap()[BLOCK_ALIGN]<<". blockAlign       "<<wav->getBlockAlign()<<endl;
	cout<<wav->getMap()[BITS_PER_SAMPLE]<<". bitsPerSample    "<<wav->getBitsPerSample()<<endl;
	cout<<wav->getMap()[CHUNK_DATA_ID]<<". chunkDataID      "<<wav->getChunkDataID()<<endl;
	cout<<wav->getMap()[CHUNK_DATA_SIZE]<<". chunkDataSize    "<<wav->getChunkDataSize()<<endl;
	cout<<wav->getMap()[DATA_AUDIO]<<endl<<endl;
	system("pause");
	*/

	/*
	//Testing para Dennys
	wav->gotoSamples();
	RandomAccessFile *ra = wav->getRAF();

	if(wav->getBitsPerSample() == 8)
	{
		uint8_t by = ra->readUnsignedInt8();
		by *= 2;
		//validacion del rango de by >0 <255
		ra->skipBytes(-1);
		ra->write(by);
	}
	else
	{
		int16_t by = ra->readInt16();
		by *= 2;
		//validacion del rango de by >0 <511
		ra->skipBytes(-1);
		ra->write(by);
	}
	*/

	/*
	//Esteganografia en ficheros WAV
	//RandomAccessFile *raf = new RandomAccessFile("Riff.wav", "rb+");
	try{
		Esteganografia_LSB::LSB_WAV_write(wav, "Mercedes Martell y Jose del Real");
		string str = Esteganografia_LSB::LSB_WAV_read(wav);
		cout<<"Texto extraido"<<endl;
		cout<<str.c_str()<<endl;
	}
	catch(exception ex)
	{
		cout<<ex.what()<<endl;
	}	
	//raf->close();

	wav->close();
	*/


	
	//Programa principal
	int option;
	do 
	{
		option = menu();

		switch(option)
		{
			case 1:
				read();
				break;
			case 2:
				write();
				break;
			case 3:1
				exit(0);
				break;
			default:
				cout<<"No se reconoce la orden"<<endl;
				system("pause");
				system("cls");
			}
	} while (true);
	


	return 0;
}

