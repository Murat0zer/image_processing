#include "Resim.h"

Resim::Resim()
{
	this->input = new TCHAR[100];
	this->output = new TCHAR[100];
	this->Width = new int;
	this->Height = new int;
	this->Size = new long;
	this->new_size = new long;
	this->buffer = new BYTE;
	this->raw_intensity = new BYTE;
	this->display_imge = new BYTE;

}
Resim::~Resim()
{
	delete this->Width;
	delete this->Height;
	delete this->Size;
	delete this->new_size;
	delete[] this->buffer;
	delete[] this->raw_intensity;
	delete[] this->display_imge;
	delete[] this->input;
	delete[] this->output;
}
//setters
void Resim::setInput(LPCTSTR  input )
{
	this->input = input;
}

void Resim::setOutput(LPCTSTR  output)
{
	this->output= output;
}

void Resim::setWidth(int width)
{
	this->Width = &width;
}

void Resim::setHeight(int height)
{
	this->Height = &height;
}

void Resim::setSize(long size)
{
	this->Size = &size;
}

void Resim::setNewSize(long newSize)
{
	this->new_size = &newSize;
}

void Resim::setBuffer(BYTE * buffer)
{
	this->buffer = buffer;
}

void Resim::setRawIntensity(BYTE * rawIntensity)
{
	this->raw_intensity = rawIntensity;
}

void Resim::setDisplayImage(BYTE * displayImage)
{
	this->display_imge = displayImage;
}
///////////////////////////////////
//getters
////////////////////////////////////
LPCTSTR  Resim::getInput()
{
	return this->input;
}

LPCTSTR  Resim::getOutput()
{
	
	return this->output;
}

int * Resim::getWidth()
{
	return this->Width;
}

int * Resim::getHeight()
{
	return  this->Height;
}


long * Resim::getSize()
{
	return this->Size;
}

long * Resim::getNewSize()
{
	return this->new_size;
}

BYTE * Resim::getBuffer()
{
	return this->buffer;
}

BYTE * Resim::getRawIntensity()
{
	return this->raw_intensity;
}

BYTE * Resim::getDisplayImage()
{
	return this->display_imge;
}

