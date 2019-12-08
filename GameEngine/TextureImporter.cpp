#include "TextureImporter.h"

void TextureImporter::LoadBMP(const char * bmpFile, BMPheader &hed)
{
	unsigned char header[54];// Each BMP file begins by a 54-bytes header

	FILE * file;
	fopen_s(&file, bmpFile, "rb");

	if (!bmpCorrectFormat(header, file))
		hed.data = NULL;

	hed.dataPos = *(int*)&(header[0x0A]);
	hed.imageSize = *(int*)&(header[0x22]);
	hed.width = *(int*)&(header[0x12]);
	hed.height = *(int*)&(header[0x16]);

	if (hed.imageSize == 0)
		hed.imageSize = hed.width * hed.height * 3;
	if (hed.dataPos == 0)
		hed.dataPos = 54;

	hed.data = new unsigned char[hed.imageSize];
	fread(hed.data, 1, hed.imageSize, file);
	fclose(file);
}

bool TextureImporter::bmpCorrectFormat(unsigned char header[], FILE *bmpFile)
{
	if (!bmpFile) {
		printf("Image could not be opened\n");
		return false;
	}

	if (fread(header, 1, 54, bmpFile) != 54) {
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return false;
	}
	
	return true;
}


