#pragma once
#include <memory>
#include "DisplayBase.h"
#include "ConsoleDisplay.h"

namespace O3DCppEngine
{
	class CppConsoleDisplay : public DisplayBase
	{
		DECLARE_CLASS(CppConsoleDisplay)

	protected:
		DisplaySettings* mDisplaySettings=nullptr;
		DisplayZone* mFullScreenZone = nullptr;

		// max displaySize for console display is 320*240
		vect2Dui	getMaxPixelSize() const override
		{
			return { 320,240 };
		}

	public:

		CppConsoleDisplay() : DisplayBase()
		{

		}

		virtual ~CppConsoleDisplay()
		{
			close();
		}


		void init() override;
		void close() override;

		void	swap() override;

	};

}