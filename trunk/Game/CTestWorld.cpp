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