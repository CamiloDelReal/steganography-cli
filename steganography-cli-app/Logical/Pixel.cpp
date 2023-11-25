#include "Pixel.h"


Pixel::Pixel(void)
{
	red = 0;
	green = 0;
	blue = 0;
}

Pixel::Pixel(uint8_t _red, uint8_t _green, uint8_t _blue)
{
	red = _red;
	green = _green;
	blue = _blue;
}


Pixel::~Pixel(void)
{
}

void Pixel::setRed(uint8_t _red)
{
	red = _red;
}
void Pixel::setGreen(uint8_t _green)
{
	green = _green;
}
void Pixel::setBlue(uint8_t _blue)
{
	blue = _blue;
}

uint8_t Pixel::getRed()
{
	return red;
}
uint8_t Pixel::getGreen()
{
	return green;
}
uint8_t Pixel::getBlue()
{
	return blue;
}

uint8_t * Pixel::getBytesRGB()
{
	uint8_t *bytes = new uint8_t[3];
	bytes[0] = red;
	bytes[1] = green;
	bytes[2] = blue;
	return bytes;
}

uint8_t * Pixel::getBytesBGR()
{
	uint8_t *bytes = new uint8_t[3];
	bytes[0] = blue;
	bytes[1] = green;
	bytes[2] = red;
	return bytes;
}
