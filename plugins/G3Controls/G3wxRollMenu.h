#pragma once


#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/artprov.h>
#include <wx/dcclient.h>

#include "G3wxControls.h"

#include <vector>

#define G3ROLLMENU_VERTICAL_ITEM_SPACE 32
#define G3ROLLMENU_VERTICAL_SUB_ITEM_SPACE G3ROLLMENU_VERTICAL_ITEM_SPACE

//namespace Editor
//{

class WXDLLIMPEXP_G3CONTROLS G3RollMenuEvent;

class WXDLLIMPEXP_G3CONTROLS G3RollMenu;

class WXDLLIMPEXP_G3CONTROLS G3RollMenuGroup;

class WXDLLIMPEXP_G3CONTROLS G3RollMenuBase:public wxObject
{
	friend class G3ImageBrowser;

public:
	G3RollMenu *m_pRollMenu;

	G3RollMenuGroup *m_pParent;

	int m_id;
	
	wxString m_strLabel, m_strHelp;

	wxBitmap m_bmpIcon;

	G3RollMenuBase();
	G3RollMenuBase(G3RollMenu *mainMenu, const wxString &label=_("G3MenuLabel"), int id=-1, G3RollMenuGroup *parent=NULL);	
	virtual ~G3RollMenuBase();


	void SetIcon(const wxBitmap &bmp);

	virtual int Paint(wxPaintDC &dc, int verticalOffset, int &currentItem);
	
	virtual void OnLeftDown( wxMouseEvent& event );
};

class WXDLLIMPEXP_G3CONTROLS G3RollMenuGroup:public G3RollMenuBase
{
protected:
	bool m_bClosed;

	wxList m_childs;
	
public:

	G3RollMenuGroup();
	G3RollMenuGroup(G3RollMenu *mainMenu, const wxString &label, int id, bool closed=false);	
	virtual ~G3RollMenuGroup();

	void AddChild(G3RollMenuBase *child);
	
	int Paint(wxPaintDC &dc, int verticalOffset, int &currentItem);

	void OnLeftDown( wxMouseEvent& event );

	bool IsClosed() const;

	void Close();
};

class WXDLLIMPEXP_G3CONTROLS G3RollMenuButton:public G3RollMenuBase
{
public:

	G3RollMenuButton();
	G3RollMenuButton(G3RollMenu *mainMenu, const wxString &label, int id, G3RollMenuGroup *parent=NULL);	
	virtual ~G3RollMenuButton();

	int Paint(wxPaintDC &dc, int verticalOffset, int &currentItem);
};

class WXDLLIMPEXP_G3CONTROLS G3RollMenuPanel:public G3RollMenuBase
{
public:

	G3RollMenuPanel();
	G3RollMenuPanel(G3RollMenu *mainMenu, const wxString &label, const int id, G3RollMenuGroup *parent=NULL);	
	virtual ~G3RollMenuPanel();

	int Paint(wxPaintDC &dc, int verticalOffset, int &currentItem);
};

class WXDLLIMPEXP_G3CONTROLS G3RollMenuSpacer:public G3RollMenuBase
{
public:
	G3RollMenuSpacer();
	G3RollMenuSpacer(G3RollMenu *mainMenu);	
	virtual ~G3RollMenuSpacer();

	int Paint(wxPaintDC &dc, int verticalOffset, int &currentItem);
};

class WXDLLIMPEXP_G3CONTROLS G3RollMenu:public wxPanel//wxBookCtrlBase
{		
	friend class G3RollMenuPanel;
	friend class G3RollMenuButton;
	friend class G3RollMenuGroup;

private:
	void OnRollMenuEvent( G3RollMenuEvent& event );
	
	int m_iStyle;

	wxFont m_labelMainFont;
	wxFont m_labelItemFont;

	wxColour m_labelItemColour;
	wxColour m_labelSelectedItemColour;
	wxColour m_selectedItemBackgroundColor;

	wxColour m_backgroundColor;

	wxRect m_menuClientRect;
		

	G3RollMenuBase *m_pSelectedItem, *m_pPreviousSelectedItem;

	wxString m_strMenuData;
protected:		
	// Virtual event handlers, overide them in your derived class
	void OnLeftDown( wxMouseEvent& event );

	void OnPaintMenu(wxPaintEvent &event);

	void OnSize(wxSizeEvent& event);

	void UpdateControl();

public:
	G3RollMenu();
	G3RollMenu( wxWindow* parent, wxWindowID id = wxID_ANY, 
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,250 )
		, long style = wxNO_BORDER); 
	virtual ~G3RollMenu();

	void SetLabelItemColour(wxColor &color);
	void SetLabelSelectedItemColour(wxColor &color);
	void SetLabelSelectedItemBackgroundColour(wxColor &color);
	void SetBackgroundColour(wxColor &color);

	virtual G3RollMenuSpacer *AddSpacer(G3RollMenuSpacer *spacer);

	virtual G3RollMenuGroup *AddGroup(G3RollMenuGroup *group);
	virtual bool RemoveGroup(const wxString &name);
	virtual bool RemoveGroup(int index);

	virtual G3RollMenuButton *AddButton(G3RollMenuButton *button);
	virtual bool RemoveButton(const wxString &name);
	virtual bool RemoveButton(int index);	

	virtual bool AddPanel(G3RollMenuPanel *panel);

	void SelectPanel(G3RollMenuBase *item);

	virtual int GetNumItems() const;

	virtual void Clear();	

	virtual void SelectItem(const wxString &name);
	virtual void SelectItem(const G3RollMenuBase &menuBase);
	virtual void SelectItem(int index);

	virtual void EnsureItemVisible(const wxString &name);
	virtual void EnsureItemVisible(const G3RollMenuBase &menuBase);
	virtual void EnsureItemVisible(int index);

	void BuildFromDate(const wxString &menuData);

	wxList m_itemsList;

	//////////////////////////////////////////////////////////////////////////
	DECLARE_DYNAMIC_CLASS(G3RollMenu)

	//DECLARE_EVENT_TABLE()
};
// 
// class WXDLLIMPEXP_G3CONTROLS G3RollMenu:public wxPanel//wxBookCtrlBase
// {		
// private:
// 	void OnRollMenuEvent( G3RollMenuEvent& event );
// 
// 	int m_iStyle;
// 
// 	wxFont m_labelGroupFont;
// 	wxFont m_labelItemFont;
// 		
// 	wxColour m_labelGroupColour;
// 	wxColour m_labelItemColour;
// 	wxColour m_labelSelectedItemColour;
// 
// 	wxColour m_backgroundColor;
// 			
// 	wxRect m_menuClientRect;
// 
// 	// true jesli menu animuje sie
// 	bool m_bMenuPreparing;
// 
// 	wxList m_itemsList;
// 
// 	G3RollMenuBase *m_pSelectedItem, *m_pPreviousSelectedItem;
// 
// 	wxString m_strMenuData;
// protected:		
// 	// Virtual event handlers, overide them in your derived class
// 	void OnLeftDown( wxMouseEvent& event );
// 
// 	void OnPaintMenu(wxPaintEvent &event);
// 
// 	void OnSize(wxSizeEvent& event);
// 	
// 	void UpdateControl();
// 
// public:
// 	G3RollMenu();
// 	G3RollMenu( wxWindow* parent, wxWindowID id = wxID_ANY, 
// 		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,250 )
// 		, long style = wxNO_BORDER); 
// 	virtual ~G3RollMenu();
// 				
// 	virtual G3RollMenuGroup *AddGroup(G3RollMenuGroup *group);
// 	virtual bool RemoveGroup(const wxString &name);
// 	virtual bool RemoveGroup(int index);
// 
// 	virtual G3RollMenuButton *AddButton(G3RollMenuButton *button);
// 	virtual bool RemoveButton(const wxString &name);
// 	virtual bool RemoveButton(int index);	
// 
// 	virtual bool AddPanel(wxPanel *panel, const wxString &label);
// 
// 	virtual int GetNumItems() const;
// 
// 	virtual void Clear();	
// 
// 	virtual void SelectItem(const wxString &name);
// 	virtual void SelectItem(const G3RollMenuBase &menuBase);
// 	virtual void SelectItem(int index);
// 
// 	virtual void EnsureItemVisible(const wxString &name);
// 	virtual void EnsureItemVisible(const G3RollMenuBase &menuBase);
// 	virtual void EnsureItemVisible(int index);
// 
// 	wxPanel* m_panel1;
// 	wxTreeCtrl* m_treeCtrl1;
// 	wxBoxSizer* bSizer2;
// 
// 	void BuildFromDate(const wxString &menuData);
// 
// 	// Virtual event handlers, overide them in your derived class
// 	void OnTreeSelChanged( wxTreeEvent& event );
// 
// 	std::vector<wxPanel*> panels;
// 
// 	wxTreeItemId m_rootID;
// 
// // 		bool SetPageText(size_t,const wxString &){return true;};
// // 
// // 		
// // 		wxString GetPageText(size_t) const{return wxT("");};
// // 			
// // 		int GetPageImage(size_t) const{return 0;};
// // 			
// // 		bool SetPageImage(size_t,int){return true;};
// // 			
// // 		bool InsertPage(size_t,wxWindow *,const wxString &,bool,int){return true;};
// // 
// // 		
// // 		int SetSelection(size_t){return 0;};
// // 			
// // 		int ChangeSelection(size_t){return 0;};
// // 			
// // 		wxWindow *DoRemovePage(size_t){return 0;};
// 
// 	
// 		
// 	// Virtual event handlers, overide them in your derived class
// 	//virtual void OnToggle( wxCommandEvent& event );
// 
// 	//////////////////////////////////////////////////////////////////////////
// 	DECLARE_DYNAMIC_CLASS(G3RollMenu)
// 
// 	//DECLARE_EVENT_TABLE()
// };



class WXDLLIMPEXP_G3CONTROLS G3RollMenuEvent:public wxNotifyEvent
{
private:
	G3RollMenuBase *m_pItem;
	
public:
	G3RollMenuEvent(wxEventType commandType=wxEVT_NULL, int id=0, G3RollMenuBase *item=0);

	G3RollMenuBase *GetItem() const;
	
	virtual wxEvent *Clone() const { return new G3RollMenuEvent( *this ); }

	DECLARE_DYNAMIC_CLASS(G3RollMenuEvent)
};
//}

// ----------------------------------------------------------------------------
// macros for handling WizardEvents
// ----------------------------------------------------------------------------


BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_ROLLMENU_ITEM_SELECTED, 10000 );
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_ROLLMENU_GROUP_OPEN, 10001 );
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_ROLLMENU_GROUP_CLOSE, 10002 );
// 	DECLARE_EVENT_TYPE(G3_EVT_IMAGEBROWSER_ITEM_SELECTED, 10000)
// 	DECLARE_EVENT_TYPE(G3_EVT_IMAGEBROWSER_ITEM_DRAGGED, 10001)
// 	DECLARE_EVENT_TYPE(G3_EVT_IMAGEBROWSER_ITEM_RCLICK, 10003)
// 	DECLARE_EVENT_TYPE(G3_EVT_IMAGEBROWSER_ITEM_MORE_CLICK, 10003)
END_DECLARE_EVENT_TYPES()

typedef void (wxEvtHandler::*G3RollMenuEventFunction)(G3RollMenuEvent&);

#define G3RollMenuEventHandler(func) \
	(wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(G3RollMenuEventFunction, &func)

#define EVT_G3_ROLLMENU_ITEM_SELECTED(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_ROLLMENU_ITEM_SELECTED, winid, G3RollMenuEventFunction(fn))

#define EVT_G3_ROLLMENU_GROUP_OPEN(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_ROLLMENU_GROUP_OPEN, winid, G3RollMenuEventFunction(fn))

#define EVT_G3_ROLLMENU_GROUP_CLOSE(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_ROLLMENU_GROUP_CLOSE, winid, G3RollMenuEventFunction(fn))

//}