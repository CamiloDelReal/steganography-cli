#ifndef ESTEGANOGRAFIA_LSB_H
#define ESTEGANOGRAFIA_LSB_H
#endif

#ifndef BITMAP_FILE
#include "BMP.h"
#endif

#ifndef WAVE_FILE
#include "WAV.h"
#endif

class Esteganografia_LSB
{
public:
	Esteganografia_LSB(void);
	~Esteganografia_LSB(void);

	static __declspec(dllexport) void LSB_BMP_write(BMP *file, string text);
	static __declspec(dllexport) void LSB_WAV_write(WAV *file, string text);

	static __declspec(dllexport) string LSB_BMP_read(BMP *file);
	static __declspec(dllexport) string LSB_WAV_read(WAV *file);

private:
	static __declspec(dllexport) string padding(string text);
	static __declspec(dllexport) string toBinary(string text);
	static __declspec(dllexport) string toBinary(int entero);
	static __declspec(dllexport) int toInt(string entero, int bitsSize);
	static __declspec(dllexport) string toString(string bits);
	static __declspec(dllexport) int square(int value, int po);

};

