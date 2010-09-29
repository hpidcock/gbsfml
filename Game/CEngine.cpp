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

	std::map<std::string, IBaseGameState *>::iterator end = m_GameStates.end();
	for(std::map<std::string, IBaseGameState *>::iterator i = m_GameStates.begin(); i != end; ++i)
	{
		delete (*i).second;
	}
	m_GameStates.clear();
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
	CCamera::Get().SetZoom(1.0f);

	// Setup physics
	m_pPhysicsWorld = new b2World(Vector(0.0f, 256.0f), true);
	m_pPhysicsWorld->SetContactListener(&m_CollisionCallbacks);

	// Setup the entity system.
	CEntityRegister::Get().Init();

	// Create all the game states.
	std::vector<std::string> stateNames = CGameStateRegister::Get().GetNames();
	std::vector<std::string>::iterator end = stateNames.end();
	for(std::vector<std::string>::iterator i = stateNames.begin(); i != end; ++i)
	{
		std::string name = (*i);

		IBaseGameState *state = CGameStateRegister::Get().Create(name.c_str());
		state->Initilise();

		m_GameStates[name] = state;
	}

	m_pCurrentState = NULL;
}

IBaseGameState *CEngine::GetGameState(void)
{
	return m_pCurrentState;
}

// THIS CAN ONLY BE CALLED IN PRE THINK
IBaseGameState *CEngine::ChangeState(const char *name, const CKeyValues &values)
{
	std::string classname = name;
	std::transform(classname.begin(), classname.end(), classname.begin(), toupper);

	IBaseGameState *nextState = m_GameStates[classname];

	assert(nextState != NULL);

	if(m_pCurrentState != NULL)
		m_pCurrentState->Close(nextState);

	IBaseGameState *lastState = m_pCurrentState;
	m_pCurrentState = nextState;

	CEntityRegister::Get().Cleanup();
	CCamera::Get().Reset();
	CSounds::Get().StopAllSounds();
	CUtil::Get().Reset();

	m_pCanvas->RemoveAllChildren();

	m_pCurrentState->Open(lastState, values);

	return m_pCurrentState;
}

void CEngine::HandleEvent(sf::Event &e)
{
	switch(e.Type)
	{
	case sf::Event::Closed:
		m_pRenderWindow->Close();
		break;
	case sf::Event::KeyPressed:
		m_pCanvas->InputKey(e.Key.Code, true);
		m_pCurrentState->OnKeyEvent(e);
		break;
	case sf::Event::KeyReleased:
		m_pCanvas->InputKey(e.Key.Code, false);
		m_pCurrentState->OnKeyEvent(e);
		break;
	case sf::Event::MouseWheelMoved:
		m_pCanvas->InputMouseWheel(e.MouseWheel.Delta);
		m_pCurrentState->OnMouseEvent(e);
		break;
	case sf::Event::MouseMoved:
		m_pCanvas->InputMouseMoved(e.MouseMove.X, e.MouseMove.Y, 0, 0);
		m_pCurrentState->OnMouseEvent(e);
		break;
	case sf::Event::MouseButtonPressed:
		m_pCanvas->InputMouseButton(e.MouseButton.Button, true);
		m_pCurrentState->OnMouseEvent(e);
		break;
	case sf::Event::MouseEntered:
	case sf::Event::MouseLeft:
		m_pCanvas->InputMouseButton(0, false);
		m_pCanvas->InputMouseButton(1, false);
		break;
	case sf::Event::MouseButtonReleased:
		m_pCanvas->InputMouseButton(e.MouseButton.Button, false);
		m_pCurrentState->OnMouseEvent(e);
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
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_pCanvas->RenderCanvas();
}

void CEngine::DrawEntities(void)
{
	CEntityRegister::Get().DrawAll();
}

void CEngine::UpdateCamera(void)
{
	CCamera::Get().Think();

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
	m_pPhysicsWorld->Step(1.0f / 60.0f, 10, 100);
	m_pPhysicsWorld->ClearForces();

	std::vector<CollideEvent> *callbacks = m_CollisionCallbacks.PopCollisions();

	std::vector<CollideEvent>::iterator end = callbacks->end();
	for(std::vector<CollideEvent>::iterator i = callbacks->begin(); i != end; ++i)
	{
		CollideEvent &collision = (*i);

		if(collision.a.IsValid())
		{
			collision.a->OnCollide(collision.b);
		}

		if(collision.b.IsValid())
		{
			collision.b->OnCollide(collision.a);
		}

		m_pCurrentState->OnCollide(collision.a, collision.b);
	}
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
	while(m_pRenderWindow->IsOpened())
	{
		CUtil::Get().UpdateTime(m_pRenderWindow->GetFrameTime());

		sf::Event e;
		while (m_pRenderWindow->GetEvent(e))
		{
			HandleEvent(e);
		}

		assert(m_pCurrentState != NULL);

		m_pCurrentState->PreThink();
		UpdatePhysics();
		m_pCurrentState->Think();
		UpdateEntities();
		UpdateSounds();
		UpdateCamera();
		m_pCurrentState->PostThink();

		m_pRenderWindow->Clear(m_pCurrentState->GetBackgroundColor());

		m_pCurrentState->PreDraw();

		Vector cameraPos;
		float cameraZoom;
		CCamera::Get().GetTranslations(cameraPos, cameraZoom);
		for(int i = 5; i >= 0; i--)
		{
			sf::View view = sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
			view.Move(cameraPos);
			view.Zoom(cameraZoom - (i * 0.05));
			m_pRenderWindow->SetView(view);

			m_pCurrentState->DrawBackground(i);
		}
		m_pRenderWindow->SetView(m_View);

		m_pCurrentState->DrawForeground();
		DrawEntities();
		DrawParticles();
		m_pCurrentState->PostDraw();

		DrawGUI();

		m_pRenderWindow->Display();
	}
}

TraceResult CEngine::RayTrace(Vector start, Vector end, CBaseEntity *filter)
{
	CRayTraceCallback callback(filter);

	m_pPhysicsWorld->RayCast(&callback, start, end);

	return callback.GetResult();
}

sf::RenderWindow &CEngine::GetRenderWindow(void)
{
	return *m_pRenderWindow;
}

b2World *CEngine::GetPhysicsWorld(void)
{
	return m_pPhysicsWorld;
}

Gwen::Controls::Canvas *CEngine::GetCanvas(void)
{
	return m_pCanvas;
}