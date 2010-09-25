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

#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector
{
public:
	float x, y;

	Vector(void) : x(0), y(0)
	{
	};

	Vector(float x, float y) : x(x), y(y)
	{
	};

	Vector(const Vector &other) : x(other.x), y(other.y)
	{
	};

	Vector(const sf::Vector2f &other) : x(other.x), y(other.y)
	{
	};

	Vector(const sf::Vector2i &other) : x((float)other.x), y((float)other.y)
	{
	};

	Vector(const b2Vec2 &other) : x(other.x), y(other.y)
	{
	};

	inline operator sf::Vector2f(void) const
	{
		return sf::Vector2f(x, y);
	};

	inline operator sf::Vector2i(void) const
	{
		return sf::Vector2i((int)x, (int)y);
	};

	inline operator b2Vec2(void) const
	{
		return b2Vec2(x, y);
	};

	inline Vector operator-(const Vector &other) const
	{
		return Vector(x - other.x, y - other.y);
	};

	inline Vector operator+(const Vector &other) const
	{
		return Vector(x + other.x, y + other.y);
	};

	inline Vector operator*(const Vector &other) const
	{
		return Vector(x * other.x, y * other.y);
	};

	inline Vector operator/(const Vector &other) const
	{
		return Vector(x / other.x, y / other.y);
	};

	inline Vector operator*(const float other) const
	{
		return Vector(x * other, y * other);
	};
	
	inline Vector operator/(const float other) const
	{
		return Vector(x / other, y / other);
	};
	
	inline Vector &operator-=(const Vector &other)
	{
		x -= other.x;
		y -= other.y;
		return (*this);
	};

	inline Vector &operator+=(const Vector &other)
	{
		x += other.x;
		y += other.y;
		return (*this);
	};

	inline Vector &operator*=(const Vector &other)
	{
		x *= other.x;
		y *= other.y;
		return (*this);
	};

	inline Vector &operator/=(const Vector &other)
	{
		x /= other.x;
		y /= other.y;
		return (*this);
	};

	inline Vector &operator*=(const float other)
	{
		x *= other;
		y *= other;
		return (*this);
	};

	inline Vector &operator/=(const float other)
	{
		x /= other;
		y /= other;
		return (*this);
	};

	inline float Length(void) const
	{
		return sqrtf(x * x + y * y);
	};

	inline float Distance(const Vector &other) const
	{
		return (other - (*this)).Length();
	};

	inline float DotProduct(const Vector &other) const
	{
		return x * other.x + y * other.y;
	};

	inline float AngleBetween(const Vector &other) const
	{
		return acosf(DotProduct(other)/(Length() * other.Length()));
	};

	inline Vector Normalise(void) const
	{
		return (*this) / Length();
	};
	
	inline Vector Invert(void) const
	{
		return (*this) * Vector(-1.0f, -1.0f);
	};
};

inline Vector operator*(const float fl, const Vector &vec)
{
	return Vector(vec.x * fl, vec.y * fl);
}

inline std::ostream &operator<<(std::ostream &stream, const Vector &vec)
{
	stream << "(" << vec.x << ", " << vec.y << ")";
	return stream;
}

#endif // __VECTOR_H__