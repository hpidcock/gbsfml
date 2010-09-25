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

#include "CParticles.h"

CParticles::CParticles(void)
{
	m_Particles.reserve(1024);
}

void CParticles::Think(void)
{
	int size = m_Particles.size();
	float curTime = CUtil::Get().CurTime();
	float deltaTime = CUtil::Get().DeltaTime();

	for(int i = 0; i < size; i++)
	{
		Particle &part = m_Particles[i];

		// Remove if life is over.
		if(part.m_flDeath <= curTime)
		{
			if(i != size - 1)
			{
				// Sigh...
				// Atleast its fast and works.
				memcpy(&m_Particles[i], &m_Particles[size - 1], sizeof(Particle));
				m_Particles.pop_back();
				i--;
			}
			else
			{
				m_Particles.pop_back();
			}
			size--;
		}
		else
		{
			part.m_flRotation += part.m_flRotationVel * deltaTime;
			part.m_vPos += part.m_vVelocity * deltaTime;
		}
	}
}

void CParticles::Draw(void)
{
	int size = m_Particles.size();
	float curTime = CUtil::Get().CurTime();
	float deltaTime = CUtil::Get().DeltaTime();
	sf::RenderWindow &window = CEngine::Get().GetRenderWindow();

	sf::Sprite sprite;
	sprite.SetBlendMode(sf::Blend::Add);

	for(int i = 0; i < size; i++)
	{
		Particle &part = m_Particles[i];

		float lifeFrac = (curTime - part.m_flBirth) / (part.m_flDeath - part.m_flBirth);

		assert(part.m_Tex != NULL);

		sprite.SetImage(*part.m_Tex);
		sprite.SetPosition(part.m_vPos);
		sprite.SetRotation(part.m_flRotation);
		sprite.SetColor(Lerp(part.m_cStartColour, part.m_cEndColour, lifeFrac));

		float scale = Lerp(part.m_flStartSize, part.m_flEndSize, lifeFrac);
		sprite.SetScale(scale, scale);
		sprite.SetCenter(-scale/2, -scale/2);
		
		window.Draw(sprite);
	}
}

void CParticles::AddParticle(Particle &particle)
{
	m_Particles.push_back(particle);
}