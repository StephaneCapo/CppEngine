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
}


void CppBitmapDisplay::close()
{
	ReleaseDC(mConsoleHandle, mDeviceContext);

	if (mDisplaySettings)
		CloseDisplay(mDisplaySettings);

	mDisplaySettings = nullptr;
}

void	CppBitmapDisplay::swap()
{
	renderAll();
	HDC memHdc = CreateCompatibleDC(mDeviceContext);
	BITMAPINFO bi;
	ZeroMemory(&bi, sizeof(BITMAPINFO));
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = mPixelSizeX;
	bi.bmiHeader.biHeight = mPixelSizeY;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	char* buffer;
	HBITMAP bitmap = CreateDIBSection(mDeviceContext, &bi, DIB_RGB_COLORS, (void**)&buffer, NULL, 0);
	
	char* writeBuffer = buffer;

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

	//memcpy(buffer, mPixelBuffer, mPixelSizeX * mPixelSizeY * sizeof(unsigned int));

	HBITMAP restore;
	restore = (HBITMAP)SelectObject(memHdc, bitmap);
	BitBlt(mDeviceContext, 0, 0, mPixelSizeX, mPixelSizeY, memHdc, 0, 0, SRCCOPY);
	SelectObject(memHdc, restore);
	DeleteDC(memHdc);
	DeleteObject(bitmap);

}

