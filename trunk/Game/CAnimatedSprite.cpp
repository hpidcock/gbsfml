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

#include "CAnimatedSprite.h"

CAnimatedSprite::CAnimatedSprite(void) : 
	sf::Sprite(),
	m_iFrameRate(0),
	m_iNumRows(0),
	m_iNumColumns(0),
	m_iCurrentSequence(-1),
	m_flStartTime(0.0f)
{
}

CAnimatedSprite::CAnimatedSprite(const sf::Image& Img, const sf::Vector2f& Position, const sf::Vector2f& Scale, float Rotation, const sf::Color& Col) :
	sf::Sprite(Img, Position, Scale, Rotation, Col),
	m_iFrameRate(0),
	m_iNumRows(0),
	m_iNumColumns(0),
	m_iCurrentSequence(-1),
	m_flStartTime(0.0f)
{
}

void CAnimatedSprite::SetAnimationParams(const sf::Vector2i &frameSize, int framesPerSecond, int rows, int columns, bool rowMajor)
{
	m_iFrameRate = framesPerSecond;
	m_iNumRows = rows;
	m_iNumColumns = columns;
	m_bRowMajor = rowMajor;
	m_vFrameSize = frameSize;
}

void CAnimatedSprite::CreateSequence(const char *name, int startFrame, int frameCount)
{
	Sequence seq;
	seq.name = name;
	seq.startFrame = startFrame;
	seq.frameCount = frameCount;

	m_Sequences.push_back(seq);
}

void CAnimatedSprite::SetCurrentSequence(const char *name, bool restart)
{
	for(int i = 0; i < (int)m_Sequences.size(); i++)
	{
		if(m_Sequences[i].name == name)
		{
			m_iCurrentSequence = i;
		}
	}

	assert(m_iCurrentSequence != -1);

	if(restart)
	{
		m_flStartTime = 0;
	}
}

void CAnimatedSprite::Render(sf::RenderTarget &target) const
{
	if(m_iCurrentSequence == -1)
		return;

	const Sequence &seq = m_Sequences[m_iCurrentSequence];

	int frame = seq.startFrame + Wrap((int)floorf((CUtil::Get().CurTime() - m_flStartTime) * (float)m_iFrameRate), (int)0, (int)seq.frameCount - 1);
	int y = (int)floorf(frame / m_iNumColumns);
	int x = frame - (m_iNumColumns * y);

	sf::IntRect rect;
	rect.Left = x * m_vFrameSize.x;
	rect.Right = (x + 1) * m_vFrameSize.x;
	rect.Top = y * m_vFrameSize.y;
	rect.Bottom = (y + 1) * m_vFrameSize.y;

	// Unsafe, but must be done.
	CAnimatedSprite *self = const_cast<CAnimatedSprite *>(this);
	self->SetSubRect(rect);

	sf::Sprite::Render(target);
}