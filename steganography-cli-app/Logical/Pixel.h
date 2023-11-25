#pragma once

#ifndef PIXEL
#define PIXEL
#endif

#include <stdint.h>

class Pixel
{
	public:
		__declspec(dllexport) Pixel(void);
		__declspec(dllexport) Pixel(uint8_t _red, uint8_t _green, uint8_t _blue);

		virtual __declspec(dllexport) ~Pixel(void);

		//Getters & setters
		__declspec(dllexport) void setRed(uint8_t _red);
		__declspec(dllexport) void setGreen(uint8_t _green);
		__declspec(dllexport) void setBlue(uint8_t _blue);

		__declspec(dllexport) uint8_t getRed();
		__declspec(dllexport) uint8_t getGreen();
		__declspec(dllexport) uint8_t getBlue();

		__declspec(dllexport) uint8_t *getBytesRGB();
		__declspec(dllexport) uint8_t *getBytesBGR();

	private:
		uint8_t red;
		uint8_t green;
		uint8_t blue;
};

