#include "Texture.h"

using namespace O3DCppEngine;

void	Texture::init()
{
	if (mFileName.length() == 0)
		return;

	if (mPixelBuffer)
	{
		close();
	}

	// TODO
	
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