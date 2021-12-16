#include "Rectangle2D.h"
#include "DisplayBase.h"
#include "PixelBufferDrawer.h"
#include "VerticeType.h"

using namespace O3DCppEngine;

vect2Df& Rectangle2D::operator [](size_t index)
{
	return mPoses[index];
}

void	Rectangle2D::render(const DisplayBase* disp)
{
	vect2Df	transformPoses[4];

	transformPoses[0] = mPoses[0];
	transformPoses[1].x = mPoses[1].x;
	transformPoses[1].y = mPoses[0].y;
	transformPoses[2] = mPoses[1];
	transformPoses[3].x = mPoses[0].x;
	transformPoses[3].y = mPoses[1].y;

	mTransform.transform(transformPoses, transformPoses, 4);

	std::vector<std::tuple<vect2Df, RGBAColor>>	vertices = { {transformPoses[0],mColor[0]},{transformPoses[1],mColor[1]},{transformPoses[2],mColor[2]},{transformPoses[3],mColor[3]} };
	disp->rasterizePoly(vertices);

}