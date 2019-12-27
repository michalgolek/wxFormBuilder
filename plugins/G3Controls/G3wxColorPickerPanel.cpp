#include "G3wxColorPickerPanel.h"

#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/valtext.h>
#include <wx/valnum.h>

//IMPLEMENT_DYNAMIC_CLASS(G3ColorPickerPanel, wxPanel);
IMPLEMENT_DYNAMIC_CLASS(G3ColorPickerPanel, wxPanel);

IMPLEMENT_DYNAMIC_CLASS(G3ColorPickerPanelEvent, wxNotifyEvent);

DEFINE_EVENT_TYPE(G3_EVT_COLORPICKER_CHANGE_VALUE)

// statyczne eventy, jesli uzywamy dynamicznych(Connect,Bind) to zakomentowac TABLE
// BEGIN_EVENT_TABLE( G3ImageBrowser, wxPanel )
// //EVT_G3_TABLE_(G3_EVT_IMAGEBROWSER_ITEM_SELECTED, wxID_ANY, G3ImageBrowser::OnImageBrowserEvent)
// EVT_G3_IMAGEBROWSER_ITEM_SELECTED(wxID_ANY, G3ImageBrowser::OnImageBrowserEvent )
// EVT_G3_IMAGEBROWSER_ITEM_BEGIN_DRAGGED(wxID_ANY, G3ImageBrowser::OnImageBrowserEvent )
// EVT_G3_IMAGEBROWSER_ITEM_END_DRAGGED(wxID_ANY, G3ImageBrowser::OnImageBrowserEvent )
// END_EVENT_TABLE

///////////////////////////////////////////////////////////////////////////

G3ColorPickerPanel::G3ColorPickerPanel()
{

}

G3ColorPickerPanel::G3ColorPickerPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size) : 
wxPanel(parent, id, pos, size),
	m_selectedComponent(3),
	m_lButtonDownColor(false),
	m_bButtonDownColor24(false)
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	m_bitmapColor = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 255,255 ), wxTAB_TRAVERSAL );
	m_bitmapColor->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );

	bSizer1->Add( m_bitmapColor, 0, wxALL, 7 );

	m_bitmapColor24 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 37,255 ), wxTAB_TRAVERSAL );
	m_bitmapColor24->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );

	bSizer1->Add( m_bitmapColor24, 0, wxTOP|wxBOTTOM, 7 );

	m_bitmapAlpha = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 37,255 ), wxTAB_TRAVERSAL );
	m_bitmapAlpha->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );

	bSizer1->Add( m_bitmapAlpha, 0, wxTOP|wxBOTTOM|wxLEFT, 7 );

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxVERTICAL );

	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_spinCtrlR = new wxSpinCtrl( this, ID_RSPIN, wxEmptyString, wxDefaultPosition, wxSize( 47,-1 ), wxSP_ARROW_KEYS, 0, 255, 255 );
	gbSizer1->Add( m_spinCtrlR, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxTOP, 5 );

	m_spinCtrlG = new wxSpinCtrl( this, ID_GSPIN, wxEmptyString, wxDefaultPosition, wxSize( 47,-1 ), wxSP_ARROW_KEYS, 0, 255, 255 );
	gbSizer1->Add( m_spinCtrlG, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxTOP, 5 );

	m_spinCtrlB = new wxSpinCtrl( this, ID_BSPIN, wxEmptyString, wxDefaultPosition, wxSize( 47,-1 ), wxSP_ARROW_KEYS, 0, 255, 255 );
	gbSizer1->Add( m_spinCtrlB, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxTOP, 5 );

	m_spinCtrlA = new wxSpinCtrl( this, ID_ASPIN, wxEmptyString, wxDefaultPosition, wxSize( 47,-1 ), wxSP_ARROW_KEYS, 0, 255, 255 );
	gbSizer1->Add( m_spinCtrlA, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxTOP, 5 );

	m_staticText6 = new wxStaticText( this, wxID_ANY, _("R"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	gbSizer1->Add( m_staticText6, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxTOP|wxRIGHT|wxLEFT, 5 );

	m_staticText61 = new wxStaticText( this, wxID_ANY, _("G"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	gbSizer1->Add( m_staticText61, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );

	m_staticText611 = new wxStaticText( this, wxID_ANY, _("B"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText611->Wrap( -1 );
	gbSizer1->Add( m_staticText611, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );

	m_staticText1 = new wxStaticText( this, wxID_ANY, _("A"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	gbSizer1->Add( m_staticText1, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );


	bSizer41->Add( gbSizer1, 0, 0, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_radioBtnH = new wxRadioButton( this, ID_H, _("H"), wxDefaultPosition, wxDefaultSize, 0 );
	m_radioBtnH->SetValue( true ); 
	bSizer5->Add( m_radioBtnH, 0, wxALL, 5 );

	m_radioBtnS = new wxRadioButton( this, ID_S, _("S"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_radioBtnS, 0, wxALL, 5 );

	m_radioBtnV = new wxRadioButton( this, ID_V, _("V"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_radioBtnV, 0, wxALL, 5 );

	m_bitmapCurrentColor = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 40,30 ), wxSTATIC_BORDER );
	m_bitmapCurrentColor->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWFRAME ) );

	bSizer5->Add( m_bitmapCurrentColor, 0, wxALL, 5 );

	m_bitmapPreviousColor = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 40,30 ), wxSTATIC_BORDER );
	m_bitmapPreviousColor->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWFRAME ) );

	bSizer5->Add( m_bitmapPreviousColor, 0, wxALL, 5 );


	bSizer41->Add( bSizer5, 0, 0, 5 );


	bSizer1->Add( bSizer41, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	// Connect Events
	m_bitmapColor->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3ColorPickerPanel::OnLeftDownColor ), NULL, this );
	m_bitmapColor->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( G3ColorPickerPanel::OnLeftUpColor ), NULL, this );
	m_bitmapColor->Connect( wxEVT_MOTION, wxMouseEventHandler( G3ColorPickerPanel::OnMotionColor ), NULL, this );
	m_bitmapColor->Connect( wxEVT_PAINT, wxPaintEventHandler( G3ColorPickerPanel::OnPaintColor ), NULL, this );
	m_bitmapColor24->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3ColorPickerPanel::OnLeftDownColor24 ), NULL, this );
	m_bitmapColor24->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( G3ColorPickerPanel::OnLeftUpColor24 ), NULL, this );
	m_bitmapColor24->Connect( wxEVT_MOTION, wxMouseEventHandler( G3ColorPickerPanel::OnMotionColor24 ), NULL, this );
	m_bitmapColor24->Connect( wxEVT_PAINT, wxPaintEventHandler( G3ColorPickerPanel::OnPaintColor24 ), NULL, this );
	m_bitmapAlpha->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3ColorPickerPanel::OnLeftDownAlpha ), NULL, this );
	m_bitmapAlpha->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( G3ColorPickerPanel::OnLeftUpAlpha ), NULL, this );
	m_bitmapAlpha->Connect( wxEVT_MOTION, wxMouseEventHandler( G3ColorPickerPanel::OnMotionAlpha ), NULL, this );
	m_bitmapAlpha->Connect( wxEVT_PAINT, wxPaintEventHandler( G3ColorPickerPanel::OnPaintAlpha ), NULL, this );
	m_radioBtnH->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( G3ColorPickerPanel::OnRadioButton ), NULL, this );
	m_radioBtnS->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( G3ColorPickerPanel::OnRadioButton ), NULL, this );
	m_radioBtnV->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( G3ColorPickerPanel::OnRadioButton ), NULL, this );
	m_spinCtrlR->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( G3ColorPickerPanel::OnSpinCtrl ), NULL, this );
	m_spinCtrlG->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( G3ColorPickerPanel::OnSpinCtrl ), NULL, this );
	m_spinCtrlB->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( G3ColorPickerPanel::OnSpinCtrl ), NULL, this );
	m_spinCtrlA->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( G3ColorPickerPanel::OnSpinCtrl ), NULL, this );
	m_bitmapPreviousColor->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3ColorPickerPanel::OnLeftDownCurrentColor ), NULL, this );
	m_bitmapPreviousColor->Connect( wxEVT_PAINT, wxPaintEventHandler( G3ColorPickerPanel:: OnPaintPreviousColor), NULL, this );
	m_bitmapCurrentColor->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3ColorPickerPanel::OnLeftDownPreviousColor ), NULL, this );
	m_bitmapCurrentColor->Connect( wxEVT_PAINT, wxPaintEventHandler( G3ColorPickerPanel::OnPaintCurrentColor), NULL, this );
	// my events
	m_bitmapColor->Connect(wxEVT_MOUSE_CAPTURE_LOST, wxMouseCaptureLostEventHandler(G3ColorPickerPanel::OnMouseCaptureLost), NULL, this);
	
	this->Connect( wxID_ANY, G3_EVT_COLORPICKER_CHANGE_VALUE, G3ColorPickerPanelEventHandler( G3ColorPickerPanel::OnColorPickerEvent ));
	
	//////////////////////////////////////////////////////////////////////////
	m_bitmapColor->SetDoubleBuffered(true);
	m_bitmapColor24->SetDoubleBuffered(true);
	m_bitmapAlpha->SetDoubleBuffered(true);
	m_bitmapCurrentColor->SetDoubleBuffered(true);

	SetRGBA(*wxRED);

	PaintColor();
	PaintColor24();	
	PaintAlpha();
}

G3ColorPickerPanel::~G3ColorPickerPanel()
{
	// My Events
	m_bitmapColor->Disconnect(wxEVT_MOUSE_CAPTURE_LOST, wxMouseCaptureLostEventHandler(G3ColorPickerPanel::OnMouseCaptureLost), NULL, this);

	this->Disconnect( wxID_ANY, G3_EVT_COLORPICKER_CHANGE_VALUE, G3ColorPickerPanelEventHandler( G3ColorPickerPanel::OnColorPickerEvent ));

	// Disconnect Events
	m_bitmapColor->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3ColorPickerPanel::OnLeftDownColor ), NULL, this );
	m_bitmapColor->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( G3ColorPickerPanel::OnLeftUpColor ), NULL, this );
	m_bitmapColor->Disconnect( wxEVT_MOTION, wxMouseEventHandler( G3ColorPickerPanel::OnMotionColor ), NULL, this );
	m_bitmapColor->Disconnect( wxEVT_PAINT, wxPaintEventHandler( G3ColorPickerPanel::OnPaintColor ), NULL, this );
	m_bitmapColor24->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3ColorPickerPanel::OnLeftDownColor24 ), NULL, this );
	m_bitmapColor24->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( G3ColorPickerPanel::OnLeftUpColor24 ), NULL, this );
	m_bitmapColor24->Disconnect( wxEVT_MOTION, wxMouseEventHandler( G3ColorPickerPanel::OnMotionColor24 ), NULL, this );
	m_bitmapColor24->Disconnect( wxEVT_PAINT, wxPaintEventHandler( G3ColorPickerPanel::OnPaintColor24 ), NULL, this );
	m_bitmapAlpha->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3ColorPickerPanel::OnLeftDownAlpha ), NULL, this );
	m_bitmapAlpha->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( G3ColorPickerPanel::OnLeftUpAlpha ), NULL, this );
	m_bitmapAlpha->Disconnect( wxEVT_MOTION, wxMouseEventHandler( G3ColorPickerPanel::OnMotionAlpha ), NULL, this );
	m_bitmapAlpha->Disconnect( wxEVT_PAINT, wxPaintEventHandler( G3ColorPickerPanel::OnPaintAlpha ), NULL, this );
	m_radioBtnH->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( G3ColorPickerPanel::OnRadioButton ), NULL, this );
	m_radioBtnS->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( G3ColorPickerPanel::OnRadioButton ), NULL, this );
	m_radioBtnV->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( G3ColorPickerPanel::OnRadioButton ), NULL, this );
	m_spinCtrlR->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( G3ColorPickerPanel::OnSpinCtrl ), NULL, this );
	m_spinCtrlG->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( G3ColorPickerPanel::OnSpinCtrl ), NULL, this );
	m_spinCtrlB->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( G3ColorPickerPanel::OnSpinCtrl ), NULL, this );
	m_spinCtrlA->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( G3ColorPickerPanel::OnSpinCtrl ), NULL, this );
	m_bitmapPreviousColor->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3ColorPickerPanel::OnLeftDownCurrentColor ), NULL, this );
	m_bitmapPreviousColor->Disconnect( wxEVT_PAINT, wxPaintEventHandler( G3ColorPickerPanel::OnPaintPreviousColor), NULL, this );
	m_bitmapCurrentColor->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3ColorPickerPanel::OnLeftDownPreviousColor ), NULL, this );
	m_bitmapCurrentColor->Disconnect( wxEVT_PAINT, wxPaintEventHandler( G3ColorPickerPanel::OnPaintCurrentColor  ), NULL, this );
}

void G3ColorPickerPanel::OnLeftDownColor( wxMouseEvent& event )
{
	m_lButtonDownColor=true;
	
	picker.h=(unsigned short) picker.h;
	picker.s=(unsigned short)(event.GetX()/255.0*100.0);
	picker.v=(unsigned short)((255-event.GetY())/255.0*100.0);
	picker.UpdateRGB();

	UpdateValues(picker);

	m_bitmapColor->Refresh();
	m_bitmapColor24->Refresh();
	m_bitmapAlpha->Refresh();
	m_bitmapCurrentColor->Refresh();

	//if(!HasCapture())CaptureMouse();	
}

void G3ColorPickerPanel::OnLeftUpColor( wxMouseEvent& event )
{
	m_lButtonDownColor=false;	

	//if(HasCapture()) ReleaseMouse(); 
}

void G3ColorPickerPanel::OnMotionColor( wxMouseEvent& event )
{
	if(m_lButtonDownColor)
	{
	}
}

void G3ColorPickerPanel::OnLeftDownColor24( wxMouseEvent& event )
{
	m_bButtonDownColor24=true;
	
	picker.h=(unsigned short) ((255 - event.GetY())/255.0*359.0);
	picker.s=picker.s;
	picker.v=picker.v;
	picker.UpdateRGB();

	UpdateValues(picker);

	m_bitmapColor->Refresh();
	m_bitmapColor24->Refresh();
	m_bitmapAlpha->Refresh();
	m_bitmapCurrentColor->Refresh();
}

void G3ColorPickerPanel::OnLeftUpColor24( wxMouseEvent& event )
{
	m_bButtonDownColor24=false;
}

void G3ColorPickerPanel::OnMotionColor24( wxMouseEvent& event )
{
	if(m_bButtonDownColor24)
	{
		m_bitmapColor->Refresh();
		m_bitmapColor24->Refresh();
		m_bitmapCurrentColor->Refresh();
	}
}

void G3ColorPickerPanel::OnPaintColor( wxPaintEvent& event )
{
	wxPaintDC dc(m_bitmapColor);

	wxSize clientRect=m_bitmapColor->GetSize();

	switch(m_selectedComponent)
	{
	case 3: //HUE
		{			
			double sat, val, step;
			SColour *tempcol=new SColour();
			
			sat = val = 0.0;
			step = 100.0/255.0;

			tempcol->h = (unsigned short) picker.h;
			tempcol->s = (unsigned short) sat;
			tempcol->v = (unsigned short) val;

			for (int y=255; y>0; y--)
			{
				for (int x=0; x<255; x++)
				{			
					tempcol->UpdateRGB();
					dc.SetPen(wxPen(wxColour(tempcol->r, tempcol->g, tempcol->b)));
					dc.DrawPoint(x, y);	

					sat += step;
					tempcol->s = (unsigned short) sat;
				}

				val += step;
				sat = 0.0;
				tempcol->v = (unsigned short) val;
				//					tempcol->UpdateRGB();
			}

			// Draws circle
			tempcol->s = (unsigned short) picker.s;
			tempcol->v = (unsigned short) picker.v;
			tempcol->UpdateRGB();
			
			
			
 			dc.SetPen(wxPen(wxColour(255-picker.r, 255-picker.g, 255-picker.b), 1, wxPENSTYLE_SOLID));
 			dc.SetBrush(wxBrush(wxColour(), wxBRUSHSTYLE_TRANSPARENT));
 			dc.DrawCircle((int)(tempcol->s/step), 255-(int)(tempcol->v/step), 5);				delete tempcol;
// 			
			// Draws circle
			// 			tempcol->s = (unsigned short) GetDlgItemInt(hDlg, IDC_SATURATION, NULL, false);
			// 			tempcol->v = (unsigned short) GetDlgItemInt(hDlg, IDC_VALUE, NULL, false);
			// 			tempcol->UpdateRGB();
			// 
			// 			pen = CreatePen(PS_SOLID, 1, RGB(255-tempcol->r, 255-tempcol->g, 255-tempcol->b));
			// 			SelectObject(hcomp, pen);
			// 
			// 			Arc(hcomp, (int)(tempcol->s/step)-5, 255-(int)(tempcol->v/step)+5, (int)(tempcol->s/step)+5, 
			// 				255-(int)(tempcol->v/step)-5, 0, 0, 0, 0		}
		}
		break;
	case 4: //SATURATION
		{
			//double hue, val, step, step2;
			////SColour tempcol;

			//hue = val = 0.0;
			//step2 = 359.0/255.0;
			//step = 100.0/255.0;

			//m_iHue = (unsigned short) hue;
			////m_iSat = (unsigned short) GetDlgItemInt(hDlg, IDC_SATURATION, NULL, false);
			//m_iVal = (unsigned short) val;

			//for (int y=255; y>0; y--)
			//{
			//	for (int x=0; x<255; x++)
			//	{
			//		UpdateRGB();
			//		dc.SetPen(wxPen(wxColour(picker.r, picker.g, picker.b)));
			//		dc.DrawPoint(x, y);		


			//		hue += step2;
			//		m_iHue = (unsigned short) hue;
			//		//						tempcol->UpdateRGB();
			//	}

			//	val += step;
			//	hue = 0.0;
			//	m_iVal = (unsigned short) val;
			//}


			// Draws circle
			// 			tempcol->h = (unsigned short) GetDlgItemInt(hDlg, IDC_HUE, NULL, false);
			// 			tempcol->v = (unsigned short) GetDlgItemInt(hDlg, IDC_VALUE, NULL, false);
			// 			tempcol->UpdateRGB();
			// 
			// 			pen = CreatePen(PS_SOLID, 1, RGB(255-tempcol->r, 255-tempcol->g, 255-tempcol->b));
			// 			SelectObject(hcomp, pen);
			// 
			// 			Arc(hcomp, (int)(tempcol->h/step2)-5, 255-(int)(tempcol->v/step)+5, (int)(tempcol->h/step2)+5, 
			// 				255-(int)(tempcol->v/step)-5, 0, 0, 0, 0);
		}	
		break;
	case 5: //VALUE
		{
// 			double hue, sat, step, step2;
// 
// 			hue = sat = 0.0;
// 			step2 = 359.0/255.0;
// 			step = 100.0/255.0;
// 
// 			m_iHue = (unsigned short) hue;
// 			m_iSat = (unsigned short) sat;
// 			//tempcol->v = (unsigned short) GetDlgItemInt(hDlg, IDC_VALUE, NULL, false);
// 
// 			for (int y=255; y>0; y--)
// 			{
// 				for (int x=0; x<255; x++)
// 				{
// 					UpdateRGB();
// 					dc.SetPen(wxPen(wxColour(m_iRed, m_iGreen, m_iBlue)));
// 					dc.DrawPoint(x, y);	
// 					hue += step2;
// 					m_iHue = (unsigned short) hue;
// 					//						tempcol->UpdateRGB();
// 				}
// 
// 				sat += step;
// 				hue = 0.0;
// 				m_iSat = (unsigned short) sat;
			}
		break;

	}	
}

void G3ColorPickerPanel::OnPaintColor24( wxPaintEvent& event )
{
	wxPaintDC dc(m_bitmapColor24);

	wxSize clientRect=m_bitmapColor24->GetSize();
	
	dc.SetBrush(wxBrush(*wxLIGHT_GREY));
	dc.SetPen(wxPen(*wxLIGHT_GREY, 0));
	dc.DrawRectangle(clientRect);

	switch(m_selectedComponent)
	{
	case 3: //H
		{
			double hue, step;
			SColour *tempcol=new SColour();
			hue = 0.0;
			
			tempcol->h= 0;
			tempcol->s= 100;
			tempcol->v=100;

			step = 359.0/255.0;

			for (int y=255; y>0; y--) // NB: 255 is the height of IDC_COLOR and IDC_COLOR1
			{
				tempcol->UpdateRGB();

				for (int x=6; x<clientRect.GetWidth()-6; x++)
				{
					dc.SetPen(wxPen(wxColour(tempcol->r, tempcol->g, tempcol->b)));
					dc.DrawPoint(x, y);
				}

				hue += step;
				tempcol->h = hue;
			}
			delete tempcol;

			hue = (double) picker.h;
			hue = hue / step;

			dc.SetPen(wxPen(*wxBLACK));
			
			dc.DrawLine(0, 255-((int)(hue)-5), 5, 255-((int)(hue)));
			dc.DrawLine(5, 255-((int)(hue)), 0, 255-((int)(hue+5)));
			dc.DrawLine(0, 255-((int)(hue)+5), 0, 255-((int)(hue-5)));

			dc.DrawLine(clientRect.GetWidth()-1,255- ((int)(hue)-5), clientRect.GetWidth()-6, 255-((int)(hue)));
			dc.DrawLine(clientRect.GetWidth()-6, 255-((int)(hue)), clientRect.GetWidth()-1, 255-((int)(hue+5)));
			dc.DrawLine(clientRect.GetWidth()-1, 255-((int)(hue)-5), clientRect.GetWidth()-1, 255-((int)(hue+5)));
		}
		break;
	case 4: //V
		{
// 			double sat, step;
// 
// 			sat = 0.0;
// 			
// 			step = 100.0/255.0;
// 
// 			for (int y=255; y>0; y--) // NB: 255 is the height of IDC_COLOR and IDC_COLOR1
// 			{
// 				UpdateRGB();
// 
// 				for (int x=6; x<clientRect.GetWidth()-6; x++)
// 				{
// 					dc.SetPen(wxPen(wxColour(picker.r, picker.g, picker.b)));
// 					dc.DrawPoint(x, y);
// 				}
// 
// 				sat += step;
// 				m_iSat = sat;
// 			}
// 
// 			sat = (double) m_iSat;
// 			sat = sat / step;
// 
// 			dc.SetPen(wxPen(*wxBLACK));
// 			dc.DrawLine(0, ((int)(sat)-5), 5, ((int)(sat)));
// 			dc.DrawLine(5, ((int)(sat)), 0, ((int)(sat+5)));
// 			dc.DrawLine(0, ((int)(sat)+5), 0, ((int)(sat-5)));
		}
		break;
	}
}

void G3ColorPickerPanel::OnLeftDownAlpha( wxMouseEvent& event )
{
	m_lButtonDownColor=true;
		
	picker.a=255-(unsigned short) event.GetY();
	picker.UpdateRGB();

	UpdateValues(picker);
		
	m_bitmapAlpha->Refresh();
	m_bitmapCurrentColor->Refresh();

	//if(!HasCapture())CaptureMouse();
}

void G3ColorPickerPanel::OnLeftUpAlpha( wxMouseEvent& event )
{

}

void G3ColorPickerPanel::OnMotionAlpha( wxMouseEvent& event )
{

}

void G3ColorPickerPanel::OnPaintAlpha( wxPaintEvent& event )
{
	wxPaintDC dc(m_bitmapAlpha);

	wxSize clientRect=m_bitmapAlpha->GetSize();

	dc.SetBrush(wxBrush(*wxLIGHT_GREY));
	dc.SetPen(wxPen(*wxLIGHT_GREY, 0));
	dc.DrawRectangle(clientRect);
	
	wxSize checkboardStretch=wxSize((clientRect.GetWidth()-12)/2, (clientRect.GetWidth()-12)/2);
	
	wxColour m_checkboardColor1=wxColour(200, 200, 200);
	wxColour m_checkboardColor2=wxColour(140, 140, 140);

	switch(m_selectedComponent)
	{
	case 3: //H
		{			
			for (int y=255; y>0; y--) // NB: 255 is the height of IDC_COLOR and IDC_COLOR1
			{				
				float alpha=y/(float)255.0f;

				for (int x=6; x<clientRect.GetWidth()-6; x++)
				{
					
					int rSrc=picker.r;
					int gSrc=picker.g;
					int bSrc=picker.b;

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


					dc.SetPen(wxPen(wxColour(r, g, b)));
					dc.DrawPoint(x, y);
				}
			}
		
 			dc.SetPen(wxPen(*wxBLACK));
 
			dc.DrawLine(0, 255-((int)(picker.a)-5), 5, 255-((int)(picker.a)));
			dc.DrawLine(5, 255-((int)(picker.a)), 0, 255-((int)(picker.a+5)));
			dc.DrawLine(0, 255-((int)(picker.a)+5), 0, 255-((int)(picker.a-5)));

			dc.DrawLine(clientRect.GetWidth()-1,255- ((int)(picker.a)-5), clientRect.GetWidth()-6, 255-((int)(picker.a)));
			dc.DrawLine(clientRect.GetWidth()-6, 255-((int)(picker.a)), clientRect.GetWidth()-1, 255-((int)(picker.a+5)));
			dc.DrawLine(clientRect.GetWidth()-1, 255-((int)(picker.a)-5), clientRect.GetWidth()-1, 255-((int)(picker.a+5)));
		}
		break;
	case 4: //V
		{
		}
		break;
	}
}

void G3ColorPickerPanel::OnSpinCtrl( wxSpinEvent& event )
{
	picker.rPrev=picker.r;
	picker.gPrev=picker.g;
	picker.bPrev=picker.b;
	picker.aPrev=picker.a;

	switch(event.GetId())
	{
	case ID_RSPIN:
		picker.r=event.GetValue();

		m_bitmapColor->Refresh();
		m_bitmapColor24->Refresh();
		m_bitmapAlpha->Refresh();
		m_bitmapCurrentColor->Refresh();
		break;
	case ID_GSPIN:
		picker.g=event.GetValue();

		m_bitmapColor->Refresh();
		m_bitmapColor24->Refresh();
		m_bitmapAlpha->Refresh();
		m_bitmapCurrentColor->Refresh();
		break;
	case ID_BSPIN:
		picker.b=event.GetValue();

		m_bitmapColor->Refresh();
		m_bitmapColor24->Refresh();
		m_bitmapAlpha->Refresh();
		m_bitmapCurrentColor->Refresh();
		break;	
	case ID_ASPIN:
		picker.a=event.GetValue();

		m_bitmapAlpha->Refresh();
		m_bitmapCurrentColor->Refresh();
		break;	
	}

	picker.UpdateHSV();

	G3ColorPickerPanelEvent eventChangeValue( G3_EVT_COLORPICKER_CHANGE_VALUE, GetId(), GetColour(), GetPrevColour());
	eventChangeValue.SetEventObject(this);
	GetEventHandler()->ProcessEvent(eventChangeValue);
}

void G3ColorPickerPanel::OnRadioButton( wxCommandEvent& event )
{
	switch(event.GetId())
	{
	case ID_H:
		m_selectedComponent=3;
		break;
	case ID_S:
		m_selectedComponent=4;
		break;
	case ID_V:
		m_selectedComponent=5;		
		break;
	}

	PaintColor();
	PaintColor24();		

	m_bitmapColor->Refresh();
	m_bitmapColor24->Refresh();
	m_bitmapAlpha->Refresh();
	m_bitmapCurrentColor->Refresh();
}

void G3ColorPickerPanel::OnPaintCurrentColor( wxPaintEvent& event )
{
	wxPaintDC dc(m_bitmapCurrentColor);

	wxSize clientSize=m_bitmapCurrentColor->GetSize();

	//ToDo ?
// 	if(!m_bUseAlpha)
// 	{
// 		// 	dc.SetBrush(wxBrush(GetColour()));
// 		// 	dc.SetPen(wxPen(GetColour(), 0));
// 		// 	dc.DrawRectangle(clientSize);
// 	}
// 	else

	
	wxSize checkboardStretch=wxSize((clientSize.GetWidth())/3, (clientSize.GetHeight())/3);

	wxColour m_checkboardColor1=wxColour(200, 200, 200);
	wxColour m_checkboardColor2=wxColour(140, 140, 140);

	for (int x=0;x<clientSize.GetWidth();x++)
	{
		for (int y=0; y<clientSize.GetHeight();y++)
		{				
			float alpha=1.0f-picker.a/(float)255.0f;
						
			int rSrc=GetColour().Red();
			int gSrc=GetColour().Green();
			int bSrc=GetColour().Blue();

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


			dc.SetPen(wxPen(wxColour(r, g, b)));
			dc.DrawPoint(x, y);
			
		}
	}
}

void G3ColorPickerPanel::OnLeftDownCurrentColor( wxMouseEvent& event )
{

}

void G3ColorPickerPanel::OnLeftDownPreviousColor( wxMouseEvent& event )
{

}

void G3ColorPickerPanel::OnPaintPreviousColor( wxPaintEvent& event )
{

}

void G3ColorPickerPanel::PaintColor()
{
}

void G3ColorPickerPanel::PaintColor24()
{

	
}

void G3ColorPickerPanel::PaintAlpha()
{

}

void G3ColorPickerPanel::UpdateValues(SColour &colour)
{
	// 	m_textCtrlR->ChangeValue(wxString::Format("%i",colour.r));	
	// 	m_textCtrlG->ChangeValue(wxString::Format("%i",colour.g));
	// 	m_textCtrlB->ChangeValue(wxString::Format("%i",colour.b));
	// 	m_textCtrlA->ChangeValue(wxString::Format("%i",colour.a));	

	m_spinCtrlR->SetValue(wxString::Format("%i",colour.r));
	m_spinCtrlG->SetValue(wxString::Format("%i",colour.g));
	m_spinCtrlB->SetValue(wxString::Format("%i",colour.b));
	m_spinCtrlA->SetValue(wxString::Format("%i",colour.a));

	G3ColorPickerPanelEvent eventChangeValue( G3_EVT_COLORPICKER_CHANGE_VALUE, GetId(), GetColour(), GetPrevColour());
	eventChangeValue.SetEventObject(this);
	GetEventHandler()->ProcessEvent(eventChangeValue);
}

void G3ColorPickerPanel::OnMouseCaptureLost(wxMouseCaptureLostEvent &event) 
{ 
	m_lButtonDownColor=false;	

	//if(HasCapture())
	//	ReleaseMouse(); 
}

void SColour::UpdateRGB()
{
	int conv;
	double hue, sat, val;
	int base;

	hue = (float)h / 100.0f;
	sat = (float)s / 100.0f;
	val = (float)v / 100.0f;

	if ((float)s == 0) // Acromatic color (gray). Hue doesn't mind.
	{
		conv = (unsigned short) (255.0f * val);
		r = b = g = conv;
		return;
	}

	base = (unsigned short)(255.0f * (1.0 - sat) * val);

	switch ((unsigned short)((float)h/60.0f))
	{
	case 0:
		r = (unsigned short)(255.0f * val);
		g = (unsigned short)((255.0f * val - base) * (h/60.0f) + base);
		b = base;
		break;

	case 1:
		r = (unsigned short)((255.0f * val - base) * (1.0f - ((h%60)/ 60.0f)) + base);
		g = (unsigned short)(255.0f * val);
		b = base;
		break;

	case 2:
		r = base;
		g = (unsigned short)(255.0f * val);
		b = (unsigned short)((255.0f * val - base) * ((h%60)/60.0f) + base);
		break;

	case 3:
		r = base;
		g = (unsigned short)((255.0f * val - base) * (1.0f - ((h%60) / 60.0f)) + base);
		b = (unsigned short)(255.0f * val);
		break;

	case 4:
		r = (unsigned short)((255.0f * val - base) * ((h%60) / 60.0f) + base);
		g = base;
		b = (unsigned short)(255.0f * val);
		break;

	case 5:
		r = (unsigned short)(255.0f * val);
		g = base;
		b = (unsigned short)((255.0f * val - base) * (1.0f - ((h%60) / 60.0f)) + base);
		break;
	}
}

// Updates the HSV color from the RGB
void SColour::UpdateHSV()
{
	unsigned short max, min, delta;
	short temp;

	max = MAX(r, g, b);
	min = MIN(r, g, b);
	delta = max-min;

	if (max == 0)
	{
		s = h = v = 0;
		return;
	}

	v = (unsigned short) ((double)max/255.0*100.0);
	s = (unsigned short) (((double)delta/max)*100.0);

	if (r == max)
		temp = (short)(60 * ((g-b) / (double) delta));
	else if (g == max)
		temp = (short)(60 * (2.0 + (b-r) / (double) delta));
	else
		temp = (short)(60 * (4.0 + (r-g) / (double) delta));

	if (temp<0)
		h = temp + 360;
	else
		h = temp;
}

void G3ColorPickerPanel::SetRGB(const wxColour &colour)
{
	picker.rPrev=picker.r;
	picker.gPrev=picker.g;
	picker.bPrev=picker.b;
	picker.aPrev=picker.a;
	
	picker.r=colour.Red();
	picker.g=colour.Green();
	picker.b=colour.Blue();
	picker.UpdateHSV();

	UpdateValues(picker);
}

void G3ColorPickerPanel::SetAlpha(int alpha)
{	
	picker.a=alpha;

	UpdateValues(picker);
}

void G3ColorPickerPanel::SetRGBA(const wxColour &colour)
{
	picker.rPrev=picker.r;
	picker.gPrev=picker.g;
	picker.bPrev=picker.b;
	picker.aPrev=picker.a;

	picker.r=colour.Red();
	picker.g=colour.Green();
	picker.b=colour.Blue();
	picker.a=colour.Alpha();
	picker.UpdateHSV();

	UpdateValues(picker);
}

wxColour G3ColorPickerPanel::GetColour() const
{
	return wxColour(picker.r, picker.g, picker.b, picker.a);
}

wxColour G3ColorPickerPanel::GetPrevColour() const
{
	return wxColour(picker.rPrev, picker.gPrev, picker.bPrev, picker.aPrev);
}

void G3ColorPickerPanel::OnColorPickerEvent( G3ColorPickerPanelEvent& event )
{

}

//////////////////////////////////////////////////////////////////////////

G3ColorPickerPanelEvent::G3ColorPickerPanelEvent(wxEventType commandType, int id, const wxColour& currentColour, const wxColour& previousColour)
	:wxNotifyEvent(commandType, id)
{
	m_currentColour=currentColour;
	m_previousColour=previousColour;
}

wxColour G3ColorPickerPanelEvent::GetCurrentColour() const
{
	return m_currentColour;
}

wxColour G3ColorPickerPanelEvent::GetPreviousColour() const
{
	return m_previousColour;
}
