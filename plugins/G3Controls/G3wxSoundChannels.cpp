#include "G3wxSoundChannels.h"

#include <wx/dnd.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/dc.h>
#include <wx/image.h>
#include <wx/graphics.h>
#include <wx/log.h> 

#include <algorithm>


//using namespace Editor;

IMPLEMENT_DYNAMIC_CLASS(G3SoundChannels, wxPanel);

IMPLEMENT_DYNAMIC_CLASS(G3SoundChannelsEvent, wxNotifyEvent);

DEFINE_EVENT_TYPE(G3_EVT_SOUNDCHANNELS_ITEM_SELECTED)
DEFINE_EVENT_TYPE(G3_EVT_SOUNDCHANNELS_ITEM_BEGIN_DRAGGED)
DEFINE_EVENT_TYPE(G3_EVT_SOUNDCHANNELS_ITEM_END_DRAGGED)
DEFINE_EVENT_TYPE(G3_EVT_SOUNDCHANNELS_ITEM_RCLICK)
DEFINE_EVENT_TYPE(G3_EVT_SOUNDCHANNELS_ITEM_MORE_CLICK)

// statyczne eventy, jesli uzywamy dynamicznych(Connect,Bind) to zakomentowac TABLE
// BEGIN_EVENT_TABLE( G3SoundChannels, wxPanel )
// //EVT_G3_TABLE_(G3_EVT_SOUNDCHANNELS_ITEM_SELECTED, wxID_ANY, G3SoundChannels::OnSoundChannelsEvent)
// EVT_G3_SOUNDCHANNELS_ITEM_SELECTED(wxID_ANY, G3SoundChannels::OnSoundChannelsEvent )
// EVT_G3_SOUNDCHANNELS_ITEM_BEGIN_DRAGGED(wxID_ANY, G3SoundChannels::OnSoundChannelsEvent )
// EVT_G3_SOUNDCHANNELS_ITEM_END_DRAGGED(wxID_ANY, G3SoundChannels::OnSoundChannelsEvent )
// END_EVENT_TABLE



G3SoundChannelsItem::G3SoundChannelsItem():
m_strName(wxEmptyString), m_strTitle(wxEmptyString), m_strStatus(wxEmptyString), 
	m_strLastRecord(wxEmptyString), m_strNumberOfRecords(wxEmptyString), m_pUserData(NULL)
{
}

G3SoundChannelsItem::G3SoundChannelsItem(G3SoundChannels *soundChannels, const wxString &name, const wxString &title, const wxString &status, const wxString &lastRec, const wxString &numberOfRec, void *user):
m_strName(name), m_pSoundChannels(soundChannels), m_strTitle(title), m_strStatus(status), 
	m_strLastRecord(lastRec), m_strNumberOfRecords(numberOfRec), m_pUserData(user)
{		
}

G3SoundChannelsItem::~G3SoundChannelsItem()
{

}

wxString G3SoundChannelsItem::GetNameText() const
{
	return m_strName;
}

wxString G3SoundChannelsItem::GetTitleText() const
{
	return m_strTitle;
}

void G3SoundChannelsItem::SetTitleText(const wxString &text)
{
	m_strTitle=text;
}

wxString G3SoundChannelsItem::GetStatusText() const
{
	return m_strStatus;
}

void G3SoundChannelsItem::SetStatusText(const wxString &text)
{
	m_strStatus=text;
}

wxString G3SoundChannelsItem::GetLastRecordText() const
{
	return m_strLastRecord;
}

void G3SoundChannelsItem::SetLastRecordsText(const wxString &text)
{
	m_strLastRecord=text;
}

wxString G3SoundChannelsItem::GetNumberOfRecordsText() const
{
	return m_strNumberOfRecords;
}

void G3SoundChannelsItem::SetNumberOfRecordsText(const wxString &text)
{
	m_strNumberOfRecords=text;
}

void *G3SoundChannelsItem::GetUserData() const
{
	return m_pUserData;
}


void G3SoundChannelsItem::OnLeftDown(wxMouseEvent &event)
{

}
//////////////////////////////////////////////////////////////////////////
G3SoundChannels::G3SoundChannels()
{

}

G3SoundChannels::G3SoundChannels( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ):
wxScrolledWindow(parent, id, pos, size, /*wxScrolledWindowStyle*/wxVSCROLL|style),
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
	m_mouseOverPos(wxPoint(-1, -1))

{
	//http://wiki.wxwidgets.org/Drawing_on_a_panel_with_a_DC
	SetDoubleBuffered(true);

	SetScrollRate(5, 5);

	//////////////////////////////////////////////////////////////////////////

	// Connect Events	
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3SoundChannels::OnLeftDown ), NULL, this );
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( G3SoundChannels::OnLeftUp ), NULL, this );
	this->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( G3SoundChannels::OnRightDown ), NULL, this );
	this->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( G3SoundChannels::OnRightUp ), NULL, this );
	this->Connect( wxEVT_MOTION, wxMouseEventHandler( G3SoundChannels::OnMotion ), NULL, this );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( G3SoundChannels::OnPaint ), NULL, this );	

	this->Connect( wxEVT_SIZE, wxSizeEventHandler( G3SoundChannels::OnSize ), NULL, this );	
	this->Connect( wxID_ANY, G3_EVT_SOUNDCHANNELS_ITEM_SELECTED, G3SoundChannelsEventHandler( G3SoundChannels::OnSoundChannelsEvent ));
	this->Connect( wxID_ANY, G3_EVT_SOUNDCHANNELS_ITEM_BEGIN_DRAGGED, G3SoundChannelsEventHandler( G3SoundChannels::OnSoundChannelsEvent ) );
	this->Connect( wxID_ANY, G3_EVT_SOUNDCHANNELS_ITEM_END_DRAGGED, G3SoundChannelsEventHandler( G3SoundChannels::OnSoundChannelsEvent ) );
	this->Connect( wxID_ANY, G3_EVT_SOUNDCHANNELS_ITEM_RCLICK, G3SoundChannelsEventHandler( G3SoundChannels::OnSoundChannelsEvent ) );
	this->Connect( wxID_ANY, G3_EVT_SOUNDCHANNELS_ITEM_MORE_CLICK, G3SoundChannelsEventHandler( G3SoundChannels::OnSoundChannelsEvent ) );	

	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_THUMBTRACK, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);
	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_THUMBRELEASE, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);
	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_LINEUP, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);
	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_LINEDOWN, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);
	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_BOTTOM, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);
	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_PAGEUP, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);
	this->Connect(wxID_ANY, wxEVT_SCROLLWIN_PAGEDOWN, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);
	//////////////////////////////////////////////////////////////////////////
	m_labelFont=wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier 10 Pitch");
	m_detailFont=wxFont(7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial");
	m_detail2Font=wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial");

	SetLabelFont(m_labelFont);
	SetDetailFont(m_detailFont);
	SetDetail2Font(m_detail2Font);
}


G3SoundChannels::~G3SoundChannels()
{
	// Disconnect Events
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3SoundChannels::OnLeftDown ), NULL, this );
	this->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( G3SoundChannels::OnLeftUp ), NULL, this );
	this->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( G3SoundChannels::OnRightDown ), NULL, this );
	this->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( G3SoundChannels::OnRightUp ), NULL, this );
	this->Disconnect( wxEVT_MOTION, wxMouseEventHandler( G3SoundChannels::OnMotion ), NULL, this );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( G3SoundChannels::OnPaint ), NULL, this );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( G3SoundChannels::OnSize ), NULL, this );

	this->Disconnect( wxID_ANY, G3_EVT_SOUNDCHANNELS_ITEM_SELECTED, G3SoundChannelsEventHandler( G3SoundChannels::OnSoundChannelsEvent ) );
	this->Disconnect( wxID_ANY, G3_EVT_SOUNDCHANNELS_ITEM_BEGIN_DRAGGED, G3SoundChannelsEventHandler( G3SoundChannels::OnSoundChannelsEvent ) );
	this->Disconnect( wxID_ANY, G3_EVT_SOUNDCHANNELS_ITEM_END_DRAGGED, G3SoundChannelsEventHandler( G3SoundChannels::OnSoundChannelsEvent ) );
	this->Disconnect( wxID_ANY, G3_EVT_SOUNDCHANNELS_ITEM_RCLICK, G3SoundChannelsEventHandler( G3SoundChannels::OnSoundChannelsEvent ) );
	this->Disconnect( wxID_ANY, G3_EVT_SOUNDCHANNELS_ITEM_MORE_CLICK, G3SoundChannelsEventHandler( G3SoundChannels::OnSoundChannelsEvent ) );	

	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_THUMBTRACK, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_THUMBRELEASE, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_LINEUP, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_LINEDOWN, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_BOTTOM, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_PAGEUP, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_SCROLLWIN_PAGEDOWN, wxScrollWinEventHandler(G3SoundChannels::OnScrollWinEvents), NULL, this);

	//////////////////////////////////////////////////////////////////////////
	ClearAll();
}

void G3SoundChannels::RecalcVirtualSize()
{
	int itemHeight=115;

	m_virtualHeight=itemHeight;
	
	
	
	int col=0;
	for(int i=0;i<m_channelList.size();i++)
	{
		col++;
		if(col>2)
		{
			m_virtualHeight+=itemHeight+2;
			col=0;
		}
	}
// 
// 
// 
// 	switch(m_iViewMode)
// 	{
// 	case G3_SCVM_TILES:
// 		{
// 			for(int i=0;i<m_channelList.size();i++)
// 			{
// 				if(i%2)
// 					m_virtualHeight+=115;
// 			}
// 		}
// 		break;
// 	case G3_SCVM_DETAILS:
// 		{
// 			for(int i=0;i<m_channelList.size();i++)
// 				if(i%2)
// 					m_virtualHeight+=64;
// 		}
// 		break;	
// 	}
}

void G3SoundChannels::OnScrollWinEvents(wxScrollWinEvent& event)
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

void G3SoundChannels::UpdateControl()
{
	wxSizeEvent sz(GetSize(), GetId());
	ProcessEvent(sz);
}

void G3SoundChannels::SetCheckboardColour(const wxColour &color1, const wxColour &color2)
{
	m_checkboardColor1=color1;
	m_checkboardColor2=color2;

	UpdateControl();
}

void G3SoundChannels::SetImageSize(wxSize size)
{
	m_imageSize=size;

	UpdateControl();
}

void G3SoundChannels::SetItemSpace(wxSize space)
{
	m_itemSpace=space;

	UpdateControl();
}

void G3SoundChannels::SetLabelFont(const wxFont &font)
{
	m_labelFont=font;

	wxMemoryDC memDC;
	memDC.SelectObject(wxNullBitmap);
	memDC.SetFont(m_labelFont);
	m_labelHeight=memDC.GetTextExtent(_T("AYj")).GetHeight();

	UpdateControl();
}

void G3SoundChannels::SetDetailFont(const wxFont &font)
{
	m_detailFont=font;

	wxMemoryDC memDC;
	memDC.SelectObject(wxNullBitmap);
	memDC.SetFont(m_detailFont);
	m_labelHeight=memDC.GetTextExtent(_T("AYj")).GetHeight();

	UpdateControl();
}

void G3SoundChannels::SetDetail2Font(const wxFont &font)
{
	m_detail2Font=font;

	wxMemoryDC memDC;
	memDC.SelectObject(wxNullBitmap);
	memDC.SetFont(m_detail2Font);
	m_labelHeight=memDC.GetTextExtent(_T("AYj")).GetHeight();

	UpdateControl();
}

void G3SoundChannels::SetBgGradientColour1(const wxColour &colour)
{
	m_bgGradientColor1=colour;

	UpdateControl();
}

void G3SoundChannels::SetBgGradientColour2(const wxColour &colour)
{
	m_bgGradientColor2=colour;

	UpdateControl();
}

void G3SoundChannels::SetLabelColour(const wxColour &colour)
{
	m_labelColour=colour;

	UpdateControl();
}

void G3SoundChannels::SetSelectedLabelColour(const wxColour &colour)
{
	m_selectedLabelColour=colour;

	UpdateControl();
}

void G3SoundChannels::SetLabelGradientColour1(const wxColour &colour)
{
	m_labelBgGradientColour1=colour;

	UpdateControl();
}

void G3SoundChannels::SetLabelGradientColour2(const wxColour &colour)
{
	m_labelBgGradientColour2=colour;

	UpdateControl();
}

void G3SoundChannels::SetSelectedFrameColour(const wxColour &colour)
{
	m_selectedFrameColour=colour;

	UpdateControl();
}

void G3SoundChannels::SetSelectedFrameWidth(int width)
{
	m_selectedFrameWidth=width;

	UpdateControl();
}

void G3SoundChannels::SetSelectedLabelBgColour(const wxColour &colour)
{
	m_selectedLabelBgColour=colour;

	UpdateControl();
}

void G3SoundChannels::SetViewMode(int mode)
{
	m_iViewMode=mode;

	// 	SetScrollPos(wxHORIZONTAL, 0, true);
	// 	SetScrollPos(wxVERTICAL, 0, true);
	//EnsureItemVisible(GetSelectedItem());
	Scroll(0, 0);

	UpdateControl();


	//wxMessageBox(wxString::Format("%i", mode));
}
// void G3SoundChannels::AssignImageList(wxImageList *imageList, int which)
// {
// 	m_pImageList=imageList;
// }

// wxImageList *G3SoundChannels::GetImageList(int which) const
// {
// 	return m_pImageList;
// }

int G3SoundChannels::GetItemCount() const
{
	return m_channelList.size();
}

G3SoundChannelsItem *G3SoundChannels::GetItemSelected() const
{
	return m_pSelectedItem;
}

void G3SoundChannels::ClearAll()
{
	for (int i=0;i<m_channelList.size();i++)
	{
		wxDELETE(m_channelList[i]);
	}
	m_channelList.clear();
}
#include <vector>

G3SoundChannelsItem *G3SoundChannels::CreateChannel(const wxString &name, const wxString &title, const wxString &status, const wxString &lastRec, const wxString &numberOfRec, void *user)
{
	std::vector<G3SoundChannelsItem*>::iterator itChannel=std::find_if(m_channelList.begin(), m_channelList.end(), G3SoundChannelsItem::ByName(name));

	if(itChannel!=m_channelList.end())
		return NULL;

	G3SoundChannelsItem *pChannel=new G3SoundChannelsItem(this, name, title, status, lastRec, numberOfRec, user);
	if(!pChannel)
		return 0;

	m_channelList.push_back(pChannel);

	UpdateControl();

	return pChannel;
}

bool G3SoundChannels::RemoveChannel(wxString &name)
{	
	std::vector<G3SoundChannelsItem*>::iterator itChannel=std::find_if(m_channelList.begin(), m_channelList.end(), G3SoundChannelsItem::ByName(name));

	if(itChannel!=m_channelList.end())
		return false;

	wxDELETE(*itChannel);
	
	m_channelList.erase(itChannel);	

	return true;
}

bool G3SoundChannels::RemoveChannel(int index)
{
	if(index<0)
		return false;

	if(m_channelList.size()==0)
		return false;

	if(index>=m_channelList.size())
		return false;

	m_channelList.erase(m_channelList.begin()+index);	

	return true;
}

void G3SoundChannels::OnSize( wxSizeEvent& event )
{
	m_canvasSize=GetClientSize();

	RecalcVirtualSize();

	m_scrollPos.x=GetViewStart().x;
	m_scrollPos.y=GetViewStart().y;

	if(m_scrollPos.y>m_virtualHeight-m_canvasSize.GetHeight())
		m_scrollPos.y=m_virtualHeight-m_canvasSize.GetHeight();

	if(m_virtualHeight<m_canvasSize.GetHeight())
		m_scrollPos.y=0;

	SetScrollbars(1, 1, m_canvasSize.GetWidth(), m_virtualHeight, m_scrollPos.x, m_scrollPos.y);

	//SetVirtualSize(m_virtualSize.GetWidth(), m_virtualSize.GetHeight());

	Refresh();
}
#include <wx/renderer.h>
void G3SoundChannels::OnPaint( wxPaintEvent& event )
{
	//wxPaintDC dc(m_imageBrowserPanel);
	wxPaintDC dc(this);
	wxGraphicsContext *gc = wxGraphicsContext::Create( dc );

	dc.SetBrush(wxBrush(wxColour(80,80,80)));
	dc.DrawRectangle(m_canvasSize);

	if(m_channelList.size()==0)
		return;
	
	int itemHeight=115;

	int itemsVerticalSpace=0;

	int col=0;
	for(int i=0;i<m_channelList.size();i++)
	{
		wxRect rect;

		rect.SetWidth(m_canvasSize.GetWidth()/2-2);
		rect.SetHeight(itemHeight);

		if(col==0)
		{
			rect.SetLeftTop(wxPoint(1, -m_scrollPos.y+itemsVerticalSpace));	
		}
		else	
		
		{
			rect.SetLeftTop(wxPoint(m_canvasSize.GetWidth()/2, -m_scrollPos.y+itemsVerticalSpace));		
		}
		
		col++;
		if(col>2)
		{
			itemsVerticalSpace+=itemHeight+2;
			col=0;
		}
		
		dc.GradientFillLinear(rect, wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE), wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE), wxNORTH);
 		dc.SetPen(wxPen(wxColour(70, 70, 70),1));
 		//dc.SetBrush(wxBrush(wxColour(200, 200, 200)));
		dc.SetBrush(*wxTRANSPARENT_BRUSH);		
 		dc.DrawRoundedRectangle(rect, 3);

		
		wxRect recTitlebar;
		recTitlebar.SetLeftTop(wxPoint(2, 2));
		recTitlebar.SetSize(wxSize(m_canvasSize.GetWidth()/2-2-4, 18));
		dc.SetPen(wxPen(wxColour(110, 110, 110),1));
		dc.SetBrush(wxBrush(wxColour(230, 230, 230)));
		//dc.DrawRectangle(recTitlebar);
		dc.GradientFillLinear(recTitlebar, wxColour(51, 153, 255), wxColour(210, 210, 210), wxNORTH);
		dc.SetPen(wxPen(wxColour(50, 50, 50),1));
		dc.DrawLine(recTitlebar.GetLeft(), 20, recTitlebar.GetRight(), 20);
		dc.SetPen(wxPen(wxColour(240, 240, 240),1));
		dc.DrawLine(recTitlebar.GetLeft(), 21, recTitlebar.GetRight(), 21);


		//////////////////////////////////////////////////////////////////////////
		wxRect rectButton;
		rectButton.SetTopLeft(wxPoint(rect.GetLeft()+10, rect.GetTop()+25));
		rectButton.SetSize(wxSize(39, 49));
		wxRendererNative::Get().DrawPushButton(this, dc, rectButton, i%2?wxCONTROL_PRESSED:wxCONTROL_CURRENT);
	}

	//int m_iDrawingOffsetX=0;
	//int m_iDrawingOffsetY=0;

	//// 	if(GetWindowStyleFlag() & G3_IB_STRETCH2HEIGHT)
	//// 	{
	//// 		m_imageSize.SetWidth(m_canvasSize.GetHeight());
	//// 		m_imageSize.SetHeight(m_canvasSize.GetHeight()-m_labelHeight);
	//// 	}

	//// hmm udpate przy resizeowaniu ?
	//// 	if(m_canvasPreviousSize!=m_canvasSize)
	//// 	{
	//// 		for(int i=0;i<m_channelList.size();i++)
	//// 		{
	//// 			m_iDrawingOffsetX+=m_imageSize.GetWidth()+m_itemSpace.GetWidth();
	//// 			if(m_iDrawingOffsetX+m_imageSize.GetWidth()/2>m_canvasSize.GetWidth())
	//// 			{
	//// 				m_iDrawingOffsetX=0;
	//// 				m_iDrawingOffsetY+=m_imageSize.GetHeight()+m_labelHeight+m_itemSpace.GetHeight();
	//// 			}
	//// 		}
	//// 
	//// 		if(m_iLayoutMode==0)
	//// 			m_iDrawingOffsetY+=m_imageSize.GetHeight()+m_labelHeight+m_itemSpace.GetHeight();
	//// 
	//// 		if(m_channelList.size()>0)
	//// 		{		
	//// 			//clientSize=GetClientSize();
	//// 
	//// 			//	m_virtualSize=wxSize(m_channelList.size()*clientSize.GetHeight()-(clientSize.GetWidth()-clientSize.GetHeight()), clientSize.GetHeight());
	//// 
	//// 			m_virtualSize=wxSize(m_canvasSize.GetHeight(), m_iDrawingOffsetY);
	//// 
	//// 			m_imageBrowserPanel->SetSize(m_canvasSize.GetWidth(), m_iDrawingOffsetY);
	//// 			bSizer1->Layout();
	//// 			Layout();
	//// 
	//// 			scrollPos.x=GetScrollPos(wxHORIZONTAL);
	//// 			scrollPos.y=GetScrollPos(wxVERTICAL);
	//// 			SetScrollbar(wxVERTICAL, GetScrollPos(wxVERTICAL), m_virtualSize.GetWidth(), m_virtualSize.GetHeight());
	//// 		}
	//// 	}


	////m_imageSize=m_canvasSize;



	//if(GetWindowStyleFlag() & G3_IB_GRADIENTBACKGROUND)
	//	dc.GradientFillLinear(m_canvasSize, m_bgGradientColor1, m_bgGradientColor2, wxSOUTH);

	////GetScrollPos()

	//m_iDrawingOffsetX=-m_scrollPos.x;
	//m_iDrawingOffsetY=-m_scrollPos.y;

	//switch(m_iViewMode)
	//{
	//case G3_IBVM_VIEWTHUMBNAILS:
	//	for(int i=0;i<m_channelList.size();i++)
	//	{
	//		G3SoundChannelsItem *item=(G3SoundChannelsItem*) m_channelList[i];

	//		wxASSERT_MSG(item, "G3SoundChannels - OnPaint Event: Invalid item pointer");

	//		wxBitmap bmp=*item->GetBitmap();

	//		wxMemoryDC memdc(&dc);

	//		memdc.SelectObject(bmp);
	//		dc.StretchBlit(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight(), &memdc, 0, 0, bmp.GetWidth(), bmp.GetHeight(), wxCOPY, false);			
	//		memdc.SelectObject(wxNullBitmap);

	//		dc.SetFont(m_labelFont);

	//		wxSize textSize=dc.GetTextExtent(item->GetText());

	//		dc.SetBrush(*wxBLACK_BRUSH);


	//		wxRect labelBgRect=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY+m_imageSize.GetHeight(),
	//			m_imageSize.GetWidth(), textSize.GetHeight());		

	//		// 		wxRect labelRect=wxRect(m_iDrawingOffsetX+m_imageSize.GetWidth()/2-textSize.GetWidth()/2,
	//		// 			m_iDrawingOffsetY+m_imageSize.GetHeight(),
	//		// 			textSize.GetWidth(), textSize.GetHeight());

	//		wxRect labelRect=wxRect(m_iDrawingOffsetX,
	//			m_iDrawingOffsetY+m_imageSize.GetHeight(),
	//			m_imageSize.GetWidth(), textSize.GetHeight());

	//		if(GetWindowStyleFlag() & G3_IB_SELECTED_RENDER_IN_FRAME)
	//		{
	//			labelRect=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY+m_imageSize.GetHeight(),
	//				m_imageSize.GetWidth(), textSize.GetHeight());
	//		}

	//		if(GetWindowStyleFlag() & G3_IB_FILLED_BACKGROUND_LABEL)
	//		{
	//			if(GetWindowStyleFlag() & G3_IB_GRADIENT_BG_LABEL)
	//				dc.GradientFillLinear(labelBgRect, m_labelBgGradientColour1, m_labelBgGradientColour2, wxSOUTH);
	//			else
	//				dc.GradientFillLinear(labelBgRect, m_labelBgGradientColour1, m_labelBgGradientColour1, wxSOUTH);
	//		}

	//		if(m_pSelectedItem)
	//		{
	//			if(m_pSelectedItem==item)
	//			{
	//				if(GetWindowStyleFlag() & G3_IB_SELECTED_RENDER_IN_FRAME)
	//				{
	//					dc.SetPen(wxPen(m_selectedFrameColour, m_selectedFrameWidth));
	//					//dc.SetBrush(*wxTRANSPARENT_BRUSH);
	//					dc.SetBrush(wxBrush(*wxRED, wxBRUSHSTYLE_TRANSPARENT));
	//					dc.DrawRectangle(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight());
	//				}
	//				else
	//				{
	//					dc.SetPen(m_selectedLabelBgColour);
	//					dc.SetBrush(*wxTRANSPARENT_BRUSH);
	//					dc.DrawRectangle(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight());

	//					dc.SetPen(*wxTRANSPARENT_PEN);
	//					dc.SetBrush(m_selectedLabelBgColour);
	//					dc.DrawRectangle(labelRect);
	//				}			
	//			}
	//		}

	//		dc.SetFont(wxFont(7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier 10 Pitch"));
	//		dc.SetTextForeground(wxColour(220, 220, 220));
	//		wxString topString(_("Mesh"));
	//		wxSize topTextSize=dc.GetTextExtent(topString);
	//		wxRect typeLabelRect(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), topTextSize.GetHeight());
	//		dc.DrawLabel(_("Mesh"), typeLabelRect, wxALIGN_CENTER);


	//		dc.SetTextForeground(m_labelColour);

	//		if(m_pSelectedItem && !(GetWindowStyleFlag() & G3_IB_SELECTED_RENDER_IN_FRAME))
	//		{
	//			if(m_pSelectedItem==item)
	//				dc.SetTextForeground(m_selectedLabelColour);
	//		}

	//		// 		if(m_iLayoutMode==0)
	//		// 			dc.DrawText(item->GetText(), 
	//		// 			m_iDrawingOffsetX+m_imageSize.GetWidth()/2-textSize.GetWidth()/2, 
	//		// 			m_iDrawingOffsetY+m_imageSize.GetHeight());
	//		// 		else
	//		// 			dc.DrawText(item->GetText(), 
	//		// 			m_iDrawingOffsetX+m_imageSize.GetWidth()/2-textSize.GetWidth()/2, 
	//		// 			m_iDrawingOffsetY+m_imageSize.GetHeight()-textSize.GetHeight());
	//		//if(m_iLayoutMode==0)

	//		dc.SetClippingRegion(labelRect);
	//		wxRect labelRect2=labelRect;
	//		labelRect2.Deflate(2, 0);
	//		dc.DrawLabel(item->GetText(), labelRect2, textSize.GetWidth()>m_imageSize.GetWidth()?wxALIGN_LEFT:wxALIGN_CENTER);
	//		dc.DestroyClippingRegion();	



	//		m_iDrawingOffsetX+=m_imageSize.GetWidth()+m_itemSpace.GetWidth();
	//		if(m_iDrawingOffsetX+m_imageSize.GetWidth()/*/1.5*/>m_canvasSize.GetWidth())
	//		{
	//			m_iDrawingOffsetX=0;
	//			m_iDrawingOffsetY+=m_imageSize.GetHeight()+m_labelHeight+m_itemSpace.GetHeight();
	//		}	
	//	}
	//	break;
	//case G3_IBVM_VIEWDETAILS:
	//	m_imageSize.SetWidth(m_imageSize.GetHeight());
	//	m_imageSize.SetHeight(m_imageSize.GetHeight());

	//	for(int i=0;i<m_channelList.size();i++)
	//	{
	//		G3SoundChannelsItem *item=(G3SoundChannelsItem*) m_channelList[i];

	//		wxASSERT_MSG(item, "G3SoundChannels - OnPaint Event: Invalid item pointer");

	//		//if(GetWindowStyleFlag() & G3_IB_ITEM2BACKGROUND)
	//		{
	//			dc.SetPen(*wxTRANSPARENT_PEN);
	//			//dc.SetBrush(*wxTRANSPARENT_BRUSH);
	//			dc.SetBrush(wxBrush(i%2?wxColour(120, 120, 120):wxColour(125, 125,125)));
	//			dc.DrawRectangle(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_canvasSize.GetHeight());
	//		}			



	//		if(m_pSelectedItem)
	//		{
	//			if(m_pSelectedItem==item)
	//			{
	//				// 					dc.SetPen(wxPen(m_selectedFrameColour, m_selectedFrameWidth));
	//				// 					//dc.SetBrush(*wxTRANSPARENT_BRUSH);
	//				// 					dc.SetBrush(wxBrush(*wxRED, wxBRUSHSTYLE_TRANSPARENT));
	//				// 					dc.DrawRectangle(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight());
	//				// 
	//				// 					wxRect selectRect;
	//				// 					selectRect.SetTop(m_iDrawingOffsetY);
	//				// 					selectRect.SetLeft(0);
	//				// 					selectRect.SetWidth(m_canvasSize.GetWidth());
	//				// 					selectRect.SetHeight((m_imageSize.GetHeight())/2);
	//				// 					dc.GradientFillLinear(selectRect, m_bgGradientColor1, m_bgGradientColor2, wxNORTH);
	//				// 
	//				// 					selectRect.SetTop(m_iDrawingOffsetY+m_imageSize.GetHeight()/2);
	//				// 					selectRect.SetHeight(m_imageSize.GetHeight()/2);
	//				// 					dc.GradientFillLinear(selectRect, m_bgGradientColor1, m_bgGradientColor2, wxSOUTH);



	//				//

	//				wxRect rectList(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_imageSize.GetHeight()+m_itemSpace.GetHeight());

	//				dc.SetPen(*wxTRANSPARENT_PEN);
	//				//dc.SetBrush(*wxTRANSPARENT_BRUSH);
	//				dc.SetBrush(wxBrush(m_selectedLabelBgColour));
	//				dc.DrawRectangle(rectList);
	//			}
	//		}
	//		wxBitmap bmp=*item->GetBitmap();

	//		wxMemoryDC memdc(&dc);

	//		memdc.SelectObject(bmp);
	//		dc.StretchBlit(m_itemSpace.GetWidth()+m_iDrawingOffsetX, m_itemSpace.GetHeight()+m_iDrawingOffsetY, m_imageSize.GetWidth()-m_itemSpace.GetWidth()*2, m_imageSize.GetHeight()-m_itemSpace.GetHeight()*2, &memdc, 0, 0, bmp.GetWidth(), bmp.GetHeight(), wxCOPY, false);			
	//		memdc.SelectObject(wxNullBitmap);

	//		// 			dc.SetPen(wxPen(wxColour(160, 160, 160), 1/*, wxPENSTYLE_DOT*/));
	//		// 			dc.DrawLine(m_imageSize.GetHeight(), m_iDrawingOffsetY, m_imageSize.GetHeight(), m_iDrawingOffsetY+m_imageSize.GetHeight()+m_itemSpace.GetHeight());
	//		// 			dc.SetPen(wxPen(wxColour(0, 0, 0), 1/*, wxPENSTYLE_DOT*/));
	//		// 			dc.DrawLine(m_imageSize.GetHeight()-1, m_iDrawingOffsetY, m_imageSize.GetHeight()-1, m_iDrawingOffsetY+m_imageSize.GetHeight()+m_itemSpace.GetHeight());

	//		dc.SetPen(wxPen(wxColour(160, 160, 160), 1/*, wxPENSTYLE_DOT*/));
	//		dc.DrawLine(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_iDrawingOffsetY);
	//		dc.SetPen(wxPen(wxColour(0, 0, 0), 1/*, wxPENSTYLE_DOT*/));
	//		dc.DrawLine(0, m_iDrawingOffsetY-1, m_canvasSize.GetWidth(), m_iDrawingOffsetY-1);

	//		wxRect detailRect;
	//		detailRect.SetTop(m_iDrawingOffsetY);
	//		detailRect.SetLeft(m_imageSize.GetHeight());
	//		detailRect.SetWidth(m_canvasSize.GetWidth()-m_imageSize.GetHeight());
	//		detailRect.SetHeight(m_imageSize.GetHeight());

	//		dc.SetClippingRegion(detailRect);

	//		dc.SetFont(m_detailFont);
	//		dc.SetTextForeground(wxColour(40,40,40));
	//		detailRect.x+=1;
	//		detailRect.y+=1;
	//		dc.DrawLabel(item->GetTextDetail(), detailRect, wxALIGN_CENTER);
	//		detailRect.x-=1;
	//		detailRect.y-=1;
	//		dc.SetFont(m_detailFont);
	//		dc.SetTextForeground(m_labelColour);
	//		dc.DrawLabel(item->GetTextDetail(), detailRect, wxALIGN_CENTER);


	//		if(item->GetTextDetail2().size()>0)
	//		{
	//			dc.SetFont(m_detail2Font);		
	//			detailRect.x+=detailRect.GetWidth()/2;
	//			detailRect.width-=detailRect.GetWidth()/2;;
	//			dc.SetFont(m_detail2Font);
	//			dc.SetTextForeground(wxColour(135, 135, 135));
	//			dc.DrawLabel(item->GetTextDetail2(), detailRect, wxALIGN_CENTER);

	//		}
	//		dc.DestroyClippingRegion();	


	//		// 				if(m_pSelectedItem)
	//		// 				{
	//		// 					if(m_pSelectedItem==item)
	//		// 					{
	//		// 						dc.SetPen(wxPen(m_selectedFrameColour, m_selectedFrameWidth));
	//		// 						//dc.SetBrush(*wxTRANSPARENT_BRUSH);
	//		// 						dc.SetBrush(wxBrush(*wxRED, wxBRUSHSTYLE_TRANSPARENT));
	//		// 						dc.DrawRectangle(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight());
	//		// 
	//		// 						detailRect.SetLeft(0);
	//		// 						detailRect.SetWidth(m_canvasSize.GetWidth());
	//		// 						dc.GradientFillLinear(detailRect, m_bgGradientColor1, m_bgGradientColor2, wxNORTH);
	//		// 					}
	//		// 				}

	//		m_iDrawingOffsetY+=m_imageSize.GetHeight()+m_itemSpace.GetHeight();				
	//	}
	//	break;
	//case G3_IBVM_VIEWLIST:
	//	//dc.SetPen(wxPen(wxColour(160, 160, 160), 1/*, wxPENSTYLE_DOT*/));
	//	//dc.DrawLine(m_canvasSize.GetWidth()/3, 0, m_canvasSize.GetWidth()/3, m_canvasSize.GetHeight());

	//	for(int i=0;i<m_channelList.size();i++)
	//	{
	//		G3SoundChannelsItem *item=(G3SoundChannelsItem*) m_channelList[i];

	//		wxASSERT_MSG(item, "G3SoundChannels - OnPaint Event: Invalid item pointer");

	//		int labelHeight=m_labelHeight*4;

	//		//if(GetWindowStyleFlag() & G3_IB_ITEM2BACKGROUND)
	//		{
	//			dc.SetPen(*wxTRANSPARENT_PEN);
	//			//dc.SetBrush(*wxTRANSPARENT_BRUSH);
	//			dc.SetBrush(wxBrush(i%2?wxColour(120, 120, 120):wxColour(125, 125,125)));
	//			dc.DrawRectangle(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_canvasSize.GetHeight());
	//		}

	//		// DODAC FLAGE DO UZYCIA ???
	//		// 			dc.SetPen(wxPen(wxColour(160, 160, 160), 1/*, wxPENSTYLE_DOT*/));
	//		// 			dc.DrawLine(m_canvasSize.GetWidth()/3, m_iDrawingOffsetY, m_canvasSize.GetWidth()/3, m_iDrawingOffsetY+labelHeight);
	//		// 			dc.SetPen(wxPen(wxColour(0, 0, 0), 1/*, wxPENSTYLE_DOT*/));
	//		// 			dc.DrawLine(m_canvasSize.GetWidth()/3-1, m_iDrawingOffsetY, m_canvasSize.GetWidth()/3-1, m_iDrawingOffsetY+labelHeight);

	//		dc.SetPen(wxPen(wxColour(160, 160, 160), 1/*, wxPENSTYLE_DOT*/));
	//		dc.DrawLine(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_iDrawingOffsetY);
	//		dc.SetPen(wxPen(wxColour(0, 0, 0), 1/*, wxPENSTYLE_DOT*/));
	//		dc.DrawLine(0, m_iDrawingOffsetY-1, m_canvasSize.GetWidth(), m_iDrawingOffsetY-1);


	//		wxRect labelRect(0, m_iDrawingOffsetY, m_canvasSize.GetWidth()/3, labelHeight);

	//		wxRect detailRect(m_canvasSize.GetWidth()/3, m_iDrawingOffsetY, m_canvasSize.GetWidth()-m_canvasSize.GetWidth()/3, labelHeight);

	//		if(m_pSelectedItem)
	//		{
	//			if(m_pSelectedItem==item)
	//			{
	//				//wxRect rectList=labelRect.Union(detailRect);
	//				wxRect rectList(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), labelHeight);

	//				dc.SetPen(*wxTRANSPARENT_PEN);
	//				//dc.SetBrush(*wxTRANSPARENT_BRUSH);
	//				dc.SetBrush(wxBrush(m_selectedLabelBgColour));
	//				dc.DrawRectangle(rectList);

	//				//dc.GradientFillLinear(rectList, m_bgGradientColor1, m_bgGradientColor2, wxSOUTH);
	//			}
	//		}

	//		// DODAC FLAGE DO UZYCIA ???
	//		//dc.SetPen(wxPen(wxColour(160, 160, 160), 1/*, wxPENSTYLE_DOT*/));
	//		//dc.DrawLine(0, m_iDrawingOffsetY, m_canvasSize.GetWidth(), m_iDrawingOffsetY);

	//		labelRect.x+=10; //akapit

	//		dc.SetClippingRegion(labelRect);
	//		dc.SetFont(m_labelFont);
	//		dc.SetTextForeground(wxColour(40,40,40));
	//		labelRect.x+=1;
	//		labelRect.y+=1;
	//		dc.DrawLabel(item->GetText(), labelRect, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL);
	//		labelRect.x-=1;
	//		labelRect.y-=1;
	//		dc.SetTextForeground(m_labelColour);
	//		dc.DrawLabel(item->GetText(), labelRect, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL);
	//		dc.DestroyClippingRegion();	

	//		dc.SetClippingRegion(detailRect);
	//		dc.SetFont(m_detailFont);
	//		dc.SetTextForeground(wxColour(40,40,40));
	//		detailRect.x+=1;
	//		detailRect.y+=1;
	//		dc.DrawLabel(item->GetTextDetail(), detailRect, wxALIGN_CENTER);
	//		detailRect.x-=1;
	//		detailRect.y-=1;
	//		dc.SetTextForeground(m_labelColour);
	//		dc.DrawLabel(item->GetTextDetail(), detailRect, wxALIGN_CENTER);
	//		dc.DestroyClippingRegion();	

	//		m_iDrawingOffsetY+=labelHeight;	
	//	}
	//	break;
	//case G3_IBVM_VIEWSINLELIST:
	//	{
	//		m_imageSize.SetWidth(m_canvasSize.GetHeight());
	//		m_imageSize.SetHeight(m_canvasSize.GetHeight());

	//		for(int i=0;i<m_channelList.size();i++)
	//		{
	//			G3SoundChannelsItem *item=(G3SoundChannelsItem*) m_channelList[i];

	//			wxASSERT_MSG(item, "G3SoundChannels - OnPaint Event: Invalid item pointer");

	//			wxBitmap bmp=*item->GetBitmap();

	//			wxMemoryDC memdc(&dc);

	//			memdc.SelectObject(bmp);
	//			dc.StretchBlit(m_itemSpace.GetWidth()+m_iDrawingOffsetX, m_itemSpace.GetHeight()+m_iDrawingOffsetY, m_imageSize.GetWidth()-m_itemSpace.GetWidth()*2, m_imageSize.GetHeight()-m_itemSpace.GetHeight()*2, &memdc, 0, 0, bmp.GetWidth(), bmp.GetHeight(), wxCOPY, false);			
	//			memdc.SelectObject(wxNullBitmap);

	//			if(m_pSelectedItem)
	//			{
	//				if(m_pSelectedItem==item)
	//				{
	//					dc.SetPen(wxPen(m_selectedFrameColour, m_selectedFrameWidth));
	//					//dc.SetBrush(*wxTRANSPARENT_BRUSH);
	//					dc.SetBrush(wxBrush(*wxRED, wxBRUSHSTYLE_TRANSPARENT));
	//					dc.DrawRectangle(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight());

	//				}
	//			}

	//			m_iDrawingOffsetX+=m_imageSize.GetHeight()+m_itemSpace.GetWidth();				
	//		}
	//	}
	//	break;
	//}





	////int m_iDrawingOffsetX=-scrollPos.x*m_imageSize.GetWidth();

}

void G3SoundChannels::OnLeftDown( wxMouseEvent& event )
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

	for(int i=0;i<m_channelList.size();i++)
	{
		G3SoundChannelsItem *item=(G3SoundChannelsItem*) m_channelList[i];

		wxASSERT_MSG(item, "G3ImageBritem1owser - OnPaint Event: Invalid item pointer");


		if(m_iViewMode==G3_IBVM_VIEWTHUMBNAILS)
		{
			wxRect rectItem=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight()+m_labelHeight);

			if(rectItem.Contains(event.GetPosition()))
			{
				m_pSelectedItem=item;

				//BLAD !!!!!!!!!!!!!!!
				G3SoundChannelsEvent eventDrag( G3_EVT_SOUNDCHANNELS_ITEM_SELECTED, GetId(), m_pSelectedItem, event.GetPosition());
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
					G3SoundChannelsEvent eventDrag( G3_EVT_SOUNDCHANNELS_ITEM_SELECTED, GetId(), m_pSelectedItem, event.GetPosition());
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
						G3SoundChannelsEvent eventDrag( G3_EVT_SOUNDCHANNELS_ITEM_SELECTED, GetId(), m_pSelectedItem, event.GetPosition());
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
							G3SoundChannelsEvent eventDrag( G3_EVT_SOUNDCHANNELS_ITEM_SELECTED, GetId(), m_pSelectedItem, event.GetPosition());
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

void G3SoundChannels::OnLeftUp( wxMouseEvent& event )
{
	m_bLeftDown=false;
}

void G3SoundChannels::OnRightDown( wxMouseEvent& event )
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

	for(int i=0;i<m_channelList.size();i++)
	{
		G3SoundChannelsItem *item=(G3SoundChannelsItem*) m_channelList[i];

		wxRect rectItem=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight());

		if(rectItem.Contains(event.GetPosition()))
		{
			m_pSelectedItem=item;

			G3SoundChannelsEvent eventRClick( G3_EVT_SOUNDCHANNELS_ITEM_RCLICK, GetId(), m_pSelectedItem, event.GetPosition());
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

void G3SoundChannels::OnRightUp( wxMouseEvent& event )
{

}

void G3SoundChannels::OnMotion( wxMouseEvent& event )
{
	int m_iDrawingOffsetX=-m_scrollPos.x;
	int m_iDrawingOffsetY=-m_scrollPos.y;

	m_mouseOverPos=wxPoint(-1, -1);
	for(int i=0;i<m_channelList.size();i++)
	{
		G3SoundChannelsItem *item=(G3SoundChannelsItem*) m_channelList[i];

		wxASSERT_MSG(item, "G3ImageBritem1owser - OnPaint Event: Invalid item pointer");

		if(m_iViewMode==G3_IBVM_VIEWTHUMBNAILS)
		{
			wxRect rectItem=wxRect(m_iDrawingOffsetX, m_iDrawingOffsetY, m_imageSize.GetWidth(), m_imageSize.GetHeight()+m_labelHeight);

			if(rectItem.Contains(event.GetPosition()))
			{
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
				G3SoundChannelsEvent eventBeginDrag( G3_EVT_SOUNDCHANNELS_ITEM_BEGIN_DRAGGED, GetId(), m_pSelectedItem, event.GetPosition());
				eventBeginDrag.SetEventObject(this);
				GetEventHandler()->ProcessEvent(eventBeginDrag);

				m_bLeftDown=false;

				G3SoundChannelsEvent eventEndDrag( G3_EVT_SOUNDCHANNELS_ITEM_END_DRAGGED, GetId(), m_pSelectedItem, event.GetPosition());
				eventEndDrag.SetEventObject(this);
				GetEventHandler()->ProcessEvent(eventEndDrag);
			}

			/*m_imageBrowserPanel->*/Refresh();
		}		
	}
}

void G3SoundChannels::OnSoundChannelsEvent( G3SoundChannelsEvent& event )
{
	if ( event.IsAllowed() )
	{
		wxEventType eventType = event.GetEventType();

		if ( eventType == G3_EVT_SOUNDCHANNELS_ITEM_SELECTED )
		{
			wxLogDebug( wxT("G3SoundChannels item selected") );
		}
		else if ( eventType == G3_EVT_SOUNDCHANNELS_ITEM_BEGIN_DRAGGED )
		{
			wxLogDebug( wxT("G3SoundChannels item begin dragged") );
		}
		else if ( eventType == G3_EVT_SOUNDCHANNELS_ITEM_END_DRAGGED )
		{
			wxLogDebug( wxT("G3SoundChannels item end dragged") );
		}
		else if ( eventType == G3_EVT_SOUNDCHANNELS_ITEM_RCLICK )
		{
			wxLogDebug( wxT("G3SoundChannels item right button click") );
		}
		else if ( eventType == G3_EVT_SOUNDCHANNELS_ITEM_MORE_CLICK )
		{
			wxLogDebug( wxT("G3SoundChannels more click") );
		}
	}
}

G3SoundChannelsEvent::G3SoundChannelsEvent(wxEventType commandType, int id, G3SoundChannelsItem *item, wxPoint &mousePoint)
	: wxNotifyEvent(commandType, id)
{
	m_pItem=item;
	m_mousePoint=mousePoint;
}

G3SoundChannelsItem *G3SoundChannelsEvent::GetItem() const
{
	return m_pItem;
}

wxPoint G3SoundChannelsEvent::GetPoint() const
{
	return m_mousePoint;
}

