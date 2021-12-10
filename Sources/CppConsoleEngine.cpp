#include "CppConsoleDisplay.h"
#include "TimeManagement.h"
#include "DisplayZoneDrawing.h"

using namespace O3DCppEngine;

void CppConsoleDisplay::init()
{
	if (mIsInit) // already init
	{
		return;
	}
	InitTime();
	mDisplaySettings = InitDisplay(mPixelSizeX/2, mPixelSizeY /2 , 8, 1);
	//ShowFPS(mDisplaySettings, 1);

	mFullScreenZone = (DisplayZone*)malloc(sizeof(DisplayZone));
	InitDisplayZone(mFullScreenZone, 0, 0, mPixelSizeX / 2, mPixelSizeX / 2, 1);
	mIsInit = true;
	clear(ENCODE_COLOR(0,0,0,0xFF),0.0f);
}

void CppConsoleDisplay::close()
{
	if (!mIsInit)
		return;

	mIsInit = false;

	if (mDisplaySettings)
		CloseDisplay(mDisplaySettings);

	mDisplaySettings = nullptr;

	if (mFullScreenZone)
	{
		CloseDisplayZone(mFullScreenZone);
		free(mFullScreenZone);
		mFullScreenZone = nullptr;
	}
}

void	CppConsoleDisplay::swap()
{
	renderAll();
	ClearDisplayZone(mFullScreenZone, BLACK, BLACK, ' ', NO_CHARACTER);
	for (unsigned int j = 0; j < mPixelSizeY; j += 2)
	{
		unsigned int lineOffset = j * mPixelSizeX;
		for (unsigned int i = 0; i < mPixelSizeX; i += 2)
		{
			RGBAPixel pixel[4];

			pixel[0] = *(RGBAPixel*)(&mPixelBuffer[i+ lineOffset]);
			pixel[0].A = 0xFF;
			pixel[1] = *(RGBAPixel*)(&mPixelBuffer[i + 1 + lineOffset]);
			pixel[1].A = 0xFF;
			pixel[2] = *(RGBAPixel*)(&mPixelBuffer[i + lineOffset + mPixelSizeX]);
			pixel[2].A = 0xFF;
			pixel[3] = *(RGBAPixel*)(&mPixelBuffer[i + 1 + lineOffset + mPixelSizeX]);
			pixel[3].A = 0xFF;

			DisplayCharacter color = GetDisplayCharacterFrom4Pixels(pixel);
			PrintDisplayCharacterInDisplayZone(mFullScreenZone, color, i / 2, j / 2);
		}
	}
	FlushDisplayZone(mDisplaySettings, mFullScreenZone);
	SwapBuffer(mDisplaySettings);
}