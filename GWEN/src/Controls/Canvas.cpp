/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#include "stdafx.h"
#include "Gwen/Gwen.h"
#include "Gwen/Controls/Canvas.h"
#include "Gwen/Skin.h"
#include "Gwen/Controls/Menu.h"
#include "Gwen/DragAndDrop.h"
#include "Gwen/ToolTip.h"

#ifndef GWEN_NO_ANIMATION
#include "Gwen/Anim.h"
#endif

using namespace Gwen::Controls;


Canvas::Canvas( Gwen::Skin::Base* pSkin ) : BaseClass( NULL )
{
	SetBounds( 0, 0, 10000, 10000 );
	SetSkin( pSkin );
	SetScale( 1.0f );
}

void Canvas::RenderCanvas()
{
	DoThink();

	Gwen::Renderer::Base* render = m_Skin->GetRender();

	render->Begin();

		RecurseLayout( m_Skin );

		render->SetClipRegion( GetBounds() );
		render->SetRenderOffset( Point( 0, 0 ) );
		render->SetScale( Scale() );

		DoRender( m_Skin );

		DragAndDrop::RenderOverlay( this, m_Skin );

		ToolTip::RenderToolTip( m_Skin );

		render->EndClip();

	render->End();

	ProcessDelayedDeletes();

}

void Canvas::Render( Gwen::Skin::Base* pRender )
{
	m_bNeedsRedraw = false;
}

void Canvas::OnBoundsChanged( Rect oldBounds )
{
	BaseClass::OnBoundsChanged( oldBounds );
	InvalidateChildren( true );
}


void Canvas::DoThink()
{
	if ( Hidden() ) return;

	#ifndef GWEN_NO_ANIMATION
	Gwen::Anim::Think();
	#endif

	// Reset tabbing
	{
		NextTab = NULL;
		FirstTab = NULL;
	}

	ProcessDelayedDeletes();
	// Check has focus etc..
	RecurseLayout( m_Skin );

	// If we didn't have a next tab, cycle to the start.
	if ( NextTab == NULL ) 
		NextTab = FirstTab;

	Gwen::Input::OnCanvasThink( this );
	
}

void Canvas::SetScale( float f )
{ 
	if ( m_fScale == f ) return;

	m_fScale = f;

	if ( m_Skin && m_Skin->GetRender() )
		m_Skin->GetRender()->SetScale( m_fScale );

	OnScaleChanged();
	Redraw();
}

void Canvas::AddDelayedDelete( Gwen::Controls::Base* pControl )
{
	m_DeleteList.push_back( pControl );
}

void Canvas::ProcessDelayedDeletes()
{
	for ( Gwen::Controls::Base::List::iterator it = m_DeleteList.begin(); it != m_DeleteList.end(); ++it )
	{
		Gwen::Controls::Base* pControl = *it;
		delete pControl;
	}

	m_DeleteList.clear();
}

void Canvas::Release()
{
	Base::List::iterator iter = Children.begin();
	while ( iter != Children.end() )
	{
		Base* pChild = *iter;
		iter = Children.erase( iter );
		delete pChild;
	}

	delete this;
}

bool Canvas::InputMouseMoved( int x, int y, int deltaX, int deltaY )
{
	if ( Hidden() ) return false;

	float fScale = 1.0f / Scale();
	Gwen::Input::OnMouseMoved( this, x, y, deltaX, deltaY );

	if ( !Gwen::HoveredControl ) return false;
	if ( Gwen::HoveredControl == this ) return false;
	if ( Gwen::HoveredControl->GetCanvas() != this ) return false;

	Gwen::HoveredControl->OnMouseMoved( x, y, deltaX, deltaY );
	Gwen::HoveredControl->UpdateCursor();

	DragAndDrop::OnMouseMoved( Gwen::HoveredControl, x, y );
	return true;
}

bool Canvas::InputMouseButton( int iButton, bool bDown )
{
	if ( Hidden() ) return false;

	return Gwen::Input::OnMouseClicked( this, iButton, bDown );
}

bool Canvas::InputKey( int iKey, bool bDown )
{
	if ( Hidden() ) return false;

	return Gwen::Input::OnKeyEvent( this, iKey, bDown );
}

bool Canvas::InputCharacter( Gwen::UnicodeChar chr )
{
	if ( Hidden() ) return false;
	if ( !iswprint( chr ) ) return false;

	//Handle Accelerators
	if ( Gwen::Input::HandleAccelerator( this, chr ) )
		return true;

	//Handle characters
	if ( !Gwen::KeyboardFocus ) return false;
	if ( Gwen::KeyboardFocus->GetCanvas() != this ) return false;
	if ( !Gwen::KeyboardFocus->Visible() ) return false;
	if( Gwen::Input::IsControlDown() ) return false; 

	return KeyboardFocus->OnChar( chr );
}

bool Canvas::InputMouseWheel( int val )
{
	if ( Hidden() ) return false;
	if ( !Gwen::HoveredControl ) return false;
	if ( Gwen::HoveredControl == this ) return false;
	if ( Gwen::HoveredControl->GetCanvas() != this ) return false;

	return Gwen::HoveredControl->OnMouseWheeled( val );
}