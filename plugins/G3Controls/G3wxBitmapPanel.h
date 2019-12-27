#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/custombgwin.h>

#include "G3wxControls.h"


// KLASA wxCustomBackgroundWindow TWORZACA OBIEKT WXPANEL Z TLEM BITMAPOWYM
// WIECEJ: http://docs.wxwidgets.org/trunk/classwx_custom_background_window.html

class WXDLLIMPEXP_G3CONTROLS G3BitmapPanel:public wxCustomBackgroundWindow<wxPanel>
{
protected:
	bool m_bGradientMode;
	wxColour m_gradientColour1, m_gradientColour2;
	wxDirection m_gradientDirection;
		
public:
	G3BitmapPanel();	

	G3BitmapPanel(wxWindow *parent, wxBitmap &bitmap, wxWindowID id,
		const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, 
		long style=0, const wxString &name=wxPanelNameStr);

	G3BitmapPanel(wxWindow *parent, wxColour gradientColour1, wxColour gradientColour2, wxDirection gradientDir, wxWindowID id,
		const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, 
		long style=0, const wxString &name=wxPanelNameStr);

	~G3BitmapPanel();

	void OnSize(wxSizeEvent &event);

	void SetBitmap(const wxBitmap &bmp);
};
