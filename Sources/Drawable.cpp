#include "Drawable.h"
#include "PixelBufferDrawer.h"
#include "DisplayBase.h"

using namespace O3DCppEngine;

PixelBufferDrawer<true, false>	Drawable::getUnsafePixelDrawer(const DisplayBase* disp) const
{
	return disp->getUnsafePixelDrawer();
}