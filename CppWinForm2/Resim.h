#pragma once
#include "stdafx.h"
#include <Windows.h>
using namespace System;
ref  class Resim
{
	
public:
	Resim();
	~Resim();
	// setters
	void setInput(LPCTSTR  input);
	void setOutput(LPCTSTR  output);
	void setWidth(int width);
	void setHeight(int height);
	void setSize(long size);
	void setNewSize(long newSize);
	void setBuffer(BYTE *buffer);
	void setRawIntensity(BYTE *rawIntensity);
	void setDisplayImage(BYTE *displayImage);

	// getters
	LPCTSTR getInput();
	LPCTSTR getOutput();
	int *   getWidth();
	int *   getHeight();
	long *  getSize();
	long *	getNewSize();
	BYTE*   getBuffer();
	BYTE*   getRawIntensity();
	BYTE*   getDisplayImage();


private:
	LPCTSTR  input, output;
	int * Width, * Height;
	long * Size; long * new_size;
	BYTE* buffer;
	BYTE* raw_intensity;
	BYTE* display_imge;
};

