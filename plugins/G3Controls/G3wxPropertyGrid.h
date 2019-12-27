#pragma once

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

#include "G3wxControls.h"

#include "G3wxPropertyGridProperty.h"
#include "G3wxPropertyEditors.h"

class WXDLLIMPEXP_G3CONTROLS G3MultiStringProperty;
class WXDLLIMPEXP_G3CONTROLS G3MultiBoolProperty;
class WXDLLIMPEXP_G3CONTROLS G3MultiFloatProperty;
class WXDLLIMPEXP_G3CONTROLS G3MultiIntProperty;
class WXDLLIMPEXP_G3CONTROLS G3MultiEnumProperty;
class WXDLLIMPEXP_G3CONTROLS G3ContentDataProperty;
class WXDLLIMPEXP_G3CONTROLS G3MultiFrameProperty;

//namespace Editor
//{
//class WXDLLIMPEXP_G3CONTROLS G3PropertyGridEvent;

class WXDLLIMPEXP_G3CONTROLS G3PGCellRenderer:public wxPGCellRenderer
{
public:
	virtual bool Render( wxDC& dc,
		const wxRect& rect,
		const wxPropertyGrid* propertyGrid,
		wxPGProperty* property,
		int column,
		int item,
		int flags ) const;

	// do renderowania na przemian roznych kolorow komorkek z kolumny 0
	int m_iIndex;

};

class WXDLLIMPEXP_G3CONTROLS G3PropertyGridEvent;

class WXDLLIMPEXP_G3CONTROLS G3PropertyGrid:public wxPropertyGrid
{		
private:

protected:		
	void DrawExpanderButton( wxDC& dc, const wxRect& rect, wxPGProperty* property ) const;

	//tutaj sa renderowane wszystkie itemy jesli nie sa aktywne\zaznaczone
	int DoDrawItems( wxDC& dc, const wxRect* itemsRect, bool isBuffered ) const;

	void OnPropertyGridChanged( wxPropertyGridEvent& event);

	void OnPropertyGridEvent( G3PropertyGridEvent& event );

public:
	G3PropertyGrid();
	G3PropertyGrid(wxWindow *parent, wxWindowID id=wxID_ANY, 
		const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, 
		long style=wxPG_DEFAULT_STYLE, const wxString &name=wxPropertyGridNameStr); 

	virtual ~G3PropertyGrid();	

	void ProcessButtonEventEditor(int controlID, wxPGProperty *prop);
	void ProcessToggleButtonEventEditor(int controlID, wxPGProperty *prop);

	wxPGProperty *AddCategory(const wxString& label, const wxString& name=wxPG_LABEL);

	wxPGProperty *AddComposed(const wxString& label, const wxString& name=wxPG_LABEL);
	
	G3MultiStringProperty *AddStringProperty(wxPGProperty *parent, const wxString& label, const wxString& name=wxPG_LABEL);	

	G3MultiBoolProperty *AddBoolProperty(wxPGProperty *parent, const wxString& label, const wxString& name=wxPG_LABEL);	

	G3MultiFloatProperty *AddFloatProperty(wxPGProperty *parent, const wxString& label, const wxString& name=wxPG_LABEL, float spinnerStep=0.1f);	

	G3MultiIntProperty *AddIntProperty(wxPGProperty *parent, const wxString& label, const wxString& name=wxPG_LABEL, int spinnerStep=1);

	// tylko dla tych samych wartosci CHOICES , lub -przetestowac>po dodaniu nowego itema sumowac liste choices ?, albo dac najmniejsza ilosc choice jaka mial wybranty item!
	// WYLACZNIE DLA JEDNEGO TYPU CHOICES`ow !!!!
	G3MultiEnumProperty *AddEnumProperty(wxPGProperty *parent, const wxString& label, wxPGChoices &choices, int defaultSelected, const wxString& name=wxPG_LABEL);

	G3ContentDataProperty *AddContentDataProperty(wxPGProperty *parent, const wxString& label, const wxString& name=wxPG_LABEL);

	G3MultiFrameProperty *AddFrameProperty(wxPGProperty *parent, const wxString& label, const wxString& name=wxPG_LABEL, int framePerSec=30);

	void EnableProperty(wxPGProperty *property);

	void DisableProperty(wxPGProperty *property);

	DECLARE_DYNAMIC_CLASS(G3PropertyGrid)

private:
	DECLARE_EVENT_TABLE()
};

class WXDLLIMPEXP_G3CONTROLS G3PropertyGridEvent:public wxNotifyEvent
{
protected:
	wxPGProperty *m_pProperty;

	int m_iButton;

public:
	G3PropertyGridEvent(wxEventType commandType=wxEVT_NULL, int id=0, wxPGProperty *prop=0, int button=-1);

	virtual wxEvent *Clone() const { return new G3PropertyGridEvent( *this ); }

	wxPGProperty *GetProperty() const;

	int GetButton() const;

	DECLARE_DYNAMIC_CLASS(G3PropertyGridEvent)
};

// ----------------------------------------------------------------------------
// macros for handling WizardEvents
// ----------------------------------------------------------------------------

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_PROPERTYGRID_PROPERTY_CHANGED, 10000)
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_PROPERTYGRID_PROPERTY_BUTTON, 10001)
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_PROPERTYGRID_PROPERTY_TOGGLE, 10002)
// DECLARE_EVENT_TYPE(G3_EVT_PROPERTYGRID_PROPERTY_CHANGED)
// DECLARE_EVENT_TYPE(G3_EVT_PROPERTYGRID_PROPERTY_BUTTON)
// DECLARE_EVENT_TYPE(G3_EVT_PROPERTYGRID_PROPERTY_TOGGLE)
END_DECLARE_EVENT_TYPES()

typedef void (wxEvtHandler::*G3PropertyGridEventFunction)(G3PropertyGridEvent&);

#define G3PropertyGridEventHandler(func) (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(G3PropertyGridEventFunction, &func)

// wylacznie dla DECLARE_EVENT_TABLE
#define EVT_G3_PROPERTYGRID_PROPERTY_CHANGED(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_PROPERTYGRID_PROPERTY_CHANGED, winid, G3ImageBrowserEventHandler(fn))

#define EVT_G3_PROPERTYGRID_PROPERTY_BUTTON(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_PROPERTYGRID_PROPERTY_BUTTON, winid, G3ImageBrowserEventHandler(fn))

#define EVT_G3_PROPERTYGRID_PROPERTY_TOGGLE(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_PROPERTYGRID_PROPERTY_TOGGLE, winid, G3ImageBrowserEventHandler(fn))

