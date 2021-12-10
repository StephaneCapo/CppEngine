#pragma once
#include "Shape2D.h"

namespace O3DCppEngine
{
	class DisplayBase;
	// base class for Shape (circle, rectangle...)
	class Segment2D : public Shape2D
	{
		DECLARE_CLASS(Segment2D);
	protected:

		vect2Df			mPoses[2];
		unsigned int	mColor=0x000000FF;

		void	init() override
		{
		}
		void	close() override
		{
		}

	public:

		unsigned int getColor()
		{
			return mColor;
		}
		void	setColor(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
		{
			mColor = (R) | (G << 8) | (B << 16) | (A<<24);
		}

		void setColor(unsigned int c)
		{
			mColor = c;
		}

		// operateur pour récupérer une des points du segment
		vect2Df& operator [](size_t index);
		void	render(const DisplayBase* disp) override;

	};
}