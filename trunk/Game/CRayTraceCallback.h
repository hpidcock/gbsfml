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

#ifndef __CRAYTRACECALLBACK_H__
#define __CRAYTRACECALLBACK_H__

struct TraceResult
{
	TraceResult()
	{
		entity = NULL;
		fraction = -1.0f;
	};

	CBaseEntity *entity;
	Vector pos;
	Vector normal;
	float fraction;
};

class CRayTraceCallback : public b2RayCastCallback
{
public:
	CRayTraceCallback(void)
	{
	};

	virtual float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction)
	{
		m_Result.entity = static_cast<CBaseEntity *>(fixture->GetBody()->GetUserData());
		m_Result.pos = point;
		m_Result.normal = normal;
		m_Result.fraction = fraction;

		return fraction;
	};

	const TraceResult &GetResult(void)
	{
		return m_Result;
	};

private:
	TraceResult m_Result;
};

#endif // __CRAYTRACECALLBACK_H__