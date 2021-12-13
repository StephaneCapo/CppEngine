#pragma once
#include "EngineManagedClass.h"
#include "vect2D.h"

namespace O3DCppEngine
{
	class DisplayBase;
	// base class for Shape (circle, rectangle...)
	class Texture : public EngineManagedClass
	{
		DECLARE_CLASS(Texture);
	protected:

		std::string		mFileName;
		vect2Dui		mPixelSize;
		unsigned int*	mPixelBuffer=nullptr;


	public:

		std::string getFileName()
		{
			return mFileName;
		}

		void setFileName(const std::string& name)
		{
			mFileName = name;
		}
		void	init() override;
		void	close() override;

	};
}
