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

#include <vector>

enum EG3SoundChannelsStyles
{
	G3_SCS_GRADIENTBACKGROUND=1,
	G3_SCS_BITMAPBACKGROUND=2	
};

enum EG3SoundChannelsViewModes
{
	G3_SCVM_TILES,
	G3_SCVM_DETAILS	
};

//namespace Editor
//{

class WXDLLIMPEXP_G3CONTROLS G3SoundChannelsEvent;

class WXDLLIMPEXP_G3CONTROLS G3SoundChannelsItem:public wxObject
{
	friend class G3SoundChannels;

protected:
	G3SoundChannels *m_pSoundChannels;
	wxString m_strName;
	wxString m_strTitle;
	wxString m_strStatus;
	wxString m_strLastRecord;
	wxString m_strNumberOfRecords;
	
	void *m_pUserData;

	void OnLeftDown(wxMouseEvent &event);

public:
	G3SoundChannelsItem();
	G3SoundChannelsItem(G3SoundChannels *soundChannels, const wxString &name, const wxString &title, const wxString &status, const wxString &lastRec, const wxString &numberOfRec, void *user=0);	
	virtual ~G3SoundChannelsItem();

	wxString GetNameText() const;

	wxString GetTitleText() const;
	void SetTitleText(const wxString &text);

	wxString GetStatusText() const;
	void SetStatusText(const wxString &text);

	wxString GetLastRecordText() const;
	void SetLastRecordsText(const wxString &text);

	wxString GetNumberOfRecordsText() const;
	void SetNumberOfRecordsText(const wxString &text);

	void *GetUserData() const;

	struct ByName
	{
		wxString m_strName;

		ByName(const wxString &name):
		m_strName(name)
		{

		}

		bool operator ()(const G3SoundChannelsItem *item)  
		{
			return m_strName==item->GetNameText();
		}
	};

// 	struct ByName
// 	{
// 		wxString m_strName;
// 
// 		ByName(const wxString &name):
// 		  m_strName(name)
// 		{
// 
// 		}
// 
// 		bool operator()(G3SoundChannelsItem *item2)
// 		{   
// 			return m_strName==item2->GetNameText();
// 		}   
// 	};
};

class WXDLLIMPEXP_G3CONTROLS G3SoundChannels:public wxScrolledWindow // typedef wxScrolled< wxPanel > wxScrolledWindow
{		
	friend class G3SoundChannelsItem;

private:
	void OnSoundChannelsEvent( G3SoundChannelsEvent& event );
	void OnScrollWinEvents(wxScrollWinEvent& event);
	
	void RecalcVirtualSize();
	
	wxPoint m_scrollPos;

	wxColour m_checkboardColor1, m_checkboardColor2;		

	int m_virtualHeight;

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

	G3SoundChannelsItem *m_pSelectedItem, *m_pPreviousSelectedItem;

	int m_iBackGroundStyle;

	std::vector<G3SoundChannelsItem*> m_channelList;

	int m_iViewMode;
	
	wxPoint m_mouseOverPos;
	
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
	G3SoundChannels();
	G3SoundChannels( wxWindow* parent, wxWindowID id = wxID_ANY, 
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,250 )
		, long style = wxTAB_TRAVERSAL ); 
	virtual ~G3SoundChannels();

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

	G3SoundChannelsItem *GetItemSelected() const;

	void ClearAll();
	G3SoundChannelsItem *CreateChannel(const wxString &name, const wxString &title, const wxString &status, const wxString &lastRec, const wxString &numberOfRec, void *user=NULL);			
	bool RemoveChannel(G3SoundChannelsItem *channel);
	bool RemoveChannel(wxString &name);
	bool RemoveChannel(int index);

	DECLARE_DYNAMIC_CLASS(G3SoundChannels)

	//DECLARE_EVENT_TABLE()
};

class WXDLLIMPEXP_G3CONTROLS G3SoundChannelsEvent:public wxNotifyEvent
{
private:
	G3SoundChannelsItem *m_pItem;

	wxPoint m_mousePoint;

public:
	G3SoundChannelsEvent(wxEventType commandType=wxEVT_NULL, int id=0, G3SoundChannelsItem *item=0, wxPoint &mousePoint=wxPoint(0,0));

	G3SoundChannelsItem *GetItem() const;

	wxPoint GetPoint() const;

	virtual wxEvent *Clone() const { return new G3SoundChannelsEvent( *this ); }

	DECLARE_DYNAMIC_CLASS(G3SoundChannelsEvent)
};
//}

// ----------------------------------------------------------------------------
// macros for handling WizardEvents
// ----------------------------------------------------------------------------


BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_SOUNDCHANNELS_ITEM_SELECTED, 10000 );
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_SOUNDCHANNELS_ITEM_BEGIN_DRAGGED, 10001 );
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_SOUNDCHANNELS_ITEM_END_DRAGGED, 10002 );
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_SOUNDCHANNELS_ITEM_RCLICK, 10003 );
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_SOUNDCHANNELS_ITEM_MORE_CLICK, 10004 );
// 	DECLARE_EVENT_TYPE(G3_EVT_SOUNDCHANNELS_ITEM_SELECTED, 10000)
// 	DECLARE_EVENT_TYPE(G3_EVT_SOUNDCHANNELS_ITEM_DRAGGED, 10001)
// 	DECLARE_EVENT_TYPE(G3_EVT_SOUNDCHANNELS_ITEM_RCLICK, 10003)
// 	DECLARE_EVENT_TYPE(G3_EVT_SOUNDCHANNELS_ITEM_MORE_CLICK, 10003)
END_DECLARE_EVENT_TYPES()

	typedef void (wxEvtHandler::*G3SoundChannelsEventFunction)(G3SoundChannelsEvent&);

#define G3SoundChannelsEventHandler(func) \
	(wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(G3SoundChannelsEventFunction, &func)

#define EVT_G3_SOUNDCHANNELS_ITEM_SELECTED(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_SOUNDCHANNELS_ITEM_SELECTED, winid, G3SoundChannelsEventHandler(fn))

#define EVT_G3_SOUNDCHANNELS_ITEM_BEGIN_DRAGGED(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_SOUNDCHANNELS_ITEM_BEGIN_DRAGGED, winid, G3SoundChannelsEventHandler(fn))

#define EVT_G3_SOUNDCHANNELS_ITEM_END_DRAGGED(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_SOUNDCHANNELS_ITEM_END_DRAGGED, winid, G3SoundChannelsEventHandler(fn))

#define EVT_G3_SOUNDCHANNELS_ITEM_RCLICK(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_SOUNDCHANNELS_ITEM_RCLICK, winid, G3SoundChannelsEventHandler(fn))

#define EVT_G3_SOUNDCHANNELS_ITEM_MORE_CLICK(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_SOUNDCHANNELS_ITEM_MORE_CLICK, winid, G3SoundChannelsEventHandler(fn))


//BEGIN_DECLARE_EVENT_TYPES()
// DECLARE_EXPORTED_EVENT_TYPE( wxFBDLLIMPEXP, G3_EVT_SOUNDCHANNELS_ITEM_SELECTED, 900 );
// DECLARE_EXPORTED_EVENT_TYPE( wxFBDLLIMPEXP, G3_EVT_SOUNDCHANNELS_ITEM_DRAGGED, 901 );
// DECLARE_EXPORTED_EVENT_TYPE( wxFBDLLIMPEXP, G3_EVT_SOUNDCHANNELS_ITEM_RCLICK, 902 );
// DECLARE_EXPORTED_EVENT_TYPE( wxFBDLLIMPEXP, G3_EVT_SOUNDCHANNELS_ITEM_MORE_CLICK, 903 );
//END_DECLARE_EVENT_TYPES()


//V2
// typedef void ( wxEvtHandler::*G3SoundChannelsEventFunction )( G3SoundChannelsEvent& );
// 
// #define G3SoundChannelsEventHandler( func ) \
// 	(wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent( G3SoundChannelsEventFunction, &func )
// 
// #define G3__DECLARE_IMAGEBROWSEREVT( evt, id, fn ) wx__DECLARE_EVT1( evt, id, G3SoundChannelsEventHandler( fn ) )
// 
// #define EVT_G3_SOUNDCHANNELS_ITEM_SELECTED( id, fn ) G3__DECLARE_IMAGEBROWSEREVT( G3_EVT_SOUNDCHANNELS_ITEM_SELECTED, id, fn )
// 
// #define EVT_G3_SOUNDCHANNELS_ITEM_DRAGGED( id, fn ) G3__DECLARE_IMAGEBROWSEREVT( G3_EVT_SOUNDCHANNELS_ITEM_DRAGGED, id, fn )
// 
// #define EVT_G3_SOUNDCHANNELS_ITEM_RCLICK(id, fn) G3__DECLARE_IMAGEBROWSEREVT( G3_EVT_SOUNDCHANNELS_ITEM_RCLICK, id, fn)
// 
// #define EVT_G3_SOUNDCHANNELS_ITEM_RCLICK( id, fn ) G3__DECLARE_IMAGEBROWSEREVT( G3_EVT_SOUNDCHANNELS_ITEM_MORE_CLICK, id, fn )
// 

//V3
// typedef void (wxEvtHandler::*G3SoundChannelsEventFunction)(G3SoundChannelsEvent&);
// 
// wxDEFINE_EVENT(myEVT_THREAD_GET_PING, G3SoundChannelsEvent);
// 
// #define G3SoundChannelsEventHandler(func) wxEVENT_HANDLER_CAST(G3SoundChannelsEventFunction, func)
// 
// // deklaruje event dowolnego typu uzywajacy szabonu eventa G3SoundChannelsEventHandler
// #define EVT_G3_CUSTOM(evt, id, func) wx__DECLARE_EVT1(evt, id, G3SoundChannelsEventHandler(func))
// 
// // gotowe typy uzywajace eventa G3SoundChannelsEventHandler
// #define EVT_G3_SOUNDCHANNELS_ITEM_SELECTED(id, func) wx__DECLARE_EVT1(G3_EVT_SOUNDCHANNELS_ITEM_SELECTED, id, G3SoundChannelsEventHandler(func))
// #define EVT_G3_SOUNDCHANNELS_ITEM_DRAGGED(id, func) wx__DECLARE_EVT1(G3_EVT_SOUNDCHANNELS_ITEM_DRAGGED, id, G3SoundChannelsEventHandler(func))

