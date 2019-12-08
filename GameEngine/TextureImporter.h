#pragma once
#include "Exports.h"
#include <stdio.h>
#include <fstream>
#include <stdlib.h>

struct BMPheader
{
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char  * data;
};

static class FRANKENGINE_API TextureImporter
{
private:
	static bool bmpCorrectFormat(unsigned char header[], FILE *bmpFile);

public:
	static void LoadBMP(const char * bmpFile, BMPheader &hed);
	
};

