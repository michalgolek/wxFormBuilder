#include "G3wxBitmapButton.h"

#include <wx/dcclient.h>
#include <wx/dcgraph.h>

G3BitmapButton::G3BitmapButton():
m_strLabel(wxEmptyString),
	m_bHover(false),
	m_bChecked(false),
	m_bitmapNormal(wxNullBitmap),
	m_bitmapHover(wxNullBitmap)
{
	//Init();
}

G3BitmapButton::G3BitmapButton(wxWindow *parent, const wxString &label, wxBitmap &bitmapNormal, wxBitmap &bitmapHover, wxWindowID id,
	const wxPoint &pos, const wxSize &size, 
	long style, const wxString &name):
wxPanel(parent, id, pos, size, style, name),
	m_bitmapNormal(bitmapNormal),
	m_bitmapHover(bitmapHover),
	m_strLabel(label)
{
	//Create(parent, id, pos, size, style, name);

	Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3BitmapButton::OnLeftDown ), NULL, this );
	Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( G3BitmapButton::OnEnterWindow ) );
	Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( G3BitmapButton::OnLeaveWindow ) );
	Connect( wxEVT_PAINT, wxPaintEventHandler( G3BitmapButton::OnPaint ), NULL, this );

	//SetDoubleBuffered(true);

	wxSizeEvent event;
	event.SetEventObject(this);
	OnSize(event);
}

G3BitmapButton::G3BitmapButton(wxWindow *parent, const wxString &label, wxBitmap &bitmapNormal, wxBitmap &bitmapHover, wxBitmap &bitmapChecked,
	wxWindowID id, const wxPoint &pos, const wxSize &size, 
	long style, const wxString &name):
wxPanel(parent, id, pos, size, style, name),
	m_bitmapNormal(bitmapNormal),
	m_bitmapHover(bitmapHover),
	m_bitmapChecked(bitmapChecked),
	m_strLabel(label)
{
	//Create(parent, id, pos, size, style, name);

	Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3BitmapButton::OnLeftDown ), NULL, this );
	Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( G3BitmapButton::OnEnterWindow ) );
	Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( G3BitmapButton::OnLeaveWindow ) );
	Connect( wxEVT_PAINT, wxPaintEventHandler( G3BitmapButton::OnPaint ), NULL, this );
	//Connect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( G3BitmapButton::OnEraseBackground), NULL, this );

	//SetDoubleBuffered(true);

	wxSizeEvent event;
	event.SetEventObject(this);
	OnSize(event);
}


G3BitmapButton::~G3BitmapButton()
{
	Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3BitmapButton::OnLeftDown ), NULL, this );
	Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( G3BitmapButton::OnEnterWindow ) );
	Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( G3BitmapButton::OnLeaveWindow ) );
	Disconnect( wxEVT_PAINT, wxPaintEventHandler( G3BitmapButton::OnPaint ), NULL, this );
	//Disconnect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( G3BitmapButton::OnEraseBackground), NULL, this );
}

void G3BitmapButton::OnLeftDown(wxMouseEvent& event)
{
	wxCommandEvent eventCommand(wxEVT_COMMAND_BUTTON_CLICKED, GetId());
	eventCommand.SetEventObject(this);
	GetEventHandler()->ProcessEvent(eventCommand);

	if(!m_bitmapChecked.IsNull())
	{
		//wxMessageBox("checked");

		m_bChecked=!m_bChecked;
		Refresh();
		wxCommandEvent eventCommand(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, GetId());
		eventCommand.SetEventObject(this);
		GetEventHandler()->ProcessEvent(eventCommand);
	}
}

void G3BitmapButton::OnEnterWindow( wxMouseEvent& event ) 
{
	m_bHover=true;

	Refresh();
}

void G3BitmapButton::OnLeaveWindow( wxMouseEvent& event ) 
{
	m_bHover=false;

	Refresh();
}

void G3BitmapButton::OnPaint(wxPaintEvent& event)
{
	wxPaintDC memDC(this);
	wxGCDC dc(memDC);
	if(m_bitmapNormal.IsNull() || m_bitmapHover.IsNull())
	{
		dc.SetBrush(*wxRED_BRUSH);
		dc.DrawRectangle(GetClientRect());
		return;
	}
	// 	

	dc.SetBackground(*wxTRANSPARENT_BRUSH );
	dc.Clear();

	if(m_bHover )
		dc.DrawBitmap(m_bitmapHover, 0, 0, true);
	else
		dc.DrawBitmap(m_bitmapNormal, 0, 0, true);

	if(!m_bitmapChecked.IsNull())
	{
		if(m_bChecked)
			dc.DrawBitmap(m_bitmapChecked, 0, 0, true);
	}

	// 	if(IsEnabled())
	// 		dc.SetTextForeground(wxSystemSettings::GetColour(wxBut))
	// 	else
	// 		dc.SetTextForeground(wxSystemSettings::GetColour(readonlky))

	if(m_strLabel.Len()>0)
	{
		//dc.SetClippingRegion(m_rect);
		dc.SetTextForeground(GetForegroundColour());
		dc.DrawLabel(m_strLabel, m_rect, wxALIGN_CENTER_VERTICAL);
		//dc.DestroyClippingRegion();
	}
}

// void G3BitmapButton::OnEraseBackground(wxEraseEvent& rEvent)
// {
// 
// }

wxSize G3BitmapButton::DoGetBestSize() const
{
	if(m_bitmapNormal.IsNull() || m_bitmapHover.IsNull())
		return wxSize(50, 50);

	wxSize bmpNormal=m_bitmapNormal.GetSize();
	wxSize bmpHover=m_bitmapHover.GetSize();

	wxSize bestSize=wxSize(bmpNormal.GetWidth()>bmpHover.GetWidth()?bmpNormal.GetWidth():bmpHover.GetWidth(),
		bmpNormal.GetHeight()>bmpHover.GetHeight()?bmpNormal.GetHeight():bmpHover.GetHeight());

	if(m_strLabel.Len()>0)
	{
		bestSize.SetWidth(bestSize.GetWidth()+GetTextExtent(m_strLabel).GetWidth()+5+5); //5 po lewej strone i 5 po prawej
	}

	return bestSize;
}

void G3BitmapButton::OnSize(wxSizeEvent& event)
{	
	m_rect=GetClientRect();

	if(m_bitmapNormal.IsNull() || m_bitmapHover.IsNull())
		return;

	if(m_bitmapNormal.GetWidth()>0 && m_bitmapNormal.GetHeight()>0)
	{
		m_rect=wxRect(m_bitmapNormal.GetWidth()+5, 0, m_rect.GetWidth()-m_bitmapNormal.GetWidth()-5, m_bitmapNormal.GetHeight());
	}	
}

bool G3BitmapButton::IsChecked() const
{
	return m_bChecked;
}

void G3BitmapButton::SetValue(bool state)
{
	m_bChecked=state;
}