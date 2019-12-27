#pragma once

#include "G3wxControls.h"

#include <wx/srchctrl.h>

class WXDLLIMPEXP_G3CONTROLS G3PropertyGridEvent;

class G3PropertyGrid;

class WXDLLIMPEXP_G3CONTROLS G3PropertyGridEx:public wxPanel 
{
protected:
	wxSearchCtrl* m_searchCtrl1;

	// Virtual event handlers, overide them in your derived class
	virtual void OnTextSearch( wxCommandEvent& event ) ;		

	G3PropertyGrid* m_propertyGrid1;	
	
public:		
	G3PropertyGridEx();

	G3PropertyGridEx( wxWindow* parent, wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,582 ),
		long style = wxTAB_TRAVERSAL, const wxString &name=wxPropertyGridNameStr ); 

	~G3PropertyGridEx();
	
	G3PropertyGrid *GetG3PropertyGrid() const;

	void OnPropertyGridEvent( G3PropertyGridEvent& event );
	
	DECLARE_DYNAMIC_CLASS(G3PropertyGridEx)
};

