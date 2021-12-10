#pragma once
#include "Drawable.h"
#include "vect2D.h"

namespace O3DCppEngine
{
	class transform2D
	{
	protected:
		float			mRotationAngle = 0.0f;
		float			mScale = 1.0f;
		vect2Df			mTranslation = { 0.0f,0.0f };
	public:

		float getRotationAngle()
		{
			return mRotationAngle;
		}
		void setRotationAngle(float a)
		{
			mRotationAngle=a;
		}
		float getScale()
		{
			return mScale;
		}
		void setScale(float s)
		{
			mScale = s;
		}
		vect2Df getTranslation()
		{
			return mTranslation;
		}
		void setTranslation(const vect2Df& t)
		{
			mTranslation = t;
		}

		void			transform(vect2Df* dst, vect2Df* src, unsigned int count);
	};

	class DisplayBase;
	// base class for Shape (circle, rectangle...)
	class Shape2D : public Drawable
	{
	protected:

		transform2D		mTransform;
		

	public:

		transform2D& getTransform()
		{
			return mTransform;
		}
		
	};
}