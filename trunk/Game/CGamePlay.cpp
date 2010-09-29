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

#include "CCamera.h"

#include <Gwen/Controls/Button.h>

class CGamePlay : public IBaseGameState
{
public:
	CGamePlay(void)
	{
	};

	virtual ~CGamePlay(void)
	{
	};

	//////////////////////////////////////////////////////////////////////
	//	State Management
	//////////////////////////////////////////////////////////////////////
	virtual void Initilise(void)
	{
	};

	void OnButtonPressed(Gwen::Controls::Base *control)
	{
		CBaseEntity *ent = CEntityRegister::Get().CreateFromClassname("CTestEntity");
		ent->Initialise();
		ent->SetPos(Vector(128, 32));
		ent->SetAngle(10);
		ent->AddEffect(EFFECT_MOTIONBLUR);
		CCamera::Get().SetFollowEntity(ent);
	}

	virtual void Open(IBaseGameState *previous, const CKeyValues &keyValues)
	{
		for(int i = 0; i < 16; i++)
		{
			CBaseEntity *ent = CEntityRegister::Get().CreateFromClassname("CTestEntity");
			ent->Initialise();
			ent->SetPos(Vector(128, 2 * i));
			ent->SetAngle(i * 10);
		}

		CBaseEntity *ent2 = CEntityRegister::Get().CreateFromClassname("CTestWorld");
		ent2->Initialise();
		ent2->SetPos(Vector(0, 400));
		ent2->SetAngle(20);



		Gwen::Controls::Canvas *canvas = CEngine::Get().GetCanvas();

		Gwen::Controls::Button *button = new Gwen::Controls::Button(canvas);

		button->SetPos(32, 32);
		button->SetSize(128, 32);
		button->SetText("Spawn a Block");

		button->onDown.Add(this, &CGamePlay::OnButtonPressed);
	};

	virtual void Close(IBaseGameState *next)
	{
	};


	//////////////////////////////////////////////////////////////////////
	//	Thinking
	//////////////////////////////////////////////////////////////////////
	virtual void PreThink(void)
	{
	};

	virtual void Think(void)
	{
		CCamera::Get().SetPosition(Vector(0, 0));
	};

	virtual void PostThink(void)
	{
	};


	//////////////////////////////////////////////////////////////////////
	//	Drawing
	//////////////////////////////////////////////////////////////////////
	virtual void PreDraw(void)
	{
	};

	virtual Color GetBackgroundColor(void)
	{
		return Color(0, 127, 255, 255);
	};

	virtual void DrawBackground(int plane)
	{
		sf::Shape s = sf::Shape::Circle(128, 128, 32, Color(255, 255, plane * 32, 255), 16.0f);
		CEngine::Get().GetRenderWindow().Draw(s);
	};

	virtual void DrawForeground(void)
	{
	};

	virtual void PostDraw(void)
	{
	};


	//////////////////////////////////////////////////////////////////////
	//	Events
	//////////////////////////////////////////////////////////////////////
	virtual void OnCollide(CEntityHandle &a, CEntityHandle &b)
	{
	};

	virtual void OnKeyEvent(const sf::Event &e)
	{
		if(e.Key.Code == sf::Key::Space)
		{
			CBaseEntity *ent = CEntityRegister::Get().CreateFromClassname("CTestEntity");
			ent->Initialise();
			ent->SetPos(Vector(128, 32));
			ent->SetAngle(10);
			ent->AddEffect(EFFECT_MOTIONBLUR);
			CCamera::Get().SetFollowEntity(ent);
		}
	};

	virtual void OnMouseEvent(const sf::Event &e)
	{
	};

private:
};

RegisterGameState(CGamePlay);