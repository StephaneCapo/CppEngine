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

		std::string		mTextureName;
		vect2Dui		mTexturePixelSize;
		unsigned int*	mTexturePixelBuffer;

		void	init() override;
		void	close() override;

		static unsigned int blendAlpha(unsigned int colora, unsigned int colorb)
		{
			unsigned int alpha = colorb >> 24;

			unsigned int rb1 = ((0xFF - alpha) * (colora & 0xFF00FF)) >> 8;
			unsigned int rb2 = (alpha * (colorb & 0xFF00FF)) >> 8;
			unsigned int g1 = ((0xFF - alpha) * (colora & 0x00FF00)) >> 8;
			unsigned int g2 = (alpha * (colorb & 0x00FF00)) >> 8;
			return ((rb1 + rb2) & 0xFF00FF) | ((g1 + g2) & 0x00FF00) | 0xFF000000;
		}

		friend class DisplayBase;

	public:

		std::string getTextureName()
		{
			return mTextureName;
		}

		void setTextureName(const std::string& name)
		{
			mTextureName = name;
		}

		unsigned int	getPixel(unsigned int px, unsigned int py) const
		{
			if ((px >= mTexturePixelSize.x) || (py >= mTexturePixelSize.y))
			{
				return 0xFFFFFFFF;
			}
			return mTexturePixelBuffer[px + py * mTexturePixelSize.x];
		}

		void	setPixel(unsigned int px, unsigned int py, unsigned int color) const
		{
			if ((px >= mTexturePixelSize.x) || (py >= mTexturePixelSize.y))
			{
				return;
			}

			mTexturePixelBuffer[px + py * mTexturePixelSize.x] = color;
		}

	};
}
