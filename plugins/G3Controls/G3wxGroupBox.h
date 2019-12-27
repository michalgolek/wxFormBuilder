#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>

#include "G3wxControls.h"

class WXDLLIMPEXP_G3CONTROLS G3GroupBox:public wxPanel
{
private:
	wxString m_label;

	wxColour m_edgeColour;

	unsigned int m_uiBorderRoundSize;

	unsigned int m_uiEdgeWidth;

	wxBitmap m_bmp;
public:
	G3GroupBox();

	G3GroupBox(wxWindow *parent, const wxString &label=_("G3GroupBox"), wxColour edgeColor=*wxBLACK, int edgeWidth=1, int roundBorderSize=5,
		wxWindowID id=wxID_ANY,  const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, 
		long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);

	~G3GroupBox();

	void OnSize(wxSizeEvent& event);

	void OnPaint(wxPaintEvent& event);
	//void OnEraseBackground(wxEraseEvent& rEvent);

	void SetEdgeWidth(int width);
	void SetRoundEdgeSize(int edge);
};