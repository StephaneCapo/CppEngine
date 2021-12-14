#pragma once
#include "EngineManagedClass.h"
#include "vect2D.h"
#include "PixelBufferDrawer.h"

namespace O3DCppEngine
{
	class DisplayBase;
	// base class for all drawables
	class Drawable : public EngineManagedClass
	{
	protected:

		virtual void	render(const DisplayBase* disp) = 0;

		PixelBufferDrawer<true, false>	getUnsafePixelDrawer(const DisplayBase* disp) const;

	public:

		friend class DisplayBase;
	};
}