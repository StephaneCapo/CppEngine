#include "Shape2D.h"

using namespace O3DCppEngine;

void	transform2D::transform(vect2Df* dst, vect2Df* src, unsigned int count)
{
	vect2Df rotMatrix[2];
	rotMatrix[0][0] = cosf(mRotationAngle);
	rotMatrix[0][1] = -sinf(mRotationAngle);
	rotMatrix[1][0] = -rotMatrix[0][1];
	rotMatrix[1][1] = rotMatrix[0][0];

	for (unsigned int i = 0; i < count; i++)
	{
		vect2Df result;
		result.x = src[i].x * rotMatrix[0][0] + src[i].y * rotMatrix[0][1];
		result.y = src[i].x * rotMatrix[1][0] + src[i].y * rotMatrix[1][1];
		result *= mScale;
		result += mTranslation;
		dst[i] = result;
	}
}