#pragma once
#include "Shape2D.h"

namespace O3DCppEngine
{
	class DisplayBase;
	// base class for Shape (circle, rectangle...)
	class Sprite : public Shape2D
	{
		DECLARE_CLASS(Sprite);
	protected:

		std::string	mTextureName;

		void	init() override;
		void	close() override;

	public:

		std::string getTextureName()
		{
			return mTextureName;
		}

		void setTextureName(const std::string& name)
		{
			mTextureName = name;
		}
		
		void	render(const DisplayBase* disp) override;

	};
}
