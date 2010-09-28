#include "Core.h"

#include "CCamera.h"

void CCamera::Reset(void)
{
	m_vPosition = Vector(0, 0);
	m_flZoom = 1.0f;

	m_vLastPosition = Vector(0, 0);
	m_flLastZoom = 1.0f;
}

void CCamera::SetPosition(Vector &position)
{
	m_vPosition = position;
	m_vLastPosition = position;
}

void CCamera::SetZoom(float zoom)
{
	m_flZoom = zoom;
	m_flLastZoom = zoom;
}

void CCamera::Think(void)
{
	if(m_FollowEntity.IsValid())
	{
		m_flZoom = Clamp(256.0f / m_FollowEntity->GetVel().Length(), 0.7f, 1.0f);
		m_vPosition = m_FollowEntity->GetPos() - Vector(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
		
		m_vLastPosition = m_vPosition;

		m_flLastZoom = Lerp(m_flLastZoom, m_flZoom, 0.5f);
	}
}

void CCamera::GetTranslations(Vector &outPosition, float &outZoom)
{
	if(m_FollowEntity.IsValid())
	{
		outPosition = m_vLastPosition;
		outZoom = m_flLastZoom;
	}
	else
	{
		outPosition = m_vPosition;
		outZoom = m_flZoom;
	}
}

void CCamera::SetFollowEntity(const CEntityHandle &follow)
{
	m_FollowEntity = follow;
}

const CEntityHandle &CCamera::GetFollowEntity(void)
{
	return m_FollowEntity;
}