/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#include <sstream>
#include <vector>
#include "Gwen/Structures.h"

namespace Gwen
{
	namespace Utility
	{
		template <typename T>
		const T& Max( const T& x, const T& y )
		{
		  if ( y < x ) return x;
		  return y;
		}

		template <typename T>
		const T& Min( const T& x, const T& y )
		{
		  if ( y > x ) return x;
		  return y;
		}

		inline String UnicodeToString( const UnicodeString& strIn )
		{
			String temp = "";
			for(int i = 0; i < (int)strIn.size(); i++)
			{
				char c = (char)strIn[i];
				temp.append(&c, 1);
			}
			return temp; 
		}

		inline UnicodeString StringToUnicode( const String& strIn )
		{
			UnicodeString temp( strIn.length(), L' ' );
			std::copy( strIn.begin(), strIn.end(), temp.begin() );
			return temp; 
		}

		template <class T>
		String ToString( const T& object )
		{
			std::ostringstream os;
			os << object;
			return os.str();
		}

		inline Rect ClampRectToRect( Rect inside, Rect outside, bool clampSize = false )
		{
			if ( inside.x < outside.x )
				inside.x = outside.x; 

			if ( inside.y  < outside.y )
				inside.y = outside.y;

			if ( inside.x + inside.w > outside.x + outside.w )
			{
				if ( clampSize )
					inside.w = outside.w;
				else
					inside.x = outside.x + outside.w - inside.w;
			}
			if ( inside.y + inside.h > outside.y + outside.h )
			{
				if ( clampSize )
					inside.h = outside.h;
				else
					inside.y = outside.w + outside.h - inside.h;
			}
			
			return inside;
		}

		GWEN_EXPORT UnicodeString Format( const wchar_t* fmt, ... );

		namespace Strings
		{
			typedef std::vector<Gwen::String> List;
			typedef std::vector<Gwen::UnicodeString> UnicodeList;

			GWEN_EXPORT void Split( const Gwen::String& str, const Gwen::String& seperator, Strings::List& outbits, bool bLeaveSeperators = false );
			GWEN_EXPORT void Split( const Gwen::UnicodeString& str, const Gwen::UnicodeString& seperator, Strings::UnicodeList& outbits, bool bLeaveSeperators = false );

			template <typename T>
			T TrimLeft( const T& str, const T& strChars )
			{
				T outstr = str;
				outstr.erase( 0, outstr.find_first_not_of( strChars ) );
				return outstr;
			}

			namespace To
			{
				GWEN_EXPORT bool Bool( const Gwen::String& str );
				GWEN_EXPORT int Int( const Gwen::String& str );
				GWEN_EXPORT float Float( const Gwen::String& str );
				GWEN_EXPORT bool Floats( const Gwen::String& str, float* f, int iCount );
			}
		}
	}



}