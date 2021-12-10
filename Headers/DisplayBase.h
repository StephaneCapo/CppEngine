#pragma once
#include "EngineManagedClass.h"
#include "Drawable.h"
#include <vector>

namespace O3DCppEngine
{
	// manage display in console
	class DisplayBase : public EngineManagedClass
	{
	protected:

		void memset32(unsigned int* dst, unsigned int val, unsigned int ui32count) const;

		unsigned int mPixelSizeX = 320;
		unsigned int mPixelSizeY = 240;
		
		bool		 mIsInit = false;

		// internal buffers
		unsigned int*	mPixelBuffer = nullptr;
		float*			mZBuffer = nullptr;
		float			m2DCurrentDisplayZ=0.0f;

		std::vector<std::shared_ptr<Drawable>>	mDrawableList;

		// render All drawables in the order of the list
		// 
		void renderAll();

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

		void	setDisplaySize(unsigned int pixelSizeX, unsigned int pixelSizeY);

		// if not init, return 0,0
		std::pair<unsigned int, unsigned int>	getDisplaySize()
		{
			if (mIsInit)
			{
				return { mPixelSizeX ,mPixelSizeY };
			}
			return { 0,0 };
		}

		// add drawable to be draw and return its position in drawable list 
		unsigned int	add(std::shared_ptr<Drawable> drw);
		// remove the first occurrance of the given drawable from list 
		// return true if found 
		bool			removeFirst(std::shared_ptr<Drawable> drw);
		// remove all occurances of given drawable
		void			removeAll(std::shared_ptr<Drawable> drw);
		
		void			clear(unsigned int clearColor, float clearZ) const;

		// inherited classes must override swap (flush screen)
		virtual void	swap() = 0;

		virtual ~DisplayBase();

		unsigned int	getPixel(unsigned int px, unsigned int py) const
		{
			if ((px >= mPixelSizeX) || (py>= mPixelSizeY))
			{
				return 0xFFFFFFFF;
			}
			return mPixelBuffer[px + py * mPixelSizeX];
		}

		void	setPixel(unsigned int px, unsigned int py,unsigned int color,float Z) const
		{
			if ((px >= mPixelSizeX) || (py >= mPixelSizeY))
			{
				return;
			}

			if (Z < mZBuffer[px + py * mPixelSizeX])
				return;

			if ((color & 0xFF000000) != 0xFF000000) // transparency
			{
				color = blendAlpha(mPixelBuffer[px + py * mPixelSizeX], color);
			}
			if (color & 0xFF000000) // not fully transparent
				mPixelBuffer[px + py * mPixelSizeX] = color;

			mZBuffer[px + py * mPixelSizeX] = Z;
		}

		float get2DCurrentDisplayZ() const
		{
			return m2DCurrentDisplayZ;
		}

		void set2DCurrentDisplayZ(float Z)
		{
			m2DCurrentDisplayZ=Z;
		}
	};

	// RGBA to unsigned int
#define ENCODE_COLOR(r,g,b,a) ((unsigned int)((r)|(g<<8)|(b<<16)|(a<<24)))
}