#ifndef RANDOM_ACCESS_FILE
#include "RandomAccessFile.h"
#endif

#ifndef EXCEPTION_TYPES
#include "ExceptionTypes.h"
#endif

//Constructor
RandomAccessFile::RandomAccessFile(const string &_path, const string &mode)
{
	path = _path;
	fopen_s(&raf, path.c_str(), mode.c_str());
	if(raf == NULL)
	{
		NotFoundFile ex = *(new NotFoundFile("Fichero no encontrado"));
		throw ex;
	}
}


//Destructor
RandomAccessFile::~RandomAccessFile(void)
{
}


//Read data types
int8_t RandomAccessFile::readInt8()
{
	int8_t value;
	fread(&value, sizeof(int8_t), 1, raf);
	return value;
}
int8_t RandomAccessFile::readInt8(const uint32_t &index)
{
	lessMovementFromCursor(index);
	return readInt8();
}
uint8_t RandomAccessFile::readUnsignedInt8()
{
	uint8_t value;
	fread(&value, sizeof(uint8_t), 1, raf);
	return value;
}
uint8_t RandomAccessFile::readUnsignedInt8(const uint32_t &index)
{
	lessMovementFromCursor(index);
	return readUnsignedInt8();
}
int16_t RandomAccessFile::readInt16()
{
	int16_t value;
	fread(&value, sizeof(int16_t), 1, raf);
	return value;
}
int16_t RandomAccessFile::readInt16(const uint32_t &index)
{
	lessMovementFromCursor(index);
	return readInt16();
}
uint16_t RandomAccessFile::readUnsignedInt16()
{
	uint16_t value;
	fread(&value, sizeof(uint16_t), 1, raf);
	return value;
}
uint16_t RandomAccessFile::readUnsignedInt16(const uint32_t &index)
{
	lessMovementFromCursor(index);
	return readUnsignedInt16();
}
int32_t RandomAccessFile::readInt32()
{
	int32_t value;
	fread(&value, sizeof(int32_t), 1, raf);
	return value;
}
int32_t RandomAccessFile::readInt32(const uint32_t &index)
{
	lessMovementFromCursor(index);
	return readInt32();
}
uint32_t RandomAccessFile::readUnsignedInt32()
{
	uint32_t value;
	fread(&value, sizeof(uint32_t), 1, raf);
	return value;
}
uint32_t RandomAccessFile::readUnsignedInt32(const uint32_t &index)
{
	lessMovementFromCursor(index);
	return readUnsignedInt32();
}
int64_t RandomAccessFile::readInt64()
{
	int64_t value;
	fread(&value, sizeof(int64_t), 1, raf);
	return value;
}
int64_t RandomAccessFile::readInt64(const uint32_t &index)
{
	lessMovementFromCursor(index);
	return readInt64();
}
uint64_t RandomAccessFile::readUnsignedInt64()
{
	uint64_t value;
	fread(&value, sizeof(uint64_t), 1, raf);
	return value;
}
uint64_t RandomAccessFile::readUnsignedInt64(const uint32_t &index)
{
	lessMovementFromCursor(index);
	return readUnsignedInt64();
}
float RandomAccessFile::readFloat()
{
	float value;
	fread(&value, sizeof(float), 1, raf);
	return value;
}
float RandomAccessFile::readFloat(const uint32_t &index)
{
	lessMovementFromCursor(index);
	return readFloat();
}
double RandomAccessFile::readDouble()
{
	double value;
	fread(&value, sizeof(double), 1, raf);
	return value;
}
double RandomAccessFile::readDouble(const uint32_t &index)
{
	lessMovementFromCursor(index);
	return readDouble();
}
char RandomAccessFile::readChar()
{
	char value;
	fread(&value, sizeof(char), 1, raf);
	return value;
}
char RandomAccessFile::readChar(const uint32_t &index)
{
	lessMovementFromCursor(index);
	return readChar();
}
uchar RandomAccessFile::readUnsignedChar()
{
	uchar value;
	fread(&value, sizeof(uchar), 1, raf);
	return value;
}
uchar RandomAccessFile::readUnsignedChar(const uint32_t &index)
{
	lessMovementFromCursor(index);
	return readUnsignedChar();
}

//Read bytes
bool RandomAccessFile::read(uint8_t bytes[], const uint32_t &size)
{
	return fread(bytes, sizeof(uint8_t), size, raf) == size ? true : false;
}
bool RandomAccessFile::read(uint8_t bytes[], const uint32_t &index, const uint32_t &size)
{
	lessMovementFromCursor(index);
	return fread(bytes, sizeof(uint8_t), size, raf) == size ? true : false;
}
bool RandomAccessFile::read(int8_t bytes[], const uint32_t &size)
{
	return fread(bytes, sizeof(int8_t), size, raf) == size ? true : false;
}
bool RandomAccessFile::read(int8_t bytes[], const uint32_t &index, const uint32_t &size)
{
	lessMovementFromCursor(index);
	return fread(bytes, sizeof(int8_t), size, raf) == size ? true : false;
}

//Write data types
bool RandomAccessFile::write(const int8_t &value)
{
	return fwrite(&value, sizeof(int8_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const int8_t &value, const uint32_t &index)
{
	lessMovementFromCursor(index);
	return fwrite(&value, sizeof(int8_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const uint8_t &value)
{
	return fwrite(&value, sizeof(uint8_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const uint8_t &value, const uint32_t &index)
{
	lessMovementFromCursor(index);
	return fwrite(&value, sizeof(uint8_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const int16_t &value)
{
	return fwrite(&value, sizeof(int16_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const int16_t &value, const uint32_t &index)
{
	lessMovementFromCursor(index);
	return fwrite(&value, sizeof(int16_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const uint16_t &value)
{
	return fwrite(&value, sizeof(uint16_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const uint16_t &value, const uint32_t &index)
{
	lessMovementFromCursor(index);
	return fwrite(&value, sizeof(uint16_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const int32_t &value)
{
	return fwrite(&value, sizeof(int32_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const int32_t &value, const uint32_t &index)
{
	lessMovementFromCursor(index);
	return fwrite(&value, sizeof(int32_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const uint32_t &value)
{
	return fwrite(&value, sizeof(uint32_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const uint32_t &value, const uint32_t &index)
{
	lessMovementFromCursor(index);
	return fwrite(&value, sizeof(uint32_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const int64_t &value)
{
	return fwrite(&value, sizeof(int64_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const int64_t &value, const uint32_t &index)
{
	lessMovementFromCursor(index);
	return fwrite(&value, sizeof(int64_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const uint64_t &value)
{
	return fwrite(&value, sizeof(uint64_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const uint64_t &value, const uint32_t &index)
{
	lessMovementFromCursor(index);
	return fwrite(&value, sizeof(uint64_t), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const float &value)
{
	return fwrite(&value, sizeof(float), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const float &value, const uint32_t &index)
{
	lessMovementFromCursor(index);
	return fwrite(&value, sizeof(float), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const double &value)
{
	return fwrite(&value, sizeof(double), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const double &value, const uint32_t &index)
{
	lessMovementFromCursor(index);
	return fwrite(&value, sizeof(double), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const char &value)
{
	return fwrite(&value, sizeof(char), 1, raf) == 1 ? true : false;
}
bool RandomAccessFile::write(const char &value, const uint32_t &index)
{
	lessMovementFromCursor(index);
	return fwrite(&value, sizeof(char), 1, raf) == 1 ? true : false;
}

//Write bytes
bool RandomAccessFile::write(uint8_t bytes[], const uint32_t &size)
{
	return fwrite(bytes, sizeof(uint8_t), size, raf) == size ? true : false;
}
bool RandomAccessFile::write(uint8_t bytes[], const uint32_t &index, const uint32_t &size)
{
	lessMovementFromCursor(index);
	return fwrite(bytes, sizeof(uint8_t), size, raf) == size ? true : false;
}
bool RandomAccessFile::write(int8_t bytes[], const uint32_t &size)
{
	return fwrite(bytes, sizeof(int8_t), size, raf) == size ? true : false;
}
bool RandomAccessFile::write(int8_t bytes[], const uint32_t &index, const uint32_t &size)
{
	lessMovementFromCursor(index);
	return fwrite(bytes, sizeof(int8_t), size, raf) == size ? true : false;
}

//Movement
bool RandomAccessFile::isEOF()
{
	return feof(raf) != 0 ? true : false;
}
bool RandomAccessFile::seek(const uint32_t &byte)
{
	return fseek(raf, byte, SEEK_SET) == 0 ? true : false;
}
bool RandomAccessFile::skipBytes(const uint32_t &bytes)
{
	return fseek(raf, bytes, SEEK_CUR) == 0 ? true : false;
}
uint32_t RandomAccessFile::bytePosition()
{
	return ftell(raf);
}
void RandomAccessFile::begin()
{
	//return fseek(raf, 0, SEEK_SET) == 0 ? true : false;
	rewind(raf);
}
bool RandomAccessFile::end()
{
	return fseek(raf, 0, SEEK_END) == 0 ? true : false;
}
bool RandomAccessFile::lessMovementFromCursor(const uint32_t &index)
{
	uint32_t movement = ftell(raf);
	movement = index - movement;
	return fseek(raf, movement, SEEK_CUR) == 0 ? true : false;
}

//Errors
bool RandomAccessFile::haveErrors()
{
	return ferror(raf) != 0 ? true : false;
}

//Redireccion
void RandomAccessFile::setBuffer(char data[], const uint32_t &size, const uint32_t &mode)
{
	setvbuf(raf, data, mode, size);
}
bool RandomAccessFile::flush()
{
	return fflush(raf) == 0 ? true : false;
}

//Endding
bool RandomAccessFile::close()
{
	return fclose(raf) == 0 ? true : false;
}