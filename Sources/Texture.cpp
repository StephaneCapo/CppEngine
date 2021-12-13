#include "Texture.h"
#include "bitmap.h"

using namespace O3DCppEngine;

void	Texture::init()
{
	if (mFileName.length() == 0)
		return;

	if (mPixelBuffer)
	{
		close();
	}

	BITMAPINFO* BitmapInfo = NULL;
	unsigned char* bmpdata = LoadDIBitmap(mFileName.c_str(), &BitmapInfo);
	if ((!BitmapInfo) || (!bmpdata))
	{
		// error
		return;
	}

	mPixelSize.x= BitmapInfo->bmiHeader.biWidth;
	mPixelSize.y = BitmapInfo->bmiHeader.biHeight;

	mPixelBuffer = new unsigned int[mPixelSize.x * mPixelSize.y];
	unsigned int* writeBuffer = mPixelBuffer;

	for (int j = 0; j < mPixelSize.y; j += 2)
	{
		for (int i = 0; i < mPixelSize.x; i += 2)
		{
			RGBAPixel px= getBitmapRGBA(BitmapInfo, bmpdata, i, j);
			*writeBuffer = *(unsigned int*)&px;
			
			writeBuffer++;
		}
	}
	
	
}
void	Texture::close()
{
	if (mPixelBuffer)
	{
		delete[] mPixelBuffer;
		mPixelBuffer = nullptr;
	}
	mPixelSize[0] = mPixelSize[1] = 0;
}