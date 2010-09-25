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

#ifndef __CPARTICLES_H__
#define __CPARTICLES_H__

struct Particle
{
	Particle()
	{
		m_Tex = NULL;
		m_flDeath = 0.0f;
		m_flBirth = 0.0f;
		m_flRotation = 0.0f;
		m_flRotationVel = 0.0f;
	}

	sf::Image *m_Tex;

	float m_flDeath;
	float m_flBirth;

	Vector m_vPos;
	Vector m_vVelocity;

	Color m_cStartColour;
	Color m_cEndColour;

	float m_flStartSize;
	float m_flEndSize;

	float m_flRotation;
	float m_flRotationVel;
};

class CParticles : public CSingleton<CParticles>
{
public:
	CParticles();

	void Think(void);
	void Draw(void);

	void AddParticle(Particle &particle);

private:
	std::vector<Particle> m_Particles;
};

#endif // __CPARTICLES_H__