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

#ifndef __CANIMATEDSPRITE_H__
#define __CANIMATEDSPRITE_H__

class CAnimatedSprite : public sf::Sprite
{
public:
	CAnimatedSprite(void);
	CAnimatedSprite(const sf::Image& Img,
					const sf::Vector2f& Position = sf::Vector2f(0, 0),
					const sf::Vector2f& Scale = sf::Vector2f(1, 1),
					float Rotation = 0.0f,
					const sf::Color& Col = sf::Color(255, 255, 255, 255));

	void SetAnimationParams(const sf::Vector2i &frameSize, int framesPerSecond, int rows, int columns, bool rowMajor = true);
	
	void CreateSequence(const char *name, int startFrame, int frameCount);
	void SetCurrentSequence(const char *name, bool restart = false);

protected:
	virtual void Render(sf::RenderTarget &target) const;

private:
	struct Sequence
	{
		std::string name;
		int startFrame;
		int frameCount;
	};

	std::vector<Sequence> m_Sequences;

	int m_iFrameRate;
	int m_iNumRows;
	int m_iNumColumns;
	bool m_bRowMajor;
	sf::Vector2i m_vFrameSize;
	
	int m_iCurrentSequence;
	float m_flStartTime;
};

#endif // __CANIMATEDSPRITE_H__