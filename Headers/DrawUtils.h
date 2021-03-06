#pragma once
#include "vect2D.h"

namespace O3DCppEngine
{
	inline unsigned int blendAlpha(unsigned int colora, unsigned int colorb)
	{
		unsigned int alpha = colorb >> 24;
		unsigned int rb1 = ((0xFF - alpha) * (colora & 0xFF00FF)) >> 8;
		unsigned int rb2 = (alpha * (colorb & 0xFF00FF)) >> 8;
		unsigned int g1 = ((0xFF - alpha) * (colora & 0x00FF00)) >> 8;
		unsigned int g2 = (alpha * (colorb & 0x00FF00)) >> 8;
		return ((rb1 + rb2) & 0xFF00FF) | ((g1 + g2) & 0x00FF00) | 0xFF000000;
	}

	// blendFactor must be in 0x00-0xFF
	inline unsigned int blendColor(unsigned int colora, unsigned int colorb, unsigned int blendFactor)
	{
		unsigned int rb1 = ((0xFF - blendFactor) * (colora & 0xFF00FF)) >> 8;
		unsigned int rb2 = (blendFactor * (colorb & 0xFF00FF)) >> 8;
		unsigned int ag1 = ((0xFF - blendFactor) * ((colora & 0xFF00FF00) >> 8)) >> 8;
		unsigned int ag2 = (blendFactor * ((colorb & 0xFF00FF00) >> 8)) >> 8;
		return ((rb1 + rb2) & 0xFF00FF) | (((ag1 + ag2) << 8) & 0xFF00FF00);
	}

	inline unsigned int multColor(unsigned int colora, unsigned int colorb)
	{
		unsigned int result = 0;
		for (unsigned int i = 0; i < 4; i++)
		{
			unsigned int decal = (i << 3);
			unsigned int compa = (colora & (0xFF << decal))>> decal;
			unsigned int compb = (colorb & (0xFF << decal))>> decal;

			result |= (((compa * compb) >> 8) & 0xFF) << decal;
		}
		return result;
	}

	// RGBA to unsigned int
#define ENCODE_COLOR(r,g,b,a) ((unsigned int)((r)|(g<<8)|(b<<16)|(a<<24)))

	typedef unsigned int	RGBAColor;
	class TextureUV : public vect2Df
	{
	public:
		using vect2Df::vect2Df;
	};
}