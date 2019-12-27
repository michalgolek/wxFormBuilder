#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>

#include "G3wxControls.h"

class WXDLLIMPEXP_G3CONTROLS G3BitmapButton:public wxPanel
{
private:
	wxSize DoGetBestSize() const;

	wxString m_strLabel;

	wxBitmap m_bitmapNormal, m_bitmapHover, m_bitmapChecked;

	bool m_bHover;

	bool m_bChecked;

	wxRect m_rect;

	void OnLeftDown(wxMouseEvent& event);
	void OnEnterWindow(wxMouseEvent& event);
	void OnLeaveWindow(wxMouseEvent& event); 
	void OnPaint(wxPaintEvent& event);
	//void OnEraseBackground(wxEraseEvent& rEvent);

	void OnSize(wxSizeEvent& event);

public:
	G3BitmapButton();	

	G3BitmapButton(wxWindow *parent, const wxString &label, wxBitmap &bitmapNormal, wxBitmap &bitmapHover, wxWindowID id,
		const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, 
		long style=0, const wxString &name=wxButtonNameStr);

	G3BitmapButton(wxWindow *parent, const wxString &label, wxBitmap &bitmapNormal, wxBitmap &bitmapHover, wxBitmap &bitmapChecked,
		wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, 
		long style=0, const wxString &name=wxButtonNameStr);

	~G3BitmapButton();

	//potem dziedziczyc z wxCheckbox ?
	bool IsChecked() const;

	virtual void SetValue(bool state);
};