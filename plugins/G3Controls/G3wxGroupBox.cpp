#include "G3wxGroupBox.h"

#include <wx/dcclient.h>
#include <wx/dcgraph.h>

#include <wx/dcmemory.h>

G3GroupBox::G3GroupBox():
m_label(_("G3GroupBox")),
	m_edgeColour(*wxBLACK),	
	m_uiEdgeWidth(1),
	m_uiBorderRoundSize(5)
{
}

G3GroupBox::G3GroupBox(wxWindow *parent, const wxString &label, wxColour edgeColor, int edgeWidth, int roundBorderSize,
	wxWindowID id, const wxPoint &pos, const wxSize &size, 
	long style, const wxString &name):		  
m_label(label),
	m_edgeColour(edgeColor),
	m_uiEdgeWidth(edgeWidth),
	m_uiBorderRoundSize(roundBorderSize)
{
	Create(parent, id, pos, size, style, name);

	Connect( wxEVT_PAINT, wxPaintEventHandler( G3GroupBox::OnPaint), NULL, this );	
	//Connect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( G3GroupBox::OnEraseBackground), NULL, this );
	Connect( wxEVT_SIZE, wxSizeEventHandler( G3GroupBox::OnSize), NULL, this );	

	wxSizeEvent event;
	event.SetEventObject(this);
	OnSize(event);
}

G3GroupBox::~G3GroupBox()
{
	Disconnect( wxEVT_PAINT, wxPaintEventHandler( G3GroupBox::OnPaint), NULL, this );	
	//	Disconnect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( G3GroupBox::OnEraseBackground), NULL, this );
	Disconnect( wxEVT_SIZE, wxSizeEventHandler( G3GroupBox::OnSize), NULL, this );	
}

void G3GroupBox::OnSize(wxSizeEvent& event)
{
	wxRect rc=GetVirtualSize();

	wxMemoryDC memDC;
	m_bmp=wxBitmap(rc.GetWidth(), rc.GetHeight());
	m_bmp.UseAlpha();

	memDC.SelectObject(m_bmp);

	wxGCDC dc( memDC );

	// 

	dc.SetBackground( *wxTRANSPARENT_BRUSH );

	dc.Clear();

	//memDC.GradientFillLinear(rc, m_gradientColour1, m_gradientColour2, m_gradientDirection);
	dc.SetPen(wxPen(m_edgeColour, m_uiEdgeWidth));
	//rc.Deflate(2);
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	dc.DrawRoundedRectangle(rc, m_uiBorderRoundSize);

	memDC.SelectObject(wxNullBitmap);

	//SetBackgroundBitmap(bitmap);

	Layout();
}

void G3GroupBox::OnPaint(wxPaintEvent& event)
{
	wxRect rc=wxPanel::GetClientRect();
	// 
	wxPaintDC memDC( this);

	wxGCDC dc( memDC );

	// 

	dc.SetBackground( *wxTRANSPARENT_BRUSH );

	dc.Clear();

	dc.DrawBitmap(m_bmp, 0,0, true);
}

// void G3GroupBox::OnEraseBackground(wxEraseEvent& rEvent)
// {
// 
// }

void G3GroupBox::SetEdgeWidth(int width)
{
	m_uiEdgeWidth=width;

	wxSizeEvent eventSize;
	OnSize(eventSize);
}

void G3GroupBox::SetRoundEdgeSize(int size)
{
	m_uiBorderRoundSize=size;

	wxSizeEvent eventSize;
	OnSize(eventSize);
}