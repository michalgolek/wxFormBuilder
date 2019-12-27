//#include "stdafx.h"
#include "G3wxCustomFileSelect.h"

#include <wx/dcmemory.h>

#include <wx/dir.h>

#pragma comment(lib, "winmm.lib")

IMPLEMENT_DYNAMIC_CLASS(G3CustomFileSelect, wxPanel);

IMPLEMENT_DYNAMIC_CLASS(G3CustomFileChangedEvent, wxNotifyEvent);

DEFINE_EVENT_TYPE(G3_EVT_FILE_CHANGED)

G3CustomFileSelect::G3CustomFileSelect()
{
}

G3CustomFileSelect::G3CustomFileSelect( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) :
	wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer1->Add( m_textCtrl1, 1, wxEXPAND|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_button1 = new wxButton( this, ID_BROWSEPHOTOS, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	
	bSizer1->Add( m_button1, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_button11 = new wxButton( this, ID_CLEARPHOTO, _("U"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	
	bSizer1->Add( m_button11, 0, wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( G3CustomFileSelect::OnButtonClick ), NULL, this );
	m_button11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( G3CustomFileSelect::OnButtonClick ), NULL, this );
}

G3CustomFileSelect::G3CustomFileSelect(wxWindow* parent, int dialogType, const wxString &path, const wxString &fileExt, bool browseSubFolders, wxWindowID id):
	wxPanel( parent, id),
	m_iDialogType(dialogType),
	m_strFileExt(fileExt)
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer1->Add( m_textCtrl1, 1, wxEXPAND|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_button1 = new wxButton( this, ID_BROWSEPHOTOS, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	
	bSizer1->Add( m_button1, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_button11 = new wxButton( this, ID_CLEARPHOTO, _("U"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	
	bSizer1->Add( m_button11, 0, wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( G3CustomFileSelect::OnButtonClick ), NULL, this );
	m_button11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( G3CustomFileSelect::OnButtonClick ), NULL, this );

	this->Connect( wxID_ANY, G3_EVT_FILE_CHANGED, G3CustomFileChangedEventHandler( G3CustomFileSelect::OnPathChangedEvent ));

	//////////////////////
	SetPath(path);

	EnableSubfolders(browseSubFolders);
}

G3CustomFileSelect::~G3CustomFileSelect()
{
	// Disconnect Events
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( G3CustomFileSelect::OnButtonClick ), NULL, this );
	m_button11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( G3CustomFileSelect::OnButtonClick ), NULL, this );
	
	
	this->Disconnect( wxID_ANY, G3_EVT_FILE_CHANGED, G3CustomFileChangedEventHandler( G3CustomFileSelect::OnPathChangedEvent ));
}

void G3CustomFileSelect::OnButtonClick( wxCommandEvent& event )
{
	switch (event.GetId())
	{
	case ID_BROWSEPHOTOS:
		{
			switch(m_iDialogType)
			{
			case G3CUSTOM_FILE_SELECT_DLG_TYPE_IMAGE:
				{
					ImageSelectDialog imageSelectDialog(m_strPath, m_strFileExt, m_bBrowseSubfolders, m_textCtrl1->GetValue(), this);
					if(imageSelectDialog.ShowModal()==wxID_OK)
					{
						wxString strPath=m_strPath+wxFileName::GetPathSeparator()+imageSelectDialog.GetSelectedFilename();

						//if(m_flaq & G3CUSTOM_FILE_SELECT_DLG_FLAG_SHOW_FULL_PATH)
							//m_textCtrl1->SetValue(strPath);				
						//else
							m_textCtrl1->SetValue(imageSelectDialog.GetSelectedFilename());				

						if(wxFileExists(strPath))
							m_textCtrl1->SetForegroundColour(*wxBLACK);
						else
							m_textCtrl1->SetForegroundColour(*wxRED);

						G3CustomFileChangedEvent eventFileChanged(G3_EVT_FILE_CHANGED, GetId(), strPath);
						eventFileChanged.SetEventObject(this);
						GetEventHandler()->ProcessEvent(eventFileChanged);
					}
				}
				break;
			case G3CUSTOM_FILE_SELECT_DLG_TYPE_SOUND:
				{
					SoundSelectDialog soundSelectDialog(m_strPath, m_strFileExt, m_bBrowseSubfolders, m_textCtrl1->GetValue(), this);
					if(soundSelectDialog.ShowModal()==wxID_OK)
					{
						wxString strPath=m_strPath+wxFileName::GetPathSeparator()+soundSelectDialog.GetSelectedFilename();

						//if(m_flaq & G3CUSTOM_FILE_SELECT_DLG_FLAG_SHOW_FULL_PATH)
							//m_textCtrl1->SetValue(strPath);				
						//else
							m_textCtrl1->SetValue(soundSelectDialog.GetSelectedFilename());				

						if(wxFileExists(strPath))
							m_textCtrl1->SetForegroundColour(*wxBLACK);
						else
							m_textCtrl1->SetForegroundColour(*wxRED);

						G3CustomFileChangedEvent eventFileChanged(G3_EVT_FILE_CHANGED, GetId(), strPath);
						eventFileChanged.SetEventObject(this);
						GetEventHandler()->ProcessEvent(eventFileChanged);
					}
				}
				break;
			}
		}
		break;
	case ID_CLEARPHOTO:
		m_textCtrl1->SetValue(wxEmptyString);
		break;
	}	
}

void G3CustomFileSelect::OnPathChangedEvent( G3CustomFileChangedEvent& event )
{
	if ( event.IsAllowed() )
	{
		wxEventType eventType = event.GetEventType();

		if ( eventType == G3_EVT_FILE_CHANGED )
		{
			wxString strMsg="G3CustomFileSelect file changed: ";
			strMsg<<event.GetSelectedFilename();
			wxMessageBox(strMsg);
			wxLogDebug(strMsg);
		}
	}
}

void G3CustomFileSelect::SetPath(const wxString &path)
{
	wxFileName fn(m_strPath);
	wxASSERT(fn.GetExt().Length()==0);

	m_strPath=path;
}

void G3CustomFileSelect::SelectFile(const wxString &file)
{
	if(file.Length()==0)
	{
		m_textCtrl1->SetValue(wxEmptyString);
		m_textCtrl1->SetForegroundColour(*wxBLACK);
		return;
	}

	wxFileName fn(file);
	fn.MakeRelativeTo(m_strPath);
	
	if(wxFileExists(file))
		m_textCtrl1->SetForegroundColour(*wxBLACK);
	else
		m_textCtrl1->SetForegroundColour(*wxRED);

	m_textCtrl1->SetValue(fn.GetFullPath());
}

wxString G3CustomFileSelect::GetSelectedFile() const
{
	wxString strPath=m_strPath+wxFileName::GetPathSeparator()+m_textCtrl1->GetValue();

	wxFileName fn(strPath);
	fn.MakeRelativeTo(wxGetCwd());

	return fn.GetFullPath();
}

void G3CustomFileSelect::EnableSubfolders(bool iSsubFolderEnable)
{
	m_bBrowseSubfolders=iSsubFolderEnable;
}

G3CustomFileChangedEvent::G3CustomFileChangedEvent(wxEventType commandType, int id, wxString path)
	: wxNotifyEvent(commandType, id)
{
	m_strSelectedFilename=path;
}

wxString G3CustomFileChangedEvent::GetSelectedFilename() const
{
	return m_strSelectedFilename;
}


///////////////////////////////////////////
class FilesTraverser: public wxDirTraverser
{
protected:
	wxString m_strPathToFiles;

	wxListBox *m_ListBox;	

	wxString m_strFileSpecs;

	bool m_bSubDirs;

	wxArrayString m_arrFileSpecs;

public:
	FilesTraverser(const wxString &path, wxListBox *listbox, const wxString &fileSpecs, bool subDirs):
		m_strPathToFiles(path),
	  m_ListBox(listbox),
	  m_strFileSpecs(fileSpecs),
	  m_bSubDirs(subDirs)
	{
		m_ListBox->Clear();

		m_arrFileSpecs=wxSplit(fileSpecs, ';');
		wxASSERT(m_arrFileSpecs.GetCount()>0);
	}

	virtual wxDirTraverseResult OnFile(const wxString& fn)
	{
		wxFileName filename(fn);

		if(filename.FileExists())
		{
			wxString &strExtension=filename.GetExt().Lower();

			for(int i=0;i<m_arrFileSpecs.GetCount();i++)
			{
				wxString strFileSpec=m_arrFileSpecs[i];
				strFileSpec.Remove(0, 2);
				strFileSpec.LowerCase();

				if(strExtension!=strFileSpec)
					continue;
			
				// WZGLEDNA SCIEZKA DO RAPORTU*NUMER PLIKU RAPORTU*NUMER LINII
				filename.MakeRelativeTo(m_strPathToFiles);	
				  
				/*if(filename.GetDirCount()>0)
					filename.RemoveDir(0);*/

				m_ListBox->Append(filename.GetFullPath());			
			}							
		}

		return wxDIR_CONTINUE;
	}

	virtual wxDirTraverseResult OnDir(const wxString& dirname)
	{	
		return m_bSubDirs?wxDIR_CONTINUE:wxDIR_STOP;
	}

	virtual wxDirTraverseResult OnOpenError(const wxString &openerrorname)
	{
		return wxDIR_CONTINUE;
	}
};

ImageSelectDialog::ImageSelectDialog(const wxString &path, const wxString &fileExt, bool subfolders, const wxString &selectedFilename, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style ),
	m_strPath(path)
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listBox1 = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_HSCROLL|wxLB_SINGLE ); 
	m_listBox1->SetMinSize( wxSize( 200,-1 ) );
	m_listBox1->SetMaxSize( wxSize( 200,-1 ) );
	bSizer2->Add( m_listBox1, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer3->Add( m_panel2, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button2 = new wxButton( this, ID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer4->Add( m_button2, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_button3 = new wxButton( this, ID_CANCEL, _("Anuluj"), wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer4->Add( m_button3, 0, wxALL, 5 );
	
	
	bSizer3->Add( bSizer4, 0, wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_listBox1->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ImageSelectDialog::OnListBox ), NULL, this );
	m_panel2->Connect( wxEVT_PAINT, wxPaintEventHandler( ImageSelectDialog::OnPaint ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ImageSelectDialog::OnButtonClick ), NULL, this );
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ImageSelectDialog::OnButtonClick ), NULL, this );
		
	//////////////////////////////////

	CenterOnScreen();

	
	BuildTempBitmap();

	BuildFileList(path, fileExt, subfolders);

	SelectFile(selectedFilename);
}

ImageSelectDialog::~ImageSelectDialog()
{
	// Disconnect Events
	m_listBox1->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ImageSelectDialog::OnListBox ), NULL, this );
	m_panel2->Disconnect( wxEVT_PAINT, wxPaintEventHandler( ImageSelectDialog::OnPaint ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ImageSelectDialog::OnButtonClick ), NULL, this );
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ImageSelectDialog::OnButtonClick ), NULL, this );	
}

void ImageSelectDialog::BuildTempBitmap()
{
	m_bitmapEmptyTemplate=wxBitmap(m_panel2->GetClientSize());

	wxMemoryDC memDC;
	memDC.SelectObject(m_bitmapEmptyTemplate);

	memDC.SetBackground(*wxBLACK_BRUSH);
	memDC.Clear();

	wxRect rcFrame(m_bitmapEmptyTemplate.GetSize());
	memDC.SetTextForeground(*wxWHITE);
	memDC.DrawLabel("Nie zaznaczono obrazka", rcFrame, wxALIGN_CENTRE);
}

void ImageSelectDialog::BuildFileList(const wxString &path, const wxString &fileExt, bool subFolders)
{
	wxDir dir(path);
		
	if(!dir.IsOpened())
		return;

	dir.Traverse(FilesTraverser(m_strPath, m_listBox1, fileExt, subFolders));		
			
	dir.Close();	
}

void ImageSelectDialog::OnListBox( wxCommandEvent& event )
{
	m_button2->Disable();

	wxString strPath=m_strPath+wxFileName::GetPathSeparator()+event.GetString();
	
	if(m_bitmapBackground.IsOk())
		m_bitmapBackground.FreeResource();

	m_bitmapBackground=wxBitmap(strPath, wxBITMAP_TYPE_ANY);

	if(m_bitmapBackground.IsOk())
	{
		wxSize &bmpSize=m_bitmapBackground.GetSize();

		wxImage img=m_bitmapBackground.ConvertToImage();

		float bitmapAspectRadio=(float)bmpSize.GetWidth()/(float)bmpSize.GetHeight();

		if(bmpSize.GetWidth()>bmpSize.GetHeight())
		{
			int h=m_panel2->GetSize().GetWidth()/bitmapAspectRadio;
			img.Rescale(m_panel2->GetSize().GetWidth(), h, wxIMAGE_QUALITY_HIGH);
		}
		else
		{
			int w=m_panel2->GetSize().GetHeight()*bitmapAspectRadio;
			img.Rescale(w, m_panel2->GetSize().GetHeight(), wxIMAGE_QUALITY_HIGH);
		}

		m_bitmapBackground.FreeResource();

		m_bitmapBackground=wxBitmap(img);

		m_strSelectedFilename=event.GetString();

		m_button2->Enable();
	}
	else
		m_bitmapBackground=m_bitmapEmptyTemplate;

	m_panel2->Refresh();
}

void ImageSelectDialog::OnPaint( wxPaintEvent& event )
{
	wxPaintDC dc(m_panel2);

	if(m_bitmapBackground.IsOk())
	{
		wxPoint pos;
		pos.x=m_panel2->GetSize().GetWidth()/2-m_bitmapBackground.GetWidth()/2;
		pos.y=m_panel2->GetSize().GetHeight()/2-m_bitmapBackground.GetHeight()/2;
		dc.DrawBitmap(m_bitmapBackground, pos, true);
	}
}

void ImageSelectDialog::OnButtonClick( wxCommandEvent& event )
{
	switch(event.GetId())
	{
	case ID_OK:
		{
			m_strReturnedFilename=m_strSelectedFilename;

			EndDialog(wxID_OK);
		}
		break;
	case ID_CANCEL:
		EndDialog(wxID_CANCEL);
		break;
	}
}

wxString ImageSelectDialog::GetSelectedFilename() const
{
	return m_strReturnedFilename;
}

void ImageSelectDialog::SelectFile(const wxString &filename)
{
	/*wxFileName fn(m_strPath+wxFileName::GetPathSeparator()+filename);
	if(!fn.FileExists())
		return;

	fn.MakeRelativeTo(m_strPath);*/

	for(size_t i=0;i<m_listBox1->GetCount();i++)
	{
		if(m_listBox1->GetString(i)==filename/*fn.GetFullPath()*/)
		{
			m_listBox1->Select(i);

			wxCommandEvent evt;
			evt.SetString(m_listBox1->GetString(i));
			OnListBox(evt);
			break;
		}
	}
}

///////////////////////////////////////////

SoundSelectDialog::SoundSelectDialog(const wxString &path, const wxString &fileExt, bool subfolders, const wxString &selectedFilename, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style ),
	m_strPath(path)
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_listBox1 = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_HSCROLL|wxLB_SINGLE ); 
	m_listBox1->SetMinSize( wxSize( 200,-1 ) );
	m_listBox1->SetMaxSize( wxSize( 200,-1 ) );
	bSizer2->Add( m_listBox1, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel1->SetBackgroundColour( wxColour( 81, 81, 81 ) );
	
	bSizer3->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button21 = new wxButton( this, ID_PLAY, _("Play"), wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer4->Add( m_button21, 0, wxALL, 5 );
	
	
	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button2 = new wxButton( this, ID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer4->Add( m_button2, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_button3 = new wxButton( this, ID_CANCEL, _("Anuluj"), wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer4->Add( m_button3, 0, wxALL, 5 );
	
	
	bSizer3->Add( bSizer4, 0, wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_listBox1->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( SoundSelectDialog::OnListBox ), NULL, this );
	m_listBox1->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( SoundSelectDialog::OnListBoxDClick ), NULL, this );
	m_panel1->Connect( wxEVT_PAINT, wxPaintEventHandler( SoundSelectDialog::OnPaint ), NULL, this );
	m_button21->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SoundSelectDialog::OnButtonClick ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SoundSelectDialog::OnButtonClick ), NULL, this );
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SoundSelectDialog::OnButtonClick ), NULL, this );
	//////////////////////////////////

	CenterOnScreen();

	BuildFileList(path, fileExt, subfolders);

	SelectFile(selectedFilename);
}

SoundSelectDialog::~SoundSelectDialog()
{
	// Disconnect Events
	m_listBox1->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( SoundSelectDialog::OnListBox ), NULL, this );
	m_listBox1->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( SoundSelectDialog::OnListBoxDClick ), NULL, this );
	m_panel1->Disconnect( wxEVT_PAINT, wxPaintEventHandler( SoundSelectDialog::OnPaint ), NULL, this );
	m_button21->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SoundSelectDialog::OnButtonClick ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SoundSelectDialog::OnButtonClick ), NULL, this );
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SoundSelectDialog::OnButtonClick ), NULL, this );
	
	m_sound.Stop();
}

void SoundSelectDialog::BuildFileList(const wxString &path, const wxString &fileExt, bool subFolders)
{
	wxDir dir(path);
		
	if(!dir.IsOpened())
		return;

	dir.Traverse(FilesTraverser(m_strPath, m_listBox1, fileExt, subFolders));		
			
	dir.Close();
}

void SoundSelectDialog::OnListBox( wxCommandEvent& event )
{
	wxString strPath=m_strPath+wxFileName::GetPathSeparator()+event.GetString();
	
	if(!wxFileExists(strPath))
	{
		m_button21->Disable();

		m_strMsg="Brak pliku dźwiękowego!";

		return;
	}

	m_button21->Enable();

	m_strMsg="Nacisnij przycisk Start, aby odsłuchać";
		
	m_strSelectedFilename=event.GetString();

	m_panel1->Refresh();
}

void SoundSelectDialog::OnPaint( wxPaintEvent& event )
{
	wxPaintDC dc(m_panel1);

	dc.SetBackground(*wxBLACK_BRUSH);
	dc.Clear();

	wxRect rcFrame(m_panel1->GetClientRect());

	dc.SetTextForeground(*wxWHITE);
	dc.DrawLabel(m_strMsg, rcFrame, wxALIGN_CENTRE);
}

void SoundSelectDialog::OnListBoxDClick( wxCommandEvent& event )
{
}


void SoundSelectDialog::OnButtonClick( wxCommandEvent& event )
{
	switch(event.GetId())
	{
	case ID_PLAY:
		{
			wxString strPath=m_strPath+wxFileName::GetPathSeparator()+m_listBox1->GetStringSelection();

			if(wxFileExists(strPath))
			{
				m_sound.Stop();
				m_sound.Create(strPath);
				
				m_sound.Play();	
			}			
		}
		break;
	case ID_OK:
		{
			m_strReturnedFilename=m_strSelectedFilename;

			EndDialog(wxID_OK);
		}
		break;
	case ID_CANCEL:
		EndDialog(wxID_CANCEL);
		break;
	}
}

wxString SoundSelectDialog::GetSelectedFilename() const
{
	return m_strReturnedFilename;
}

void SoundSelectDialog::SelectFile(const wxString &filename)
{
	wxFileName fn(m_strPath+wxFileName::GetPathSeparator()+filename);
	if(!fn.FileExists())
	{
		m_button21->Disable();

		m_strMsg="Brak pliku dźwiękowego!";

		m_panel1->Refresh();

		return;
	}

	//fn.MakeRelativeTo(m_strPath);

	for(size_t i=0;i<m_listBox1->GetCount();i++)
	{
		if(m_listBox1->GetString(i)==filename)
		{
			m_listBox1->Select(i);

			wxCommandEvent evt;
			evt.SetString(m_listBox1->GetString(i));
			OnListBox(evt);

			break;
		}
	}
}