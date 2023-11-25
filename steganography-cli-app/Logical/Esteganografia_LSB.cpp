#ifndef ESTEGANOGRAFIA_LSB_H
#include "Esteganografia_LSB.h"
#endif

#ifndef EXCEPTION_TYPES
#include "ExceptionTypes.h"
#endif

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

Esteganografia_LSB::Esteganografia_LSB(void)
{
}


Esteganografia_LSB::~Esteganografia_LSB(void)
{
}

string Esteganografia_LSB::toBinary(string text)
{
	string bits;

	for(int i = 0; i < text.size(); i++)
	{
		char c = text.at(i);
		
		for(int i = 7; i >= 0; i--)
		{
			if(c & (1 << i))
			{
				bits += "1";
			}
			else
			{
				bits += "0";
			}
		}
	}

	return bits;
}

string Esteganografia_LSB::toBinary( int entero )
{
	string bits;
	for(int i = 31; i >= 0; i--)
	{
		if(entero & (1 << i))
		{
			bits += "1";
		}
		else
		{
			bits += "0";
		}
	}
	return bits;
}


string Esteganografia_LSB::padding( string text )
{
	char size[5] = {0};
	sprintf_s(size, "%d", text.size());
	string str = (char*)size;
	int le = 4 - str.size();
	for(int i = 0; i < le; i++)
		str.insert(0, "0");
	return str;
}


void Esteganografia_LSB::LSB_BMP_write( BMP *bmp, string text )
{
	RandomAccessFile *file = bmp->getRAF();

	string bitsLSB = toBinary("LSB");
	string bitsLength = toBinary(text.size());
	string bitsText = toBinary(text);


	//cout<<bitsLSB.size()<< "---" <<bitsLSB.c_str()<<endl;
	//cout<<bitsLength.size()<<"---"<<bitsLength.c_str()<<endl;
	//cout<<bitsText.size()<<"---"<<bitsText.c_str()<<endl;

	//representaion binaria
	string str = bitsLSB + bitsLength + bitsText;
	//cout<<str.size()<<"---"<<str.c_str()<<endl;

	if(bmp->getBitsPerPixel() != 24)
	{
		InconsistentData ex = *(new InconsistentData("El fichero no es de 24 bits por pixels"));
		throw ex;
	}

	file->end();
	int lengthfile = file->bytePosition();
	if(lengthfile - 54 < str.size())
	{
		NoBytes ex = *(new NoBytes("No hay espacio suficiente"));
		throw ex;
	}

	file->seek(54);
	for(int i = 0; i < str.size(); i++)
	{
		uint8_t byt = file->readUnsignedInt8();
		//cout<<(int)byt<<endl;
		if(byt & 1 && str.at(i) == '0')
			byt -= 1;
		else if( !(byt & 1) && str.at(i) == '1')
			byt += 1;
		//cout<<(int)byt<<endl;
		file->skipBytes(-1);
		file->write(byt);
	}


}

string Esteganografia_LSB::LSB_BMP_read( BMP *bmp )
{
	RandomAccessFile *file = bmp->getRAF();

	file->seek(54);

	uint8_t *lsb = new uint8_t[24];
	memset(lsb, 0, 25);
	file->read(lsb, 24);

	string bitsLSB = toBinary("LSB");

	string isLSB;
	for(int i = 0; i < 24; i++)
	{
		if(lsb[i] & 1)
			isLSB.append("1");
		else
			isLSB.append("0");
	}
	//cout<<"firma leida  "<<isLSB.c_str()<<endl;
	if(isLSB != bitsLSB)
	{
		NoSignature ex = *(new NoSignature("El fichero no contiene firma"));
		throw ex;
	}

	uint8_t *size = new uint8_t[32];
	memset(size, 0, 33);
	file->read(size, 32);

	string bitsLength;
	for(int i = 0; i < 32; i++)
	{
		if(size[i] & 1)
			bitsLength.append("1");
		else
			bitsLength.append("0");
	}
	int length = toInt(bitsLength, 32);


	uint8_t *data = new uint8_t[length*8];
	memset(data, 0, length*8+1);
	file->read(data, length*8);

	string text;
	for(int i = 0; i < length * 8; i++)
	{
		if(data[i] & 1)
			text.append("1");
		else
			text.append("0");
	}

	string finalText = toString(text);

	return finalText;
}

int Esteganografia_LSB::toInt( string entero , int bitsSize)
{
	int length = 0;

	for(int i = 0; i < entero.size(); i++)
	{
		if(entero.at(i) == '1')
			length += square(2, (bitsSize - 1) - i);
	}

	return length;
}

int Esteganografia_LSB::square(int value, int po)
{
	int re = 1;
	for(int i = 0; i < po ; i++)
		re *= value;
	return re;
}

string Esteganografia_LSB::toString( string bits )
{
	string text;
	uint8_t *cad = new uint8_t[bits.size() / 8];
	memset(cad, 0, bits.size() / 8 + 1);

	int index = 0;
	for(int i = 0; i < bits.size(); i += 8, index++)
	{
		string str = bits.substr(i, 8);
		int value = toInt(str, 8);
		//char c = value;
		cad[index] = value;
	}

	return (char*)cad;
}

void Esteganografia_LSB::LSB_WAV_write( WAV *wav, string text )
{
	RandomAccessFile *file = wav->getRAF();

	string bitsLSB = toBinary("LSB");
	string bitsLength = toBinary(text.size());
	string bitsText = toBinary(text);


	//cout<<bitsLSB.size()<< "---" <<bitsLSB.c_str()<<endl;
	//cout<<bitsLength.size()<<"---"<<bitsLength.c_str()<<endl;
	//cout<<bitsText.size()<<"---"<<bitsText.c_str()<<endl;

	//representaion binaria
	string str = bitsLSB + bitsLength + bitsText;
	//cout<<str.size()<<"---"<<str.c_str()<<endl;
	
	uint32_t size = wav->getChunkDataSize();
	//cout<<"Size "<<size;

	if(wav->getBitsPerSample() != 16)
	{
		InconsistentData ex = *(new InconsistentData("El fichero de es de 16 bits/muestra"));
		throw ex;
	}
	if(wav->getNumberChannels() != 1)
	{
		InconsistentData ex = *(new InconsistentData("El fichero no es de un solo canal"));
		throw ex;
	}


	if(size / 2 < str.size())
	{
		NoBytes ex = *(new NoBytes("No hay espacio suficiente"));
		throw ex;
	}

	wav->gotoSamples();
	for(int i = 0; i < str.size(); i++)
	{
		int16_t byt = file->readInt16();
		//cout<<(int)byt<<endl;
		if(byt & 1 && str.at(i) == '0')
			byt -= 1;
		else if( !(byt & 1) && str.at(i) == '1')
			byt += 1;
		//cout<<(int)byt<<endl;
		file->skipBytes(-2);
		file->write(byt);
	}
}

string Esteganografia_LSB::LSB_WAV_read( WAV *wav )
{
	RandomAccessFile *file = wav->getRAF();

	wav->gotoSamples();

	string isLSB;
	string bitsLSB = toBinary("LSB");
	for(int i = 0; i < 24; i++)
	{
		int16_t byt = file->readInt16();
		if(byt & 1)
			isLSB += "1";
		else
			isLSB += "0";
	}
	if(isLSB != bitsLSB)
	{
		NoSignature ex = *(new NoSignature("El fichero no contiene firma"));
		throw ex;
	}
	//cout<<endl<<"Tiene la firma"<<endl<<endl;

	string bitsLength;
	for(int i = 0; i < 32; i++)
	{
		int16_t byt = file->readInt16();
		if(byt & 1)
			bitsLength.append("1");
		else
			bitsLength.append("0");
	}
	int length = toInt(bitsLength, 32);
	//cout<<"Length "<<length<<endl;

	string text;
	for(int i = 0; i < length * 8; i++)
	{
		int16_t byt = file->readInt16();
		if(byt & 1)
			text.append("1");
		else
			text.append("0");
	}

	string finalText = toString(text);
	//cout<<"Testo  "<<finalText.c_str()<<endl;

	return finalText;
}


