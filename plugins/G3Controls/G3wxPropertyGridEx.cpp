#include "G3wxPropertyGridEx.h"
#include "G3wxPropertyGrid.h"

// #include "res/configure_16x16.png.h"
// #include "res/favorites_16x16.png.h"
// #include "res/filefind_16x16.png.h"

IMPLEMENT_DYNAMIC_CLASS(G3PropertyGridEx, wxPanel);

G3PropertyGridEx::G3PropertyGridEx()
{

}

G3PropertyGridEx::G3PropertyGridEx( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString &name ):
wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	m_searchCtrl1 = new wxSearchCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
#ifndef __WXMAC__
	m_searchCtrl1->ShowSearchButton( true );
#endif
	m_searchCtrl1->ShowCancelButton( true );
	bSizer2->Add( m_searchCtrl1, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5 );


	bSizer1->Add( bSizer2, 0, wxEXPAND, 0 );

	m_propertyGrid1 = new G3PropertyGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_BOLD_MODIFIED|wxPG_SPLITTER_AUTO_CENTER, name);
	bSizer1->Add( m_propertyGrid1, 1, wxEXPAND | wxALL, 0 );


	this->SetSizer( bSizer1 );
	this->Layout();

	// Connect Events
	m_searchCtrl1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( G3PropertyGridEx::OnTextSearch ), NULL, this );

	//////////////////////////////////////////////////////////////////////////
	
	GetG3PropertyGrid()->Connect( wxID_ANY, G3_EVT_PROPERTYGRID_PROPERTY_CHANGED, G3PropertyGridEventHandler( G3PropertyGridEx::OnPropertyGridEvent ));
	GetG3PropertyGrid()->Connect( wxID_ANY, G3_EVT_PROPERTYGRID_PROPERTY_BUTTON, G3PropertyGridEventHandler( G3PropertyGridEx::OnPropertyGridEvent ));
	GetG3PropertyGrid()->Connect( wxID_ANY, G3_EVT_PROPERTYGRID_PROPERTY_TOGGLE, G3PropertyGridEventHandler( G3PropertyGridEx::OnPropertyGridEvent ));
}

G3PropertyGridEx::~G3PropertyGridEx()
{
	// Disconnect Events
	m_searchCtrl1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( G3PropertyGridEx::OnTextSearch ), NULL, this );

	//////////////////////////////////////////////////////////////////////////
	GetG3PropertyGrid()->Disconnect( wxID_ANY, G3_EVT_PROPERTYGRID_PROPERTY_CHANGED, G3PropertyGridEventHandler( G3PropertyGridEx::OnPropertyGridEvent ));
	GetG3PropertyGrid()->Disconnect( wxID_ANY, G3_EVT_PROPERTYGRID_PROPERTY_BUTTON, G3PropertyGridEventHandler( G3PropertyGridEx::OnPropertyGridEvent ));
	GetG3PropertyGrid()->Disconnect( wxID_ANY, G3_EVT_PROPERTYGRID_PROPERTY_TOGGLE, G3PropertyGridEventHandler( G3PropertyGridEx::OnPropertyGridEvent ));
}

void G3PropertyGridEx::OnTextSearch( wxCommandEvent& event )
{
	wxPropertyGridIterator it;
	
	//const wxPGProperty *propFirst=m_propertyGrid1->GetFirst();
	for ( it = m_propertyGrid1->GetIterator(wxPG_ITERATE_PROPERTIES|wxPG_ITERATE_HIDDEN , wxTOP);
		!it.AtEnd();
		it++ )
	{
		wxPGProperty* p = *it;

		//wxMessageBox(p->GetLabel());
		//wxMessageBox(m_searchCtrl1->GetValue());
		
		if(!p->GetLabel().Lower().Contains(m_searchCtrl1->GetValue().Lower()))
		//if(p->GetLabel().Find(m_searchCtrl1->GetValue())==wxNOT_FOUND)
		//if(p->GetLabel()==m_searchCtrl1->GetValue())
		 
		{	
			//if(m_propertyGrid1->IsPropertyShown(p))
			if(!p->IsSubProperty()) //fix, dzieki temu sa widoczne property wkomponowane(<composite>) w innego prop, np position>x, y,z
				p->Hide(true, wxPG_DONT_RECURSE);

			
		}
		else
		{
			//if(!m_propertyGrid1->IsPropertyShown(p))
				p->Hide(false, wxPG_DONT_RECURSE);
				
				if(p->IsCategory() )
					p->Hide(true, wxPG_DONT_RECURSE);

				//zrobic
// 				jesli p jest kategoria
// 				to przelatujemy jego dzieci
// 				jesli wszystkie dzieci sa ukryte to tez ukrywamy kategorie
				//potem dodac opcje match case to rozpoznawania wielkoscio liter
		}
		
	}
	//wxMessageBox(m_searchCtrl1->GetValue());
}

G3PropertyGrid *G3PropertyGridEx::GetG3PropertyGrid() const
{
	return m_propertyGrid1;
}

void G3PropertyGridEx::OnPropertyGridEvent( G3PropertyGridEvent& event )
{
	if ( event.IsAllowed() )
 	{
 		wxEventType eventType = event.GetEventType();
 
		if ( eventType == G3_EVT_PROPERTYGRID_PROPERTY_CHANGED)
		{
			//	wxLogDebug( wxT("G3PropertyGrid property changed") );
			//wxMessageBox( wxT("G3PropertyGridEX property changed") );

// 			G3MultiStringProperty *prop=(G3MultiStringProperty *)event.GetProperty();
// 			if(prop)
// 			{
// 				wxMessageBox(wxString::Format("aaa %s", prop->GetWxProperty()->GetName()));
// 			}

		}
		else if ( eventType == G3_EVT_PROPERTYGRID_PROPERTY_BUTTON )
		{
			//wxLogDebug( wxT("G3PropertyGrid button clicked") );
			wxMessageBox(wxString::Format("G3PropertyGridEX button evt: %i\n\nTUTAJ PRZYPISUJEMY CONTENT Z TEGO KTORY JEST WYBRANY W CONTENT EDITORZE", event.GetButton()));
		}	
		else if ( eventType == G3_EVT_PROPERTYGRID_PROPERTY_TOGGLE )
		{
			//wxLogDebug( wxT("G3PropertyGrid button clicked") );
			wxMessageBox(wxString::Format("G3PropertyGridEX toggle evt: %i\nproperty: %s", event.GetButton(), event.GetProperty()->GetName()));
		}		
 	}
}

