#pragma once
#include <vector>
#include <tuple>
#include "DrawUtils.h"
#include "PixelBufferDrawer.h"

namespace O3DCppEngine
{
	class DrawContext;

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

	template <class T, class... Types>
	struct Index<T, std::tuple<T, Types...>> {
		static const std::size_t value = 0;
	};

	template <class T, class U, class... Types>
	struct Index<T, std::tuple<U, Types...>> {
		static const std::size_t value = 1 + Index<T, std::tuple<Types...>>::value;
	};


	template<bool useZ, typename ... verticesComponents>
	class Poly_3_4_Rasterizer
	{
	protected:

		typedef std::tuple<verticesComponents...> verticeType;

		PixelBufferDrawer<useZ,false>& mPixelBufferDrawer;

		// for each line in buffer, list of starting/ending pos
		std::vector<std::vector<std::pair<unsigned int, verticeType>>>	mLimits;

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

			if (tuple_contains_type<RGBAColor, verticeType>::value)
			{
				const size_t i = Index<RGBAColor, verticeType>::value;
				RGBAColor lc = blendColor(std::get<i>(p1), std::get<i>(p2), lfactor >> 8);
				std::get<i>(result) = lc;
			}
			return result;
		}

	public:
		Poly_3_4_Rasterizer(PixelBufferDrawer<useZ, false>& buffer,DrawContext* c=nullptr) : mPixelBufferDrawer(buffer)
		{
			mLimits.resize(buffer.getPixelSize().y);
		}

		void	draw(const std::vector<verticeType>& vlist);
	};

	template<bool useZ, typename ... verticesComponents>
	void	Poly_3_4_Rasterizer<useZ, verticesComponents...>::draw(const std::vector<verticeType>& vlist)
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

		// compute limits for each segment
		for (size_t i = 0; i < vlist.size(); i++)
		{
			drawSegmentLimits(vlist[i], vlist[(i + 1) % vlist.size()]);
		}
		// then rasterize each horizontal line
		rasterizeLines();
	}

	template<bool useZ, typename ... verticesComponents>
	void	Poly_3_4_Rasterizer<useZ, verticesComponents...>::drawSegmentLimits(const verticeType& p1, const verticeType& p2)
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
		
		if ((fp[1-order].y < 0.0f)||(fp[order].y >= (float)pixSize.y)) // out of screen
			return;

		if (fp[order].y < 0.0f)
		{
			// TODO
			//cutSegment();
		}
		
		vect2Dui uip[2];
		uip[0].x = (unsigned int)fp[order].x;
		uip[0].y = (unsigned int)fp[order].y;
		uip[1].x = (unsigned int)fp[1-order].x;
		uip[1].y = (unsigned int)fp[1-order].y;

		int oneOnLenght = 0;
		if (uip[1].y != uip[0].y)
			oneOnLenght = 0xFFFF / (uip[1].y - uip[0].y);

		int dx = uip[1].x - uip[0].x;
		int lfactor = 0;

		unsigned int starty = uip[0].y;
		unsigned int endy = uip[1].y;

		if (starty == endy)
		{
			return;
		}

		for (unsigned int py = starty; py <= endy; py++)
		{
			int lerp = (lfactor * oneOnLenght);
			unsigned int px = uip[0].x+ ( (dx * lerp) >> 16);

			if (py == endy)
			{
				printf("");
			}

			verticeType	blended= Lerp(*vtp[order], *vtp[1-order], lerp);

			mLimits[py].push_back({px, blended });
			lfactor++;
		}
	}

	template<bool useZ, typename ... verticesComponents>
	void	Poly_3_4_Rasterizer<useZ, verticesComponents...>::rasterizeLines()
	{
		int lineIndex = 0;
		for (auto& l : mLimits)
		{
			if (l.size())
			{
				auto drawer = mPixelBufferDrawer.getLine(lineIndex);
				unsigned int indexOrder = 0;
				(l[0].first < l[1].first) ? indexOrder = 0:indexOrder = 1;

				std::pair<unsigned int, verticeType>& p1 = l[indexOrder];
				std::pair<unsigned int, verticeType>& p2 = l[1- indexOrder];
				
				verticeType& p1tuple = p1.second;
				verticeType& p2tuple = p2.second;

				unsigned int color=0xFF00FF00;
				float		 z = 0.0f;

				unsigned int oneOnLenght = 0xFFFF / (p2.first - p1.first + 1);
				unsigned int lfactor = 0;
				for (unsigned int px = p1.first; px <= p2.first; px++)
				{
					unsigned int lerp = (lfactor * oneOnLenght) >> 8;

					/*if (useZ && tuple_contains_type<vect3Df, verticeType>::value)
					{
						
					}
					else*/ if(tuple_contains_type<vect2Df, verticeType>::value)
					{
						
					}
					
					// color management
					if (tuple_contains_type<RGBAColor, verticeType>::value)
					{
						const size_t i=Index<RGBAColor, verticeType>::value;
						color = blendColor(std::get<i>(p1tuple), std::get<i>(p2tuple), lerp);
					}

					drawer.setPixel(px, color, z);
					lfactor++;
				}

			}
			lineIndex++;
		}
	}
}
