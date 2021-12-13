#pragma once

namespace O3DCppEngine
{
	template<bool useZ>
	class PixelBufferDrawer
	{
	protected:
		unsigned int	mPixelSizeX;
		unsigned int	mPixelSizeY;
		unsigned int*	mPixelBuffer;
		float*			mZBuffer = nullptr;

		static unsigned int blendAlpha(unsigned int colora, unsigned int colorb)
		{
			unsigned int alpha = colorb >> 24;

			unsigned int rb1 = ((0xFF - alpha) * (colora & 0xFF00FF)) >> 8;
			unsigned int rb2 = (alpha * (colorb & 0xFF00FF)) >> 8;
			unsigned int g1 = ((0xFF - alpha) * (colora & 0x00FF00)) >> 8;
			unsigned int g2 = (alpha * (colorb & 0x00FF00)) >> 8;
			return ((rb1 + rb2) & 0xFF00FF) | ((g1 + g2) & 0x00FF00) | 0xFF000000;
		}

	public:
		PixelBufferDrawer(unsigned int* pixelBuffer, unsigned int psx, unsigned int psy,float* zbuf=nullptr) : mPixelBuffer(pixelBuffer)
			, mPixelSizeX(psx)
			, mPixelSizeY(psy)
			, mZBuffer(zbuf)
		{

		}

		inline unsigned int	getPixel(unsigned int px, unsigned int py) const
		{
			if ((px >= mPixelSizeX) || (py >= mPixelSizeY))
			{
				return 0xFFFFFFFF;
			}
			return mPixelBuffer[px + py * mPixelSizeX];
		}

		inline void	setPixel(unsigned int px, unsigned int py, unsigned int color, float Z=0.0f) const
		{
			if ((px >= mPixelSizeX) || (py >= mPixelSizeY))
			{
				return;
			}

			if (useZ)
			{
				if (Z < mZBuffer[px + py * mPixelSizeX])
					return;
			}

			if ((color & 0xFF000000) != 0xFF000000) // transparency
			{
				color = blendAlpha(mPixelBuffer[px + py * mPixelSizeX], color);
			}
			if (color & 0xFF000000) // not fully transparent
				mPixelBuffer[px + py * mPixelSizeX] = color;

			if (useZ)
			{
				mZBuffer[px + py * mPixelSizeX] = Z;
			}
		}
	};
}