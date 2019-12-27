#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
class wxPanel;

#include <wx/string.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/bitmap.h>
#include <wx/image.h>

#include "G3wxControls.h"

#include <wx/popupwin.h>

#include <wx/timer.h>

class SimpleTransientPopup: public wxPopupTransientWindow
{
public:
	SimpleTransientPopup( wxWindow *parent );
	virtual ~SimpleTransientPopup();

	// wxPopupTransientWindow virtual methods are all overridden to log them
	virtual void Popup(wxWindow *focus = NULL);
	virtual void OnDismiss();
	virtual bool ProcessLeftDown(wxMouseEvent& event);
	virtual bool Show( bool show = true );

	wxScrolledWindow* GetChild() { return m_panel; }

private:
	wxScrolledWindow *m_panel;


private:
	void OnMouse( wxMouseEvent &event );
	void OnSize( wxSizeEvent &event );
	void OnSetFocus( wxFocusEvent &event );
	void OnKillFocus( wxFocusEvent &event );
	void OnButton( wxCommandEvent& event );
	void OnSpinCtrl( wxSpinEvent& event );

private:
	DECLARE_CLASS(SimpleTransientPopup)
	DECLARE_EVENT_TABLE()
};


enum EG3ImageBrowserStyles
{
	//G3_IB_STRETCH2HEIGHT=1,
	G3_IB_GRADIENTBACKGROUND=1,
	G3_IB_FILLED_BACKGROUND_LABEL=2,
	G3_IB_GRADIENT_BG_LABEL=4,
	G3_IB_SELECTED_RENDER_IN_FRAME=8
};

enum EG3ImageBrowserViewModes
{
	G3_IBVM_VIEWTHUMBNAILS,
	G3_IBVM_VIEWDETAILS,
	G3_IBVM_VIEWLIST,
	G3_IBVM_VIEWSINLELIST

	// 	G3_IBVM_VIEWTHUMBNAILS=1,
	// 	G3_IBVM_VIEWDETAILS=2,
	// 	G3_IBVM_VIEWLIST=4,
	// 	G3_IBVM_VIEWSINLELIST=8
};

//namespace Editor
//{
class WXDLLIMPEXP_G3CONTROLS G3ImageBrowserEvent;

class WXDLLIMPEXP_G3CONTROLS G3ImageBrowserItem:public wxObject
{
	friend class G3ImageBrowser;

protected:
	wxString m_strText;
	wxString m_strTextDetails, m_strTextDetails2;
	wxImage *m_pImage;
	void *m_pUserData;

	wxBitmap *m_pBitmap;

	bool m_bUseCheckboard4Alpha;

	int m_iViewType;

	wxBitmap *GetBitmap() const;

public:
	G3ImageBrowserItem();
	G3ImageBrowserItem(const wxString &name, wxImage *image, const wxString &detailText=_(""), void *user=0);
	G3ImageBrowserItem(const wxString &name, wxImage *image, const wxString &detailText=_(""), const wxString &detail2Text=_(""), void *user=0);
	G3ImageBrowserItem(const wxString &name, wxImage *image, const wxString &detailText=_(""), bool backgroundCheckboard=false, void *user=0);
	virtual ~G3ImageBrowserItem();

	wxString GetText() const;
	wxString GetTextDetail() const;
	wxString GetTextDetail2() const;
	void SetText(const wxString &text);
	wxImage *GetImage() const;
	void *GetUserData() const;
};

class WXDLLIMPEXP_G3CONTROLS G3ImageBrowser:public wxScrolledWindow // typedef wxScrolled< wxPanel > wxScrolledWindow
{		
private:
	void OnImageBrowserEvent( G3ImageBrowserEvent& event );
	void OnScrollWinEvents(wxScrollWinEvent& event);
	void OnTimer(wxTimerEvent& event);

	void RecalcVirtualSize();

	wxTimer m_timerTooltip;

	wxPoint m_scrollPos;

	wxColour m_checkboardColor1, m_checkboardColor2;		

	wxSize m_virtualSize;

	wxColour m_bgGradientColor1, m_bgGradientColor2;		

	wxFont m_labelFont, m_detailFont, m_detail2Font;

	int m_labelHeight;

	wxColour m_labelColour, m_selectedLabelColour;

	wxColour m_labelBgGradientColour1, m_labelBgGradientColour2;

	wxColour m_selectedFrameColour, m_selectedLabelBgColour;

	int m_selectedFrameWidth;

	wxSize m_imageSize;		

	wxSize m_itemSpace;

	wxSize m_canvasSize;

	bool m_bLeftDown;

	wxPoint m_leftMousePos;

	G3ImageBrowserItem *m_pSelectedItem, *m_pPreviousSelectedItem;

	int m_iBackGroundStyle;

	wxList m_itemList;

	int m_iViewMode;

	int m_popupTime;

	wxPoint m_mouseOverPos;
	SimpleTransientPopup *m_simplePopup;
protected:		
	// Virtual event handlers, overide them in your derived class
	virtual void OnLeftDown( wxMouseEvent& event );
	virtual void OnLeftUp( wxMouseEvent& event );
	virtual void OnRightDown( wxMouseEvent& event );
	virtual void OnRightUp( wxMouseEvent& event );
	virtual void OnMotion( wxMouseEvent& event );
	virtual void OnPaint( wxPaintEvent& event );		
	virtual void OnSize( wxSizeEvent& event );		

	void UpdateControl();

public:
	G3ImageBrowser();
	G3ImageBrowser( wxWindow* parent, wxWindowID id = wxID_ANY, 
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,250 )
		, long style = wxTAB_TRAVERSAL ); 
	virtual ~G3ImageBrowser();

	void SetCheckboardColour(const wxColour &color1, const wxColour &color2);

	void SetImageSize(wxSize size);

	void SetItemSpace(wxSize space);

	void SetBgGradientColour1(const wxColour &colour);
	void SetBgGradientColour2(const wxColour &colour);

	void SetLabelFont(const wxFont &font);

	void SetDetailFont(const wxFont &font);

	void SetDetail2Font(const wxFont &font);

	void SetLabelColour(const wxColour &colour);

	void SetSelectedLabelColour(const wxColour &colour);

	void SetLabelGradientColour1(const wxColour &colour);
	void SetLabelGradientColour2(const wxColour &colour);

	void SetSelectedFrameColour(const wxColour &colour);

	void SetSelectedFrameWidth(int width);

	void SetSelectedLabelBgColour(const wxColour &colour);

	void SetViewMode(int mode);

	int GetItemCount() const;

	G3ImageBrowserItem *GetItemSelected() const;

	void ClearAll();
	void AddItem(wxImage *img, wxString &name, void *userData);
	void AddItem(G3ImageBrowserItem *item);			
	void RemoveItem(int index);
	void RemoveItem(wxString &name);
	void RemoveItem(G3ImageBrowserItem *item);

	DECLARE_DYNAMIC_CLASS(G3ImageBrowser)

	//DECLARE_EVENT_TABLE()
};

class WXDLLIMPEXP_G3CONTROLS G3ImageBrowserEvent:public wxNotifyEvent
{
private:
	G3ImageBrowserItem *m_pItem;

	wxPoint m_mousePoint;

public:
	G3ImageBrowserEvent(wxEventType commandType=wxEVT_NULL, int id=0, G3ImageBrowserItem *item=0, wxPoint &mousePoint=wxPoint(0,0));

	G3ImageBrowserItem *GetItem() const;

	wxPoint GetPoint() const;

	virtual wxEvent *Clone() const { return new G3ImageBrowserEvent( *this ); }

	DECLARE_DYNAMIC_CLASS(G3ImageBrowserEvent)
};
//}

// ----------------------------------------------------------------------------
// macros for handling WizardEvents
// ----------------------------------------------------------------------------


BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_IMAGEBROWSER_ITEM_SELECTED, 10000 );
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_IMAGEBROWSER_ITEM_BEGIN_DRAGGED, 10001 );
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_IMAGEBROWSER_ITEM_END_DRAGGED, 10002 );
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_IMAGEBROWSER_ITEM_RCLICK, 10003 );
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_IMAGEBROWSER_ITEM_MORE_CLICK, 10004 );
// 	DECLARE_EVENT_TYPE(G3_EVT_IMAGEBROWSER_ITEM_SELECTED, 10000)
// 	DECLARE_EVENT_TYPE(G3_EVT_IMAGEBROWSER_ITEM_DRAGGED, 10001)
// 	DECLARE_EVENT_TYPE(G3_EVT_IMAGEBROWSER_ITEM_RCLICK, 10003)
// 	DECLARE_EVENT_TYPE(G3_EVT_IMAGEBROWSER_ITEM_MORE_CLICK, 10003)
END_DECLARE_EVENT_TYPES()

	typedef void (wxEvtHandler::*G3ImageBrowserEventFunction)(G3ImageBrowserEvent&);

#define G3ImageBrowserEventHandler(func) \
	(wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(G3ImageBrowserEventFunction, &func)

#define EVT_G3_IMAGEBROWSER_ITEM_SELECTED(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_IMAGEBROWSER_ITEM_SELECTED, winid, G3ImageBrowserEventHandler(fn))

#define EVT_G3_IMAGEBROWSER_ITEM_BEGIN_DRAGGED(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_IMAGEBROWSER_ITEM_BEGIN_DRAGGED, winid, G3ImageBrowserEventHandler(fn))

#define EVT_G3_IMAGEBROWSER_ITEM_END_DRAGGED(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_IMAGEBROWSER_ITEM_END_DRAGGED, winid, G3ImageBrowserEventHandler(fn))

#define EVT_G3_IMAGEBROWSER_ITEM_RCLICK(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_IMAGEBROWSER_ITEM_RCLICK, winid, G3ImageBrowserEventHandler(fn))

#define EVT_G3_IMAGEBROWSER_ITEM_MORE_CLICK(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_IMAGEBROWSER_ITEM_MORE_CLICK, winid, G3ImageBrowserEventHandler(fn))


//BEGIN_DECLARE_EVENT_TYPES()
// DECLARE_EXPORTED_EVENT_TYPE( wxFBDLLIMPEXP, G3_EVT_IMAGEBROWSER_ITEM_SELECTED, 900 );
// DECLARE_EXPORTED_EVENT_TYPE( wxFBDLLIMPEXP, G3_EVT_IMAGEBROWSER_ITEM_DRAGGED, 901 );
// DECLARE_EXPORTED_EVENT_TYPE( wxFBDLLIMPEXP, G3_EVT_IMAGEBROWSER_ITEM_RCLICK, 902 );
// DECLARE_EXPORTED_EVENT_TYPE( wxFBDLLIMPEXP, G3_EVT_IMAGEBROWSER_ITEM_MORE_CLICK, 903 );
//END_DECLARE_EVENT_TYPES()


//V2
// typedef void ( wxEvtHandler::*G3ImageBrowserEventFunction )( G3ImageBrowserEvent& );
// 
// #define G3ImageBrowserEventHandler( func ) \
// 	(wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent( G3ImageBrowserEventFunction, &func )
// 
// #define G3__DECLARE_IMAGEBROWSEREVT( evt, id, fn ) wx__DECLARE_EVT1( evt, id, G3ImageBrowserEventHandler( fn ) )
// 
// #define EVT_G3_IMAGEBROWSER_ITEM_SELECTED( id, fn ) G3__DECLARE_IMAGEBROWSEREVT( G3_EVT_IMAGEBROWSER_ITEM_SELECTED, id, fn )
// 
// #define EVT_G3_IMAGEBROWSER_ITEM_DRAGGED( id, fn ) G3__DECLARE_IMAGEBROWSEREVT( G3_EVT_IMAGEBROWSER_ITEM_DRAGGED, id, fn )
// 
// #define EVT_G3_IMAGEBROWSER_ITEM_RCLICK(id, fn) G3__DECLARE_IMAGEBROWSEREVT( G3_EVT_IMAGEBROWSER_ITEM_RCLICK, id, fn)
// 
// #define EVT_G3_IMAGEBROWSER_ITEM_RCLICK( id, fn ) G3__DECLARE_IMAGEBROWSEREVT( G3_EVT_IMAGEBROWSER_ITEM_MORE_CLICK, id, fn )
// 

//V3
// typedef void (wxEvtHandler::*G3ImageBrowserEventFunction)(G3ImageBrowserEvent&);
// 
// wxDEFINE_EVENT(myEVT_THREAD_GET_PING, G3ImageBrowserEvent);
// 
// #define G3ImageBrowserEventHandler(func) wxEVENT_HANDLER_CAST(G3ImageBrowserEventFunction, func)
// 
// // deklaruje event dowolnego typu uzywajacy szabonu eventa G3ImageBrowserEventHandler
// #define EVT_G3_CUSTOM(evt, id, func) wx__DECLARE_EVT1(evt, id, G3ImageBrowserEventHandler(func))
// 
// // gotowe typy uzywajace eventa G3ImageBrowserEventHandler
// #define EVT_G3_IMAGEBROWSER_ITEM_SELECTED(id, func) wx__DECLARE_EVT1(G3_EVT_IMAGEBROWSER_ITEM_SELECTED, id, G3ImageBrowserEventHandler(func))
// #define EVT_G3_IMAGEBROWSER_ITEM_DRAGGED(id, func) wx__DECLARE_EVT1(G3_EVT_IMAGEBROWSER_ITEM_DRAGGED, id, G3ImageBrowserEventHandler(func))

