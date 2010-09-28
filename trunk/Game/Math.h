//////////////////////////////////////////////////////////////////////////////////////////////////
//	Copyright (c) 2010 Harry Pidcock
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Vector.h"
#include "Color.h"

#ifndef __MATH_H__
#define __MATH_H__

template<typename T>
inline T Min(T a, T b)
{
	return a < b ? a : b;
}

template<typename T>
inline T Max(T a, T b)
{
	return a > b ? a : b;
}

template<typename T>
inline T Wrap(T x, T min, T max)
{
	return min + ((x - min) % (max - min + (T)1));
}

template<typename T>
inline T Clamp(T x, T min, T max)
{
	if(x < min)
		return min;

	if(x > max)
		return max;

	return x;
}

template<typename T> 
inline T Lerp(T a, T b, float frac)
{
	return a + (b - a) * frac;
}

inline Color Lerp(Color a, Color b, float frac)
{
	Color ret;

	ret.r = Lerp(a.r, b.r, frac);
	ret.g = Lerp(a.g, b.g, frac);
	ret.b = Lerp(a.b, b.b, frac);
	ret.a = Lerp(a.a, b.a, frac);

	return ret;
}

#endif // __MATH_H__