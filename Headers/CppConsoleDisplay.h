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