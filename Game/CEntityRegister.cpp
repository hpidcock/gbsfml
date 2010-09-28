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

void CEntityRegister::Init(void)
{
	m_iUniqueIndex = 0;
	ZeroMemory(m_pEnts, sizeof(m_pEnts));
}

void CEntityRegister::Cleanup(void)
{
	for(int i = 0; i < MAX_ENTS; i++)
	{
		if(m_pEnts[i] != NULL)
		{
			delete m_pEnts[i];
			m_pEnts[i] = NULL;
		}
	}

	m_iUniqueIndex = 0;
}

CBaseEntity *CEntityRegister::CreateFromClassname(const char *classname)
{
	CBaseEntity *entity = Create(classname);

	if(entity == NULL)
		return NULL;

	for(int i = 0; i < MAX_ENTS; i++)
	{
		if(m_pEnts[i] == NULL)
		{
			m_pEnts[i] = entity;

			entity->SetIndex(i, m_iUniqueIndex++);

			return entity;
		}
	}
	
	assert(false);

	return NULL;
}

bool CEntityRegister::IsValid(CBaseEntity *entity, int index, int uniqueIndex)
{
	if(entity != NULL && index != -1 && index < MAX_ENTS)
	{
		CBaseEntity *stored = m_pEnts[index];

		if(stored != NULL && stored == entity)
		{
			int idx, uidx;
			entity->GetIndex(idx, uidx);

			if(idx == index && uniqueIndex == uidx)
			{
				return true;
			}
		}
	}

	return false;
}

void CEntityRegister::Destroy(CBaseEntity *entity, int index)
{
	if(m_pEnts[index] == entity)
	{
		delete entity;
		m_pEnts[index] = NULL;
		return;
	}

	assert(false);
}

std::vector<CEntityHandle> CEntityRegister::FindByClassName(const char *classname)
{
	std::vector<CEntityHandle> result;

	for(int i = 0; i < MAX_ENTS; i++)
	{
		if(m_pEnts[i] != NULL)
		{
			if(_strcmpi(classname, m_pEnts[i]->GetClassname()) == 0)
			{
				result.push_back(m_pEnts[i]);
			}
		}
	}

	return result;
}

std::vector<CEntityHandle> CEntityRegister::FindInCircle(const Vector &pos, float radius)
{
	std::vector<CEntityHandle> result;

	for(int i = 0; i < MAX_ENTS; i++)
	{
		if(m_pEnts[i] != NULL)
		{
			if(pos.Distance(m_pEnts[i]->GetPos()) <= radius)
			{
				result.push_back(m_pEnts[i]);
			}
		}
	}

	return result;
}
std::vector<CEntityHandle> CEntityRegister::FindInSquare(const Vector &min, const Vector &max)
{
	std::vector<CEntityHandle> result;

	for(int i = 0; i < MAX_ENTS; i++)
	{
		if(m_pEnts[i] != NULL)
		{
			const Vector &pos = m_pEnts[i]->GetPos();
			if(pos >= min && pos <= max)
			{
				result.push_back(m_pEnts[i]);
			}
		}
	}

	return result;
}

void CEntityRegister::ThinkAll(void)
{
	for(int i = 0; i < MAX_ENTS; i++)
	{
		CBaseEntity *ent = m_pEnts[i];
		if(ent != NULL)
		{
			ent->PreThink();
			ent->Think();
		}
	}
}

void CEntityRegister::DrawAll(void)
{
	for(int i = 0; i < MAX_ENTS; i++)
	{
		CBaseEntity *ent = m_pEnts[i];
		if(ent != NULL)
		{
			ent->Draw();
		}
	}
}