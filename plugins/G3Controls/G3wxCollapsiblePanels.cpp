#include "G3wxCollapsiblePanels.h"

//using namespace Editor;
#include <wx/dcclient.h>
#include <wx/window.h>

IMPLEMENT_DYNAMIC_CLASS(G3CollapsiblePanels, wxControl);

class G3CollapsiblePanelsToggleEvent : public wxEvtHandler
{
private:
	G3CollapsiblePanels *m_collPanels;
	wxPanel* m_panel;
	wxToggleButton  *m_button;

	void OnToggle(wxCommandEvent &event)
	{
		if(event.IsChecked())
			m_panel->Show();
		else
			m_panel->Hide();

		m_collPanels->GetScrolledWnd()->Layout();
		m_collPanels->GetScrolledWnd()->GetParent()->Layout();
	}

	void OnPaint(wxPaintEvent &event)
	{
		wxPaintDC dc(m_button);
		
		wxRect clientRect=m_button->GetClientSize();

		//if(m_collPanels->GetWindowStyle() & G3_CP_SIMPLE_BACKGROUND)
		switch(m_collPanels->GetStyle())
		{
		case G3_CP_SIMPLE_BACKGROUND:
			//dc.DrawRoundedRectangle(clientRect, 6);
			dc.SetPen(wxPen(m_collPanels->GetFrameColour(), 1));
			if(m_button->GetValue())
				dc.SetBrush(m_collPanels->GetBgColour1());
			else
				dc.SetBrush(m_collPanels->GetBgColour2());

			dc.DrawRoundedRectangle(clientRect, 6);
			break;
		case G3_CP_GRADIENTBACKGROUND:
			if(m_button->GetValue())
				dc.SetBrush(m_collPanels->GetBgColour1());
			else
				dc.SetBrush(m_collPanels->GetBgColour2());

			dc.SetPen(wxPen(m_collPanels->GetFrameColour(), 1));

			if(m_button->GetValue())
				dc.GradientFillLinear(clientRect, m_collPanels->GetBgGradientColour1(), m_collPanels->GetBgGradientColour2(), wxNORTH);
			else 
				dc.GradientFillLinear(clientRect, m_collPanels->GetBgColour1(), m_collPanels->GetBgColour2(), wxSOUTH);

			dc.SetBrush(wxBrush(*wxBLACK, wxBRUSHSTYLE_TRANSPARENT));
			dc.DrawRectangle(clientRect);
			break;
		}
		
// 		if(m_collPanels->GetWindowStyle() & G3_CP_GRADIENTBACKGROUND)
// 		{
// 			
// 		}		
				
		wxSize textSize=dc.GetTextExtent(m_button->GetLabel());
		
		dc.SetFont(m_collPanels->GetLabelFont());		
		dc.SetTextForeground(m_collPanels->GetLabelColour());
		dc.DrawText(m_button->GetLabel(), wxPoint(clientRect.GetWidth()/2-textSize.GetWidth()/2, clientRect.GetHeight()/2-textSize.GetHeight()/2));

		if(m_button->GetValue())
			dc.DrawText(_("-"), wxPoint(10, clientRect.GetHeight()/2-textSize.GetHeight()/2));
		else
			dc.DrawText(_("+"), wxPoint(10, clientRect.GetHeight()/2-textSize.GetHeight()/2));
	}

public:
	G3CollapsiblePanelsToggleEvent(G3CollapsiblePanels *collPanels, wxPanel *panel, wxToggleButton *btn):
	  m_collPanels(collPanels),
	  m_panel(panel),
	  m_button(btn)
	  {

	  }
	  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE( G3CollapsiblePanelsToggleEvent, wxEvtHandler )
	EVT_TOGGLEBUTTON(wxID_ANY, G3CollapsiblePanelsToggleEvent::OnToggle)
	EVT_PAINT(G3CollapsiblePanelsToggleEvent::OnPaint)
END_EVENT_TABLE()

G3CollapsiblePanels::G3CollapsiblePanels()
{

}

G3CollapsiblePanels::G3CollapsiblePanels( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ):
wxControl(parent, id, pos, size, style),
	m_iStyle(G3_CP_SIMPLE_BACKGROUND),
	m_labelColour(*wxBLACK),
	m_bgColor1(wxColour(222, 222, 222)),
	m_bgColor2(wxColour(190, 190, 190)),
	m_bgGradientColor1(wxColour(200, 200, 200)),
	m_bgGradientColor2(wxColour(150, 150, 150)),
	m_frameColour(*wxBLACK)
{
	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );

	bSizer1 = new wxBoxSizer( wxVERTICAL );

	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	SetLabelFont(wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier 10 Pitch"));
}
 
G3CollapsiblePanels::~G3CollapsiblePanels()
{
	wxList::iterator it;
	for (it=m_pageLists.begin();it!=m_pageLists.end();++it)
	{
		G3CollapsiblePanelPage *colPane=(G3CollapsiblePanelPage *) (*it);
		if(colPane)
		{
			colPane->m_pToggleButton->PopEventHandler();
		}
	}
}

wxToggleButton *G3CollapsiblePanels::AddPage(wxPanel *panel, const wxString &label, bool closed)
{
	wxPanel *m_panel1 = new wxPanel( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );			

	wxToggleButton *m_button1 = new wxToggleButton( m_panel1, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, 0 );	
	//GetWindowStyleFlag() & G3_CP_DEFAULT) ?? dodac ?
	m_button1->PushEventHandler( new G3CollapsiblePanelsToggleEvent(this, panel, m_button1) );	
	//m_button1->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(G3CollapsiblePanels::OnToggle ), panel, this );
	//m_button1->SetClientData(panel);	

	if(closed)
	{
		panel ->Hide();
		m_button1->SetValue(false);
	}
	else
	{
		panel ->Show();
		m_button1->SetValue(true);
	}

	bSizer3->Add( m_button1, 0, wxALL|wxEXPAND, 0 );

	panel->Reparent(m_panel1);
	bSizer3->Add( panel, 0, wxALL|wxEXPAND, 0 );

	m_panel1->SetSizer( bSizer3 );
	m_panel1->Layout();
	bSizer3->Fit( m_panel1 );
	bSizer2->Add( m_panel1, 0, wxEXPAND | wxALL, 0 );

	
 	G3CollapsiblePanelPage *page=new G3CollapsiblePanelPage();
 	page->m_label=label;
 	page->m_pToggleButton=m_button1;
 
 	m_pageLists.push_back(page);

	return m_button1;
}

// void G3CollapsiblePanels::OnToggle( wxCommandEvent& event )
// {
// 	wxPanel *panel=(wxPanel*)event.GetClientData();
// 	
// 	if(event.IsChecked())
// 		panel->Show();
// 	else
// 		panel->Hide();
// 
// 	m_scrolledWindow1->Layout();
// 	m_scrolledWindow1->GetParent()->Layout();
// }

G3CollapsiblePanelPage::G3CollapsiblePanelPage()
{

}

G3CollapsiblePanelPage::~G3CollapsiblePanelPage()
{	
	// Disconnect Events
	//m_pToggleButton->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( G3CollapsiblePanels::OnToggle ));
}

//
//bool RemovePage(const wxString &label)
//{
//
//}
//
//bool RemovePage(int index)
//{
//
//}
//
//int GetNumPages() const
//{
//}

void G3CollapsiblePanels::Finalize()
{
	m_scrolledWindow1->SetSizer( bSizer2 );
	m_scrolledWindow1->Layout();
	bSizer2->Fit( m_scrolledWindow1 );
	bSizer1->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 0 );
	
	SetSizer( bSizer1 );
	Layout();
}

void G3CollapsiblePanels::CollapseAll()
{

}

void G3CollapsiblePanels::ExpandAll()
{

}

wxScrolledWindow *G3CollapsiblePanels::GetScrolledWnd() const
{
	return m_scrolledWindow1;
}

void G3CollapsiblePanels::SetStyle(int style)
{
	m_iStyle=style;
}

int G3CollapsiblePanels::GetStyle() const
{
	return m_iStyle;
}

void G3CollapsiblePanels::SetLabelFont(const wxFont &font)
{
	m_labelFont=font;
}

wxFont G3CollapsiblePanels::GetLabelFont() const
{
	return m_labelFont;
}

wxColour G3CollapsiblePanels::GetLabelColour() const
{
	return m_labelColour;
}

void G3CollapsiblePanels::SetLabelColour(const wxColour &colour)
{
	m_labelColour=colour;
}

void G3CollapsiblePanels::SetBgColour1(const wxColour &colour)
{
	m_bgColor1=colour;
}

wxColour G3CollapsiblePanels::GetBgColour1() const
{
	return m_bgColor1;
}

void G3CollapsiblePanels::SetBgColour2(const wxColour &colour)
{
	m_bgColor2=colour;
}

wxColour G3CollapsiblePanels::GetBgColour2() const
{
	return m_bgColor2;
}

void G3CollapsiblePanels::SetBgGradientColour1(const wxColour &colour)
{
	m_bgGradientColor1=colour;
}

wxColour G3CollapsiblePanels::GetBgGradientColour1() const
{
	return m_bgGradientColor1;
}

void G3CollapsiblePanels::SetBgGradientColour2(const wxColour &colour)
{
	m_bgGradientColor2=colour;
}

wxColour G3CollapsiblePanels::GetBgGradientColour2() const
{
	return m_bgGradientColor2;
}

void G3CollapsiblePanels::SetFrameColour(const wxColour &colour)
{
	m_frameColour=colour;
}

wxColour G3CollapsiblePanels::GetFrameColour() const
{
	return m_frameColour;
}