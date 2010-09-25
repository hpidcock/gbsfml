/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#include "stdafx.h"
#include "Gwen/Anim.h"
#include "Gwen/Utility.h"
#include <math.h>

using namespace Gwen;

#ifndef GWEN_NO_ANIMATION

static Gwen::Anim::Animation::List	g_Animations;

void Gwen::Anim::Add( Gwen::Controls::Base* control, Animation* animation )
{
	animation->m_Control = control;
	g_Animations.push_back( animation );
}

void Gwen::Anim::Cancel( Gwen::Controls::Base* control )
{
	struct AnimDeletePredicate 
	{
		AnimDeletePredicate( Gwen::Controls::Base* control )
		{
			this->control = control;
		}

		bool operator() ( Gwen::Anim::Animation* anim ) 
		{
			return anim->m_Control == control;
		}

		Gwen::Controls::Base* control;
	};

	std::remove_if( g_Animations.begin(), g_Animations.end(), AnimDeletePredicate( control ) );
}

void Gwen::Anim::Think()
{
	Gwen::Anim::Animation::List::iterator it = g_Animations.begin();

	while ( it != g_Animations.end() )
	{
		Gwen::Anim::Animation* anim = *it;

		anim->Think();

		if ( anim->Finished() )
		{
			it = g_Animations.erase( it );
		}
		else
		{
			++it;
		}
	}

}

Gwen::Anim::TimedAnimation::TimedAnimation( float fLength, float fDelay, float fEase )
{
	m_fStart = Platform::GetTimeInSeconds() + fDelay;
	m_fEnd = m_fStart + fLength;
	m_fEase = fEase;
	m_bStarted = false;
	m_bFinished = false;
}

void Gwen::Anim::TimedAnimation::Think()
{
	if ( m_bFinished ) return;

	float fCurrent = Platform::GetTimeInSeconds();
	float fSecondsIn = fCurrent - m_fStart;
	if ( fSecondsIn < 0.0f ) return;

	if ( !m_bStarted )
	{
		m_bStarted = true;
		OnStart();
	}

	float fDelta = fSecondsIn / ( m_fEnd - m_fStart );
	if ( fDelta < 0.0f ) fDelta = 0.0f;
	if ( fDelta > 1.0f ) fDelta = 1.0f;

	Run( pow( fDelta, m_fEase ) );

	if ( fDelta == 1.0f )
	{
		m_bFinished = true;
		OnFinish();
	}
}

bool Gwen::Anim::TimedAnimation::Finished()
{
	return m_bFinished;
}

#endif