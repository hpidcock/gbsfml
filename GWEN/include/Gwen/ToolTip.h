/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/


#pragma once

#include "Gwen/Controls/Base.h"
#include "Gwen/Gwen.h"
#include "Gwen/Skin.h"

using namespace Gwen;
using namespace Gwen::Controls;

namespace ToolTip
{
	GWEN_EXPORT void Enable	( Controls::Base* pControl );
	GWEN_EXPORT void Disable ( Controls::Base* pControl );

	GWEN_EXPORT void ControlDeleted	( Controls::Base* pControl );

	GWEN_EXPORT void RenderToolTip	( Skin::Base* skin );
}


