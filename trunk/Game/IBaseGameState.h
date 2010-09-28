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

#ifndef __IBASEGAMESTATE_H__
#define __IBASEGAMESTATE_H__

class CBaseHandle;
class CKeyValues;

class IBaseGameState
{
public:
	virtual ~IBaseGameState(void) { };

	virtual void Initilise(void) = 0;

	virtual void Open(IBaseGameState *previous, const CKeyValues &keyValues) = 0;
	virtual void Close(IBaseGameState *next) = 0;

	virtual void PreThink(void) = 0;
	virtual void Think(void) = 0;
	virtual void PostThink(void) = 0;

	virtual void PreDraw(void) = 0;
	virtual Color GetBackgroundColor(void) = 0;
	virtual void DrawBackground(int plane) = 0; // 0 is directly behind the foreground.
	virtual void DrawForeground(void) = 0;
	virtual void PostDraw(void) = 0;

	virtual void OnCollide(CEntityHandle &a, CEntityHandle &b) = 0;

	virtual void OnKeyEvent(const sf::Event &e) = 0;
	virtual void OnMouseEvent(const sf::Event &e) = 0;
};

#endif // __IBASEGAMESTATE_H__