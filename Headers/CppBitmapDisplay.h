#pragma once
#include <Windows.h>
#include <memory>
#include "DisplayBase.h"
#include "ConsoleDisplay.h"

namespace O3DCppEngine
{
	// implementation of DisplayBase for displaying a bitmap buffer in the console
	class CppBitmapDisplay : public DisplayBase
	{
		DECLARE_CLASS(CppBitmapDisplay)

	protected:
		DisplaySettings* mDisplaySettings = nullptr; // just for console init
		HWND mConsoleHandle;
		HDC  mDeviceContext;

		// used for drawing/copying
		HDC		mMemHdc;
		char*	mBuffer=nullptr;
		HBITMAP mBitmap;


		// max displaySize for bitmap display is 1024*720
		vect2Dui	getMaxPixelSize() const override
		{
			return { 1024,720 };
		}
	public:

		CppBitmapDisplay() : DisplayBase()
		{

		}

		virtual ~CppBitmapDisplay()
		{
			close();
		}


		void init() override;
		void close() override;

		void	swap() override;

	};

}
