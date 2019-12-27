#pragma once


#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/tglbtn.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>

#include "G3wxControls.h"

enum EG3CollapsiblePanelsStyles
{
// 	G3_CP_DEFAULT=1, //domyslny toggle button z wx
// 	G3_CP_SIMPLE_BACKGROUND=2, // zaokraglony toggle button 2 kolorowy	
// 	G3_CP_GRADIENTBACKGROUND=4 // gradient toggle button	

	G3_CP_DEFAULT, //domyslny toggle button z wx
	G3_CP_SIMPLE_BACKGROUND, // zaokraglony toggle button 2 kolorowy	
	G3_CP_GRADIENTBACKGROUND // gradient toggle button	
};

//namespace Editor
//{
	class WXDLLIMPEXP_G3CONTROLS G3CollapsiblePanelPage:public wxObject
	{
	public:
		wxString m_label;

		wxPanel *m_pBackgroundPanel;

		wxToggleButton *m_pToggleButton;

		wxPanel *m_pUserPanel;

		G3CollapsiblePanelPage();
		virtual ~G3CollapsiblePanelPage();
	};

	class WXDLLIMPEXP_G3CONTROLS G3CollapsiblePanels:public wxControl//wxBookCtrlBase
	{		
	private:
		int m_iStyle;

		wxFont m_labelFont;
		
		wxColour m_labelColour;

		wxColour m_bgColor1, m_bgColor2;

		wxColour m_bgGradientColor1, m_bgGradientColor2;

		wxColour m_frameColour;

		wxScrolledWindow *m_scrolledWindow1;
		wxBoxSizer *bSizer1, *bSizer2;
		wxList m_pageLists;

	public:
		G3CollapsiblePanels();
		G3CollapsiblePanels( wxWindow* parent, wxWindowID id = wxID_ANY, 
			const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,250 )
			, long style = wxTAB_TRAVERSAL ); 
		virtual ~G3CollapsiblePanels();
				
		virtual wxToggleButton *AddPage(wxPanel *panel, const wxString &label, bool closed=false);
// 		virtual bool RemovePage(const wxString &label);
// 		virtual bool RemovePage(int index);
// 		virtual int GetNumPages() const;

// 		bool SetPageText(size_t,const wxString &){return true;};
// 
// 		
// 		wxString GetPageText(size_t) const{return wxT("");};
// 			
// 		int GetPageImage(size_t) const{return 0;};
// 			
// 		bool SetPageImage(size_t,int){return true;};
// 			
// 		bool InsertPage(size_t,wxWindow *,const wxString &,bool,int){return true;};
// 
// 		
// 		int SetSelection(size_t){return 0;};
// 			
// 		int ChangeSelection(size_t){return 0;};
// 			
// 		wxWindow *DoRemovePage(size_t){return 0;};

	
		void Finalize();

		void CollapseAll();

		void ExpandAll();

		wxScrolledWindow *GetScrolledWnd() const;

		void SetStyle(int style);
		int GetStyle() const;

		void SetLabelFont(const wxFont &font);
		wxFont GetLabelFont() const;

		void SetLabelColour(const wxColour &colour);
		wxColour GetLabelColour() const;

		void SetBgColour1(const wxColour &colour);
		wxColour GetBgColour1() const;

		void SetBgColour2(const wxColour &colour);
		wxColour GetBgColour2() const;

		void SetBgGradientColour1(const wxColour &colour);
		wxColour GetBgGradientColour1() const;

		void SetBgGradientColour2(const wxColour &colour);
		wxColour GetBgGradientColour2() const;

		void SetFrameColour(const wxColour &colour);
		wxColour GetFrameColour() const;

		// Virtual event handlers, overide them in your derived class
		//virtual void OnToggle( wxCommandEvent& event );

		//////////////////////////////////////////////////////////////////////////
		DECLARE_DYNAMIC_CLASS(G3CollapsiblePanels)

		//DECLARE_EVENT_TABLE()
	};
//}