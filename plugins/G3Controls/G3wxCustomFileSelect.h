#pragma once

#include "G3wxControls.h"

#include <wx/sound.h>
#include <wx/listbox.h>

enum G3CUSTOM_FILE_SELECT_DLG_TYPES
{
	G3CUSTOM_FILE_SELECT_DLG_TYPE_IMAGE,
	G3CUSTOM_FILE_SELECT_DLG_TYPE_SOUND
};

class WXDLLIMPEXP_G3CONTROLS G3CustomFileChangedEvent;

class WXDLLIMPEXP_G3CONTROLS G3CustomFileSelect : public wxPanel 
{
protected:
	enum
	{
		ID_BROWSEPHOTOS = 1001,
		ID_CLEARPHOTO
	};
		
	wxTextCtrl* m_textCtrl1;
	wxButton* m_button1;
	wxButton* m_button11;
		
	void OnButtonClick( wxCommandEvent& event );

	void OnPathChangedEvent( G3CustomFileChangedEvent& event );

	int m_iDialogType;

	wxString m_strPath, m_strFileExt;

	bool m_bBrowseSubfolders;

public:
	G3CustomFileSelect();
	G3CustomFileSelect( wxWindow* parent, int dialogType, const wxString &path, const wxString &fileExt, bool browseSubFolders, wxWindowID id=wxID_ANY);
	G3CustomFileSelect( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,41 ), long style = wxTAB_TRAVERSAL ); 
	~G3CustomFileSelect();

	void SetPath(const wxString &path);

	void SelectFile(const wxString &file);

	wxString GetSelectedFile() const;

	void EnableSubfolders(bool iSsubFolderEnable=true);
	
	DECLARE_DYNAMIC_CLASS(G3CustomFileSelect)
};

class WXDLLIMPEXP_G3CONTROLS G3CustomFileChangedEvent:public wxNotifyEvent
{
protected:
	wxString m_strSelectedFilename;

public:
	G3CustomFileChangedEvent(wxEventType commandType=wxEVT_NULL, int id=0, wxString path=wxEmptyString);

	wxString GetSelectedFilename() const;
	
	virtual wxEvent *Clone() const { return new G3CustomFileChangedEvent( *this ); }

	DECLARE_DYNAMIC_CLASS(G3CustomFileChangedEvent)
};


BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_G3CONTROLS, G3_EVT_FILE_CHANGED, 10000 );
END_DECLARE_EVENT_TYPES()

typedef void (wxEvtHandler::*G3CustomFileChangedEventFunction)(G3CustomFileChangedEvent&);

#define G3CustomFileChangedEventHandler(func) \
	(wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(G3CustomFileChangedEventFunction, &func)

#define EVT_G3_EVT_FILE_CHANGED(winid, fn) \
	wx__DECLARE_EVT1(G3_EVT_FILE_CHANGED, winid, G3CustomFileChangedEventHandler(fn))

///////////////////////////////////////////////////////////////////////////////
/// Class ImageSelectDialog
///////////////////////////////////////////////////////////////////////////////
class ImageSelectDialog : public wxDialog 
{
private:
	
protected:
	enum
	{
		ID_OK = 1001,
		ID_CANCEL
	};
		
	wxListBox* m_listBox1;
	wxPanel* m_panel2;
	wxButton* m_button2;
	wxButton* m_button3;
		
	// Virtual event handlers, overide them in your derived class
	void OnListBox( wxCommandEvent& event );
	void OnPaint( wxPaintEvent& event );
	void OnButtonClick( wxCommandEvent& event );		
		
	wxBitmap m_bitmapEmptyTemplate;

	wxBitmap m_bitmapBackground;
	
	wxString m_strPath, m_strSelectedFilename, m_strReturnedFilename;

	void BuildTempBitmap();
	void BuildFileList(const wxString &path, const wxString &fileExt, bool subFolders);
public:
		
	ImageSelectDialog(const wxString &path, const wxString &fileExt, bool subfolders, const wxString &selectedFilename, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Wybierz zdjęcie"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 496,334 ), long style = wxDEFAULT_DIALOG_STYLE ); 
	~ImageSelectDialog();

	wxString GetSelectedFilename() const;	

	void SelectFile(const wxString &filename);	
};

///////////////////////////////////////////////////////////////////////////////
/// Class SoundSelectDialog
///////////////////////////////////////////////////////////////////////////////
class SoundSelectDialog : public wxDialog 
{
private:
	
protected:
	enum
	{
		ID_PLAY = 1001,
		ID_OK,
		ID_CANCEL
	};
		
	wxListBox* m_listBox1;
	wxPanel* m_panel1;
	wxStaticText* m_staticText1;
	wxButton* m_button21;
	wxButton* m_button2;
	wxButton* m_button3;
		
	// Virtual event handlers, overide them in your derived class
	void OnListBox( wxCommandEvent& event );
	void OnPaint( wxPaintEvent& event );
	void OnListBoxDClick( wxCommandEvent& event );
	void OnButtonClick( wxCommandEvent& event );	
				
	wxString m_strPath, m_strSelectedFilename, m_strReturnedFilename;

	wxString m_strMsg;

	wxSound m_sound;

	void BuildFileList(const wxString &path, const wxString &fileExt, bool subFolders);
public:
		
	SoundSelectDialog(const wxString &path, const wxString &fileExt, bool subfolders, const wxString &selectedFilename, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Wybierz dźwięk"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 496,334 ), long style = wxDEFAULT_DIALOG_STYLE); 
	~SoundSelectDialog();

	wxString GetSelectedFilename() const;	

	void SelectFile(const wxString &filename);
	
};
