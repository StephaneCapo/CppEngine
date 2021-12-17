#include "Sprite.h"
#include "DrawUtils.h"
#include "DisplayBase.h"
#include "PixelBufferDrawer.h"
#include "VerticeType.h"
#include "Factory.h"

using namespace O3DCppEngine;

void	Sprite::init()
{
	if (mTextureName.length())
	{
		mTexture = CppEngine::getFactory().getInstance<Texture>("Texture");
		mTexture->setFileName("BBYoda.bmp");
		mTexture->init();
	}
}
void	Sprite::close()
{
	mTexture = nullptr;
	mTextureName = "";
}

void	Sprite::render(DisplayBase* disp)
{
	if (mTexture == nullptr)
	{
		return;
	}

	vect2Df	transformPoses[4];

	vect2Di	textureSize = mTexture->getPixelSize();

	transformPoses[0].x = (float)(-textureSize.x / 2);
	transformPoses[0].y = (float)(-textureSize.y / 2);
	transformPoses[1].x = (float)(textureSize.x / 2);
	transformPoses[1].y = (float)(-textureSize.y / 2);
	transformPoses[2].x = (float)(textureSize.x / 2);
	transformPoses[2].y = (float)(textureSize.y / 2);
	transformPoses[3].x = (float)(-textureSize.x / 2);
	transformPoses[3].y = (float)(textureSize.y / 2);

	mTransform.transform(transformPoses, transformPoses, 4);

	disp->getDrawContext().mTexture = mTexture;

	TextureUV	uvs[4];
	uvs[0] = { 0.0f,0.0f };
	uvs[1] = { 1.0f,0.0f };
	uvs[2] = { 1.0f,1.0f };
	uvs[3] = { 0.0,1.0f };

	std::vector<std::tuple<vect2Df, TextureUV>>	vertices = { {transformPoses[0],uvs[0]},{transformPoses[1],uvs[1]},{transformPoses[2],uvs[2]},{transformPoses[3],uvs[3]} };
	disp->rasterizePoly(vertices);

	disp->getDrawContext().mTexture = nullptr;
}