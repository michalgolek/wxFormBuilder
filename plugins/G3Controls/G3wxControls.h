#pragma once

#ifdef WXMAKINGLIB_G3CONTROLS
	#define WXDLLIMPEXP_G3CONTROLS
#elif defined(WXMAKINGDLL_G3CONTROLS)
	#define WXDLLIMPEXP_G3CONTROLS WXEXPORT
#elif defined(WXUSINGDLL_G3CONTROLS)
	#define WXDLLIMPEXP_G3CONTROLS WXIMPORT
#else // not making nor using DLL
	#define WXDLLIMPEXP_G3CONTROLS wxEMPTY_PARAMETER_VALUE
#endif

#include "G3wxImageBrowser.h"
#include "G3wxColorPickerPanel.h"
#include "G3wxColorPickerDialog.h"
#include "G3wxCollapsiblePanels.h"

#include "G3wxPropertyGridProperty.h"
#include "G3wxPropertyGrid.h"
#include "G3wxPropertyGridEx.h"
#include "G3wxRollMenu.h"
#include "G3wxBitmapButton.h"
#include "G3wxBitmapPanel.h"
#include "G3wxGroupBox.h"
#include "G3wxCustomFileSelect.h"
//tymczasowo ?
#include "G3wxSoundChannels.h"