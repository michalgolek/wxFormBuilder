#include "G3wxImageBrowser.h"

#include <wx/dnd.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/dc.h>
#include <wx/image.h>
#include <wx/graphics.h>
#include <wx/log.h> 

//using namespace Editor;

//----------------------------------------------------------------------------
// SimpleTransientPopup
//----------------------------------------------------------------------------
IMPLEMENT_CLASS(SimpleTransientPopup,wxPopupTransientWindow)
	// 
	BEGIN_EVENT_TABLE(SimpleTransientPopup,wxPopupTransientWindow)
	EVT_MOUSE_EVENTS( SimpleTransientPopup::OnMouse )
	// 	EVT_SIZE( SimpleTransientPopup::OnSize )
	// 	EVT_SET_FOCUS( SimpleTransientPopup::OnSetFocus )
	// 	EVT_KILL_FOCUS( SimpleTransientPopup::OnKillFocus )
	// 	EVT_BUTTON( Minimal_PopupButton, SimpleTransientPopup::OnButton )
	// 	EVT_SPINCTRL( Minimal_PopupSpinctrl, SimpleTransientPopup::OnSpinCtrl )
	END_EVENT_TABLE()

	SimpleTransientPopup::SimpleTransientPopup( wxWindow *parent )
	:wxPopupTransientWindow( parent )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxStaticText *text = new wxStaticText( this, wxID_ANY,
		wxT("wxPopupTransientWindow is a\n")
		wxT("wxPopupWindow which disappears\n")
		wxT("automatically when the user\n")
		wxT("clicks the mouse outside it or if it\n")
		wxT("(or its first child) loses focus in \n")
		wxT("any other way.") );

	bSizer1->Add( text, 1, wxALL|wxEXPAND, 0 );


	bSizer1->Fit(this);

	//////////////////////////////////////////////////////////////////////////
	//SetSize(100,100);
	//Layout();

}

SimpleTransientPopup::~SimpleTransientPopup()
{
}

void SimpleTransientPopup::Popup(wxWindow* WXUNUSED(focus))
{
	//wxLogMessage( wxT("0x%lx SimpleTransientPopup::Popup"), long(this) );
	wxPopupTransientWindow::Popup();
}

void SimpleTransientPopup::OnDismiss()
{
	//wxLogMessage( wxT("0x%lx SimpleTransientPopup::OnDismiss"), long(this) );
	wxPopupTransientWindow::OnDismiss();
}

bool SimpleTransientPopup::ProcessLeftDown(wxMouseEvent& event)
{
	//wxLogMessage( wxT("0x%lx SimpleTransientPopup::ProcessLeftDown pos(%d, %d)"), long(this), event.GetX(), event.GetY());
	return wxPopupTransientWindow::ProcessLeftDown(event);
}
bool SimpleTransientPopup::Show( bool show )
{
	//wxLogMessage( wxT("0x%lx SimpleTransientPopup::Show %d"), long(this), int(show));
	return wxPopupTransientWindow::Show(show);
}

void SimpleTransientPopup::OnSize(wxSizeEvent &event)
{
	//wxLogMessage( wxT("0x%lx SimpleTransientPopup::OnSize"), long(this) );
	event.Skip();
}

void SimpleTransientPopup::OnSetFocus(wxFocusEvent &event)
{
	//wxLogMessage( wxT("0x%lx SimpleTransientPopup::OnSetFocus"), long(this) );
	event.Skip();
}

void SimpleTransientPopup::OnKillFocus(wxFocusEvent &event)
{
	//wxLogMessage( wxT("0x%lx SimpleTransientPopup::OnKillFocus"), long(this) );
	event.Skip();
}

void SimpleTransientPopup::OnMouse(wxMouseEvent &event)
{
	//if(event.GetEventType() == wxEVT_MOTION)
	//	Dismiss ();
	// 	wxRect rect(m_mouseText->GetRect());
	// 	rect.SetX(-100000);
	// 	rect.SetWidth(1000000);
	// 	wxColour colour(*wxLIGHT_GREY);
	// 
	// 	if (rect.Contains(event.GetPosition()))
	// 	{
	// 		colour = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT);
	// 		//wxLogMessage( wxT("0x%lx SimpleTransientPopup::OnMouse pos(%d, %d)"),
	// 		//	long(event.GetEventObject()), event.GetX(), event.GetY());
	// 	}
	// 
	// 	if (colour != m_mouseText->GetBackgroundColour())
	// 	{
	// 		m_mouseText->SetBackgroundColour(colour);
	// 		m_mouseText->Refresh();
	//}
	event.Skip();
}

void SimpleTransientPopup::OnButton(wxCommandEvent& event)
{
	//wxLogMessage( wxT("0x%lx SimpleTransientPopup::OnButton ID %d"), long(this), event.GetId());

	// 	wxButton *button = wxDynamicCast(event.GetEventObject(), wxButton);
	// 	if (button->GetLabel() == wxT("Press Me"))
	// 		button->SetLabel(wxT("Pressed"));
	// 	else
	// 		button->SetLabel(wxT("Press Me"));

	event.Skip();
}

void SimpleTransientPopup::OnSpinCtrl(wxSpinEvent& event)
{
	//wxLogMessage( wxT("0x%lx SimpleTransientPopup::OnSpinCtrl ID %d Value %d"),
	//	long(this), event.GetId(), event.GetInt());
	event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(G3ImageBrowser, wxPanel);

IMPLEMENT_DYNAMIC_CLASS(G3ImageBrowserEvent, wxNotifyEvent);

DEFINE_EVENT_TYPE(G3_EVT_IMAGEBROWSER_ITEM_SELECTED)
	DEFINE_EVENT_TYPE(G3_EVT_IMAGEBROWSER_ITEM_BEGIN_DRAGGED)
	DEFINE_EVENT_TYPE(G3_EVT_IMAGEBROWSER_ITEM_END_DRAGGED)
	DEFINE_EVENT_TYPE(G3_EVT_IMAGEBROWSER_ITEM_RCLICK)
	DEFINE_EVENT_TYPE(G3_EVT_IMAGEBROWSER_ITEM_MORE_CLICK)

	// statyczne eventy, jesli uzywamy dynamicznych(Connect,Bind) to zakomentowac TABLE
	// BEGIN_EVENT_TABLE( G3ImageBrowser, wxPanel )
	// //EVT_G3_TABLE_(G3_EVT_IMAGEBROWSER_ITEM_SELECTED, wxID_ANY, G3ImageBrowser::OnImageBrowserEvent)
	// EVT_G3_IMAGEBROWSER_ITEM_SELECTED(wxID_ANY, G3ImageBrowser::OnImageBrowserEvent )
	// EVT_G3_IMAGEBROWSER_ITEM_BEGIN_DRAGGED(wxID_ANY, G3ImageBrowser::OnImageBrowserEvent )
	// EVT_G3_IMAGEBROWSER_ITEM_END_DRAGGED(wxID_ANY, G3ImageBrowser::OnImageBrowserEvent )
	// END_EVENT_TABLE


	G3ImageBrowserItem::G3ImageBrowserItem():
m_strText(_("")), m_pImage(NULL), m_pUserData(NULL), m_pBitmap(NULL), m_bUseCheckboard4Alpha(false), m_strTextDetails(_("")), m_strTextDetails2(_(""))
{
}

G3ImageBrowserItem::G3ImageBrowserItem(const wxString &name, wxImage *image, const wxString &detailText, void *user):
m_strText(name), m_pUserData(user), m_pImage(image), m_bUseCheckboard4Alpha(false), m_strTextDetails(detailText), m_strTextDetails2(_(""))
{		
}

G3ImageBrowserItem::G3ImageBrowserItem(const wxString &name, wxImage *image, const wxString &detailText, const wxString &detail2Text, void *user):
m_strText(name), m_pUserData(user), m_pImage(image), m_bUseCheckboard4Alpha(false), m_strTextDetails(detailText), m_strTextDetails2(detail2Text)
{		
}

G3ImageBrowserItem::G3ImageBrowserItem(const wxString &name, wxImage *image, const wxString &detailText, bool backgroundCheckboard, void *user):
m_strText(name), m_pImage(image), m_bUseCheckboard4Alpha(backgroundCheckboard), m_pUserData(user), m_strTextDetails(detailText), m_strTextDetails2(_(""))
{

}

G3ImageBrowserItem::~G3ImageBrowserItem()
{

}

wxBitmap *G3ImageBrowserItem::GetBitmap() const
{
	return m_pBitmap;
}

wxString G3ImageBrowserItem::GetText() const
{
	return m_strText;
}

wxString G3ImageBrowserItem::GetTextDetail() const
{
	return m_strTextDetails;
}

wxString G3ImageBrowserItem::GetTextDetail2() const
{
	return m_strTextDetails2;
}

void G3ImageBrowserItem::SetText(const wxString &text)
{
	m_strText=text;
}

wxImage *G3ImageBrowserItem::GetImage() const
{
	return m_pImage;
}

void *G3ImageBrowserItem::GetUserData() const
{
	return m_pUserData;
}

G3ImageBrowser::G3ImageBrowser()
{

}

G3ImageBrowser::G3ImageBrowser( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ):
//wxPanel(parent, wxID_ANY,pos, size, style),
wxScrolledWindow(parent, id, pos, size, wxScrolledWindowStyle|style),
	m_pSelectedItem(NULL),
	m_pPreviousSelectedItem(NULL),
	m_checkboardColor1(wxColour(220, 220, 220)),
	m_checkboardColor2(wxColour(50, 50, 50)),	
	m_selectedFrameColour(*wxGREEN),
	m_selectedFrameWidth(1),
	m_labelColour(*wxWHITE),
	m_selectedLabelColour(*wxWHITE),
	m_selectedLabelBgColour(wxColor(0, 0, 128)),
	m_labelHeight(0),
	m_imageSize(wxSize(100, 100)),
	m_itemSpace(wxSize(0, 0)),
	m_bLeftDown(false),
	m_iBackGroundStyle(0),
	m_iViewMode(G3_IBVM_VIEWTHUMBNAILS),
	m_popupTime(0),
	m_mouseOverPos(wxPoint(-1, -1))

{
	m_timerTooltip.Start(1000);
	m_timerTooltip.SetOwner(this);
	this->Connect( wxEVT_TIMER, wxTimerEventHandler( G3ImageBrowser::OnTimer ), NULL, this );


	m_simplePopup = NULL;

	//http://wiki.wxwidgets.org/Drawing_on_a_panel_with_a_DC
	SetDoubleBuffered(true);

	SetScrollRate(5, 5);

	//////////////////////////////////////////////////////////////////////////

	// Connect Events	
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3ImageBrowser::OnLeftDown ), NULL, this );
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( G3ImageBrowser::OnLeftUp ), NULL, this );
	this->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( G3ImageBrowser::OnRightDown ), NULL, this );
	this->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( G3ImageBrowser::OnRightUp ), NULL, this );
	this->Connect( wxEVT_MOTION, wxMouseEventHandler( G3ImageBrowser::OnMotion ), NULL, this );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( G3ImageBrowser::OnPaint ), NULL, this );	

	this->Connect( wxEVT_SIZE, wxSizeEventHandler( G3ImageBrowser::OnSize ), NULL, this );	
	this->Connect( wxID_ANY, G3_EVT_IMAGEBROWSER_ITEM_SELECTED, G3ImageBrowserEventHandler( G3ImageBrowser::OnImageBrowserEvent ));
	this->Connect( wxID_ANY, G3_EVT_IMAGEBROWSER_ITEM_BEGIN_DRAGGED, G3ImageBrowserEventHandler( G3ImageBrowser::OnImageBrowserEvent ) );
	this->Connect( wxID_ANY, G3_EVT_IMAGEBROWSER_ITEM_END_DRAGGED, G3ImageBrowserEventHandler( G3ImageBrowser::OnImageBrowserEvent ) );
	this->Connect( wxID_ANY, G3_EVT_IMAGEBROWSER_ITEM_RCLICK, G3ImageBrowserEventHandler( G3ImageBrowser::OnImageBrowserEvent ) );
	this->Connect( wxID_ANY, G3_EVT_IMAGEBROWSER_ITEM_MORE_CLICK, G3ImageBrowserEventHandler( G3ImageBrowser::OnImageBrowserEvent ) );	

	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_THUMBTRACK, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);
	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_THUMBRELEASE, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);
	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_LINEUP, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);
	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_LINEDOWN, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);
	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_BOTTOM, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);
	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_PAGEUP, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);
	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_PAGEDOWN, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);
	//////////////////////////////////////////////////////////////////////////
	m_labelFont=wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier 10 Pitch");
	m_detailFont=wxFont(7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial");
	m_detail2Font=wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial");

	SetLabelFont(m_labelFont);
	SetDetailFont(m_detailFont);
	SetDetail2Font(m_detail2Font);
}


G3ImageBrowser::~G3ImageBrowser()
{
	// Disconnect Events
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3ImageBrowser::OnLeftDown ), NULL, this );
	this->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( G3ImageBrowser::OnLeftUp ), NULL, this );
	this->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( G3ImageBrowser::OnRightDown ), NULL, this );
	this->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( G3ImageBrowser::OnRightUp ), NULL, this );
	this->Disconnect( wxEVT_MOTION, wxMouseEventHandler( G3ImageBrowser::OnMotion ), NULL, this );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( G3ImageBrowser::OnPaint ), NULL, this );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( G3ImageBrowser::OnSize ), NULL, this );

	this->Disconnect( wxID_ANY, G3_EVT_IMAGEBROWSER_ITEM_SELECTED, G3ImageBrowserEventHandler( G3ImageBrowser::OnImageBrowserEvent ) );
	this->Disconnect( wxID_ANY, G3_EVT_IMAGEBROWSER_ITEM_BEGIN_DRAGGED, G3ImageBrowserEventHandler( G3ImageBrowser::OnImageBrowserEvent ) );
	this->Disconnect( wxID_ANY, G3_EVT_IMAGEBROWSER_ITEM_END_DRAGGED, G3ImageBrowserEventHandler( G3ImageBrowser::OnImageBrowserEvent ) );
	this->Disconnect( wxID_ANY, G3_EVT_IMAGEBROWSER_ITEM_RCLICK, G3ImageBrowserEventHandler( G3ImageBrowser::OnImageBrowserEvent ) );
	this->Disconnect( wxID_ANY, G3_EVT_IMAGEBROWSER_ITEM_MORE_CLICK, G3ImageBrowserEventHandler( G3ImageBrowser::OnImageBrowserEvent ) );	

	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_THUMBTRACK, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_THUMBRELEASE, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_LINEUP, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_LINEDOWN, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_BOTTOM, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_PAGEUP, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_PAGEDOWN, wxScrollWinEventHandler(G3ImageBrowser::OnScrollWinEvents), NULL, this);

	//////////////////////////////////////////////////////////////////////////
	ClearAll();

	this->Disconnect( wxEVT_TIMER, wxTimerEventHandler( G3ImageBrowser::OnTimer ), NULL, this );
}

void G3ImageBrowser::RecalcVirtualSize()
{
	m_virtualSize.x=0;
	m_virtualSize.y=0;

	switch(m_iViewMode)
	{
	case G3_IBVM_VIEWTHUMBNAILS:
		{
			for(int i=0;i<m_itemList.size();i++)
			{
				m_virtualSize.x+=m_imageSize.GetWidth()+m_itemSpace.GetWidth();
				if(m_virtualSize.x+m_imageSize.GetWidth()/*/1.5*/>m_canvasSize.GetWidth())
				{
					m_virtualSize.x=0;
					m_virtualSize.y+=m_imageSize.GetHeight()+m_labelHeight+m_itemSpace.GetHeight();
				}
			}

			m_virtualSize.y+=m_imageSize.GetHeight()+m_labelHeight+m_itemSpace.GetHeight();
		}
		break;
	case G3_IBVM_VIEWDETAILS:
		{
			m_virtualSize.x=m_canvasSize.GetWidth();
			m_virtualSize.y=0;

			for(int i=0;i<m_itemList.size();i++)
				m_virtualSize.y+=m_imageSize.GetHeight()+m_itemSpace.GetHeight();
		}
		break;
	case G3_IBVM_VIEWLIST:
		{
			m_virtualSize.x=m_itemSpace.GetWidth();
			m_virtualSize.y=0;

			for(int i=0;i<m_itemList.size();i++)
				m_virtualSize.y+=m_labelHeight*4;
		}
		break;
	case G3_IBVM_VIEWSINLELIST:
		{
			m_virtualSize.x=0;
			m_virtualSize.y=m_canvasSize.GetHeight();

			for(int i=0;i<m_itemList.size();i++)
				m_virtualSize.x+=GetClientSize().GetHeight()+m_itemSpace.GetWidth();
		}
		break;
	}

	if(m_itemList.size()>0)
	{
		m_virtualSize=wxSize(m_virtualSize.x, m_virtualSize.y);
	}	
}

void G3ImageBrowser::OnScrollWinEvents(wxScrollWinEvent& event)
{
	switch(m_iViewMode)
	{
	case G3_IBVM_VIEWTHUMBNAILS:

		if(event.GetOrientation()==wxVERTICAL)
		{			
			m_scrollPos.y=event.GetPosition();

			// 			if(event.GetEventType()==wxEVT_SCROLLWIN_LINEUP)
			// 			{			
			// 				scrollPos.y-=25;
			// 				if(scrollPos.y<0)
			// 					scrollPos.y=0;
			// 			}
			// 			else
			// 				if(event.GetEventType()==wxEVT_SCROLLWIN_LINEDOWN)
			// 				{
			// 					scrollPos.y+=25;
			// 					if(scrollPos.y>=m_virtualSize.GetHeight()-m_virtualSize.GetWidth())
			// 						scrollPos.y=m_virtualSize.GetHeight()-m_virtualSize.GetWidth();
			// 				}
			// 				else
			// 					scrollPos.y = event.GetPosition();



			//aktualizacja kontrolki scrollbar
			Scroll(m_scrollPos.x, event.GetPosition());
			//SetScrollbar(wxVERTICAL, scrollPos.y, m_virtualSize.GetWidth(), m_virtualSize.GetHeight());
		}
		break;
	case G3_IBVM_VIEWDETAILS:
		if(event.GetOrientation()==wxVERTICAL)
		{
			m_scrollPos.y=event.GetPosition();

			// 			if(event.GetEventType()==wxEVT_SCROLLWIN_LINEUP)
			// 			{			
			// 				scrollPos.y-=25;
			// 				if(scrollPos.y<0)
			// 					scrollPos.y=0;
			// 			}
			// 			else
			// 				if(event.GetEventType()==wxEVT_SCROLLWIN_LINEDOWN)
			// 				{
			// 					scrollPos.y+=25;
			// 					if(scrollPos.y>=m_virtualSize.GetHeight()-m_virtualSize.GetWidth())
			// 						scrollPos.y=m_virtualSize.GetHeight()-m_virtualSize.GetWidth();
			// 				}
			// 				else
			// 					scrollPos.y = event.GetPosition();

			//aktualizacja kontrolki scrollbar
			//SetScrollbar(wxVERTICAL, scrollPos.y, m_virtualSize.GetWidth(), m_virtualSize.GetHeight());
			//Scroll (scrollPos.x, scrollPos.y);
			Scroll(m_scrollPos.x, event.GetPosition());
		}
		break;
	case G3_IBVM_VIEWLIST:
		if(event.GetOrientation()==wxVERTICAL)
		{
			m_scrollPos.y=event.GetPosition();

			// 			scrollPos.x = event.GetPosition();
			// 
			// 			if(event.GetEventType()==wxEVT_SCROLLWIN_LINEUP)
			// 			{			
			// 				scrollPos.x-=25;
			// 				if(scrollPos.x<0)
			// 					scrollPos.x=0;
			// 			}
			// 			else
			// 				if(event.GetEventType()==wxEVT_SCROLLWIN_LINEDOWN)
			// 				{
			// 					scrollPos.x+=25;
			// 					if(scrollPos.x>=m_virtualSize.GetWidth()-m_virtualSize.GetHeight())
			// 						scrollPos.x=m_virtualSize.GetWidth()-m_virtualSize.GetHeight();
			// 				}
			// 				else
			// 					scrollPos.x = event.GetPosition();

			//aktualizacja kontrolki scrollbar
			//SetScrollbar(wxHORIZONTAL, scrollPos.x, m_virtualSize.GetWidth(), m_virtualSize.GetHeight());		
			//Scroll(scrollPos.x, scrollPos.y);
			Scroll(m_scrollPos.x, event.GetPosition());

		}
		break;
	case G3_IBVM_VIEWSINLELIST:
		if(event.GetOrientation()==wxHORIZONTAL)
		{
			m_scrollPos.x=event.GetPosition();

			// 			scrollPos.x = event.GetPosition();
			// 
			// 			if(event.GetEventType()==wxEVT_SCROLLWIN_LINEUP)
			// 			{			
			// 				scrollPos.x-=25;
			// 				if(scrollPos.x<0)
			// 					scrollPos.x=0;
			// 			}
			// 			else
			// 				if(event.GetEventType()==wxEVT_SCROLLWIN_LINEDOWN)
			// 				{
			// 					scrollPos.x+=25;
			// 					if(scrollPos.x>=m_virtualSize.GetWidth()-m_virtualSize.GetHeight())
			// 						scrollPos.x=m_virtualSize.GetWidth()-m_virtualSize.GetHeight();
			// 				}
			// 				else
			// 					scrollPos.x = event.GetPosition();

			//aktualizacja kontrolki scrollbar
			//SetScrollbar(wxHORIZONTAL, scrollPos.x, m_virtualSize.GetWidth(), m_virtualSize.GetHeight());		
			//Scroll(scrollPos.x, scrollPos.y);
			Scroll(event.GetPosition(), m_scrollPos.y);

		}
		break;
	}

	Refresh();
	//m_imageBrowserPanel->Refresh();
}

void G3ImageBrowser::OnTimer(wxTimerEvent& event)
{
	m_popupTime++;
	if(m_popupTime==1)
	{
		if(m_simplePopup)
		{
			if(m_simplePopup->IsShown())
				return;
		}		

		if(m_mouseOverPos.x!=-1 && m_mouseOverPos.y!=-1)
		{
			if(m_simplePopup)
				delete m_simplePopup;
			m_simplePopup = new SimpleTransientPopup( this );

			POINT ps;
			GetCursorPos(&ps);
			//m_simplePopup->Position(wxPoint(ps.x, ps.y)/* this->ClientToScreen(m_mouseOverPos)*/, wxSize(100, 100) );
			m_simplePopup->Position(this->GetParent()->ClientToScreen(m_mouseOverPos), wxSize(100, 100) );


			//wxLogMessage( wxT("0x%lx Simple Popup Shown pos(%d, %d) size(%d, %d)"), long(m_simplePopup), pos.x, pos.y, sz.x, sz.y );
			//m_simplePopup->Popup();			
		}		
	}	
}

void G3ImageBrowser::UpdateControl()
{
	wxSizeEvent sz(GetSize(), GetId());
	ProcessEvent(sz);
}

void G3ImageBrowser::SetCheckboardColour(const wxColour &color1, const wxColour &color2)
{
	m_checkboardColor1=color1;
	m_checkboardColor2=color2;

	UpdateControl();
}

void G3ImageBrowser::SetImageSize(wxSize size)
{
	m_imageSize=size;

	UpdateControl();
}

void G3ImageBrowser::SetItemSpace(wxSize space)
{
	m_itemSpace=space;

	UpdateControl();
}

void G3ImageBrowser::SetLabelFont(const wxFont &font)
{
	m_labelFont=font;

	wxMemoryDC memDC;
	memDC.SelectObject(wxNullBitmap);
	memDC.SetFont(m_labelFont);
	m_labelHeight=memDC.GetTextExtent(_T("AYj")).GetHeight();

	UpdateControl();
}

void G3ImageBrowser::SetDetailFont(const wxFont &font)
{
	m_detailFont=font;

	wxMemoryDC memDC;
	memDC.SelectObject(wxNullBitmap);
	memDC.SetFont(m_detailFont);
	m_labelHeight=memDC.GetTextExtent(_T("AYj")).GetHeight();

	UpdateControl();
}

void G3ImageBrowser::SetDetail2Font(const wxFont &font)
{
	m_detail2Font=font;

	wxMemoryDC memDC;
	memDC.SelectObject(wxNullBitmap);
	memDC.SetFont(m_detail2Font);
	m_labelHeight=memDC.GetTextExtent(_T("AYj")).GetHeight();

	UpdateControl();
}

void G3ImageBrowser::SetBgGradientColour1(const wxColour &colour)
{
	m_bgGradientColor1=colour;

	UpdateControl();
}

void G3ImageBrowser::SetBgGradientColour2(const wxColour &colour)
{
	m_bgGradientColor2=colour;

	UpdateControl();
}

void G3ImageBrowser::SetLabelColour(const wxColour &colour)
{
	m_labelColour=colour;

	UpdateControl();
}

void G3ImageBrowser::SetSelectedLabelColour(const wxColour &colour)
{
	m_selectedLabelColour=colour;

	UpdateControl();
}

void G3ImageBrowser::SetLabelGradientColour1(const wxColour &colour)
{
	m_labelBgGradientColour1=colour;

	UpdateControl();
}

void G3ImageBrowser::SetLabelGradientColour2(const wxColour &colour)
{
	m_labelBgGradientColour2=colour;

	UpdateControl();
}

void G3ImageBrowser::SetSelectedFrameColour(const wxColour &colour)
{
	m_selectedFrameColour=colour;

	UpdateControl();
}

void G3ImageBrowser::SetSelectedFrameWidth(int width)
{
	m_selectedFrameWidth=width;

	UpdateControl();
}

void G3ImageBrowser::SetSelectedLabelBgColour(const wxColour &colour)
{
	m_selectedLabelBgColour=colour;

	UpdateControl();
}

void G3ImageBrowser::SetViewMode(int mode)
{
	m_iViewMode=mode;

	// 	SetScrollPos(wxHORIZONTAL, 0, true);
	// 	SetScrollPos(wxVERTICAL, 0, true);
	//EnsureItemVisible(GetSelectedItem());
	Scroll(0, 0);

	UpdateControl();


	//wxMessageBox(wxString::Format("%i", mode));
}
// void G3ImageBrowser::AssignImageList(wxImageList *imageList, int which)
// {
// 	m_pImageList=imageList;
// }

// wxImageList *G3ImageBrowser::GetImageList(int which) const
// {
// 	return m_pImageList;
// }

int G3ImageBrowser::GetItemCount() const
{
	return m_itemList.size();
}

G3ImageBrowserItem *G3ImageBrowser::GetItemSelected() const
{
	return m_pSelectedItem;
}

void G3ImageBrowser::ClearAll()
{
	wxList::iterator it;
	for (it=m_itemList.begin();it!=m_itemList.end();++it)
	{
		delete (*it);
	}

	m_itemList.Clear();
}

void G3ImageBrowser::AddItem(G3ImageBrowserItem *item)
{
	wxASSERT_MSG(item, wxString::Format("Cannot add item to G3ImageBrowser - %s", GetName()));

	wxImage *pImage=item->GetImage();

	if(!item->m_bUseCheckboard4Alpha)
		goto additemend;

	wxSize checkboardStretch=wxSize(15, 15);

	if(pImage->HasAlpha())
	{
		wxSize imgSize=pImage->GetSize();

		for (int x=0;x<imgSize.GetWidth();x++)
		{
			for (int y=0;y<imgSize.GetHeight();y++)
			{
				float alpha=pImage->GetAlpha(x, y)/(float)255.0f;
				//alpha+=0.7f;
				if(alpha>1.0f)alpha=1.0f;

				alpha=1-alpha;

				int rSrc=pImage->GetRed(x, y);
				int gSrc=pImage->GetGreen(x, y);
				int bSrc=pImage->GetBlue(x, y);

				int xs=x/checkboardStretch.GetWidth();
				int ys=y/checkboardStretch.GetHeight();

				int rd=m_checkboardColor1.Red();
				int gd=m_checkboardColor1.Green();
				int bd=m_checkboardColor1.Blue();

				// floor zaokragla liczbe w dol do liczby calkowitej
				if ((int(floor((double)xs) + floor((double)ys)) & 1) == 0)					
				{
					rd=m_checkboardColor2.Red();
					gd=m_checkboardColor2.Green();
					bd=m_checkboardColor2.Blue();
				}

				int r=rSrc*( 1.0-alpha) + rd*alpha;
				int g=gSrc*( 1.0-alpha) + gd*alpha;
				int b=bSrc*( 1.0-alpha) + bd*alpha;

				pImage->SetRGB(x, y, r, g, b);
				pImage->SetAlpha(x, y, 255);
			}
		}
	}

additemend:
	item->m_pBitmap=new wxBitmap(*pImage);	

	//////////////////////////////////////////////////////////////////////////

	m_itemList.push_back(item);

	UpdateControl();
}

void  G3ImageBrowser::AddItem(wxImage *img, wxString &name, void *userData)
{
	wxASSERT_MSG(m_itemList.size(), wxT("G3ImageBrowser - unassigned image list"));
}

void G3ImageBrowser::RemoveItem(int index)
{
}

void G3ImageBrowser::RemoveItem(wxString &name)
{
}

void G3ImageBrowser::RemoveItem(G3ImageBrowserItem *item)
{
}

void G3ImageBrowser::OnSize( wxSizeEvent& event )
{
	m_canvasSize=GetClientSize();

	RecalcVirtualSize();

	m_scrollPos.x=GetViewStart().x;
	m_scrollPos.y=GetViewStart().y;

	if(m_scrollPos.y>m_virtualSize.GetHeight()-m_canvasSize.GetHeight())
		m_scrollPos.y=m_virtualSize.GetHeight()-m_canvasSize.GetHeight();

	if(m_virtualSize.GetHeight()<m_canvasSize.GetHeight())
		m_scrollPos.y=0;

	SetScrollbars(1, 1, m_virtualSize.GetWidth(), m_virtualSize.GetHeight(), m_scrollPos.x, m_scrollPos.y);

	//SetVirtualSize(m_virtualSize.GetWidth(), m_virtualSize.GetHeight());

	Refresh();
}

void G3ImageBrowser::OnPaint( wxPaintEvent& event )
{
	//wxPaintDC dc(m_imageBrowserPanel);
	wxPaintDC dc(this);
	wxGraphicsContext *gc = wxGraphicsContext::Create( dc );



	if(m_itemList.size()==0)
		return;

	int m_iDrawingOffsetX=0;
	int m_iDrawingOffsetY=0;

	// 	if(GetWindowStyleFlag() & G3_IB_STRETCH2HEIGHT)
	// 	{
	// 		m_imageSize.SetWidth(m_canvasSize.GetHeight());
	// 		m_imageSize.SetHeight(m_canvasSize.GetHeight()-m_labelHeight);
	// 	}

	// hmm udpate przy resizeowaniu ?
	// 	if(m_canvasPreviousSize!=m_canvasSize)
	// 	{
	// 		for(int i=0;i<m_itemList.size();i++)
	// 		{
	// 			m_iDrawingOffsetX+=m_imageSize.GetWidth()+m_itemSpace.GetWidth();
	// 			if(m_iDrawingOffsetX+m_imageSize.GetWidth()/2>m_canvasSize.GetWidth())
	// 			{
	// 				m_iDrawingOffsetX=0;
	// 				m_iDrawingOffsetY+=m_imageSize.GetHeight()+m_labelHeight+m_itemSpace.GetHeight();
	// 			}
	// 		}
	// 
	// 		if(m_iLayoutMode==0)
	// 			m_iDrawingOffsetY+=m_imageSize.GetHeight()+m_labelHeight+m_itemSpace.GetHeight();
	// 
	// 		if(m_itemList.size()>0)
	// 		{		
	// 			//clientSize=GetClientSize();
	// 
	// 			//	m_virtualSize=wxSize(m_itemList.size()*clientSize.GetHeight()-(clientSize.GetWidth()-clientSize.GetHeight()), clientSize.GetHeight());
	// 
	// 			m_virtualSize=wxSize(m_canvasSize.GetHeight(), m_iDrawingOffsetY);
	// 
	// 			m_imageBrowserPanel->SetSize(m_canvasSize.GetWidth(), m_iDrawingOffsetY);
	// 			bSizer1->Layout();
	// 			Layout();
	// 
	// 			scrollPos.x=GetScrollPos(wxHORIZONTAL);
	// 			scrollPos.y=GetScrollPos(wxVERTICAL);
	// 			SetScrollbar(wxVERTICAL, GetScrollPos(wxVERTICAL), m_virtualSize.GetWidth(), m_virtualSize.GetHeight());
	// 		}
	// 	}


	//m_imageSize=m_canvasSize;



	if(GetWindowStyleFlag() & G3_IB_GRADIENTBACKGROUND)
		dc.GradientFillLinear(m_canvasSize, m_bgGradientColor1, m_bgGradientColor2, wxSOUTH);

	//GetScrollPos()

	m_iDrawingOffsetX=-m_scrollPos.x;
	m_iDrawingOffsetY=-m_scrollPos.y;

	switch(m_iViewMode)
	{
	case G3_IBVM_VIEWTHUMBNAILS:
		for(int i=0;i<m_itemList.size();i++)
		{
			G3ImageBrowserItem *item=(G3ImageBrowserItem*) m_itemList[i];

			wxASSERT_MSG(item, "G3ImageBrowser - OnPaint Event: Invalid item pointer");

			wxBitmap bmp=*item->GetBitmap();

			wxMemoryDC memdc(&dc);

			memdc.SelectObject(bmp);
			dc.StretchBlit(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight(), &memdc, 0, 0, bmp.GetWidth(), bmp.GetHeight(), wxCOPY, false);			
			memdc.SelectObject(wxNullBitmap);

			dc.SetFont(m_labelFont);

			wxSize textSize=dc.GetTextExtent(item->GetText());

			dc.SetBrush(*wxBLACK_BRUSH);


			wxRect labelBgRect=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY+m_imageSize.GetHeight(),
				m_imageSize.GetWidth(), textSize.GetHeight());		

			// 		wxRect labelRect=wxRect(m_iDrawingOffsetX+m_imageSize.GetWidth()/2-textSize.GetWidth()/2,
			// 			m_iDrawingOffsetY+m_imageSize.GetHeight(),
			// 			textSize.GetWidth(), textSize.GetHeight());

			wxRect labelRect=wxRect(m_iDrawingOffsetX,
				m_iDrawingOffsetY+m_imageSize.GetHeight(),
				m_imageSize.GetWidth(), textSize.GetHeight());

			if(GetWindowStyleFlag() & G3_IB_SELECTED_RENDER_IN_FRAME)
			{
				labelRect=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY+m_imageSize.GetHeight(),
					m_imageSize.GetWidth(), textSize.GetHeight());
			}

			if(GetWindowStyleFlag() & G3_IB_FILLED_BACKGROUND_LABEL)
			{
				if(GetWindowStyleFlag() & G3_IB_GRADIENT_BG_LABEL)
					dc.GradientFillLinear(labelBgRect, m_labelBgGradientColour1, m_labelBgGradientColour2, wxSOUTH);
				else
					dc.GradientFillLinear(labelBgRect, m_labelBgGradientColour1, m_labelBgGradientColour1, wxSOUTH);
			}

			if(m_pSelectedItem)
			{
				if(m_pSelectedItem==item)
				{
					if(GetWindowStyleFlag() & G3_IB_SELECTED_RENDER_IN_FRAME)
					{
						dc.SetPen(wxPen(m_selectedFrameColour, m_selectedFrameWidth));
						//dc.SetBrush(*wxTRANSPARENT_BRUSH);
						dc.SetBrush(wxBrush(*wxRED, wxBRUSHSTYLE_TRANSPARENT));
						dc.DrawRectangle(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight());
					}
					else
					{
						dc.SetPen(m_selectedLabelBgColour);
						dc.SetBrush(*wxTRANSPARENT_BRUSH);
						dc.DrawRectangle(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight());

						dc.SetPen(*wxTRANSPARENT_PEN);
						dc.SetBrush(m_selectedLabelBgColour);
						dc.DrawRectangle(labelRect);
					}			
				}
			}

			dc.SetFont(wxFont(7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier 10 Pitch"));
			dc.SetTextForeground(wxColour(220, 220, 220));
			wxString topString(_("Mesh"));
			wxSize topTextSize=dc.GetTextExtent(topString);
			wxRect typeLabelRect(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), topTextSize.GetHeight());
			dc.DrawLabel(_("Mesh"), typeLabelRect, wxALIGN_CENTER);


			dc.SetTextForeground(m_labelColour);

			if(m_pSelectedItem && !(GetWindowStyleFlag() & G3_IB_SELECTED_RENDER_IN_FRAME))
			{
				if(m_pSelectedItem==item)
					dc.SetTextForeground(m_selectedLabelColour);
			}

			// 		if(m_iLayoutMode==0)
			// 			dc.DrawText(item->GetText(), 
			// 			m_iDrawingOffsetX+m_imageSize.GetWidth()/2-textSize.GetWidth()/2, 
			// 			m_iDrawingOffsetY+m_imageSize.GetHeight());
			// 		else
			// 			dc.DrawText(item->GetText(), 
			// 			m_iDrawingOffsetX+m_imageSize.GetWidth()/2-textSize.GetWidth()/2, 
			// 			m_iDrawingOffsetY+m_imageSize.GetHeight()-textSize.GetHeight());
			//if(m_iLayoutMode==0)

			dc.SetClippingRegion(labelRect);
			wxRect labelRect2=labelRect;
			labelRect2.Deflate(2, 0);
			dc.DrawLabel(item->GetText(), labelRect2, textSize.GetWidth()>m_imageSize.GetWidth()?wxALIGN_LEFT:wxALIGN_CENTER);
			dc.DestroyClippingRegion();	



			m_iDrawingOffsetX+=m_imageSize.GetWidth()+m_itemSpace.GetWidth();
			if(m_iDrawingOffsetX+m_imageSize.GetWidth()/*/1.5*/>m_canvasSize.GetWidth())
			{
				m_iDrawingOffsetX=0;
				m_iDrawingOffsetY+=m_imageSize.GetHeight()+m_labelHeight+m_itemSpace.GetHeight();
			}	
		}
		break;
	case G3_IBVM_VIEWDETAILS:
		m_imageSize.SetWidth(m_imageSize.GetHeight());
		m_imageSize.SetHeight(m_imageSize.GetHeight());

		for(int i=0;i<m_itemList.size();i++)
		{
			G3ImageBrowserItem *item=(G3ImageBrowserItem*) m_itemList[i];

			wxASSERT_MSG(item, "G3ImageBrowser - OnPaint Event: Invalid item pointer");

			//if(GetWindowStyleFlag() & G3_IB_ITEM2BACKGROUND)
			{
				dc.SetPen(*wxTRANSPARENT_PEN);
				//dc.SetBrush(*wxTRANSPARENT_BRUSH);
				dc.SetBrush(wxBrush(i%2?wxColour(120, 120, 120):wxColour(125, 125,125)));
				dc.DrawRectangle(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_canvasSize.GetHeight());
			}			



			if(m_pSelectedItem)
			{
				if(m_pSelectedItem==item)
				{
					// 					dc.SetPen(wxPen(m_selectedFrameColour, m_selectedFrameWidth));
					// 					//dc.SetBrush(*wxTRANSPARENT_BRUSH);
					// 					dc.SetBrush(wxBrush(*wxRED, wxBRUSHSTYLE_TRANSPARENT));
					// 					dc.DrawRectangle(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight());
					// 
					// 					wxRect selectRect;
					// 					selectRect.SetTop(m_iDrawingOffsetY);
					// 					selectRect.SetLeft(0);
					// 					selectRect.SetWidth(m_canvasSize.GetWidth());
					// 					selectRect.SetHeight((m_imageSize.GetHeight())/2);
					// 					dc.GradientFillLinear(selectRect, m_bgGradientColor1, m_bgGradientColor2, wxNORTH);
					// 
					// 					selectRect.SetTop(m_iDrawingOffsetY+m_imageSize.GetHeight()/2);
					// 					selectRect.SetHeight(m_imageSize.GetHeight()/2);
					// 					dc.GradientFillLinear(selectRect, m_bgGradientColor1, m_bgGradientColor2, wxSOUTH);



					//

					wxRect rectList(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_imageSize.GetHeight()+m_itemSpace.GetHeight());

					dc.SetPen(*wxTRANSPARENT_PEN);
					//dc.SetBrush(*wxTRANSPARENT_BRUSH);
					dc.SetBrush(wxBrush(m_selectedLabelBgColour));
					dc.DrawRectangle(rectList);
				}
			}
			wxBitmap bmp=*item->GetBitmap();

			wxMemoryDC memdc(&dc);

			memdc.SelectObject(bmp);
			dc.StretchBlit(m_itemSpace.GetWidth()+m_iDrawingOffsetX, m_itemSpace.GetHeight()+m_iDrawingOffsetY, m_imageSize.GetWidth()-m_itemSpace.GetWidth()*2, m_imageSize.GetHeight()-m_itemSpace.GetHeight()*2, &memdc, 0, 0, bmp.GetWidth(), bmp.GetHeight(), wxCOPY, false);			
			memdc.SelectObject(wxNullBitmap);

			// 			dc.SetPen(wxPen(wxColour(160, 160, 160), 1/*, wxPENSTYLE_DOT*/));
			// 			dc.DrawLine(m_imageSize.GetHeight(), m_iDrawingOffsetY, m_imageSize.GetHeight(), m_iDrawingOffsetY+m_imageSize.GetHeight()+m_itemSpace.GetHeight());
			// 			dc.SetPen(wxPen(wxColour(0, 0, 0), 1/*, wxPENSTYLE_DOT*/));
			// 			dc.DrawLine(m_imageSize.GetHeight()-1, m_iDrawingOffsetY, m_imageSize.GetHeight()-1, m_iDrawingOffsetY+m_imageSize.GetHeight()+m_itemSpace.GetHeight());

			dc.SetPen(wxPen(wxColour(160, 160, 160), 1/*, wxPENSTYLE_DOT*/));
			dc.DrawLine(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_iDrawingOffsetY);
			dc.SetPen(wxPen(wxColour(0, 0, 0), 1/*, wxPENSTYLE_DOT*/));
			dc.DrawLine(0, m_iDrawingOffsetY-1, m_canvasSize.GetWidth(), m_iDrawingOffsetY-1);

			wxRect detailRect;
			detailRect.SetTop(m_iDrawingOffsetY);
			detailRect.SetLeft(m_imageSize.GetHeight());
			detailRect.SetWidth(m_canvasSize.GetWidth()-m_imageSize.GetHeight());
			detailRect.SetHeight(m_imageSize.GetHeight());

			dc.SetClippingRegion(detailRect);

			dc.SetFont(m_detailFont);
			dc.SetTextForeground(wxColour(40,40,40));
			detailRect.x+=1;
			detailRect.y+=1;
			dc.DrawLabel(item->GetTextDetail(), detailRect, wxALIGN_CENTER);
			detailRect.x-=1;
			detailRect.y-=1;
			dc.SetFont(m_detailFont);
			dc.SetTextForeground(m_labelColour);
			dc.DrawLabel(item->GetTextDetail(), detailRect, wxALIGN_CENTER);


			if(item->GetTextDetail2().size()>0)
			{
				dc.SetFont(m_detail2Font);		
				detailRect.x+=detailRect.GetWidth()/2;
				detailRect.width-=detailRect.GetWidth()/2;;
				dc.SetFont(m_detail2Font);
				dc.SetTextForeground(wxColour(135, 135, 135));
				dc.DrawLabel(item->GetTextDetail2(), detailRect, wxALIGN_CENTER);

			}
			dc.DestroyClippingRegion();	


			// 				if(m_pSelectedItem)
			// 				{
			// 					if(m_pSelectedItem==item)
			// 					{
			// 						dc.SetPen(wxPen(m_selectedFrameColour, m_selectedFrameWidth));
			// 						//dc.SetBrush(*wxTRANSPARENT_BRUSH);
			// 						dc.SetBrush(wxBrush(*wxRED, wxBRUSHSTYLE_TRANSPARENT));
			// 						dc.DrawRectangle(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight());
			// 
			// 						detailRect.SetLeft(0);
			// 						detailRect.SetWidth(m_canvasSize.GetWidth());
			// 						dc.GradientFillLinear(detailRect, m_bgGradientColor1, m_bgGradientColor2, wxNORTH);
			// 					}
			// 				}

			m_iDrawingOffsetY+=m_imageSize.GetHeight()+m_itemSpace.GetHeight();				
		}
		break;
	case G3_IBVM_VIEWLIST:
		//dc.SetPen(wxPen(wxColour(160, 160, 160), 1/*, wxPENSTYLE_DOT*/));
		//dc.DrawLine(m_canvasSize.GetWidth()/3, 0, m_canvasSize.GetWidth()/3, m_canvasSize.GetHeight());

		for(int i=0;i<m_itemList.size();i++)
		{
			G3ImageBrowserItem *item=(G3ImageBrowserItem*) m_itemList[i];

			wxASSERT_MSG(item, "G3ImageBrowser - OnPaint Event: Invalid item pointer");

			int labelHeight=m_labelHeight*4;

			//if(GetWindowStyleFlag() & G3_IB_ITEM2BACKGROUND)
			{
				dc.SetPen(*wxTRANSPARENT_PEN);
				//dc.SetBrush(*wxTRANSPARENT_BRUSH);
				dc.SetBrush(wxBrush(i%2?wxColour(120, 120, 120):wxColour(125, 125,125)));
				dc.DrawRectangle(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_canvasSize.GetHeight());
			}

			// DODAC FLAGE DO UZYCIA ???
			// 			dc.SetPen(wxPen(wxColour(160, 160, 160), 1/*, wxPENSTYLE_DOT*/));
			// 			dc.DrawLine(m_canvasSize.GetWidth()/3, m_iDrawingOffsetY, m_canvasSize.GetWidth()/3, m_iDrawingOffsetY+labelHeight);
			// 			dc.SetPen(wxPen(wxColour(0, 0, 0), 1/*, wxPENSTYLE_DOT*/));
			// 			dc.DrawLine(m_canvasSize.GetWidth()/3-1, m_iDrawingOffsetY, m_canvasSize.GetWidth()/3-1, m_iDrawingOffsetY+labelHeight);

			dc.SetPen(wxPen(wxColour(160, 160, 160), 1/*, wxPENSTYLE_DOT*/));
			dc.DrawLine(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_iDrawingOffsetY);
			dc.SetPen(wxPen(wxColour(0, 0, 0), 1/*, wxPENSTYLE_DOT*/));
			dc.DrawLine(0, m_iDrawingOffsetY-1, m_canvasSize.GetWidth(), m_iDrawingOffsetY-1);


			wxRect labelRect(0, m_iDrawingOffsetY, m_canvasSize.GetWidth()/3, labelHeight);

			wxRect detailRect(m_canvasSize.GetWidth()/3, m_iDrawingOffsetY, m_canvasSize.GetWidth()-m_canvasSize.GetWidth()/3, labelHeight);

			if(m_pSelectedItem)
			{
				if(m_pSelectedItem==item)
				{
					//wxRect rectList=labelRect.Union(detailRect);
					wxRect rectList(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), labelHeight);

					dc.SetPen(*wxTRANSPARENT_PEN);
					//dc.SetBrush(*wxTRANSPARENT_BRUSH);
					dc.SetBrush(wxBrush(m_selectedLabelBgColour));
					dc.DrawRectangle(rectList);

					//dc.GradientFillLinear(rectList, m_bgGradientColor1, m_bgGradientColor2, wxSOUTH);
				}
			}

			// DODAC FLAGE DO UZYCIA ???
			//dc.SetPen(wxPen(wxColour(160, 160, 160), 1/*, wxPENSTYLE_DOT*/));
			//dc.DrawLine(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_iDrawingOffsetY);

			labelRect.x+=10; //akapit

			dc.SetClippingRegion(labelRect);
			dc.SetFont(m_labelFont);
			dc.SetTextForeground(wxColour(40,40,40));
			labelRect.x+=1;
			labelRect.y+=1;
			dc.DrawLabel(item->GetText(), labelRect, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL);
			labelRect.x-=1;
			labelRect.y-=1;
			dc.SetTextForeground(m_labelColour);
			dc.DrawLabel(item->GetText(), labelRect, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL);
			dc.DestroyClippingRegion();	

			dc.SetClippingRegion(detailRect);
			dc.SetFont(m_detailFont);
			dc.SetTextForeground(wxColour(40,40,40));
			detailRect.x+=1;
			detailRect.y+=1;
			dc.DrawLabel(item->GetTextDetail(), detailRect, wxALIGN_CENTER);
			detailRect.x-=1;
			detailRect.y-=1;
			dc.SetTextForeground(m_labelColour);
			dc.DrawLabel(item->GetTextDetail(), detailRect, wxALIGN_CENTER);
			dc.DestroyClippingRegion();	

			m_iDrawingOffsetY+=labelHeight;	
		}
		break;
	case G3_IBVM_VIEWSINLELIST:
		{
			m_imageSize.SetWidth(m_canvasSize.GetHeight());
			m_imageSize.SetHeight(m_canvasSize.GetHeight());

			for(int i=0;i<m_itemList.size();i++)
			{
				G3ImageBrowserItem *item=(G3ImageBrowserItem*) m_itemList[i];

				wxASSERT_MSG(item, "G3ImageBrowser - OnPaint Event: Invalid item pointer");

				wxBitmap bmp=*item->GetBitmap();

				wxMemoryDC memdc(&dc);

				memdc.SelectObject(bmp);
				dc.StretchBlit(m_itemSpace.GetWidth()+m_iDrawingOffsetX, m_itemSpace.GetHeight()+m_iDrawingOffsetY, m_imageSize.GetWidth()-m_itemSpace.GetWidth()*2, m_imageSize.GetHeight()-m_itemSpace.GetHeight()*2, &memdc, 0, 0, bmp.GetWidth(), bmp.GetHeight(), wxCOPY, false);			
				memdc.SelectObject(wxNullBitmap);

				if(m_pSelectedItem)
				{
					if(m_pSelectedItem==item)
					{
						dc.SetPen(wxPen(m_selectedFrameColour, m_selectedFrameWidth));
						//dc.SetBrush(*wxTRANSPARENT_BRUSH);
						dc.SetBrush(wxBrush(*wxRED, wxBRUSHSTYLE_TRANSPARENT));
						dc.DrawRectangle(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight());

					}
				}

				m_iDrawingOffsetX+=m_imageSize.GetHeight()+m_itemSpace.GetWidth();				
			}
		}
		break;
	}





	//int m_iDrawingOffsetX=-scrollPos.x*m_imageSize.GetWidth();

}

void G3ImageBrowser::OnLeftDown( wxMouseEvent& event )
{
	SetFocus();

	//if(itemSelected)
	m_bLeftDown=true;

	m_leftMousePos=event.GetPosition();


	//////////////////////////////////////////////////////////////////////////

	int m_iDrawingOffsetX=-m_scrollPos.x;
	int m_iDrawingOffsetY=-m_scrollPos.y;

	// 	if(GetWindowStyleFlag() & G3_IB_STRETCH2HEIGHT)
	// 	{
	// 		m_imageSize.SetWidth(m_canvasSize.GetHeight());
	// 		m_imageSize.SetHeight(m_canvasSize.GetHeight()-m_labelHeight);
	// 	}


	m_pSelectedItem=NULL;

	for(int i=0;i<m_itemList.size();i++)
	{
		G3ImageBrowserItem *item=(G3ImageBrowserItem*) m_itemList[i];

		wxASSERT_MSG(item, "G3ImageBritem1owser - OnPaint Event: Invalid item pointer");


		if(m_iViewMode==G3_IBVM_VIEWTHUMBNAILS)
		{
			wxRect rectItem=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight()+m_labelHeight);

			if(rectItem.Contains(event.GetPosition()))
			{
				m_pSelectedItem=item;

				//BLAD !!!!!!!!!!!!!!!
				G3ImageBrowserEvent eventDrag( G3_EVT_IMAGEBROWSER_ITEM_SELECTED, GetId(), m_pSelectedItem, event.GetPosition());
				eventDrag.SetEventObject(this);
				GetEventHandler()->ProcessEvent(eventDrag);
				break;			



				//BLAD!!!!!!!!!!!!!!		
			}

			m_iDrawingOffsetX+=m_imageSize.GetWidth()+m_itemSpace.GetWidth();
			if(m_iDrawingOffsetX+m_imageSize.GetWidth()/*/1.5*/>m_canvasSize.GetWidth())
			{
				m_iDrawingOffsetX=0;
				m_iDrawingOffsetY+=m_imageSize.GetHeight()+m_labelHeight+m_itemSpace.GetHeight();
			}
		}
		else
		{
			if(m_iViewMode==G3_IBVM_VIEWDETAILS)
			{
				wxRect rectItem=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_imageSize.GetHeight()+m_labelHeight);

				if(rectItem.Contains(event.GetPosition()))
				{
					m_pSelectedItem=item;

					//BLAD !!!!!!!!!!!!!!!
					G3ImageBrowserEvent eventDrag( G3_EVT_IMAGEBROWSER_ITEM_SELECTED, GetId(), m_pSelectedItem, event.GetPosition());
					eventDrag.SetEventObject(this);
					GetEventHandler()->ProcessEvent(eventDrag);
					break;			










					//BLAD!!!!!!!!!!!!!!		
				}

				m_iDrawingOffsetY+=m_imageSize.GetWidth()+m_itemSpace.GetWidth();	
			}
			else
			{
				if(m_iViewMode==G3_IBVM_VIEWLIST)
				{
					int labelHeight=m_labelHeight*4;

					wxRect rectItem=wxRect(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), labelHeight);

					if(rectItem.Contains(event.GetPosition()))
					{
						m_pSelectedItem=item;

						//BLAD !!!!!!!!!!!!!!!
						G3ImageBrowserEvent eventDrag( G3_EVT_IMAGEBROWSER_ITEM_SELECTED, GetId(), m_pSelectedItem, event.GetPosition());
						eventDrag.SetEventObject(this);
						GetEventHandler()->ProcessEvent(eventDrag);
						break;
					}

					m_iDrawingOffsetY+=labelHeight;	
				}
				else
				{
					if(m_iViewMode==G3_IBVM_VIEWSINLELIST)
					{
						wxRect rectItem=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight()+m_labelHeight);

						if(rectItem.Contains(event.GetPosition()))
						{
							m_pSelectedItem=item;

							//BLAD !!!!!!!!!!!!!!!
							G3ImageBrowserEvent eventDrag( G3_EVT_IMAGEBROWSER_ITEM_SELECTED, GetId(), m_pSelectedItem, event.GetPosition());
							eventDrag.SetEventObject(this);
							GetEventHandler()->ProcessEvent(eventDrag);
							break;			










							//BLAD!!!!!!!!!!!!!!		
						}

						m_iDrawingOffsetX+=m_imageSize.GetWidth()+m_itemSpace.GetWidth();
					}
				}

			}
		}	
	}

	Refresh();
}

void G3ImageBrowser::OnLeftUp( wxMouseEvent& event )
{
	m_bLeftDown=false;
}

void G3ImageBrowser::OnRightDown( wxMouseEvent& event )
{
	//m_imageBrowserPanel->SetFocus();

	int m_iDrawingOffsetX=-m_scrollPos.x;
	int m_iDrawingOffsetY=-m_scrollPos.y;

	// 	if(GetWindowStyleFlag() & G3_IB_STRETCH2HEIGHT)
	// 	{
	// 		m_imageSize.SetWidth(m_canvasSize.GetHeight());
	// 		m_imageSize.SetHeight(m_canvasSize.GetHeight()-m_labelHeight);
	// 	}

	m_pSelectedItem=NULL;

	for(int i=0;i<m_itemList.size();i++)
	{
		G3ImageBrowserItem *item=(G3ImageBrowserItem*) m_itemList[i];

		wxRect rectItem=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight());

		if(rectItem.Contains(event.GetPosition()))
		{
			m_pSelectedItem=item;

			G3ImageBrowserEvent eventRClick( G3_EVT_IMAGEBROWSER_ITEM_RCLICK, GetId(), m_pSelectedItem, event.GetPosition());
			eventRClick.SetEventObject(this);
			GetEventHandler()->ProcessEvent(eventRClick);
			break;
		}

		m_iDrawingOffsetX+=m_imageSize.GetWidth()+m_itemSpace.GetWidth();
		if(m_iDrawingOffsetX+m_imageSize.GetWidth()/*/1.5*/>m_canvasSize.GetWidth())
		{
			m_iDrawingOffsetX=0;
			m_iDrawingOffsetY+=m_imageSize.GetHeight()+m_labelHeight+m_itemSpace.GetHeight();
		}
	}

	/*m_imageBrowserPanel->*/Refresh();
}

void G3ImageBrowser::OnRightUp( wxMouseEvent& event )
{

}

void G3ImageBrowser::OnMotion( wxMouseEvent& event )
{
	int m_iDrawingOffsetX=-m_scrollPos.x;
	int m_iDrawingOffsetY=-m_scrollPos.y;

	m_mouseOverPos=wxPoint(-1, -1);
	for(int i=0;i<m_itemList.size();i++)
	{
		G3ImageBrowserItem *item=(G3ImageBrowserItem*) m_itemList[i];

		wxASSERT_MSG(item, "G3ImageBritem1owser - OnPaint Event: Invalid item pointer");

		if(m_iViewMode==G3_IBVM_VIEWTHUMBNAILS)
		{
			wxRect rectItem=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight()+m_labelHeight);

			if(rectItem.Contains(event.GetPosition()))
			{
				m_popupTime=0;

				m_mouseOverPos=wxPoint(m_iDrawingOffsetX/2+m_scrollPos.x, m_iDrawingOffsetY/2+m_scrollPos.y);
				m_mouseOverPos=event.GetPosition();
				break;
			}

			m_iDrawingOffsetX+=m_imageSize.GetWidth()+m_itemSpace.GetWidth();
			if(m_iDrawingOffsetX+m_imageSize.GetWidth()/*/1.5*/>m_canvasSize.GetWidth())
			{
				m_iDrawingOffsetX=0;
				m_iDrawingOffsetY+=m_imageSize.GetHeight()+m_labelHeight+m_itemSpace.GetHeight();
			}
		}
		else
		{
			if(m_iViewMode==G3_IBVM_VIEWDETAILS)
			{
				wxRect rectItem=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_imageSize.GetHeight()+m_labelHeight);

				if(rectItem.Contains(event.GetPosition()))
				{
					m_popupTime=0;	

					m_mouseOverPos=wxPoint(m_iDrawingOffsetX/2+m_scrollPos.x, m_iDrawingOffsetY/2+m_scrollPos.y);
					m_mouseOverPos=event.GetPosition();
					break;
				}

				m_iDrawingOffsetY+=m_imageSize.GetWidth()+m_itemSpace.GetWidth();	
			}
			else
			{
				if(m_iViewMode==G3_IBVM_VIEWLIST)
				{
					int labelHeight=m_labelHeight*4;

					wxRect rectItem=wxRect(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), labelHeight);

					if(rectItem.Contains(event.GetPosition()))
					{
						m_popupTime=0;

						m_mouseOverPos=wxPoint(m_canvasSize.GetWidth()/2, m_iDrawingOffsetY/2+m_scrollPos.y);
						m_mouseOverPos=event.GetPosition();
						break;

					}

					m_iDrawingOffsetY+=labelHeight;	
				}
				else
				{
					if(m_iViewMode==G3_IBVM_VIEWSINLELIST)
					{
						wxRect rectItem=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight()+m_labelHeight);

						if(rectItem.Contains(event.GetPosition()))
						{
							m_popupTime=0;

							m_mouseOverPos=wxPoint(m_iDrawingOffsetX/2+m_scrollPos.x, m_iDrawingOffsetY/2+m_scrollPos.y);
							m_mouseOverPos=event.GetPosition();
							break;
						}

						m_iDrawingOffsetX+=m_imageSize.GetWidth()+m_itemSpace.GetWidth();
					}
				}

			}
		}	
	}

	if(m_bLeftDown)
	{
		if(m_pSelectedItem)
		{
			//int dragLen=distWxPoint(m_leftMousePos, event.GetPosition());
			int dragLen=wxPoint2DInt(m_leftMousePos).GetDistance(wxPoint2DInt(event.GetPosition()));
			if(dragLen>3)
			{
				G3ImageBrowserEvent eventBeginDrag( G3_EVT_IMAGEBROWSER_ITEM_BEGIN_DRAGGED, GetId(), m_pSelectedItem, event.GetPosition());
				eventBeginDrag.SetEventObject(this);
				GetEventHandler()->ProcessEvent(eventBeginDrag);

				m_bLeftDown=false;

				G3ImageBrowserEvent eventEndDrag( G3_EVT_IMAGEBROWSER_ITEM_END_DRAGGED, GetId(), m_pSelectedItem, event.GetPosition());
				eventEndDrag.SetEventObject(this);
				GetEventHandler()->ProcessEvent(eventEndDrag);
			}

			/*m_imageBrowserPanel->*/Refresh();
		}		
	}
}

void G3ImageBrowser::OnImageBrowserEvent( G3ImageBrowserEvent& event )
{
	if ( event.IsAllowed() )
	{
		wxEventType eventType = event.GetEventType();

		if ( eventType == G3_EVT_IMAGEBROWSER_ITEM_SELECTED )
		{
			wxLogDebug( wxT("G3ImageBrowser item selected") );
		}
		else if ( eventType == G3_EVT_IMAGEBROWSER_ITEM_BEGIN_DRAGGED )
		{
			wxLogDebug( wxT("G3ImageBrowser item begin dragged") );
		}
		else if ( eventType == G3_EVT_IMAGEBROWSER_ITEM_END_DRAGGED )
		{
			wxLogDebug( wxT("G3ImageBrowser item end dragged") );
		}
		else if ( eventType == G3_EVT_IMAGEBROWSER_ITEM_RCLICK )
		{
			wxLogDebug( wxT("G3ImageBrowser item right button click") );
		}
		else if ( eventType == G3_EVT_IMAGEBROWSER_ITEM_MORE_CLICK )
		{
			wxLogDebug( wxT("G3ImageBrowser more click") );
		}
	}
}

G3ImageBrowserEvent::G3ImageBrowserEvent(wxEventType commandType, int id, G3ImageBrowserItem *item, wxPoint &mousePoint)
	: wxNotifyEvent(commandType, id)
{
	m_pItem=item;
	m_mousePoint=mousePoint;
}

G3ImageBrowserItem *G3ImageBrowserEvent::GetItem() const
{
	return m_pItem;
}

wxPoint G3ImageBrowserEvent::GetPoint() const
{
	return m_mousePoint;
}

