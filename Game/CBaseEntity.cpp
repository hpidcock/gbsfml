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

CBaseEntity::CBaseEntity(void) :
	m_iIndex(-1),
	m_pClassName("CBaseEntity"),
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
	if(IsDrawable())
	{
		m_pDrawableObject->SetPosition(m_vBasePosition);
		m_pDrawableObject->SetRotation(m_vBaseAngle);
		m_pDrawableObject->SetColor(m_cDiffuseColour);
		
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

		sf::RenderWindow &window = CEngine::Get().GetRenderWindow();

		if(IsEffectSet(EFFECT_BLUR))
		{
			Color diffuse = m_cDiffuseColour;
			diffuse.a = 255 / 32;
			m_pDrawableObject->SetColor(diffuse);

			for(int x = -8; x <= 8; x++)
			{
				m_pDrawableObject->SetPosition(m_vBasePosition + Vector(x, 0));
				window.Draw(*m_pDrawableObject);
			}

			for(int y = -8; y <= 8; y++)
			{
				m_pDrawableObject->SetPosition(m_vBasePosition + Vector(0, y));
				window.Draw(*m_pDrawableObject);
			}
		}
		else if(IsEffectSet(EFFECT_MOTIONBLUR) && m_vBaseVelocity.Length() > 32.0f)
		{
			Vector direction = m_vBaseVelocity.Normalise();
			Vector start = m_vBasePosition + (m_vBaseVelocity.Invert() * 0.25f);
			float incr = (m_vBaseVelocity * 0.25f).Length() / 32.0f;

			for(int i = 0; i <= 32; i++)
			{
				m_pDrawableObject->SetPosition(start + direction * incr * i);

				Color diffuse = m_cDiffuseColour;
				diffuse.a = (logf((float)i / 32.0f) + 1.0f) * 255;
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

void CBaseEntity::PreThink(void)
{
	if(IsPhysical())
	{
		const b2Transform &t = m_pPhysicsObject->GetTransform();

		m_vBasePosition = t.position;
		m_vBaseAngle = (t.GetAngle() / 3.14159) * 180;

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

	m_pPhysicsObject = world->CreateBody(&def);
	m_pPhysicsObject->SetUserData(static_cast<void *>(this));
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