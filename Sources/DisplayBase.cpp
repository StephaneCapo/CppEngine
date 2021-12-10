#include "DisplayBase.h"
#include <iostream>

using namespace O3DCppEngine;

void DisplayBase::memset32(unsigned int* dst, unsigned int val, unsigned int ui32count) const
{
	while (ui32count)
	{
		*dst = val;
		++dst;
		--ui32count;
	}
}

void	DisplayBase::setDisplaySize(unsigned int pixelSizeX, unsigned int pixelSizeY)
{
	if (mIsInit)
	{
#ifdef _DEBUG
		std::cout << "Can't change display size after it is initialized" << std::endl;
#endif
		return;
	}

	// minimal size
	if (pixelSizeX < 160)
		pixelSizeX = 160;
	if (pixelSizeY < 120)
		pixelSizeY = 120;

	// max size
	if (pixelSizeX > 640)
		pixelSizeX = 640;
	if (pixelSizeY > 480)
		pixelSizeY = 480;

	// arrondi sur un multiple de 4

	mPixelSizeX = (pixelSizeX+3)& 0xFFFC;
	mPixelSizeY = (pixelSizeY+3)& 0xFFFC;

	if (mPixelBuffer)
		delete[] mPixelBuffer;

	mPixelBuffer = new unsigned int[mPixelSizeX * mPixelSizeY];

	if (mZBuffer)
		delete[] mZBuffer;

	mZBuffer = new float[mPixelSizeX * mPixelSizeY];

}

DisplayBase::~DisplayBase()
{
	if (mPixelBuffer)
		delete[] mPixelBuffer;

	if (mZBuffer)
		delete[] mZBuffer;
}

// add drawable to be draw and return its position in drawable list 
unsigned int	DisplayBase::add(std::shared_ptr<Drawable> drw)
{
	mDrawableList.push_back(drw);
	return (unsigned int)(mDrawableList.size() - 1);
}
// remove the first occurrance of the given drawable from list 
// return true if found 
bool			DisplayBase::removeFirst(std::shared_ptr<Drawable> drw)
{
	auto it = mDrawableList.begin();
	while(it != mDrawableList.end())
	{
		if ((*it) == drw)
		{
			mDrawableList.erase(it);
			return true;
		}
	}
	return false;
}
// remove all occurances of given drawable
void			DisplayBase::removeAll(std::shared_ptr<Drawable> drw)
{
	auto it = mDrawableList.begin();
	while (it != mDrawableList.end())
	{
		if ((*it) == drw)
		{
			it=mDrawableList.erase(it);
		}
	}
	
}

void	DisplayBase::clear(unsigned int clearColor, float clearZ) const
{
	if (!mIsInit)
	{
		return;
	}

	memset32(mPixelBuffer, clearColor, mPixelSizeX * mPixelSizeY);
	memset32((unsigned int*)mZBuffer, *(unsigned int*)&clearZ, mPixelSizeX * mPixelSizeY );
}

void DisplayBase::renderAll()
{
	if (!mIsInit)
	{
		return;
	}
	for (auto drw : mDrawableList)
	{
		drw->render(this);
	}
}