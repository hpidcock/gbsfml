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

#include "Core.h"

#include "CResources.h"
#include "CAnimatedSprite.h"

class CTestWorld : public CBaseEntity
{
public:
	virtual ~CTestWorld(void)
	{
	};

	virtual void Initialise(void)
	{
		sf::Shape *rect = new sf::Shape();
		*rect = sf::Shape::Rectangle(0, 0, 1000, 32, Color(255, 32, 32, 255), 1, Color(12, 12, 12, 255));

		SetBounds(Vector(1000, 32));

		// Once I set it here, the entity will delete it later.
		SetDrawable(rect);

		CreatePhysicsBody(false);

		b2Body *body = GetPhysicsBody();

		b2PolygonShape box;
		box.SetAsBox(1000/2, 32/2);

		b2FixtureDef def;
		def.shape = &box;

		body->CreateFixture(&def);
	};

	virtual void Think(void)
	{
	};

	virtual void Draw(void)
	{
		CBaseEntity::Draw();
	};

private:
};

RegisterEntity(CTestWorld);