#pragma once
#include <Windows.h>
#include <memory>
#include "DisplayBase.h"
#include "ConsoleDisplay.h"

namespace O3DCppEngine
{
	class CppBitmapDisplay : public DisplayBase
	{
		DECLARE_CLASS(CppBitmapDisplay)

	protected:
		DisplaySettings* mDisplaySettings = nullptr; // just for console init
		HWND mConsoleHandle;
		HDC  mDeviceContext;
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
