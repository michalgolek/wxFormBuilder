#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/gbsizer.h>
#include <wx/radiobut.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/sizer.h>

#include "G3wxControls.h"

#define MAX(a, b, c) ((a)>(b)? ((a)>(c)?(a):(c)) : ((b)>(c)?(b):(c)))
#define MIN(a, b, c) ((a)<(b)? ((a)<(c)?(a):(c)) : ((b)<(c)?(b):(c)))

struct SColour
{
	unsigned short r, g, b;		// Red, green and blue
	unsigned short rPrev, gPrev, bPrev;		// Red, green and blue	
	unsigned short h, s, v;		// Hue, saturation and value
	unsigned short a, aPrev;			// Alpha

	void UpdateRGB ();			// Updates RGB from HSV
	void UpdateHSV ();			// Updates HSV from RGB
};

class WXDLLIMPEXP_G3CONTROLS G3ColorPickerPanelEvent;

class WXDLLIMPEXP_G3CONTROLS G3ColorPickerPanel : public wxPanel 
{
private:
	void OnColorPickerEvent( G3ColorPickerPanelEvent& event );

	wxPanel* m_bitmapColor;
	wxPanel* m_bitmapColor24;
	wxPanel* m_bitmapAlpha;
	wxSpinCtrl* m_spinCtrlR;
	wxSpinCtrl* m_spinCtrlG;
	wxSpinCtrl* m_spinCtrlB;
	wxSpinCtrl* m_spinCtrlA;
	wxStaticText* m_staticText6;
	wxStaticText* m_staticText61;
	wxStaticText* m_staticText611;
	wxStaticText* m_staticText1;
	wxRadioButton* m_radioBtnH;
	wxRadioButton* m_radioBtnS;
	wxRadioButton* m_radioBtnV;
	wxStaticBitmap* m_bitmapCurrentColor;
	wxStaticBitmap* m_bitmapPreviousColor;

	
	//////////////////////////////////////////////////////////////////////////
	wxBitmap *m_colorBitmap;
	wxBitmap *m_color24Bitmap;
	wxBitmap *m_alphaBitmap;

	bool m_lButtonDownColor, m_bButtonDownColor24;
			
	int m_selectedComponent; 

	void PaintColor();
	void PaintColor24();
	void PaintAlpha();

	void UpdateValues(SColour &colour);

	SColour picker;
		
protected:
	enum
	{
		ID_RSPIN = 1000,
		ID_GSPIN,
		ID_BSPIN,
		ID_ASPIN,
		ID_H,
		ID_S,
		ID_V
	};
				
	void OnMouseCaptureLost(wxMouseCaptureLostEvent &event) ;

	void OnLeftDownColor( wxMouseEvent& event );
	void OnLeftUpColor( wxMouseEvent& event );
	void OnMotionColor( wxMouseEvent& event );
	void OnPaintColor( wxPaintEvent& event );
	void OnLeftDownColor24( wxMouseEvent& event );
	void OnLeftUpColor24( wxMouseEvent& event );
	void OnMotionColor24( wxMouseEvent& event );
	void OnPaintColor24( wxPaintEvent& event );
	void OnLeftDownAlpha( wxMouseEvent& event );
	void OnLeftUpAlpha( wxMouseEvent& event );
	void OnMotionAlpha( wxMouseEvent& event );
	void OnPaintAlpha( wxPaintEvent& event );
	void OnRadioButton( wxCommandEvent& event );
	void OnSpinCtrl( wxSpinEvent& event );
	void OnLeftDownCurrentColor( wxMouseEvent& event );
	void OnPaintCurrentColor( wxPaintEvent& event );
	void OnLeftDownPreviousColor( wxMouseEvent& event );
	void OnPaintPreviousColor( wxPaintEvent& event );


		
public:
	G3ColorPickerPanel();
	G3ColorPickerPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 460,316 )); 
	~G3ColorPickerPanel();

	void SetRGB(const wxColour &colour);
	void SetAlpha(int alpha);

	void SetRGBA(const wxColour &colour);

	wxColour GetColour() const;
	wxColour GetPrevColour() const;

	DECLARE_DYNAMIC_CLASS(G3ColorPickerPanel)	
};

class WXDLLIMPEXP_G3CONTROLS G3ColorPickerPanelEvent:public wxNotifyEvent
{
private:
	wxColour m_currentColour;
	wxColour m_previousColour;

public:
	G3ColorPickerPanelEvent(wxEventType commandType=wxEVT_NULL, int id=0, const wxColour& currentColour=*wxRED, const wxColour& previousColour=*wxRED);

	wxColour GetCurrentColour() const;
	wxColour GetPreviousColour() const;

	virtual wxEvent *Clone() const { return new G3ColorPickerPanelEvent( *this ); }

	DECLARE_DYNAMIC_CLASS(G3ColorPickerPanelEvent)
};

// ----------------------------------------------------------------------------
// macros for handling WizardEvents
// ----------------------------------------------------------------------------

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_COLORPICKER_CHANGE_VALUE, 900 );
END_DECLARE_EVENT_TYPES()

typedef void (wxEvtHandler::*G3ColorPickerPanelEventFunction)(G3ColorPickerPanelEvent&);

#define G3ColorPickerPanelEventHandler(func) \
	(wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(G3ColorPickerPanelEventFunction, &func)

#define EVT_G3_COLORPICKER_CHANGE_VALUE(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_COLORPICKER_CHANGE_VALUE, winid, G3ColorPickerPanelEventHandler(fn))