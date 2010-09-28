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

// Windows
#define WIN32_LEAN_AND_MEAN
#undef UNICODE
#define NOMINMAX
#include <windows.h>
#include <cassert>

// stl
#include <iostream>
#include <string>
#include <map>
#include <vector>

// SFML
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Box2D
#include <Box2D/Box2D.h>

// Gwen
#include <Gwen/Gwen.h>
#include <Gwen/Controls/Canvas.h>

// Local Includes
#include "Math.h"

#include "CRefCounted.h"
#include "CSingleton.h"
#include "CRegister.h"

#include "CUtil.h"

#include "CBaseEntity.h"
#include "CEntityRegister.h"

#include "CKeyValues.h"
#include "CGameStateRegister.h"
#include "IBaseGameState.h"

#include "CEngine.h"