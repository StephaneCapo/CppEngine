#include "CppEngine.h"
#include "Factory.h"
#include "CppConsoleDisplay.h"
#include "CppBitmapDisplay.h"
#include "Segment2D.h"
#include "Rectangle2D.h"
#include "Texture.h"
#include "Sprite.h"

//#define CONSOLE_DISPLAY

using namespace O3DCppEngine;

Factory* CppEngine::mFactory=nullptr;

CppEngine::CppEngine()
{
	if (mFactory) // already done
		return;
	// init Factory
	mFactory = new Factory();

	// register core classes

#ifdef CONSOLE_DISPLAY
	mFactory->registerClass("Display", CREATION_FUNC(CppConsoleDisplay));
#else
	mFactory->registerClass("Display", CREATION_FUNC(CppBitmapDisplay));
#endif
	mFactory->registerClass("Segment2D", CREATION_FUNC(Segment2D));
	mFactory->registerClass("Rectangle2D", CREATION_FUNC(Rectangle2D));

	mFactory->registerClass("Texture", CREATION_FUNC(Texture));
	mFactory->registerClass("Sprite", CREATION_FUNC(Sprite));
}

CppEngine::~CppEngine()
{
	if (mFactory)
		delete mFactory;

	mFactory = nullptr;
}