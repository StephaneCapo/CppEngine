#pragma once
#include "CppEngine.h"
#include "Shape2D.h"
#include "Texture.h"

namespace O3DCppEngine
{
	class DisplayBase;
	// base class for Shape (circle, rectangle...)
	class Sprite : public Shape2D
	{
		DECLARE_CLASS(Sprite);
	protected:

		std::string		mTextureName;
		sp<Texture>		mTexture;

	public:
		void	init() override;
		void	close() override;

		std::string getTextureName()
		{
			return mTextureName;
		}

		void setTextureName(const std::string& name)
		{
			mTextureName = name;
		}
		
		void	render(DisplayBase* disp) override;

	};
}
