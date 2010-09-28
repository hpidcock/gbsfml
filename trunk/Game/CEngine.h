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

#include "CRayTraceCallback.h"
#include "CCollisionCallback.h"

#ifndef __CENGINE_H__
#define __CENGINE_H__

class IBaseGameState;
class CBaseEntity;

class CEngine : public CSingleton<CEngine>
{
public:
	void Cleanup(void);
	void Init(void);
	void Run(void);

	TraceResult RayTrace(Vector start, Vector end, CBaseEntity *filter = NULL);

	sf::RenderWindow &GetRenderWindow(void);
	b2World *GetPhysicsWorld(void);

	IBaseGameState *GetGameState(void);

	// THIS CAN ONLY BE CALLED IN PRE THINK
	IBaseGameState *ChangeState(const char *name, const CKeyValues &values);

protected:
	void DrawParticles(void);
	void DrawGUI(void);
	void DrawEntities(void);

	void UpdateCamera(void);
	void UpdatePhysics(void);
	void UpdateEntities(void);
	void UpdateSounds(void);
	void UpdateParticles(void);

	void HandleEvent(sf::Event &e);

private:
	sf::RenderWindow *m_pRenderWindow;

	sf::View m_View;

	Gwen::Renderer::Base *m_pGwenRenderer;
	Gwen::Skin::Base *m_pGwenSkin;
	Gwen::Controls::Canvas *m_pCanvas;

	b2World *m_pPhysicsWorld;

	CCollisionCallback m_CollisionCallbacks;

	IBaseGameState *m_pCurrentState;
	std::map<std::string, IBaseGameState *> m_GameStates;
};

#endif // __CENGINE_H__