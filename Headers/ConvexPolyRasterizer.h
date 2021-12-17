#pragma once
#include <vector>
#include <tuple>
#include <map>
#include "PixelBufferDrawer.h"
#include "DrawContext.h"
#include "DrawUtils.h"

namespace O3DCppEngine
{

	template <typename T, typename Tuple>
	struct has_type;

	template <typename T>
	struct has_type<T, std::tuple<>> : std::false_type {};

	template <typename T, typename U, typename... Ts>
	struct has_type<T, std::tuple<U, Ts...>> : has_type<T, std::tuple<Ts...>> {};

	template <typename T, typename... Ts>
	struct has_type<T, std::tuple<T, Ts...>> : std::true_type {};

	template <typename T, typename Tuple>
	using tuple_contains_type = typename has_type<T, Tuple>::type;

	template <class T, class Tuple>
	struct Index;

	template <typename T>
	struct Index<T, std::tuple<>> {
		static const std::size_t value = 20; // never more than 6 or 7 verticesComponents ?
		};

	template <class T, class... Types>
	struct Index<T, std::tuple<T, Types...>> {
		static const std::size_t value = 0;
	};

	template <class T, class U, class... Types>
	struct Index<T, std::tuple<U, Types...>> {
		static const std::size_t value = 1 + Index<T, std::tuple<Types...>>::value;
	};

	// utils
	template<bool doIt, typename ... verticesComponents>
	class DoRGBAColorBlend
	{
	public:
		DoRGBAColorBlend(RGBAColor& color, const std::tuple< verticesComponents...>& p1tuple, const std::tuple< verticesComponents...>& p2tuple, unsigned int lerp)
		{
			const size_t i = Index<RGBAColor, std::tuple< verticesComponents...>>::value;
			color = blendColor(std::get<i>(p1tuple), std::get<i>(p2tuple), lerp >> 8);
		}

		DoRGBAColorBlend(std::tuple< verticesComponents...>& result, const std::tuple< verticesComponents...>& p1tuple, const std::tuple< verticesComponents...>& p2tuple, unsigned int lerp)
		{
			const size_t i = Index<RGBAColor, std::tuple< verticesComponents...>>::value;
			std::get<i>(result) = blendColor(std::get<i>(p1tuple), std::get<i>(p2tuple), lerp >> 8);
		}
	};
	template<typename ... verticesComponents>
	class DoRGBAColorBlend<false, verticesComponents...>
	{
	public:
		DoRGBAColorBlend(RGBAColor& color, const std::tuple< verticesComponents...>& p1tuple, const std::tuple< verticesComponents...>& p2tuple, unsigned int lerp)
		{
		}
		DoRGBAColorBlend(std::tuple< verticesComponents...>& result, const std::tuple< verticesComponents...>& p1tuple, const std::tuple< verticesComponents...>& p2tuple, unsigned int lerp)
		{
		}
	};

	template<bool doIt, typename ... verticesComponents>
	class DoUVBlend
	{
	public:
		DoUVBlend(TextureUV& uv, const std::tuple< verticesComponents...>& p1, const std::tuple< verticesComponents...>& p2, unsigned int lerp)
		{
			const size_t i = Index<TextureUV, std::tuple< verticesComponents...>>::value;
			uv = std::get<i>(p1) * ((float)(0xFFFF - lerp) / 65535.0f);
			uv += std::get<i>(p2) * ((float)(lerp) / 65535.0f);
		}

		DoUVBlend(RGBAColor& color,sp<Texture> texture, const std::tuple< verticesComponents...>& p1, const std::tuple< verticesComponents...>& p2, unsigned int lerp)
		{
			const size_t i = Index<TextureUV, std::tuple< verticesComponents...>>::value;
			TextureUV uv = std::get<i>(p1) * ((float)(0xFFFF - lerp) / 65535.0f);
			uv += std::get<i>(p2) * ((float)(lerp) / 65535.0f);
			color= multColor(color,texture->getColorAt(uv));
		}

		DoUVBlend(std::tuple< verticesComponents...>& result, const std::tuple< verticesComponents...>& p1, const std::tuple< verticesComponents...>& p2, unsigned int lerp)
		{
			const size_t i = Index<TextureUV, std::tuple< verticesComponents...>>::value;
			TextureUV uv = std::get<i>(p1) * ((float)(0xFFFF - lerp) / 65535.0f);
			uv += std::get<i>(p2) * ((float)(lerp) / 65535.0f);
			std::get<i>(result) = uv;
		}
	};
	template<typename ... verticesComponents>
	class DoUVBlend<false, verticesComponents...>
	{
	public:
		DoUVBlend(TextureUV& uv, const std::tuple< verticesComponents...>& p1, const std::tuple< verticesComponents...>& p2, unsigned int lerp)
		{
		}
		DoUVBlend(RGBAColor& color, sp<Texture> texture, const std::tuple< verticesComponents...>& p1, const std::tuple< verticesComponents...>& p2, unsigned int lerp)
		{
		}
		DoUVBlend(std::tuple< verticesComponents...>& result, const std::tuple< verticesComponents...>& p1, const std::tuple< verticesComponents...>& p2, unsigned int lerp)
		{
		}
	};

	template<bool useZ, typename ... verticesComponents>
	class ConvexPolyRasterizer
	{
	protected:

		typedef std::tuple<verticesComponents...> verticeType;

		PixelBufferDrawer<useZ,false>&	mPixelBufferDrawer;
		// draw context handle generic color, generic z, current texture... 
		const DrawContext*					mDrawContext=nullptr;

		// for each line in buffer, list of starting/ending pos
		std::vector<std::map<unsigned char, std::pair<unsigned int,verticeType>>>	mLimits;

		void drawSegmentLimits(const verticeType& p1, const verticeType& p2);

		void rasterizeLines();

		// lfactor in 0, 0xffff
		verticeType	Lerp(const verticeType& p1, const verticeType& p2, unsigned int lfactor)
		{
			verticeType	result;
			/*if (tuple_contains_type<vect3Df, verticeType>::value)
			{
				
			}
			else*/ if (tuple_contains_type<vect2Df, verticeType>::value)
			{
				const size_t i = Index<vect2Df, verticeType>::value;

				vect2Df l2d = std::get<i>(p1)*((float)(0xFFFF- lfactor)/65535.0f);
				l2d += std::get<i>(p2) * ((float)(lfactor)/ 65535.0f);
				std::get<i>(result) = l2d;
			}

			DoRGBAColorBlend<tuple_contains_type<RGBAColor, verticeType>::value, verticesComponents...> rgbablend(result, p1, p2, lfactor);
			DoUVBlend< tuple_contains_type<TextureUV, verticeType>::value, verticesComponents...> uvblend(result, p1, p2, lfactor);

			return result;
		}

		std::vector<verticeType> clipPolygon(const std::vector<verticeType>& vlist)
		{
			// todo
			return vlist;
		}

	public:
		ConvexPolyRasterizer(PixelBufferDrawer<useZ, false>& buffer,const DrawContext* c=nullptr) : mPixelBufferDrawer(buffer)
			, mDrawContext(c)
		{
			mLimits.resize(buffer.getPixelSize().y);
		}

		void	draw(const std::vector<verticeType>& vlist);
	};

	template<bool useZ, typename ... verticesComponents>
	void	ConvexPolyRasterizer<useZ, verticesComponents...>::draw(const std::vector<verticeType>& vlist)
	{
		bool ok=false;
		// check consistency
		/*if (useZ && tuple_contains_type<vect3Df, verticeType>::value)
		{
			ok = true;
		}
		else*/ if (tuple_contains_type<vect2Df, verticeType>::value)
		{
			ok = true;
		}
		
		if (ok == false)
		{
			return;
		}

		std::vector<verticeType> clippedvlist=clipPolygon(vlist);

		// compute limits for each segment
		for (size_t i = 0; i < clippedvlist.size(); i++)
		{
			drawSegmentLimits(clippedvlist[i], clippedvlist[(i + 1) % clippedvlist.size()]);
		}
		// then rasterize each horizontal line
		rasterizeLines();
	}

	// polygon should already be clipped here, so don't need to test out of screen points
	template<bool useZ, typename ... verticesComponents>
	void	ConvexPolyRasterizer<useZ, verticesComponents...>::drawSegmentLimits(const verticeType& p1, const verticeType& p2)
	{
		unsigned int order = 0;
		vect2Df	fp[2];

		const verticeType* vtp[2] = {&p1,&p2};
		vect2Dui pixSize=mPixelBufferDrawer.getPixelSize();
		/*if (useZ && tuple_contains_type<vect3Df, verticeType>::value)
		{
			// TODO
		}
		else*/ if (tuple_contains_type<vect2Df, verticeType>::value)
		{
			const size_t i = Index<vect2Df, verticeType>::value;
			fp[0] = std::get<i>(p1);
			fp[1] = std::get<i>(p2);
		}
		else
		{
			return;
		}

		if (fp[0].y > fp[1].y)
		{
			order = 1;
		}
		
		vect2Dui uip[2];
		uip[0].x = (unsigned int)fp[order].x;
		uip[0].y = (unsigned int)fp[order].y;
		uip[1].x = (unsigned int)fp[1-order].x;
		uip[1].y = (unsigned int)fp[1-order].y;

		unsigned int starty = uip[0].y;
		unsigned int endy = uip[1].y;

		if (starty == endy)
		{
			return;
		}

		int oneOnLenght = 0;
		oneOnLenght = 0xFFFF / (uip[1].y - uip[0].y+1);
		int dx = uip[1].x - uip[0].x;

		int lfactor = 0;

		for (unsigned int py = starty; py <= endy; py++)
		{
			int lerp = (lfactor * oneOnLenght);
			unsigned int px = uip[0].x+ ( (dx * lerp) >> 16);

			verticeType	blended= Lerp(*vtp[order], *vtp[1-order], lerp);

			mLimits[py][1-order] = { px,blended };
			lfactor++;
		}
	}

	template<bool useZ, typename ... verticesComponents>
	void	ConvexPolyRasterizer<useZ, verticesComponents...>::rasterizeLines()
	{
		int lineIndex = 0;
		for (auto& l : mLimits)
		{
			
			if (l.size()==2)
			{
				auto it = l.begin();
				std::pair<unsigned int, verticeType>& p1 = (*it).second;
				++it;
				std::pair<unsigned int, verticeType>& p2 = (*it).second;

				auto drawer = mPixelBufferDrawer.getLine(lineIndex);

				verticeType& p1tuple = p1.second;
				verticeType& p2tuple = p2.second;

				unsigned int oneOnLenght = 0xFFFF / (p2.first - p1.first + 1);
				unsigned int lfactor = 0;
				for (unsigned int px = p1.first; px <= p2.first; px++)
				{
					unsigned int color = 0xFFFFFFFF;
					float		 z = 0.0f;

					unsigned int lerp = (lfactor * oneOnLenght);

					/*if (useZ && tuple_contains_type<vect3Df, verticeType>::value)
					{
						
					}
					else*/ if (tuple_contains_type<vect2Df, verticeType>::value)
					{
						
					}

					if (mDrawContext)
					{
						color = mDrawContext->mCurrentColor;
					}
					
					// color management
					DoRGBAColorBlend<tuple_contains_type<RGBAColor, verticeType>::value, verticesComponents...> rgbablend(color, p1tuple, p2tuple, lerp);

					// texture coordinates ?
					if (mDrawContext)
					{
						if (mDrawContext->mTexture)
						{
							DoUVBlend< tuple_contains_type<TextureUV, verticeType>::value, verticesComponents...> uvblend(color, mDrawContext->mTexture, p1tuple, p2tuple, lerp);
						}
					}
					
					drawer.setPixel(px, color, z);
					lfactor++;
				}

			}

			lineIndex++;
		}
	}
}
