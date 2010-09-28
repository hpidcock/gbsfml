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

class CTestEntity : public CBaseEntity
{
public:
	virtual ~CTestEntity(void)
	{
	};

	virtual void Initialise(void)
	{
		CAnimatedSprite *a = new CAnimatedSprite(*CResources::Get().GetTexture("test.png"));
		a->SetAnimationParams(Vector(32, 32), 8, 4, 4);
		a->CreateSequence("test", 0, 4);
		a->SetCurrentSequence("test", true);

		SetBounds(Vector(32, 32));

		// Once I set it here, the entity will delete it later.
		SetDrawable(a);

		CreatePhysicsBody();

		b2Body *body = GetPhysicsBody();

		b2PolygonShape box;
		box.SetAsBox(32/2, 32/2);

		b2FixtureDef def;
		def.shape = &box;
		def.density = 20.0f;
		def.restitution = 0.1f;

		body->CreateFixture(&def);
	};

	virtual void Think(void)
	{
		CBaseEntity::Think();
	};

	virtual void Draw(void)
	{
		CBaseEntity::Draw();
	};

private:
};

RegisterEntity(CTestEntity);