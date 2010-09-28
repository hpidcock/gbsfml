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

#ifndef __CUTIL_H__
#define __CUTIL_H__

class CEngine;

class CUtil : public CSingleton<CUtil>
{
public:
	CUtil(void) : m_flCurrentTime(0.0f), m_flDeltaTime(0.0f)
	{
	};

	float CurTime(void)
	{
		return m_flCurrentTime;
	};

	float DeltaTime(void)
	{
		return m_flDeltaTime;
	};

protected:
	friend class CEngine;
	
	void UpdateTime(float delta)
	{
		m_flDeltaTime = delta;
		m_flCurrentTime += delta;
	};

	void Reset(void)
	{
		m_flDeltaTime = 0.0f;
		m_flCurrentTime = 0.0f;
	};

private:
	float m_flCurrentTime;
	float m_flDeltaTime;
};

#endif // __CUTIL_H__