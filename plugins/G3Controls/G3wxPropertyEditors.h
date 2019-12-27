#pragma once

#include "G3wxPropertyGrid.h"

#include <wx/window.h>

#include <wx/wx.h>
#include <wx/propgrid/advprops.h>

#include <vector>

class WXDLLIMPEXP_G3CONTROLS G3PropertyGrid;


// BASE CLASS FOR G3PROPERTYEditor

// class G3PGPropertyEditor
// {
// protected:
// //bool m_bSameValues;	
//  
// public:
// 	G3PGPropertyEditor();
// 	virtual ~G3PGPropertyEditor();
//  
// 	//void SetSameValue(bool val);
//  	
//  
//  
//  
//  
//  
//  
//  
//  
//  
// 	//#############################
// 	//TUTAJ DOROBIC FUNCKJE:
// 	// 	ADDBUTTON, 
// 	// 	ADDCHECKBOX, 
// 	// 	ADDSLIDER, 
// 	// 	ADDTEXTURE!!!
// 	// 	ADDSELECTEDCONTENT!!!
// 	//POTEM UZYWAC W CREATECONTROLS
//  
//  
//  
//  
//  
//  
//  
//  
//  
//  
// };

///
// KLASA DO TWORZENIA NOWYCH BUTTONOW DLA "PROPERTY"
// PO UZYCIU ADDBUTTON USTAWIC wndList.m_primary, wndList.m_secondary
// GetPrimarySize ZWRACA CALKOWITY OBSZAR DODANYCH BUTTONOW(PRZYDATNE!)
class WXDLLIMPEXP_G3CONTROLS wxPGButtonEditorManager:public wxWindow
{
public:
    wxPGButtonEditorManager(wxPropertyGrid* pg, const wxSize& sz);

    virtual ~wxPGButtonEditorManager();

    wxWindow* GetButton(unsigned int i);

   // const wxWindow* GetButton(unsigned int i);

    int GetButtonId(unsigned int i) ;//const;

    unsigned int GetCount() const;

	void AddCustomControl(wxControl *control, int itemid=-2);

    wxButton *AddButton(const wxString& label, int itemid=-2);

	wxToggleButton *AddToggleButton(const wxString& label, int itemid=-2);
	
	wxButton *AddButton(const wxBitmap& bitmap, int itemid=-2);

    wxSize GetPrimarySize() const;

    void Finalize(wxPropertyGrid* propGrid, const wxPoint& pos);

protected:

    void DoAddButton(wxWindow* button, const wxSize& sz);

    int GenId(int itemid) ;//const;

    wxArrayPtrVoid  m_buttons;
    wxSize          m_fullEditorSize;
    int             m_buttonsWidth;
};



//////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_G3CONTROLS G3SpinMultiValPGEditor:public wxPGSpinCtrlEditor//, public G3PGPropertyEditor
{
public:

	bool m_bEditedBySpinner;

protected:
	mutable wxString m_tempString;

	//wxDECLARE_DYNAMIC_CLASS(G3SpinMultiValPGEditor);
public:
	G3SpinMultiValPGEditor();

	virtual ~G3SpinMultiValPGEditor();

	/*void UpdateControl(wxPGProperty *prop,wxWindow *wnd) const
	{

	}
	virtual wxString GetName() const 
	{ 
		return "SampleMultiButtonEditor"; 
	}*/

	virtual wxPGWindowList CreateControls( wxPropertyGrid* propGrid, wxPGProperty* property, const wxPoint& pos,const wxSize& sz ) const;

	virtual bool OnEvent( wxPropertyGrid* propGrid, wxPGProperty* property, wxWindow* ctrl, wxEvent& event ) const;

	virtual void DrawValue(wxDC &dc, const wxRect &rect, wxPGProperty *property, const wxString &text) const;
};

//////////////////////////////////////////////////////////////////////////
class WXDLLIMPEXP_G3CONTROLS G3StringMultiValPGEditor : public wxPGTextCtrlEditor//, public G3PGPropertyEditor
{
protected:	

	//wxDECLARE_DYNAMIC_CLASS(G3SpinMultiValPGEditor);
public:
	G3StringMultiValPGEditor();

	virtual ~G3StringMultiValPGEditor() ;

	void DrawValue(wxDC &dc, const wxRect &rect, wxPGProperty *property, const wxString &text) const ;
};

//////////////////////////////////////////////////////////////////////////
class WXDLLIMPEXP_G3CONTROLS G3BoolMultiValPGEditor : public wxPGCheckBoxEditor//, public G3PGPropertyEditor
{
protected:	

	//wxDECLARE_DYNAMIC_CLASS(G3BoolMultiValPGEditor);
public:
	G3BoolMultiValPGEditor();

	virtual ~G3BoolMultiValPGEditor() ;

	void DrawValue(wxDC &dc, const wxRect &rect, wxPGProperty *property, const wxString &text) const ;
};

//////////////////////////////////////////////////////////////////////////
class WXDLLIMPEXP_G3CONTROLS G3EnumMultiValPGEditor : public wxPGChoiceEditor//, public G3PGPropertyEditor
{
protected:	
	
	//wxDECLARE_DYNAMIC_CLASS(G3EnumMultiValPGEditor);
public:
	G3EnumMultiValPGEditor();
	
	virtual ~G3EnumMultiValPGEditor() ;

	void DrawValue(wxDC &dc, const wxRect &rect, wxPGProperty *property, const wxString &text) const ;
};

//////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_G3CONTROLS G3CustomMultiButtonPGEditor:public wxPGTextCtrlEditor
{
protected:	

	//wxDECLARE_DYNAMIC_CLASS(G3CustomMultiButtonPGEditor);

public:
	G3CustomMultiButtonPGEditor();

	virtual ~G3CustomMultiButtonPGEditor() ;

	virtual wxPGWindowList CreateControls( wxPropertyGrid* propGrid, wxPGProperty* property, const wxPoint& pos,const wxSize& sz ) const;

	//void UpdateControl(wxPGProperty *prop, wxWindow *wnd) const;

	virtual bool OnEvent( wxPropertyGrid* propGrid, wxPGProperty* property, wxWindow* ctrl, wxEvent& event ) const;

	void DrawValue(wxDC &dc, const wxRect &rect, wxPGProperty *property, const wxString &text) const ;
};
