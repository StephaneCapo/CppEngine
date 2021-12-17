#pragma once
#include "CppEngine.h"
#include "DrawUtils.h"
#include "Texture.h"

namespace O3DCppEngine
{

	class DrawContext
	{
	public:
		RGBAColor	mCurrentColor = 0xFFFFFFFF;
		float		mCurrentZ = 0.0f;
		
		sp<Texture>	mTexture=nullptr;
	};
}