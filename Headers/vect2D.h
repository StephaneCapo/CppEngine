#pragma once
#include <iostream>

template<typename T>
class vect2D
{
protected:

public:

	vect2D(T _x, T _y) : x(_x), y(_y)
	{
		
	}

	vect2D() : x(0), y(0)
	{
		
	}

	vect2D(const vect2D& other) : x(other.x), y(other.y)
	{
	
	}

	~vect2D()
	{
		
	}

	vect2D& operator = (const vect2D& a)
	{
		x = a.x;
		y = a.y;
		return *this;
	}

	vect2D& operator += (const vect2D& a);
	vect2D& operator -= (const vect2D& a);
	vect2D& operator *= (T nbr);
	vect2D& operator /= (T nbr);

	vect2D operator +(const vect2D& a) const;

	vect2D operator *(T nbr) const
	{
		vect2D<T> tmp(x, y);
		tmp *= nbr;
		return tmp;
	}

	// operateur pour récupérer une des composantes du vecteur
	T& operator [](size_t index);

	// swap values with other vector
	void	swap(vect2D& other)
	{
		T swp = x;
		x = other.x;
		other.x = swp;
		swp = y;
		y = other.y;
		other.y = swp;
	}

	union
	{
		struct
		{
			T	x, y;
		};

		T		elems[2];
	};

};


template<typename T>
vect2D<T>& vect2D<T>::operator += (const vect2D<T>& a)
{
	x += a.x;
	y += a.y;

	return *this;
}

template<typename T>
vect2D<T>& vect2D<T>::operator -= (const vect2D<T>& a)
{
	x -= a.x;
	y -= a.y;

	return *this;
}

template<typename T>
vect2D<T>& vect2D<T>::operator *= (T nbr)
{
	x *= nbr;
	y *= nbr;

	return *this;
}

template<typename T>
inline vect2D<T>& vect2D<T>::operator /= (T nbr)
{
	x /= nbr;
	y /= nbr;

	return *this;
}

template<typename T>
vect2D<T> vect2D<T>::operator +(const vect2D<T>& a) const
{
	vect2D<T> tmp(a.x + x, a.y + y);
	return tmp;
}

template<typename T>
T& vect2D<T>::operator [](size_t index)
{
	return elems[index];
}


typedef vect2D<float>				vect2Df;
typedef vect2D<unsigned int>		vect2Dui;

template<typename T>
inline bool operator==(const vect2D<T>& a, const vect2D<T>& b)
{
	return (a.x == b.x) && (a.y == b.y);
}
