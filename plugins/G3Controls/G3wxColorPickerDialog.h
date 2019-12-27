#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/radiobut.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/dialog.h>

#include "G3wxControls.h"

enum EG3ColorPickerDialogStyles
{
	G3_CPD_USE_ALPHA=1	
};

class WXDLLIMPEXP_G3CONTROLS G3ColorPickerPanel;

class WXDLLIMPEXP_G3CONTROLS G3ColorPickerDialog : public wxDialog 
{
private:
	G3ColorPickerPanel *m_g3colorPickerPanel;
	wxButton* m_button3;
	wxButton* m_button4;

protected:
	enum
	{
		ID_OK = 1000,
		ID_CANCEL
	};
	
	void OnButtonClick( wxCommandEvent& event );

public:
	G3ColorPickerDialog();
	//G3ColorPickerDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("G3 Color Picker"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 422,335 ), long style = wxDEFAULT_DIALOG_STYLE ); 
	G3ColorPickerDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("G3 Color Picker") ); 
	~G3ColorPickerDialog();

	void SetColour(const wxColour &color);

	wxColour GetColour() const;

	DECLARE_DYNAMIC_CLASS(G3ColorPickerDialog)	
};