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

void CResources::Cleanup(void)
{
	// Textures
	std::map<std::string, sf::Image *>::iterator itor = m_TextureCache.begin();

	while(itor != m_TextureCache.end())
	{
		delete itor->second;
		itor++;
	}

	m_TextureCache.clear();

	// Sounds
	std::map<std::string, sf::SoundBuffer *>::iterator itor2 = m_SoundCache.begin();

	while(itor2 != m_SoundCache.end())
	{
		delete itor2->second;
		itor2++;
	}

	m_SoundCache.clear();
}

sf::Image *CResources::GetTexture(const char *fileName)
{
	sf::Image *ret = m_TextureCache[std::string(fileName)];

	if(ret != NULL)
		return ret;

	ret = new sf::Image();
	if(!ret->LoadFromFile(fileName))
	{
		delete ret;
		return NULL;
	}

	m_TextureCache[std::string(fileName)] = ret;

	return ret;
}

sf::SoundBuffer *CResources::GetSound(const char *fileName)
{
	sf::SoundBuffer *ret = m_SoundCache[std::string(fileName)];

	if(ret != NULL)
		return ret;

	ret = new sf::SoundBuffer();
	if(!ret->LoadFromFile(fileName))
	{
		delete ret;
		return NULL;
	}

	m_SoundCache[std::string(fileName)] = ret;

	return ret;
}