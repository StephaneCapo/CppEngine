#pragma once
#include <vector>
#include "EngineManagedClass.h"
#include "Drawable.h"
#include "Texture.h"
#include "PixelBufferDrawer.h"
#include "ConvexPolyRasterizer.h"
#include "DrawContext.h"

namespace O3DCppEngine
{

	// base class for console display manager
	// the real display is done by implementation classes of this base class
	class DisplayBase : public EngineManagedClass
	{
	protected:

		// utility method
		static void memset32(unsigned int* dst, unsigned int val, unsigned int ui32count);

		unsigned int mPixelSizeX = 320;
		unsigned int mPixelSizeY = 240;
		
		bool		 mIsInit = false;

		// internal buffers
		unsigned int*	mPixelBuffer = nullptr; // RGBA
		float*			mZBuffer = nullptr; // Z
		float			m2DCurrentDisplayZ=0.0f;

		DrawContext		mDrawContext;

		// the drawable list to be draw in the display at each swap
		std::vector<std::shared_ptr<Drawable>>	mDrawableList;

		// render All drawables in the order of the list
		void renderAll();

		// only allowed class can access to unsafe pixel drawer (faster, but don't check if pixel in inside buffer)
		PixelBufferDrawer<true, false>	getUnsafePixelDrawer() const;

		// max displaySize is given by the implementation class
		virtual vect2Dui	getMaxPixelSize() const = 0;

	public:

		// display size must be set before init
		void	setDisplaySize(unsigned int pixelSizeX, unsigned int pixelSizeY);

		// if not init, return 0,0
		std::pair<unsigned int, unsigned int>	getDisplaySize()
		{
			if (mIsInit)
			{
				return { mPixelSizeX ,mPixelSizeY };
			}
			return { 0,0 };
		}

		// add drawable to be draw and return its position in drawable list 
		unsigned int	add(std::shared_ptr<Drawable> drw);
		// remove the first occurrance of the given drawable from list 
		// return true if found 
		bool			removeFirst(std::shared_ptr<Drawable> drw);
		// remove all occurances of given drawable
		void			removeAll(std::shared_ptr<Drawable> drw);
		
		// clear the buffers using the given clearColor and Z value
		void			clear(unsigned int clearColor, float clearZ) const;

		// inherited classes must override swap (flush screen)
		virtual void	swap() = 0;

		virtual ~DisplayBase();

		float get2DCurrentDisplayZ() const
		{
			return m2DCurrentDisplayZ;
		}

		void set2DCurrentDisplayZ(float Z)
		{
			m2DCurrentDisplayZ=Z;
		}

		// return a safe pixel drawer
		PixelBufferDrawer<true,true>	getPixelDrawer() const;

		// access to unsafe pixeldrawer
		friend class Drawable;

		template <typename ... components>
		void rasterizePoly(std::vector<std::tuple<components...>>& verticelist) const;

		DrawContext& getDrawContext()
		{
			return mDrawContext;
		}
	};

	template <typename ... components>
	void DisplayBase::rasterizePoly(std::vector<std::tuple<components...>>& verticelist) const
	{
		PixelBufferDrawer<true, false>	drawer = getUnsafePixelDrawer();
		ConvexPolyRasterizer<true, components...>		rast(drawer, &mDrawContext);

		rast.draw(verticelist);
	}


}