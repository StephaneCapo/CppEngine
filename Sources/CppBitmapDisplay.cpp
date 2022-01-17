#include "CppBitmapDisplay.h"

using namespace O3DCppEngine;

void CppBitmapDisplay::init()
{
	if (mIsInit) // already init
	{
		return;
	}
	mDisplaySettings = InitDisplay(mPixelSizeX/8, mPixelSizeY /8, 8, 1);

	mConsoleHandle = GetConsoleWindow();
	mDeviceContext = GetDC(mConsoleHandle);
	mIsInit = true;
	clear(ENCODE_COLOR(0, 0, 0, 0xFF), 0.0f);

	// prepare bitmap copy
	mMemHdc = CreateCompatibleDC(mDeviceContext);

	BITMAPINFO bi;
	ZeroMemory(&bi, sizeof(BITMAPINFO));
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = mPixelSizeX;
	bi.bmiHeader.biHeight = mPixelSizeY;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	mBitmap = CreateDIBSection(mDeviceContext, &bi, DIB_RGB_COLORS, (void**)&mBuffer, NULL, 0);
}


void CppBitmapDisplay::close()
{

	DeleteDC(mMemHdc);
	DeleteObject(mBitmap);

	ReleaseDC(mConsoleHandle, mDeviceContext);

	if (mDisplaySettings)
		CloseDisplay(mDisplaySettings);

	mDisplaySettings = nullptr;
}

void	CppBitmapDisplay::swap()
{
	renderAll();
	
	char* writeBuffer = mBuffer;

	// copy mPixelBuffer to display buffer
	for (int j = mPixelSizeY-1; j >=0; j--)
	{
		unsigned int lineOffset = j * mPixelSizeX;
		for (size_t i = 0; i < mPixelSizeX; i++)
		{
			writeBuffer[3] = mPixelBuffer[i + lineOffset] >> 24;
			writeBuffer[0] = (mPixelBuffer[i + lineOffset] >> 16)&0xFF;
			writeBuffer[1] = (mPixelBuffer[i + lineOffset] >> 8)&0xFF;
			writeBuffer[2] = (mPixelBuffer[i + lineOffset] )&0xFF;
			writeBuffer += 4;
		}
	}

	HBITMAP restore;
	restore = (HBITMAP)SelectObject(mMemHdc, mBitmap);
	BitBlt(mDeviceContext, 0, 0, mPixelSizeX, mPixelSizeY, mMemHdc, 0, 0, SRCCOPY);
	SelectObject(mMemHdc, restore);

}

