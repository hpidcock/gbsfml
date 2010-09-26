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
#include "CEntityRegister.h"

#include "CAnimatedSprite.h"

#include <Gwen/Renderers/OpenGL.h>
#include <Gwen/Skins/TexturedBase.h>

#include <Gwen/Controls/WindowControl.h>
#include <Gwen/Controls/ProgressBar.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

void CEngine::Cleanup(void)
{
	CEntityRegister::Get().Cleanup();

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
	// Setup the renderer.
	m_pRenderWindow = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game Window", sf::Style::Close);
	m_pRenderWindow->SetFramerateLimit(60);
	
	// Setup the GUI.
	m_pGwenRenderer = new Gwen::Renderer::OpenGL(wglGetCurrentDC(), GetActiveWindow());
	
	Gwen::Skin::TexturedBase *skin = new Gwen::Skin::TexturedBase();
	skin->SetRender(m_pGwenRenderer);
	skin->Init("DefaultSkin.png");
	m_pGwenSkin = skin;
	
	m_pCanvas = new Gwen::Controls::Canvas(m_pGwenSkin);
	m_pCanvas->SetSize(SCREEN_WIDTH + 1, SCREEN_HEIGHT + 1);

	// Set the default camera
	CCamera::Get().SetPosition(Vector(0.0f, 0.0f));
	CCamera::Get().SetZoom(0.0f);

	// Setup physics
	m_pPhysicsWorld = new b2World(Vector(0.0f, 256.0f), true);
	
	// Setup the entity system.
	CEntityRegister::Get().Init();
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
	// Clear only the depth so the gui is drawn ontop of the scene.
	glClear(GL_DEPTH_BUFFER_BIT);

	// Setup the view port.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1.0, 0.0);
	
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	m_pCanvas->RenderCanvas();
}

void CEngine::DrawEntities(void)
{
	CEntityRegister::Get().DrawAll();
}

void CEngine::UpdateCamera(void)
{
	// Get current camera translations.
	Vector cameraOffset;
	float cameraZoom;
	CCamera::Get().GetTranslations(cameraOffset, cameraZoom);

	m_View = sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	m_View.Move(cameraOffset);
	m_View.Zoom(cameraZoom);
	m_pRenderWindow->SetView(m_View);
}

void CEngine::UpdatePhysics(void)
{
	m_pPhysicsWorld->Step(1.0f / 60.0f, 100, 100);
	m_pPhysicsWorld->ClearForces();
}

void CEngine::UpdateEntities(void)
{
	CEntityRegister::Get().ThinkAll();
}

void CEngine::UpdateSounds(void)
{
	CSounds::Get().Think();
}

void CEngine::UpdateParticles(void)
{
	CParticles::Get().Think();
}

void CEngine::Run(void)
{
	for(int i = 0; i < 32; i++)
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

	while(m_pRenderWindow->IsOpened())
	{
		CUtil::Get().UpdateTime(m_pRenderWindow->GetFrameTime());

		sf::Event e;
		while (m_pRenderWindow->GetEvent(e))
		{
			HandleEvent(e);
		}
		
		UpdatePhysics();
		UpdateEntities();
		UpdateSounds();
		
		UpdateCamera();

		m_pRenderWindow->Clear();

		DrawEntities();
		DrawParticles();
		DrawGUI();

		m_pRenderWindow->Display();
	}
}