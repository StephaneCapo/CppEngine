#include "CppEngine.h"
#include "Factory.h"
#include "CppConsoleDisplay.h"
#include "Segment2D.h"


using namespace O3DCppEngine;

// init Factory
CppEngine::CppEngine()
{
	mFactory = new Factory();

	// register core classes
	mFactory->registerClass("Display", CREATION_FUNC(CppConsoleDisplay));
	mFactory->registerClass("Segment2D", CREATION_FUNC(Segment2D));
}

CppEngine::~CppEngine()
{

}