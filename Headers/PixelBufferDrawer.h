#pragma once
#include "vect2D.h"
#include "DrawUtils.h"

namespace O3DCppEngine
{
	// safetyChecks check if pixel coordinates is in the good range
	template<bool useZ,bool safetyChecks>
	class PixelBufferDrawer
	{
	protected:
		vect2Dui		mPixelSize;
		unsigned int*	mPixelBuffer;
		float*			mZBuffer = nullptr;

		

	public:

		

		class DrawerLine
		{
		protected:
			float*			 mZBufferLine = nullptr;
			unsigned int*	 mPixelBufferLine = nullptr;
			unsigned int	 mLineSize;

			DrawerLine(unsigned int* pixelline, unsigned int lineSize, float* zline = nullptr) : mZBufferLine(zline)
				, mPixelBufferLine(pixelline)
				, mLineSize(lineSize)
			{

			}

		public:

			friend class PixelBufferDrawer;

			inline void	setPixel(unsigned int px, unsigned int color, float Z = 0.0f) const
			{
				if (safetyChecks)
				{
					if (px >= mLineSize)
					{
						return;
					}
				}

				if (useZ)
				{
					if (Z < mZBufferLine[px])
						return;
					mZBufferLine[px] = Z;
				}

				if (color & 0xFF000000) // not fully transparent
				{
					if ((color & 0xFF000000) != 0xFF000000) // transparency
					{
						color = blendAlpha(mPixelBufferLine[px], color);
					}
					mPixelBufferLine[px] = color;
				}
			}
		};

		PixelBufferDrawer(unsigned int* pixelBuffer, unsigned int psx, unsigned int psy,float* zbuf=nullptr) : mPixelBuffer(pixelBuffer)
			, mZBuffer(zbuf)
		{
			mPixelSize.x = psx;
			mPixelSize.y = psy;
		}

		inline unsigned int	getPixel(unsigned int px, unsigned int py) const
		{
			if (safetyChecks)
			{
				if ((px >= mPixelSize.x) || (py >= mPixelSize.y))
				{
					return 0xFFFFFFFF;
				}
			}
			return mPixelBuffer[px + py * mPixelSize.x];
		}

		inline void	setPixel(unsigned int px, unsigned int py, unsigned int color, float Z=0.0f) const
		{
			if (safetyChecks)
			{
				if ((px >= mPixelSize.x) || (py >= mPixelSize.y))
				{
					return;
				}
			}

			if (useZ)
			{
				if (Z < mZBuffer[px + py * mPixelSize.x])
					return;
				mZBuffer[px + py * mPixelSize.x] = Z;
			}

			if (color & 0xFF000000) // not fully transparent
			{
				if ((color & 0xFF000000) != 0xFF000000) // transparency
				{
					color = blendAlpha(mPixelBuffer[px + py * mPixelSize.x], color);
				}
				mPixelBuffer[px + py * mPixelSize.x] = color;
			}
		}
		vect2Dui getPixelSize()
		{
			return mPixelSize;
		}

		DrawerLine	getLine(unsigned int lineIndex)
		{
			if (safetyChecks)
			{
				if (lineIndex >= mPixelSize.y)
				{
					return DrawerLine(nullptr, 0, nullptr);
				}
			}

			unsigned int linepos = lineIndex * mPixelSize.x;

			return DrawerLine(&mPixelBuffer[linepos], mPixelSize.x, &mZBuffer[linepos]);
		}
	};
}