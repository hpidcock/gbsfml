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

#include "CBaseEntity.h"
#include "CEntityRegister.h"

CBaseEntity::CBaseEntity(void) :
	m_iIndex(-1),
	m_pClassName("CBaseEntity"),
	m_vBounds(0, 0),
	m_vBasePosition(0, 0),
	m_vBaseVelocity(0, 0),
	m_vBaseAngle(0),
	m_cDiffuseColour(255, 255, 255, 255),
	m_pDrawableObject(NULL),
	m_pPhysicsObject(NULL),
	m_iEffectFlags(EFFECT_NONE)
{
}

CBaseEntity::~CBaseEntity(void)
{
	if(m_pDrawableObject)
	{
		delete m_pDrawableObject;
		m_pDrawableObject = NULL;
	}

	if(m_pPhysicsObject)
	{
		DestroyPhysicsBody();
	}
}

void CBaseEntity::Initialise(void)
{
}

void CBaseEntity::Think(void)
{
}

void CBaseEntity::Draw(void)
{
	sf::RenderWindow &window = CEngine::Get().GetRenderWindow();

	Vector worldPos = GetPos();
	Vector maxBounds = GetBounds();
	maxBounds = Vector(Max(maxBounds.x, maxBounds.y),
						Max(maxBounds.x, maxBounds.y));

	Vector objectTopLeft = worldPos - maxBounds / 2;
	Vector objectBottomRight = worldPos + maxBounds / 2;
	Vector screenTopLeft = window.ConvertCoords(0, 0);
	Vector screenBottomRight = window.ConvertCoords(window.GetWidth(), window.GetHeight());

	sf::IntRect object(objectTopLeft.x, objectTopLeft.y, objectBottomRight.x, objectBottomRight.y);
	sf::IntRect screen(screenTopLeft.x, screenTopLeft.y, screenBottomRight.x, screenBottomRight.y);

	if(!object.Intersects(screen))
		return;

	if(IsDrawable())
	{
		m_pDrawableObject->SetPosition(m_vBasePosition);
		m_pDrawableObject->SetRotation(m_vBaseAngle);
		m_pDrawableObject->SetColor(m_cDiffuseColour);
		m_pDrawableObject->SetCenter(GetBounds() / 2);
		
		if(IsEffectSet(EFFECT_ADD))
		{
			m_pDrawableObject->SetBlendMode(sf::Blend::Add);
		}		
		else if(IsEffectSet(EFFECT_MULTIPLY))
		{
			m_pDrawableObject->SetBlendMode(sf::Blend::Multiply);
		}
		else
		{
			m_pDrawableObject->SetBlendMode(sf::Blend::Alpha);
		}

		if(IsEffectSet(EFFECT_BLUR))
		{
			Color diffuse = m_cDiffuseColour;
			diffuse.a = 255 / 10;
			m_pDrawableObject->SetColor(diffuse);

			for(int x = -2; x <= 2; x++)
			{
				m_pDrawableObject->SetPosition(m_vBasePosition + Vector(x, 0));
				window.Draw(*m_pDrawableObject);
			}

			for(int y = -2; y <= 2; y++)
			{
				m_pDrawableObject->SetPosition(m_vBasePosition + Vector(0, y));
				window.Draw(*m_pDrawableObject);
			}
		}
		else if(IsEffectSet(EFFECT_MOTIONBLUR) && m_vBaseVelocity.Length() > 32)
		{
			Vector direction = m_vBaseVelocity.Normalise();
			Vector start = m_vBasePosition + (m_vBaseVelocity.Invert() * 0.05f);
			int count = Clamp((int)(m_vBaseVelocity.Length() / 32), 0, 32);
			float incr = (m_vBaseVelocity * 0.05f).Length() / count;

			for(int i = 0; i <= count; i++)
			{
				m_pDrawableObject->SetPosition(start + direction * incr * i);

				Color diffuse = m_cDiffuseColour;
				diffuse.a = ((float)(i*i) / (float)(count*count)) * 255;
				m_pDrawableObject->SetColor(diffuse);

				window.Draw(*m_pDrawableObject);
			}
		}
		else
		{
			window.Draw(*m_pDrawableObject);
		}
	}
}

void CBaseEntity::OnCollide(CEntityHandle &other)
{
}

void CBaseEntity::PreThink(void)
{
	if(IsPhysical())
	{
		const b2Transform &t = m_pPhysicsObject->GetTransform();

		m_vBasePosition = t.position;
		m_vBaseAngle = -(m_pPhysicsObject->GetAngle() / 3.14159) * 180;
		
		m_vBaseVelocity = m_pPhysicsObject->GetLinearVelocity();
	}
}

bool CBaseEntity::IsPhysical(void) const
{
	return m_pPhysicsObject != NULL;
}

void CBaseEntity::CreatePhysicsBody(bool dynamic)
{
	assert(m_pPhysicsObject == NULL);

	b2World *world = CEngine::Get().GetPhysicsWorld();

	b2BodyDef def;
	def.type = dynamic ? b2_dynamicBody : b2_staticBody;
	def.allowSleep = true;
	def.fixedRotation = !dynamic;
	def.userData = static_cast<void *>(this);

	m_pPhysicsObject = world->CreateBody(&def);
}

void CBaseEntity::DestroyPhysicsBody(void)
{
	if(m_pPhysicsObject)
	{
		b2World *world = CEngine::Get().GetPhysicsWorld();
		world->DestroyBody(m_pPhysicsObject);

		m_pPhysicsObject = NULL;
	}
}

b2Body *CBaseEntity::GetPhysicsBody(void) const
{
	return m_pPhysicsObject;
}

bool CBaseEntity::IsDrawable(void) const
{
	return m_pDrawableObject != NULL;
}

sf::Drawable *CBaseEntity::GetDrawable(void) const
{
	return m_pDrawableObject;
}

void CBaseEntity::SetClassname(const char *classname)
{
	if(classname == NULL)
		m_pClassName = "CBaseEntity";
	else
		m_pClassName = classname;
}

const char *CBaseEntity::GetClassname(void) const
{
	return m_pClassName;
}

void CBaseEntity::SetIndex(int index, int uniqueIndex)
{
	m_iIndex = index;
	m_iUniqueIndex = uniqueIndex;
}

void CBaseEntity::GetIndex(int &index, int &uniqueIndex) const
{
	index = m_iIndex;
	uniqueIndex = m_iUniqueIndex;
}

void CBaseEntity::SetPos(const Vector &pos)
{
	m_vBasePosition = pos;
	if(IsPhysical())
	{
		m_pPhysicsObject->SetTransform(m_vBasePosition, (m_vBaseAngle / 180) * 3.14159);
	}
}

const Vector &CBaseEntity::GetPos(void) const
{
	return m_vBasePosition;
}

void CBaseEntity::SetVel(const Vector &vel)
{
	m_vBaseVelocity = vel;
	if(IsPhysical())
	{
		m_pPhysicsObject->SetLinearVelocity(m_vBaseVelocity);
	}
}

const Vector &CBaseEntity::GetVel(void) const
{
	return m_vBaseVelocity;
}

// Angle in degrees.
void CBaseEntity::SetAngle(float ang)
{
	m_vBaseAngle = ang;
	if(IsPhysical())
	{
		m_pPhysicsObject->SetTransform(m_vBasePosition, (m_vBaseAngle / 180) * 3.14159);
	}
}

// Angle in degrees.
float CBaseEntity::GetAngle(void) const
{
	return m_vBaseAngle;
}

void CBaseEntity::SetColor(const Color &col)
{
	m_cDiffuseColour = col;
}

const Color &CBaseEntity::GetColor(void) const
{
	return m_cDiffuseColour;
}

void CBaseEntity::SetBounds(const Vector &bounds)
{
	m_vBounds = bounds;
}

const Vector &CBaseEntity::GetBounds(void) const
{
	return m_vBounds;
}

void CBaseEntity::SetPhysicsBody(b2Body *obj)
{
	m_pPhysicsObject = obj;
}

void CBaseEntity::SetDrawable(sf::Drawable *obj)
{
	m_pDrawableObject = obj;
}

void CBaseEntity::AddEffect(EFFECTS effect)
{
	m_iEffectFlags |= effect;
}

void CBaseEntity::ClearEffects(void)
{
	m_iEffectFlags = EFFECT_NONE;
}

void CBaseEntity::RemoveEffect(EFFECTS effect)
{
	m_iEffectFlags &= ~effect;
}

bool CBaseEntity::IsEffectSet(EFFECTS effect)
{
	return (m_iEffectFlags & effect) != 0;
}

///////////////////////////////////////////////
// CEntityHandle
///////////////////////////////////////////////

CEntityHandle::CEntityHandle(void) : m_pEntity(NULL), m_iIndex(-1), m_iUniqueIndex(-1)
{
};

CEntityHandle::CEntityHandle(CBaseEntity *entity)
{
	m_pEntity = entity;
	entity->GetIndex(m_iIndex, m_iUniqueIndex);
};

bool CEntityHandle::IsValid(void) const
{
	if(m_pEntity == NULL || m_iIndex == -1 || m_iUniqueIndex == -1)
		return false;

	return CEntityRegister::Get().IsValid(m_pEntity, m_iIndex, m_iUniqueIndex);
};

CBaseEntity *CEntityHandle::operator->(void) const
{
	return m_pEntity;
};

CBaseEntity *CEntityHandle::Get(void) const
{
	return m_pEntity;
};

CEntityHandle::operator CBaseEntity *(void) const
{
	return m_pEntity;
};

CEntityHandle::operator bool(void) const
{
	return IsValid();
};

bool CEntityHandle::operator==(const CEntityHandle &other) const
{
	return m_pEntity == other.m_pEntity && m_pEntity != NULL && m_iIndex != -1 && m_iUniqueIndex != -1;
};

bool CEntityHandle::operator==(const CBaseEntity *other) const
{
	return m_pEntity == other && m_pEntity != NULL && m_iIndex != -1 && m_iUniqueIndex != -1;
};