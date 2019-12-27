#include "G3wxPropertyEditors.h"

#include "G3wxPropertyGrid.h"

#include <wx/renderer.h> // wxRendererNative

#include <wx/msgdlg.h> 

#include <wx/window.h>
#include <wx/slider.h>
#include <wx/bmpbuttn.h>

//using namespace Editor;

// class template G3PGProperty<int>;
// class template G3PGProperty<float>;

// BASE CLASS FOR G3PROPERTYEditor

// G3PGPropertyEditor::G3PGPropertyEditor()
// {
// 	//m_bSameValues=true;
// }
// 
// G3PGPropertyEditor::~G3PGPropertyEditor()
// {
// 
// }

// KLASA DO TWORZENIA NOWYCH BUTTONOW DLA "PROPERTY"
// PO UZYCIU ADDBUTTON USTAWIC wndList.m_primary, wndList.m_secondary
// GetPrimarySize ZWRACA CALKOWITY OBSZAR DODANYCH BUTTONOW(PRZYDATNE!)

//////////////////////////////////////////////////////////////////////////
// nie ma sensu tworzyc z tego globalnej klasy
class G3PGSpinButton : public wxSpinButton
{
public:
	G3PGSpinButton();	

	int GetSpins() const;

private:
	void OnPaintEvent(wxPaintEvent& event);

	void OnMouseEvent(wxMouseEvent& event);

	void OnMouseCaptureLost(wxMouseCaptureLostEvent& event);

	// oryg wxPGSPinButton
	wxPoint m_ptPosition;

	// Having a separate spins variable allows us to handle validation etc. for
	// multiple spin events at once (with quick mouse movements there could be
	// hundreds of 'spins' being done at once). Technically things like this
	// should be stored in event (wxSpinEvent in this case), but there probably
	// isn't anything there that can be reliably reused.
	int     m_spins;

	bool    m_bLeftDown;

	// SpinButton seems to be a special for mouse capture, so we may need track
	// privately whether mouse is actually captured.
	bool    m_hasCapture;

	void Capture();

	void Release();
};

G3PGSpinButton::G3PGSpinButton()
	:wxSpinButton()
{
	// oryg > wxPGSpinButton
	m_bLeftDown = false;
	m_hasCapture = false;
	m_spins = 1;

	Connect( wxEVT_LEFT_DOWN,
		wxMouseEventHandler(G3PGSpinButton::OnMouseEvent) );
	Connect( wxEVT_LEFT_UP,
		wxMouseEventHandler(G3PGSpinButton::OnMouseEvent) );
	Connect( wxEVT_MOTION,
		wxMouseEventHandler(G3PGSpinButton::OnMouseEvent) );
	Connect( wxEVT_MOUSE_CAPTURE_LOST,
		wxMouseCaptureLostEventHandler(G3PGSpinButton::OnMouseCaptureLost) );

	// < wxPGSpinButton

	Connect( wxEVT_PAINT, wxPaintEventHandler( G3PGSpinButton::OnPaintEvent ));
}

int G3PGSpinButton::GetSpins() const
{
	return m_spins;
}

void G3PGSpinButton::Capture()
{
	if ( !m_hasCapture )
	{
		CaptureMouse();
		m_hasCapture = true;
	}

	SetCursor(wxCURSOR_SIZENS);
}

void G3PGSpinButton::Release()
{
	m_bLeftDown = false;

	if ( m_hasCapture )
	{
		ReleaseMouse();
		m_hasCapture = false;
	}

	wxWindow *parent = GetParent();
	if ( parent )
		SetCursor(parent->GetCursor());
	else
		SetCursor(wxNullCursor);
}

void G3PGSpinButton::OnMouseEvent(wxMouseEvent& event)
{
	if(event.GetEventType() == wxEVT_LEFT_DOWN || event.GetEventType() == wxEVT_LEFT_UP)
		Refresh();

	if ( event.GetEventType() == wxEVT_LEFT_DOWN )
	{
		m_bLeftDown = true;
		m_ptPosition = event.GetPosition();
	}
	else if ( event.GetEventType() == wxEVT_LEFT_UP )
	{
		Release();
		m_bLeftDown = false;
	}
	else if ( event.GetEventType() == wxEVT_MOTION )
	{
		if ( m_bLeftDown )
		{
			int dy = m_ptPosition.y - event.GetPosition().y;
			if ( dy )
			{
				Capture();
				m_ptPosition = event.GetPosition();

				wxSpinEvent evtscroll( (dy >= 0) ? wxEVT_SCROLL_LINEUP :
					wxEVT_SCROLL_LINEDOWN,
					GetId() );
				evtscroll.SetEventObject(this);

				wxASSERT( m_spins == 1 );

				m_spins = abs(dy);
				GetEventHandler()->ProcessEvent(evtscroll);
				m_spins = 1;
			}
		}
	}

	event.Skip();
}
void G3PGSpinButton::OnMouseCaptureLost(wxMouseCaptureLostEvent& WXUNUSED(event))
{
	Release();

	Refresh();
}

void G3PGSpinButton::OnPaintEvent(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	wxSize rect=GetClientSize();

	dc.SetBrush(wxBrush(wxColour("#335544")));
	dc.SetPen(wxPen(wxColour("#222222"), 1));

	wxRendererNative::Get().DrawPushButton(this, dc, rect,
		m_bLeftDown?wxCONTROL_PRESSED:wxCONTROL_CURRENT);

	wxPoint triPntsUp[3]={wxPoint(rect.GetWidth()/2, 3),
		wxPoint(rect.GetWidth()/2-3, 6),
		wxPoint(rect.GetWidth()/2+3, 6)};

	dc.DrawPolygon(3, triPntsUp);

	wxPoint triPntsDown[3]={wxPoint(rect.GetWidth()/2, rect.GetHeight()/2+2+3),
		wxPoint(rect.GetWidth()/2-3, rect.GetHeight()/2+2),
		wxPoint(rect.GetWidth()/2+3, rect.GetHeight()/2+2)};

	dc.DrawPolygon(3, triPntsDown);
}

//////////////////////////////////////////////////////////////////////////

wxPGButtonEditorManager::wxPGButtonEditorManager ( wxPropertyGrid* pg, const wxSize& sz ):
wxWindow( pg->GetPanel(), /*wxPG_SUBID2*/ wxID_ANY, wxPoint(-100,-100), wxSize(0, sz.y) ),
	m_fullEditorSize(sz), 
	m_buttonsWidth(0)
{
}

wxPGButtonEditorManager::~wxPGButtonEditorManager ()
{

}

wxWindow* wxPGButtonEditorManager::GetButton(unsigned int i)
{
	return (wxWindow*) m_buttons[i];
}

// const wxWindow* wxPGButtonEditorManager::GetButton(unsigned int i) const
// {
// 	return (const wxWindow*) m_buttons[i]; 
// }

int wxPGButtonEditorManager::GetButtonId(unsigned int i)// const
{
	return GetButton(i)->GetId(); 
}

/** Returns number of buttons.
*/
unsigned int wxPGButtonEditorManager::GetCount() const
{
	return (unsigned int) m_buttons.size(); 
}

void wxPGButtonEditorManager::AddCustomControl( wxControl *control, int itemid)
{
	itemid = GenId(itemid);
	wxSize sz = GetSize();

	control->SetParent(this);
	control->SetPosition(wxPoint(sz.x, 0));
	control->SetSize(wxSize(sz.y, sz.y));

	DoAddButton( control, sz );
}

wxButton *wxPGButtonEditorManager::AddButton( const wxString& label, int itemid)
{
	itemid = GenId(itemid);
	wxSize sz = GetSize();
	wxButton* button = new wxButton( this, itemid, label, wxPoint(sz.x, 0),
		wxSize(sz.y, sz.y) );
	DoAddButton( button, sz );

	return button;
}

wxToggleButton *wxPGButtonEditorManager::AddToggleButton(const wxString& label, int itemid)
{
	itemid = GenId(itemid);
	wxSize sz = GetSize();
	wxToggleButton* toggleButton = new wxToggleButton(this, itemid, label, wxPoint(sz.x, 0),
		wxSize(sz.y, sz.y) );
	DoAddButton( toggleButton, sz );

	return toggleButton;
}

wxButton *wxPGButtonEditorManager::AddButton( const wxBitmap& bitmap, int itemid)
{
	itemid = GenId(itemid);
	wxSize sz = GetSize();
	wxButton* button = new wxBitmapButton( this, itemid, bitmap,
		wxPoint(sz.x, 0),
		wxSize(sz.y, sz.y) );
	DoAddButton( button, sz );

	return button;
}


wxSize wxPGButtonEditorManager::GetPrimarySize() const
{
	return wxSize(m_fullEditorSize.x - m_buttonsWidth, m_fullEditorSize.y);
}

void wxPGButtonEditorManager::Finalize( wxPropertyGrid* propGrid, const wxPoint& pos)
{
	Move( pos.x + m_fullEditorSize.x - m_buttonsWidth, pos.y );
}

void wxPGButtonEditorManager::DoAddButton(wxWindow* button, const wxSize& sz)
{
	m_buttons.push_back(button);
	int bw = button->GetSize().x;
	SetSize(wxSize(sz.x+bw,sz.y));
	m_buttonsWidth += bw;
}

int wxPGButtonEditorManager::GenId(int itemid) //const
{
	if ( itemid < -1 )
	{
		if ( m_buttons.size() )
			itemid = GetButton(m_buttons.size()-1)->GetId() + 1;
		else
			itemid = /*wxPG_SUBID2*/ wxID_ANY;
	}
	return itemid;
}



//////////////////////////////////////////////////////////////////////////

G3SpinMultiValPGEditor::G3SpinMultiValPGEditor():
wxPGSpinCtrlEditor(),
	//G3PGPropertyEditor(),
	m_bEditedBySpinner(false)
{
}

G3SpinMultiValPGEditor::~G3SpinMultiValPGEditor() 
{

}

wxPGWindowList G3SpinMultiValPGEditor::CreateControls( wxPropertyGrid* propGrid, wxPGProperty* property, 
	const wxPoint& pos, const wxSize& sz ) const
{	
	// 	if(property->GetAttribute("sameValues"))
	//  	{
	//  		wxVariant propValue = property->GetValue();
	//  
	//  		// Also, handle the case where property value is unspecified
	//  		if (!propValue.IsNull() )
	//  		{
	//  			if(propValue.GetType()=="long")
	//  				property->SetValue(0);
	//  
	//  			if(propValue.GetType()=="double")
	//  				property->SetValue(0.0);
	//  		}		
	//  	}	

	const int margin = 1;
	wxSize butSz(18, sz.y);
	wxSize tcSz(sz.x - butSz.x - margin, sz.y);
	wxPoint butPos(pos.x + tcSz.x + margin, pos.y);

	//////////////////////////////////////////////////////////////////////////

	wxWindow* wnd1 = wxPGTextCtrlEditor::CreateControls(propGrid, property, pos, tcSz).m_primary;
#if wxUSE_VALIDATORS
	// Let's add validator to make sure only numbers can be entered
	wxTextValidator validator(wxFILTER_NUMERIC, &m_tempString);
	wnd1->SetValidator(validator);
#endif

	//////////////////////////////////////////////////////////////////////////

	wxSpinButton* wnd2;

	//#if IS_MOTION_SPIN_SUPPORTED
	if ( property->GetAttributeAsLong(wxT("MotionSpin"), 0) )
	{
		wnd2 = new G3PGSpinButton();
	}
	//else
	//#endif
	//{
	//wnd2 = new wxSpinButton();
	//}

#ifdef __WXMSW__
	wnd2->Hide();
#endif
	wnd2->Create( propGrid->GetPanel(), /*wxPG_SUBID2*/ wxID_ANY, butPos, butSz, wxSP_VERTICAL );

	wnd2->SetRange( INT_MIN, INT_MAX );
	wnd2->SetValue( 0 );

	return wxPGWindowList(wnd1, wnd2);

	//////////////////////////////////////////////////////////////////////////

	// JESLI NIE UZYWAMY INNEGO RYSOWANIA SPINCTRL TO UZYWAMY TEGO PONIZEJ
	//	return wxPGSpinCtrlEditor::CreateControls(propGrid, property, pos, sz);	
}

bool G3SpinMultiValPGEditor::OnEvent( wxPropertyGrid* propGrid, wxPGProperty* property, wxWindow* ctrl, wxEvent& event ) const
{
	int evtType = event.GetEventType();

	G3SpinMultiValPGEditor *ptr = const_cast<G3SpinMultiValPGEditor*>(this);

	ptr->m_bEditedBySpinner=false;
	if ( evtType == wxEVT_KEY_DOWN ||
		evtType == wxEVT_SCROLL_LINEUP ||
		evtType == wxEVT_SCROLL_LINEDOWN)
	{
		ptr->m_bEditedBySpinner=true;
	}

	return wxPGSpinCtrlEditor::OnEvent(propGrid,property,ctrl,event);
}


void G3SpinMultiValPGEditor::DrawValue(wxDC &dc, const wxRect &rect, wxPGProperty *property, const wxString &text) const 
{
	if(property->GetAttribute("sameValues"))
	{
		wxPGSpinCtrlEditor::DrawValue(dc, rect, property, text);
	}
	else
	{
		//dc.GradientFillLinear(rect, wxColour(0,210,210), wxColour(160,160,160), wxNORTH);	
		//dc.GradientFillLinear(rect, wxColour(162,95,95), wxColour(246,138,138), wxEAST);
		dc.SetBrush(wxBrush(wxColour("#4ed2f3")));
		//dc.DrawRoundedRectangle(rect, 4);
		dc.DrawRectangle(wxRect(rect.x-2, rect.y-4, rect.GetWidth()+4, rect.GetHeight()+8));
		dc.DrawLabel(_("(Mixed)"), rect);
	}
}

//////////////////////////////////////////////////////////////////////////

G3StringMultiValPGEditor::G3StringMultiValPGEditor():
wxPGTextCtrlEditor()//,
	//G3PGPropertyEditor()
{
}

G3StringMultiValPGEditor::~G3StringMultiValPGEditor() 
{

}
void G3StringMultiValPGEditor::DrawValue(wxDC &dc, const wxRect &rect, wxPGProperty *property, const wxString &text) const 
{	
	if(property->GetAttribute("sameValues"))
	{
		wxPGTextCtrlEditor::DrawValue(dc, rect, property, text);
	}
	else
	{
		//dc.GradientFillLinear(rect, wxColour(0,210,210), wxColour(160,160,160), wxWEST);	
		//dc.GradientFillLinear(rect, wxColour(162,95,95), wxColour(246,138,138), wxEAST);
		dc.SetBrush(wxBrush(wxColour("#4ed2f3")));
		//dc.DrawRectangle(rect);
		dc.DrawRectangle(wxRect(rect.x-2, rect.y-4, rect.GetWidth()+4, rect.GetHeight()+8));
		dc.DrawLabel(_("(Mixed)"), rect);
	}
}

//////////////////////////////////////////////////////////////////////////
G3BoolMultiValPGEditor::G3BoolMultiValPGEditor():
wxPGCheckBoxEditor()//,
	//G3PGPropertyEditor()
{
}

G3BoolMultiValPGEditor::~G3BoolMultiValPGEditor() 
{

}
void G3BoolMultiValPGEditor::DrawValue(wxDC &dc, const wxRect &rect, wxPGProperty *property, const wxString &text) const 
{	
	if(property->GetAttribute("sameValues"))
	{
		wxPGCheckBoxEditor::DrawValue(dc, rect, property, text);
	}
	else
	{
		//dc.GradientFillLinear(rect, wxColour(0,210,210), wxColour(160,160,160), wxWEST);	
		//dc.GradientFillLinear(rect, wxColour(162,95,95), wxColour(246,138,138), wxEAST);
		dc.SetBrush(wxBrush(wxColour("#4ed2f3")));
		//dc.DrawRectangle(rect);
		dc.DrawRectangle(wxRect(rect.x-2, rect.y-4, rect.GetWidth()+4, rect.GetHeight()+8));
		dc.DrawLabel(_("(Mixed)"), rect);
	}
}


//////////////////////////////////////////////////////////////////////////

G3EnumMultiValPGEditor::G3EnumMultiValPGEditor():
wxPGChoiceEditor()//,
	//G3PGPropertyEditor()
{
}

G3EnumMultiValPGEditor::~G3EnumMultiValPGEditor() 
{

}
void G3EnumMultiValPGEditor::DrawValue(wxDC &dc, const wxRect &rect, wxPGProperty *property, const wxString &text) const 
{	
	if(property->GetAttribute("sameValues"))
	{
		wxPGChoiceEditor::DrawValue(dc, rect, property, text);
	}
	else
	{
		//dc.GradientFillLinear(rect, wxColour(0,210,210), wxColour(160,160,160), wxWEST);	
		//dc.GradientFillLinear(rect, wxColour(162,95,95), wxColour(246,138,138), wxEAST);
		dc.SetBrush(wxBrush(wxColour("#4ed2f3")));
		//dc.DrawRectangle(rect);
		dc.DrawRectangle(wxRect(rect.x-2, rect.y-4, rect.GetWidth()+4, rect.GetHeight()+8));
		dc.DrawLabel(_("(Mixed)"), rect);
	}
}

//////////////////////////////////////////////////////////////////////////

G3CustomMultiButtonPGEditor::G3CustomMultiButtonPGEditor():
wxPGTextCtrlEditor()//,
	//G3PGPropertyEditor()
{
	//	wxMessageBox(_("constr"));
}

G3CustomMultiButtonPGEditor::~G3CustomMultiButtonPGEditor() 
{
	//wxMessageBox(_("destr"));
}

wxPGWindowList G3CustomMultiButtonPGEditor::CreateControls( wxPropertyGrid* propGrid, wxPGProperty* property, 
	const wxPoint& pos, const wxSize& sz ) const
{	
	//wxMessageBox(_("createcontrols"));

	// If has children, and limited editing is specified, then don't create.
	if ( (property->GetFlags() & wxPG_PROP_NOEDITOR) &&
		property->GetChildCount() )
		return NULL;

	wxPGButtonEditorManager* buttons = new wxPGButtonEditorManager( propGrid, sz );

	// Add two regular buttons
	buttons->AddButton( wxArtProvider::GetBitmap(wxART_GO_BACK), 0 );
	buttons->AddButton( "..." , 2);	
	buttons->AddToggleButton( "E", 3 );//->SetValue((int)m_pUserData);
	// Add a bitmap button
	buttons->AddButton( wxArtProvider::GetBitmap(wxART_FOLDER), 4 );


	// Create the 'primary' editor control (textctrl in this case)
	//wxPGWindowList wndList = wxPGTextCtrlEditor::CreateControls ( propGrid, property, pos, buttons->GetPrimarySize() );
	wxPGWindowList wndList;
	// 	 	wxString text;
	// 	 	int argFlags = 0;
	// 	 	if ( !property->HasFlag(wxPG_PROP_READONLY) &&
	// 	 		!property->IsValueUnspecified() )
	// 	 		argFlags |= wxPG_EDITABLE_VALUE;
	// 	 	text = property->GetValueAsString(argFlags);
	// 	 	int flags = 0;
	// 	 	if ( (property->GetFlags() & wxPG_PROP_PASSWORD) &&
	// 	 		wxDynamicCast(property, wxStringProperty) )
	// 	 		flags |= wxTE_PASSWORD;
	// 	 	wndList.m_primary=propGrid->GenerateEditorTextCtrl(pos,sz,text,NULL,flags,
	// 	 		property->GetMaxLength());

	//dziala
	//g³ówna kontrolka pojawiajaca siê po kliknieciu w property
	wxString text;
	int argFlags = 0;
	if ( !property->HasFlag(wxPG_PROP_READONLY) &&
		!property->IsValueUnspecified() )
		argFlags |= wxPG_EDITABLE_VALUE;
	text = property->GetValueAsString(argFlags);
	int flags = 0;
	if ( (property->GetFlags() & wxPG_PROP_PASSWORD) &&
		wxDynamicCast(property, wxStringProperty) )
		flags |= wxTE_PASSWORD;
	wndList.m_primary=new wxTextCtrl(propGrid, -1, _(""), pos,buttons->GetPrimarySize()/*sz*/, flags);

	wxVariant propValue=property->GetValue();

	//wxMessageBox(propValue.GetType());
	// 	wxSlider *wndSlider=new wxSlider(propGrid, -1, 4, 0, 10, pos, wxSize(buttons->GetPrimarySize().GetWidth(), sz.GetHeight()),
	// 		wxSL_HORIZONTAL, wxDefaultValidator, _("slider"));
	// 	
	// 	int curval=property->GetValue().GetLong();
	// 	int minrange=property->GetAttribute(wxPG_ATTR_MIN).GetInteger();
	// 	int maxrange=property->GetAttribute(wxPG_ATTR_MAX).GetInteger();
	// 	//wxMessageBox(wxString::Format("val %i, min %i, max %i", curval, minrange, maxrange));
	// 	wndSlider->SetValue(curval);
	// 	wndSlider->SetRange(minrange, maxrange);
	// 	wndList.m_primary=wndSlider;
	//wndList.m_primary=0;


	// Finally, move buttons-subwindow to correct position and make sure
	// returned wxPGWindowList contains our custom button list.
	// jesli brak dodatkowych buttonow to zakomentowac
	buttons->Finalize(propGrid, pos);






	wndList.SetSecondary( buttons );
	// jesli brak dodatkowych buttonow to zakomentowac
	//wndList.SetSecondary( 0);

	return wndList;
}

// void G3CustomMultiButtonPGEditor::UpdateControl(wxPGProperty *prop, wxWindow *wnd) const
// {
// }


bool G3CustomMultiButtonPGEditor::OnEvent( wxPropertyGrid* propGrid, wxPGProperty* property, wxWindow* ctrl, wxEvent& event ) const
{

	G3PropertyGrid *g3propGrid=(G3PropertyGrid *) propGrid;
	if(g3propGrid)
	{
		if(event.GetEventType() == wxEVT_COMMAND_BUTTON_CLICKED)
		{
			g3propGrid->ProcessButtonEventEditor(ctrl->GetId(), property);
		}

		if(event.GetEventType() == wxEVT_COMMAND_TOGGLEBUTTON_CLICKED)
		{
			g3propGrid->ProcessToggleButtonEventEditor(ctrl->GetId(), property);
		}

		//m_pProperty to nasze prop przekazywane prze konstruktor edytora podczas dodawania edytora do property w g3propgrid
		//G3PropertyGridEvent eventButton( G3_EVT_PROPERTYGRID_PROPERTY_BUTTON, GetId(), m_pProperty, 1);
		//LUB
		// 		G3PropertyGridEvent eventButton( G3_EVT_PROPERTYGRID_PROPERTY_BUTTON, 0, property, ctrl->GetId());
		// 		eventButton.SetEventObject(g3propGrid);
		// 		propGrid->GetEventHandler()->ProcessEvent(eventButton);
		//wxMessageBox("asas");
		return true;
	}




	if ( event.GetEventType() == wxEVT_SCROLL_CHANGED)
	{
		//wxMessageBox(ctrl->GetName());
		wxVariant variangValue=property->GetValue();
		if(!variangValue.IsNull())
		{
			wxSlider *wndSlider=(wxSlider *) ctrl;
			property->SetValue(wndSlider->GetValue());
			//wxMessageBox(wxString::Format("%i", variangValue.GetLong()));
			//wxMessageBox(wxString::Format("%i", wndSlider->GetValue()));  //OK POBIERA DOBRZE AKTUALNY STAN SLIDERA
		}
	}

	if ( event.GetEventType() == wxEVT_COMMAND_TOGGLEBUTTON_CLICKED )
	{
		wxToggleButton *toggleButton=(wxToggleButton *) ctrl;


		if(ctrl->GetId()==3)
			/*if ( event.GetId() == buttons->GetButtonId(1) )*/
		{
			wxMessageBox(_("togglebtn"));
			return false;
		}
	}

	if ( event.GetEventType() == wxEVT_COMMAND_BUTTON_CLICKED/*wxEVT_BUTTON*/ )
	{
		//wxMessageBox(wxString::Format("%i", event.GetId()));

		//	wxPGG3Button* buttons = (wxPGG3Button*) propGrid->GetEditorControlSecondary();

		if(ctrl->GetId()==0)
			//if ( event.GetId() == buttons->GetButtonId(0) )
		{
			// Do something when the first button is pressed
			// Return true if the action modified the value in editor.
			//...
			wxMessageBox(_("<-"));
			//event.Skip();
			return true;
		}

		if(ctrl->GetId()==2)
			//if ( event.GetId() == buttons->GetButtonId(0) )
		{
			// Do something when the first button is pressed
			// Return true if the action modified the value in editor.
			//...
			wxMessageBox(_("..."));
			//event.Skip();
			return true;
		}





		if(ctrl->GetId()==4)
			//if ( event.GetId() == buttons->GetButtonId(5) )
		{
			// 			wxWindow *wndBtn=ctrl;
			// 
			// 			SimpleTransientPopup *m_simplePopup;
			// 			m_simplePopup = new SimpleTransientPopup( wndBtn );
			// 
			// 			wxPoint pos = wndBtn->ClientToScreen( wxPoint(0,0) );
			// 			wxSize sz = wndBtn->GetSize();
			// 			m_simplePopup->Position( pos, sz );			
			// 			m_simplePopup->Popup();
			return true;
		}
	}
	return true;
	//return wxPGTextCtrlEditor::OnEvent(propGrid, property, ctrl, event);






	//Return true if the action modified the value in editor.
}

void G3CustomMultiButtonPGEditor::DrawValue(wxDC &dc, const wxRect &rect, wxPGProperty *property, const wxString &text) const 
{	
	//DOSTEPNE JESLI KLASA BAZOWA TEJ KLASY JEST WXPGTEXTCTRLEDITOR
	wxPGTextCtrlEditor::DrawValue(dc, rect, property, text);
	//dc.GradientFillLinear(rect, *wxRED, *wxYELLOW, wxNORTH);

	//dc.GradientFillLinear(rect, wxColour(160,160,160), wxColour(210,210,210));	
	//	dc.DrawText(_("Click to edit"), rect.GetLeft(), rect.GetTop());
}

//////////////////////////////////////////////////////////////////////////