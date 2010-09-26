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