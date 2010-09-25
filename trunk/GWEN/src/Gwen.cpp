/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#include "stdafx.h"
#include "Gwen/Gwen.h"


namespace Gwen
{
	// Globals
	GWEN_EXPORT Controls::Base* HoveredControl = NULL;
	GWEN_EXPORT Controls::Base* KeyboardFocus = NULL;
	GWEN_EXPORT Controls::Base* MouseFocus = NULL;

	namespace Debug
	{
		void Msg( const char* str, ... )
		{
			char strOut[1024];
			va_list s;
			va_start( s, str ); 
			vsnprintf_s( strOut, sizeof(strOut), _TRUNCATE, str, s );
			va_end(s);
			OutputDebugStringA( strOut );
		}

		void Msg( const wchar_t* str, ... )
		{
			wchar_t strOut[1024];
			va_list s;
			va_start( s, str ); 
			vswprintf_s( strOut, str, s );
			va_end(s);
			OutputDebugStringW( strOut );
		}

		void AssertCheck( bool b, const char* strMsg )
		{
			if ( b ) return;

			MessageBoxA( NULL, strMsg, "Assert", MB_ICONEXCLAMATION | MB_OK );
			_asm { int 3 }
		}
	}

}
