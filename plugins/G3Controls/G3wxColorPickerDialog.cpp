#include "G3wxColorPickerDialog.h"
#include "G3wxColorPickerPanel.h"



IMPLEMENT_DYNAMIC_CLASS(G3ColorPickerDialog, wxDialog);

// statyczne eventy, jesli uzywamy dynamicznych(Connect,Bind) to zakomentowac TABLE
// BEGIN_EVENT_TABLE( G3ImageBrowser, wxPanel )
// //EVT_G3_TABLE_(G3_EVT_IMAGEBROWSER_ITEM_SELECTED, wxID_ANY, G3ImageBrowser::OnImageBrowserEvent)
// EVT_G3_IMAGEBROWSER_ITEM_SELECTED(wxID_ANY, G3ImageBrowser::OnImageBrowserEvent )
// EVT_G3_IMAGEBROWSER_ITEM_BEGIN_DRAGGED(wxID_ANY, G3ImageBrowser::OnImageBrowserEvent )
// EVT_G3_IMAGEBROWSER_ITEM_END_DRAGGED(wxID_ANY, G3ImageBrowser::OnImageBrowserEvent )
// END_EVENT_TABLE

///////////////////////////////////////////////////////////////////////////

G3ColorPickerDialog::G3ColorPickerDialog()
{
	//G3ColorPickerDialog(this)
}

G3ColorPickerDialog::G3ColorPickerDialog( wxWindow* parent, wxWindowID id, const wxString& title) 
	: wxDialog( parent, id, title, wxDefaultPosition, wxSize(440, 281), wxDEFAULT_DIALOG_STYLE)
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	m_g3colorPickerPanel=new G3ColorPickerPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1));
	bSizer14->Add( m_g3colorPickerPanel, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );

	m_button3 = new wxButton( this, ID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_button3, 0, wxALL, 5 );

	m_button4 = new wxButton( this, ID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_button4, 0, wxALL, 5 );


	bSizer14->Add( bSizer28, 0, wxALIGN_RIGHT, 5 );


	this->SetSizer( bSizer14 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( G3ColorPickerDialog::OnButtonClick ), NULL, this );
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( G3ColorPickerDialog::OnButtonClick ), NULL, this );

	//////////////////////////////////////////////////////////////////////////
	SetEscapeId(ID_CANCEL);
}

G3ColorPickerDialog::~G3ColorPickerDialog()
{
	// Disconnect Events
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( G3ColorPickerDialog::OnButtonClick ), NULL, this );
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( G3ColorPickerDialog::OnButtonClick ), NULL, this );
}

void G3ColorPickerDialog::SetColour(const wxColour &color)
{
	m_g3colorPickerPanel->SetRGBA(color);
}

wxColour G3ColorPickerDialog::GetColour() const
{
	return m_g3colorPickerPanel->GetColour();
}

void G3ColorPickerDialog::OnButtonClick( wxCommandEvent& event )
{
	switch(event.GetId())
	{
	case ID_OK:
		//SetReturnCode(wxID_OK);
		//Close(true);
		EndModal(wxID_OK);
		break;
	case ID_CANCEL:
		//SetReturnCode(wxID_CANCEL);
		//Close(true);
		EndModal(wxID_CANCEL);
		break;
	}
}