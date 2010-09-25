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

#ifndef __CREFCOUNTED_H__
#define __CREFCOUNTED_H__

class CRefCounted;

class IRefListener
{
public:
	virtual void OnFullRelease(CRefCounted *object) = 0;
};

class CRefCounted
{
public:
	CRefCounted(void) : m_iRefCount(1), m_pRefListener(NULL)
	{
	};

	virtual ~CRefCounted(void)
	{
		assert(m_iRefCount == 0);
	};

	virtual void Reference(void)
	{
		m_iRefCount++;
	};

	virtual void Release(void)
	{
		m_iRefCount--;

		if(m_iRefCount == 0)
		{
			if(m_pRefListener != NULL)
			{
				m_pRefListener->OnFullRelease(this);
			}
			delete this;
		}
	};

	virtual void SetReleaseListener(IRefListener *listener)
	{
		m_pRefListener = listener;
	};

private:
	unsigned int m_iRefCount;
	IRefListener *m_pRefListener;
};

#endif // __CREFCOUNTED_H__