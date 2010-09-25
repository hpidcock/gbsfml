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
#include "CSounds.h"

CSounds::CSounds(void)
{
	m_PlayingSounds.reserve(32);
}

void CSounds::Cleanup(void)
{
	StopAllSounds();
}

void CSounds::Think(void)
{
	int size = m_PlayingSounds.size();

	for(int i = 0; i < size; i++)
	{
		if(m_PlayingSounds[i]->GetStatus() != sf::Sound::Playing || 
			m_PlayingSounds[i]->GetPlayingOffset() >= m_PlayingSounds[i]->GetBuffer()->GetDuration())
		{
			if(i != size - 1)
			{
				sf::Sound *back = m_PlayingSounds[size - 1];
				m_PlayingSounds.pop_back();
				delete m_PlayingSounds[i];
				m_PlayingSounds[i] = back;
				i--;
			}
			else
			{
				delete m_PlayingSounds[i];
				m_PlayingSounds.pop_back();
			}
			size--;
		}
	}
}

void CSounds::PlaySound(const char *sndFile, bool loop, float pitch, float volume)
{
	sf::SoundBuffer *sndBuffer = CResources::Get().GetSound(sndFile);

	assert(sndBuffer != NULL);

	sf::Sound *snd = new sf::Sound(*sndBuffer, loop, pitch, volume);
	
	snd->Play();

	m_PlayingSounds.push_back(snd);
}

void CSounds::StopAllSounds(void)
{
	int size = m_PlayingSounds.size();

	for(int i = 0; i < size; i++)
	{
		delete m_PlayingSounds[i];
	}

	m_PlayingSounds.clear();
}