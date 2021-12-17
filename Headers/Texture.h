#pragma once
#include "EngineManagedClass.h"
#include "DrawUtils.h"

namespace O3DCppEngine
{
	class DisplayBase;
	// base class for Shape (circle, rectangle...)
	class Texture : public EngineManagedClass
	{
		DECLARE_CLASS(Texture);
	protected:

		std::string		mFileName;
		vect2Dui		mPixelSize = {0,0};
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

		RGBAColor	getColorAt(TextureUV uv) const
		{
			vect2Df wrappeduv = uv;
			wrappeduv.x = fmodf(wrappeduv.x, 1.0f);
			wrappeduv.y = fmodf(wrappeduv.y, 1.0f);

			vect2Dui texturePos = mPixelSize;
			texturePos.x = (unsigned int)((float)texturePos.x * wrappeduv.x);
			texturePos.y = (unsigned int)((float)texturePos.y * wrappeduv.y);

			return mPixelBuffer[texturePos.x + texturePos.y * mPixelSize.x];
		}

		vect2Dui	getPixelSize()
		{
			return mPixelSize;
		}

	};
}
