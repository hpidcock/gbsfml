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

#ifndef __CCOLLISIONCALLBACK_H__
#define __CCOLLISIONCALLBACK_H__

struct CollideEvent
{
	CEntityHandle a;
	CEntityHandle b;
};

class CCollisionCallback : public b2ContactListener
{
public:
	CCollisionCallback(void)
	{
		m_Collisions = &m_BufferA;
	};

	virtual void BeginContact(b2Contact *contact)
	{
		if(!contact->IsTouching())
			return;

		if(!contact->IsEnabled())
			return;

		CollideEvent e;
		e.a = static_cast<CBaseEntity *>(contact->GetFixtureA()->GetBody()->GetUserData());
		e.b = static_cast<CBaseEntity *>(contact->GetFixtureB()->GetBody()->GetUserData());
		m_Collisions->push_back(e);
	};

	std::vector<CollideEvent> *PopCollisions(void)
	{
		std::vector<CollideEvent> *ret = m_Collisions;

		m_Collisions = (m_Collisions == &m_BufferA) ? &m_BufferB : &m_BufferA;

		return ret;
	};

private:
	std::vector<CollideEvent> *m_Collisions;

	std::vector<CollideEvent> m_BufferA;
	std::vector<CollideEvent> m_BufferB;
};

#endif // __CCOLLISIONCALLBACK_H__