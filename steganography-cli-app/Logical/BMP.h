#pragma once

#ifndef BITMAP_FILE
#define BITMAP_FILE
#endif

#ifndef RANDOM_ACCESS_FILE
#include "RandomAccessFile.h"
#endif

#ifndef PIXEL
#include "Pixel.h"
#endif


//Indices de los bloques de informacion dentro del fichero BMP
const uint32_t TYPE_FILE_B = 0;
const uint32_t TYPE_FILE_M = 1;
const uint32_t SIZE_FILE = 2;
const uint32_t RESERVED_1 = 6;
const uint32_t RESERVED_2 = 8;
const uint32_t OFFSET = 10;
const uint32_t HEADER_SIZE = 14;
const uint32_t WIDTH_IN_PIXELS = 18;
const uint32_t HEIGHT_IN_PIXELS = 22;
const uint32_t PLANES_NUMBERS = 26;
const uint32_t BITS_PER_PIXELS = 28;
const uint32_t COMPRESSION = 30;
const uint32_t SIZE_IMAGE = 34;
const uint32_t HORIZONTAL_RESOLUTION = 38;
const uint32_t VERTICAL_RESOLUTION = 42;
const uint32_t TABLE_COLORS = 46;
const uint32_t IMPORTANTS_COLORS = 50;
const uint32_t PIXELS_BYTES = 54;


/*
  Excepciones que lanza esta clase
      
*/

class BMP
{
	public:
		//Constructor
		__declspec(dllexport) BMP(const string &_path);

		//Destructors
		virtual __declspec(dllexport) ~BMP(void);

		//Métodos getters y setters para los datos de todo el fichero
		/*
		  El typo de fichero obtenido en bm,
		  offset y headerSize no son modificables
		*/
		__declspec(dllexport) bool setFileSize(const uint32_t &_sizeFile);
		__declspec(dllexport) bool setReservedOne(const uint16_t &_reserved_1);
		__declspec(dllexport) bool setReservedTwo(const uint16_t &_reserved_2);
		__declspec(dllexport) bool setPixelsWidth(const uint32_t &_pixWidth);
		__declspec(dllexport) bool setPixelsHeight(const int32_t &_pixheight);
		__declspec(dllexport) bool setPlanesNumber(const uint16_t &_planesnumber);
		__declspec(dllexport) bool setBitsPexPixel(const uint16_t &_bitPerPixel);
		__declspec(dllexport) bool setCompression(const uint32_t &_compression);
		__declspec(dllexport) bool setImageSize(const uint32_t &_sizeImage);
		__declspec(dllexport) bool setHorizontalResolution(const uint32_t &_hResolution);
		__declspec(dllexport) bool setVerticalResolution(const uint32_t &_vResolution);
		__declspec(dllexport) bool setColorsTable(const uint32_t &_countUsedColors);
		__declspec(dllexport) bool setImportantsColors(const uint32_t &_countImportantcolors);

		__declspec(dllexport) string getFileType();
		__declspec(dllexport) uint32_t getFileSize();
		__declspec(dllexport) uint16_t getReservedOne();
		__declspec(dllexport) uint16_t getReservedTwo();
		__declspec(dllexport) uint32_t getOffset();
		__declspec(dllexport) uint32_t getHeaderSize();
		__declspec(dllexport) uint32_t getPixelsWidth();
		__declspec(dllexport) uint32_t getPixelsHeight();
		__declspec(dllexport) uint16_t getPlanesNumber();
		__declspec(dllexport) uint16_t getBitsPerPixel();
		__declspec(dllexport) uint32_t getCompression();
		__declspec(dllexport) uint32_t getImageSize();
		__declspec(dllexport) uint32_t getHorizontalResolution();
		__declspec(dllexport) uint32_t getVerticalResolution();
		__declspec(dllexport) uint32_t getColorsTable();
		__declspec(dllexport) uint32_t getImportantsColors();

		//Manipulacion de los pixeles de la imagen
		__declspec(dllexport) bool setPixel(Pixel &pix);
		__declspec(dllexport) bool setPixel(Pixel &pix, const uint32_t &x, const uint32_t &y);

		__declspec(dllexport) Pixel getPixel();
		__declspec(dllexport) Pixel getPixel(const uint32_t &x, const uint32_t &y);

		//Metodos propios de file
		__declspec(dllexport) bool close();

		__declspec(dllexport) RandomAccessFile *getRAF();
	private:
		RandomAccessFile *raf;

		//Informacion sobre el fichero
		uint8_t	 *bm;					//Identificacion del ficherom debe ser BM, no es modificable
		uint32_t sizeFile;				//Tamaño del fichero en bytes
		uint16_t reserved_1;			//Reservados
		uint16_t reserved_2;			//Reservados
		uint32_t offset;				//Posicion donde comienzan los pixeles, no es modificable
		//Informacion de la imagen
		uint32_t headerSize;			//Tamaño en bytes del encabezado dedicado a los datos de la imagen, no es modificable
		uint32_t pixWidth;				//Anchura en pixeles de la imagen
		uint32_t pixHeight;				//Altura en pixeles de la imagen
		uint16_t planesNumber;			//Numero de planos
		uint16_t bitPerPixel;			//Numero de bits por pixeles, profundidad de color
		uint32_t compression;			//Compresion, lo mejor es 0 que es descomprimido
		uint32_t sizeImage;				//Tamaño de la imagen en bytes
		uint32_t hResolution;			//Resolucion horizontal, pixeles por metro horizontal
		uint32_t vResolution;			//Resolucion vertical, pixeles por metro vertical
		uint32_t countUsedColors;		//Tamaño de la tabla de colores, cantidad de colores usados
		uint32_t countImportantColors;	//Contador*cantidad de colores importantes
		//Despues solo quedan los pixeles, 1 pixel = 3 bytes
};

