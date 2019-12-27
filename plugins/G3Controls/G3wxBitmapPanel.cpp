#include "G3wxBitmapPanel.h"

#include <wx/dcclient.h>
#include <wx/dcgraph.h>

#include <wx/dcmemory.h>

G3BitmapPanel::G3BitmapPanel():
m_bGradientMode(false)
{
}

G3BitmapPanel::G3BitmapPanel(wxWindow *parent, wxBitmap &bitmap, wxWindowID id,
	const wxPoint &pos, const wxSize &size, long style, const wxString &name):
m_bGradientMode(false)
{
	Create(parent, id, pos, size, style, name);		

	SetBackgroundBitmap(bitmap);	
}

G3BitmapPanel::G3BitmapPanel(wxWindow *parent, wxColour gradientColour1, wxColour gradientColour2, wxDirection gradientDir, wxWindowID id,
	const wxPoint &pos, const wxSize &size, 
	long style, const wxString &name):
m_gradientColour1(gradientColour1),
	m_gradientColour2(gradientColour2),
	m_gradientDirection(gradientDir),
	m_bGradientMode(true)
{
	Create(parent, id, pos, size, style, name);

	Connect( wxEVT_SIZE, wxSizeEventHandler( G3BitmapPanel::OnSize), NULL, this );	
}

G3BitmapPanel::~G3BitmapPanel()
{
	if(m_bGradientMode)
		Disconnect( wxEVT_SIZE, wxSizeEventHandler( G3BitmapPanel::OnSize), NULL, this );	
}

void G3BitmapPanel::OnSize(wxSizeEvent& event)
{
	//wxRect rc=wxPanel::GetClientRect();
	wxRect rc=GetVirtualSize();

	wxMemoryDC memDC;
	wxBitmap bitmap (rc.GetWidth(), rc.GetHeight());

	memDC.SelectObject(bitmap);



	memDC.GradientFillLinear(rc, m_gradientColour1, m_gradientColour2, m_gradientDirection);
	// 		memDC.SetPen(*wxBLACK_PEN);

	// 		memDC.SetBrush(*wxTRANSPARENT_BRUSH);

	// 		memDC.DrawRectangle(rc);

	memDC.SelectObject(wxNullBitmap);

	SetBackgroundBitmap(bitmap);

	Layout();
}

void G3BitmapPanel::SetBitmap(const wxBitmap &bmp)
{
	if(m_bGradientMode)
	{
		Disconnect( wxEVT_SIZE, wxSizeEventHandler( G3BitmapPanel::OnSize), NULL, this );	
		m_bGradientMode=false;
	}

	SetBackgroundBitmap(bmp);
	Refresh();
}