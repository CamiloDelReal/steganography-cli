#ifndef BITMAP_FILE
#include "BMP.h"
#endif

#ifndef EXCEPTION_TYPES
#include "ExceptionTypes.h"
#endif

#include <iostream>
#include <string>

using namespace std;

BMP::BMP(const string &_path)
{
	raf = new RandomAccessFile(_path, BINARY_MODE_UPDATE_READ);
	//raf->begin();

	bm = new uint8_t[2];
	memset(bm, 0, 3);	//Inicializamos en cero todos los caracteres de bm
						//son tres bloques de 1 byte pues se tiene en cuenta
						//el caracter EOF

	raf->read(bm, 2);
	sizeFile = raf->readUnsignedInt32();
	reserved_1 = raf->readUnsignedInt16();
	reserved_2 = raf->readUnsignedInt16();
	offset = raf->readUnsignedInt32();
	headerSize = raf->readUnsignedInt32();
	pixWidth = raf->readUnsignedInt32();
	pixHeight = raf->readUnsignedInt32();
	planesNumber = raf->readUnsignedInt16();
	bitPerPixel = raf->readUnsignedInt16();
	compression = raf->readUnsignedInt32();
	sizeImage = raf->readUnsignedInt32();
	hResolution = raf->readUnsignedInt32();
	vResolution = raf->readUnsignedInt32();
	countUsedColors = raf->readUnsignedInt32();
	countImportantColors = raf->readUnsignedInt32();
}

BMP::~BMP(void)
{
}

bool BMP::setFileSize( const uint32_t &_sizeFile )
{
	sizeFile = _sizeFile;
	return raf->write(sizeFile, SIZE_FILE);
}

bool BMP::setReservedOne( const uint16_t &_reserved_1 )
{
	reserved_1 = _reserved_1;
	return raf->write(reserved_1, RESERVED_1);
}

bool BMP::setReservedTwo( const uint16_t &_reserved_2 )
{
	reserved_2 = _reserved_2;
	return raf->write(reserved_2, RESERVED_2);
}

bool BMP::setPixelsWidth( const uint32_t &_pixWidth )
{
	pixWidth = _pixWidth;
	return raf->write(pixWidth, WIDTH_IN_PIXELS);
}

bool BMP::setPixelsHeight( const int32_t &_pixheight )
{
	pixHeight = _pixheight;
	return raf->write(pixHeight, HEIGHT_IN_PIXELS);
}

bool BMP::setPlanesNumber( const uint16_t &_planesnumber )
{
	planesNumber = _planesnumber;
	return raf->write(planesNumber, PLANES_NUMBERS);
}

bool BMP::setBitsPexPixel( const uint16_t &_bitPerPixel )
{
	bitPerPixel = _bitPerPixel;
	return raf->write(bitPerPixel, BITS_PER_PIXELS);
}

bool BMP::setCompression( const uint32_t &_compression )
{
	compression = _compression;
	return raf->write(compression, COMPRESSION);
}

bool BMP::setImageSize( const uint32_t &_sizeImage )
{
	sizeImage = _sizeImage;
	return raf->write(sizeImage, SIZE_IMAGE);
}

bool BMP::setHorizontalResolution( const uint32_t &_hResolution )
{
	hResolution = _hResolution;
	return raf->write(hResolution, HORIZONTAL_RESOLUTION);
}

bool BMP::setVerticalResolution( const uint32_t &_vResolution )
{
	vResolution = _vResolution;
	return raf->write(vResolution, VERTICAL_RESOLUTION);
}

bool BMP::setColorsTable( const uint32_t &_countUsedColors )
{
	countUsedColors = _countUsedColors;
	return raf->write(countUsedColors, TABLE_COLORS);
}

bool BMP::setImportantsColors( const uint32_t &_countImportantcolors )
{
	countImportantColors = _countImportantcolors;
	return raf->write(countImportantColors, IMPORTANTS_COLORS);
}

string BMP::getFileType()
{
	return (char*)bm;
}

uint32_t BMP::getFileSize()
{
	return sizeFile;
}

uint16_t BMP::getReservedOne()
{
	return reserved_1;
}

uint16_t BMP::getReservedTwo()
{
	return reserved_2;
}

uint32_t BMP::getOffset()
{
	return offset;
}

uint32_t BMP::getHeaderSize()
{
	return headerSize;
}

uint32_t BMP::getPixelsWidth()
{
	return pixWidth;
}

uint32_t BMP::getPixelsHeight()
{
	return pixHeight;
}

uint16_t BMP::getPlanesNumber()
{
	return planesNumber;
}

uint16_t BMP::getBitsPerPixel()
{
	return bitPerPixel;
}

uint32_t BMP::getCompression()
{
	return compression;
}

uint32_t BMP::getImageSize()
{
	return sizeImage;
}

uint32_t BMP::getHorizontalResolution()
{
	return hResolution;
}

uint32_t BMP::getVerticalResolution()
{
	return vResolution;
}

uint32_t BMP::getColorsTable()
{
	return countUsedColors;
}

uint32_t BMP::getImportantsColors()
{
	return countImportantColors;
}

bool BMP::setPixel(Pixel &pix)
{
	uint32_t pos = raf->bytePosition();
	if(sizeFile - pos < 3)
	{
		NoBytes ex = *(new NoBytes("No hay mas bytes para leer, posible EOF"));
		throw ex;
	}
	uint8_t *bgr = pix.getBytesBGR();
	return raf->write(bgr, 3);
}
bool BMP::setPixel(Pixel &pix, const uint32_t &x, const uint32_t &y)
{
	cout<<"colors "<<pix.getRed()<< " " << pix.getGreen()<< " "<<pix.getBlue()<<endl;
	if(y < 0 || y >= pixHeight || x < 0 || x >= pixWidth)
	{
		IndexOutOfRange ex = *(new IndexOutOfRange("Está tratando de accedar a un pixel fuera de la imagen"));
		throw ex;
	}
	uint32_t pos = raf->bytePosition();
	if(sizeFile - pos < 3)
	{
		NoBytes ex = *(new NoBytes("No hay mas bytes para leer, posible EOF"));
		throw ex;
	}

	//Posicionarnos
	uint32_t index = 0;
	if(y == 0)
		index = PIXELS_BYTES + 3 * x;
	else
	{
		index = PIXELS_BYTES + 3 * (y * pixWidth + x);
	}
	raf->lessMovementFromCursor(index);

	uint8_t *bgr = pix.getBytesBGR();
	return raf->write(bgr, 3);
}

Pixel BMP::getPixel()
{
	uint32_t pos = raf->bytePosition();
	if(sizeFile - pos < 3)
	{
		NoBytes ex = *(new NoBytes("No hay mas bytes para leer, posible EOF"));
		throw ex;
	}
	uint8_t bytes[3] = {0};
	raf->read(bytes, 3);
	return *(new Pixel(bytes[2], bytes[1], bytes[0]));
}
Pixel BMP::getPixel(const uint32_t &x, const uint32_t &y)
{
	if(y < 0 || y >= pixHeight || x < 0 || x >= pixWidth)
	{
		IndexOutOfRange ex = *(new IndexOutOfRange("Está tratando de accedar a un pixel fuera de la imagen"));
		throw ex;
	}
	uint32_t pos = raf->bytePosition();
	if(sizeFile - pos < 3)
	{
		NoBytes ex = *(new NoBytes("No hay mas bytes para leer, posible EOF"));
		throw ex;
	}
	//Posicionarnos
	uint32_t index = 0;
	if(y == 0)
		index = PIXELS_BYTES + 3 * x;
	else
	{
		index = PIXELS_BYTES + 3 * (y * pixWidth + x);
	}
	raf->lessMovementFromCursor(index);

	uint8_t bytes[3] = {0};
	raf->read(bytes, 3);

	return *(new Pixel(bytes[2], bytes[1], bytes[0]));
}

bool BMP::close()
{
	return raf->close();
}

RandomAccessFile * BMP::getRAF()
{
	return raf;
}
