/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once

// This will probably require some kind of ifdef windows

#ifdef GWEN_DLL
#	ifdef GWEN_COMPILE
#		define GWEN_EXPORT __declspec(dllexport)
#	else
#		define GWEN_EXPORT __declspec(dllimport)
#	endif
#else
#	define GWEN_EXPORT
#endif

