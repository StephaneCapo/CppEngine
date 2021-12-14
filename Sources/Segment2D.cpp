#include "Segment2D.h"
#include "DisplayBase.h"
#include "PixelBufferDrawer.h"

using namespace O3DCppEngine;

vect2Df& Segment2D::operator [](size_t index)
{
	return mPoses[index];
}

void	Segment2D::render(const DisplayBase* disp)
{
	// TODO optimize this (a lot)
	vect2Df	transformPoses[2];
	
	mTransform.transform(transformPoses, mPoses, 2);

	vect2Df	v = transformPoses[1];
	v-= transformPoses[0];

	float dispZ = disp->get2DCurrentDisplayZ();

	PixelBufferDrawer<true,true> drawer = disp->getPixelDrawer();

	if (fabsf(v.x) > fabsf(v.y))
	{
		if (transformPoses[0].x > transformPoses[1].x)
		{
			transformPoses[0].swap(transformPoses[1]);
		}

		float coefy = (transformPoses[1].y - transformPoses[0].y)/ (transformPoses[1].x - transformPoses[0].x);
		int y = (int)transformPoses[0].y;
		float coefx = 1.0f;
		for (int x = (int)transformPoses[0].x; x <= (int)transformPoses[1].x; x++)
		{
			drawer.setPixel(x, y, mColor, dispZ);
			y = (int)(transformPoses[0].y + coefy * coefx);
			coefx += 1.0f;
		}

	}
	else
	{
		if (transformPoses[0].y > transformPoses[1].y)
		{
			transformPoses[0].swap(transformPoses[1]);
		}

		float coefx = (transformPoses[1].x - transformPoses[0].x) / (transformPoses[1].y - transformPoses[0].y);
		int x = (int)transformPoses[0].x;
		float coefy = 1.0f;
		for (int y = (int)transformPoses[0].y; y <= (int)transformPoses[1].y; y++)
		{
			drawer.setPixel(x, y, mColor, dispZ);
			x = (int)(transformPoses[0].x + coefx * coefy);
			coefy += 1.0f;
		}
	}
}