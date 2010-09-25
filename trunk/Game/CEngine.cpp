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

#include "CEngine.h"
#include "CParticles.h"
#include "CSounds.h"
#include "CResources.h"
#include "CCamera.h"

#include <Gwen/Renderers/OpenGL.h>
#include <Gwen/Skins/TexturedBase.h>

#include <Gwen/Controls/WindowControl.h>
#include <Gwen/Controls/ProgressBar.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

void CEngine::Cleanup(void)
{
	delete m_pPhysicsWorld;

	delete m_pRenderWindow;

	delete m_pCanvas;
	delete m_pGwenSkin;
	delete m_pGwenRenderer;

	CSounds::Get().Cleanup();

	CResources::Get().Cleanup();
}

void CEngine::Init(void)
{
	m_pRenderWindow = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game Window", sf::Style::Close);
	
	m_pGwenRenderer = new Gwen::Renderer::OpenGL(wglGetCurrentDC(), GetActiveWindow());
	
	Gwen::Skin::TexturedBase *skin = new Gwen::Skin::TexturedBase();
	skin->SetRender(m_pGwenRenderer);
	skin->Init("DefaultSkin.png");
	m_pGwenSkin = skin;
	
	m_pCanvas = new Gwen::Controls::Canvas(m_pGwenSkin);
	m_pCanvas->SetSize(SCREEN_WIDTH + 1, SCREEN_HEIGHT + 1);

	CCamera::Get().SetPosition(Vector(0.0f, 0.0f));
	CCamera::Get().SetZoom(0.0f);

	m_pPhysicsWorld = new b2World(Vector(0.0f, -0.5f), true);
}

void CEngine::HandleEvent(sf::Event &e)
{
	switch(e.Type)
	{
	case sf::Event::Closed:
		m_pRenderWindow->Close();
		break;
	case sf::Event::MouseMoved:
		m_pCanvas->InputMouseMoved(e.MouseMove.X, e.MouseMove.Y, 0, 0);
		break;
	case sf::Event::MouseButtonPressed:
		m_pCanvas->InputMouseButton(e.MouseButton.Button, true);
		break;
	case sf::Event::MouseButtonReleased:
		m_pCanvas->InputMouseButton(e.MouseButton.Button, false);
		break;
	}	
}

void CEngine::DrawParticles(void)
{
	CParticles::Get().Draw();
}

void CEngine::DrawGUI(void)
{
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1.0, 0.0);
	
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	m_pCanvas->RenderCanvas();
}

void CEngine::Run(void)
{
	while(m_pRenderWindow->IsOpened())
	{
		CUtil::Get().UpdateTime(m_pRenderWindow->GetFrameTime());

		sf::Event e;
		while (m_pRenderWindow->GetEvent(e))
		{
			HandleEvent(e);
		}

		// Update Physics
		m_pPhysicsWorld->Step(CUtil::Get().DeltaTime(), 10, 10);

		m_pRenderWindow->Clear();

		// Get current camera translations.
		Vector cameraOffset;
		float cameraZoom;
		CCamera::Get().GetTranslations(cameraOffset, cameraZoom);

		sf::View v = m_pRenderWindow->GetDefaultView();
		v.Move(cameraOffset);
		v.Zoom(cameraZoom);
		m_pRenderWindow->SetView(v);

		DrawParticles();
		DrawGUI();

		m_pRenderWindow->Display();
	}
}