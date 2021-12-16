#pragma once
#include "Shape2D.h"

namespace O3DCppEngine
{
	class DisplayBase;
	// base class for Shape (circle, rectangle...)
	class Rectangle2D : public Shape2D
	{
		DECLARE_CLASS(Rectangle2D);
	protected:

		vect2Df			mPoses[2];
		unsigned int	mColor[4] = { 0x000000FF,0x000000FF,0x000000FF,0x000000FF };

		void	init() override
		{
		}
		void	close() override
		{
		}

	public:

		void	setColor(unsigned int index,unsigned char R, unsigned char G, unsigned char B, unsigned char A)
		{
			mColor[index] = (R) | (G << 8) | (B << 16) | (A << 24);
		}

		void setColor(unsigned int index,unsigned int c)
		{
			mColor[index] = c;
		}

		// operateur pour récupérer une des points du rectangle
		vect2Df& operator [](size_t index);
		void	render(const DisplayBase* disp) override;

	};
}