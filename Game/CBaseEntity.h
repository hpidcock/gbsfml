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

#ifndef __CBASEENTITY_H__
#define __CBASEENTITY_H__

enum EFFECTS
{
	EFFECT_NONE			= 0,
	EFFECT_BLUR			= (1 << 0),
	EFFECT_MOTIONBLUR	= (1 << 1),
	EFFECT_ADD			= (1 << 2),
	EFFECT_MULTIPLY		= (1 << 3)
};

class CEntityRegister;

class CBaseEntity
{
protected:
	friend class CEntityRegister;

	CBaseEntity(void);
	virtual ~CBaseEntity(void);

public:
	virtual void Initialise(void);
	virtual void Think(void);
	virtual void Draw(void);

	void PreThink(void);
	bool IsPhysical(void) const;
	void CreatePhysicsBody(bool dynamic = true);
	void DestroyPhysicsBody(void);
	b2Body *GetPhysicsBody(void) const;

	bool IsDrawable(void) const;
	sf::Drawable *GetDrawable(void) const;

	void SetClassname(const char *classname);
	const char *GetClassname(void) const;

	void SetIndex(int index, int uniqueIndex);
	void GetIndex(int &index, int &uniqueIndex) const;

	void SetPos(const Vector &pos);
	const Vector &GetPos(void) const;

	void SetVel(const Vector &vel);
	const Vector &GetVel(void) const;

	// Angle in degrees.
	void SetAngle(float ang);
	// Angle in degrees.
	float GetAngle(void) const;

	void SetColor(const Color &col);
	const Color &GetColor(void) const;

	void AddEffect(EFFECTS effect);
	void ClearEffects(void);
	void RemoveEffect(EFFECTS effect);
	bool IsEffectSet(EFFECTS effect);

protected:
	void SetPhysicsBody(b2Body *obj);
	void SetDrawable(sf::Drawable *obj);

private:
	int m_iIndex;
	int m_iUniqueIndex;
	const char *m_pClassName;

	Vector m_vBasePosition;
	Vector m_vBaseVelocity;
	float m_vBaseAngle;

	Color m_cDiffuseColour;

	sf::Drawable *m_pDrawableObject;
	b2Body *m_pPhysicsObject;

	int m_iEffectFlags;
};

class CEntityHandle
{
public:
	CEntityHandle(void) : m_pEntity(NULL), m_iIndex(-1), m_iUniqueIndex(-1)
	{
	};

	CEntityHandle(CBaseEntity *entity)
	{
		m_pEntity = entity;
		entity->GetIndex(m_iIndex, m_iUniqueIndex);
	};

	inline bool IsValid(void) const
	{
		if(m_pEntity == NULL || m_iIndex == -1 || m_iUniqueIndex == -1)
			return false;

		return true;
	};

	inline CBaseEntity *operator->(void) const
	{
		return m_pEntity;
	};

	inline CBaseEntity *Get(void) const
	{
		return m_pEntity;
	};

	inline operator CBaseEntity *(void) const
	{
		return m_pEntity;
	};

	inline operator bool(void) const
	{
		return IsValid();
	};

	inline bool operator==(const CEntityHandle &other) const
	{
		return m_pEntity == other.m_pEntity && m_pEntity != NULL && m_iIndex != -1 && m_iUniqueIndex != -1;
	};

	inline bool operator==(const CBaseEntity *other) const
	{
		return m_pEntity == other && m_pEntity != NULL && m_iIndex != -1 && m_iUniqueIndex != -1;
	};

private:
	int m_iIndex;
	int m_iUniqueIndex;
	CBaseEntity *m_pEntity;
};

#endif // __CBASEENTITY_H__