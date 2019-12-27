#include "G3wxRollMenu.h"

//using namespace Editor;
#include <wx/dcclient.h>
#include <wx/window.h>
#include <wx/log.h> 

IMPLEMENT_DYNAMIC_CLASS(G3RollMenu, wxControl);

IMPLEMENT_DYNAMIC_CLASS(G3RollMenuEvent, wxNotifyEvent);

DEFINE_EVENT_TYPE(G3_EVT_ROLLMENU_ITEM_SELECTED)
DEFINE_EVENT_TYPE(G3_EVT_ROLLMENU_GROUP_OPEN)
DEFINE_EVENT_TYPE(G3_EVT_ROLLMENU_GROUP_CLOSE)
	
//////////////////////////////////////////////////////////////////////////

//zobacz do containters:
//template < class T >
//void OnBookPageChanged( int selPage, wxEvent* event )
//...
//m_manager->SelectObject( book->GetPage( selPage ) );




G3RollMenu::G3RollMenu()
{

}

G3RollMenu::G3RollMenu( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ):
wxPanel(parent, id, pos, size, style),
	m_labelItemColour(*wxWHITE),
	m_labelSelectedItemColour(wxColor(0, 160, 255)),
	m_selectedItemBackgroundColor(wxColor(60, 60, 60)),
	m_backgroundColor(wxColour(46, 46, 46)),
	m_pSelectedItem(NULL),
	m_pPreviousSelectedItem(NULL)
{
	m_labelMainFont=wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
	m_labelMainFont.SetPointSize(10);
	m_labelMainFont.MakeBold();

	m_labelItemFont=wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
	m_labelItemFont.SetPointSize(8);
	//m_labelItemFont.MakeBold();
	
	//SetLabelFont(wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier 10 Pitch"));
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3RollMenu::OnLeftDown ), NULL, this );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( G3RollMenu::OnPaintMenu ), NULL, this );	
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( G3RollMenu::OnSize ), NULL, this );	

	this->Connect( wxID_ANY, G3_EVT_ROLLMENU_ITEM_SELECTED, G3RollMenuEventHandler( G3RollMenu::OnRollMenuEvent ));
}

G3RollMenu::~G3RollMenu()
{
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( G3RollMenu::OnLeftDown ), NULL, this );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( G3RollMenu::OnPaintMenu ), NULL, this );	
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( G3RollMenu::OnSize ), NULL, this );	
	// 
	this->Disconnect( wxID_ANY, G3_EVT_ROLLMENU_ITEM_SELECTED, G3RollMenuEventHandler( G3RollMenu::OnRollMenuEvent ));

	wxList::iterator it;
	for (it=m_itemsList.begin();it!=m_itemsList.end();++it)
	{
		wxDELETE(*it);
	}

	m_itemsList.Clear();
}

void G3RollMenu::SetLabelItemColour(wxColor &color)
{
	m_labelItemColour=color;
}

void G3RollMenu::SetLabelSelectedItemColour(wxColor &color)
{
	m_labelSelectedItemColour=color;
}

void G3RollMenu::SetLabelSelectedItemBackgroundColour(wxColor &color)
{
	m_selectedItemBackgroundColor=color;
}

void G3RollMenu::SetBackgroundColour(wxColor &color)
{
	m_backgroundColor=color;
}

void G3RollMenu::OnLeftDown( wxMouseEvent& event )
{

	int curPaintHeight=0;
	
	for(size_t i=0;i<m_itemsList.size();i++)
	{
		G3RollMenuBase *itemBase=(G3RollMenuBase*) m_itemsList[i];

		if(itemBase)
		{
			// kliknieto w item w grupie ?
			if(itemBase->m_pParent)
			{
				G3RollMenuGroup*itemGroup=(G3RollMenuGroup*) itemBase->m_pParent;
				if(itemGroup)
				{
					// grupa jest zwijeta to lecimy dalej
					if(itemGroup->IsClosed())
						continue;
				}
			}

			if(event.GetY()>curPaintHeight && event.GetY()<curPaintHeight+G3ROLLMENU_VERTICAL_ITEM_SPACE)
			{
				m_pSelectedItem=itemBase;
				m_pSelectedItem->OnLeftDown(event);
				Refresh();
				break;			
			}
			
			curPaintHeight+=G3ROLLMENU_VERTICAL_ITEM_SPACE;
		}
	}
	
	G3RollMenuEvent eventSelected(G3_EVT_ROLLMENU_ITEM_SELECTED, m_pSelectedItem->m_id, m_pSelectedItem);
	eventSelected.SetEventObject(this);
	GetEventHandler()->ProcessEvent(eventSelected);
}

void G3RollMenu::OnPaintMenu(wxPaintEvent &event)
{
	wxPaintDC dc(this);

	dc.SetBrush(m_backgroundColor);
	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.DrawRectangle(m_menuClientRect);

	
	int curPaintHeight=0, curItem=0;
	for(int i=0;i<m_itemsList.size();i++)
	{
		G3RollMenuBase *itemBase=(G3RollMenuBase*) m_itemsList[i];
		
		if(itemBase)
		{
			curPaintHeight+=itemBase->Paint(dc, curPaintHeight, curItem);
		}
	}
}

void G3RollMenu::OnSize(wxSizeEvent& event)
{
	m_menuClientRect=GetClientRect();
}

void G3RollMenu::UpdateControl()
{
	wxSizeEvent sz(GetSize(), GetId());
	ProcessEvent(sz);
}

int G3RollMenu::GetNumItems() const
{
	return m_itemsList.size();
}

G3RollMenuGroup *G3RollMenu::AddGroup(G3RollMenuGroup *group)
{
	wxASSERT_MSG(group, wxString::Format("Cannot add group to G3RollMenu - %s", GetName()));

	m_itemsList.push_back(group);

	UpdateControl();



	return group;
}

bool G3RollMenu::RemoveGroup(const wxString &name)
{
	

	UpdateControl();

	return true;
}

bool G3RollMenu::RemoveGroup(int index)
{
	UpdateControl();

	return true;
}


#include "Embedded\channels32.png.h"
#include "Embedded\options32.png.h"
#include "Embedded\channelList32.png.h"
#include "Embedded\schedule32.png.h"
#include "Embedded\player32.png.h"
#include "Embedded\logs32.png.h"
#include "Embedded\exit32.png.h"




void G3RollMenu::BuildFromDate(const wxString &menuData)
{
	G3RollMenuPanel *pChannelList=new G3RollMenuPanel(this, _("Channel list"), 0, 0);
	pChannelList->SetIcon(channels32_png_to_wx_bitmap());
	
	AddPanel(pChannelList);
	G3RollMenuGroup *rollMenuGroupSettings=AddGroup(new G3RollMenuGroup(this, _("Settings"), 1, false));
	{
		rollMenuGroupSettings->SetIcon(options32_png_to_wx_bitmap());

		G3RollMenuPanel *pControlPanel=new G3RollMenuPanel(this, _("Control panel"), 1, rollMenuGroupSettings);		
		AddPanel(pControlPanel);

		G3RollMenuPanel *pChannels=new G3RollMenuPanel(this, _("Channels"), 2, rollMenuGroupSettings);
		pChannels->SetIcon(channelList32_png_to_wx_bitmap());
		AddPanel(pChannels);

		G3RollMenuPanel *pScheduler=new G3RollMenuPanel(this, _("Scheduler"), 3, rollMenuGroupSettings);
		pScheduler->SetIcon(schedule32_png_to_wx_bitmap());
		AddPanel(pScheduler);
		AddPanel(new G3RollMenuPanel(this, _("Password settings"), 4, rollMenuGroupSettings));
	}
	G3RollMenuPanel *pPlayer=new G3RollMenuPanel(this, _("Player"), 5, 0);
	pPlayer->SetIcon(player32_png_to_wx_bitmap());
	AddPanel(pPlayer);
	//AddSpacer(new G3RollMenuSpacer(this));

	G3RollMenuPanel *pHelp=new G3RollMenuPanel(this, _("Help"), 6, 0);
	AddPanel(pHelp);

	AddButton(new G3RollMenuButton(this, _("Hide"), 7, 0));

	G3RollMenuButton *pExit=new G3RollMenuButton(this, _("Exit"), 8, 0);
	pExit->SetIcon(exit32_png_to_wx_bitmap());
	AddButton(pExit);

	G3RollMenuPanel *pLogs=new G3RollMenuPanel(this, _("Logs"), 9, 0);
	pLogs->SetIcon(logs32_png_to_wx_bitmap());
	AddPanel(pLogs);

	SelectPanel(pChannelList);

	m_strMenuData=menuData;
};


G3RollMenuSpacer *G3RollMenu::AddSpacer(G3RollMenuSpacer *spacer)
{
	wxASSERT_MSG(spacer, wxString::Format("Cannot add item to G3RollMenu - %s", GetName()));

	m_itemsList.push_back(spacer);

	UpdateControl();

	return spacer;
}

G3RollMenuButton *G3RollMenu::AddButton(G3RollMenuButton *button)
{
	wxASSERT_MSG(button, wxString::Format("Cannot add item to G3RollMenu - %s", GetName()));

	m_itemsList.push_back(button);

	UpdateControl();

	return button;
}

bool G3RollMenu::RemoveButton(const wxString &name)
{
	UpdateControl();

	return true;
}

bool G3RollMenu::RemoveButton(int index)
{
	UpdateControl();

	return true;
}

// zrobic wxpanel jako G3RollMenuPanel ?
bool G3RollMenu::AddPanel(G3RollMenuPanel *panel)
{
	m_itemsList.push_back(panel);

	Layout();
	return true;
}

void G3RollMenu::SelectPanel(G3RollMenuBase *item)
{
	m_pPreviousSelectedItem=m_pSelectedItem;
	m_pSelectedItem=item;
}

void G3RollMenu::Clear()
{
	UpdateControl();
}

void G3RollMenu::SelectItem(const wxString &name)
{
	Layout();
	UpdateControl();
}

void G3RollMenu::SelectItem(const G3RollMenuBase &menuBase)
{
	UpdateControl();
}

void G3RollMenu::SelectItem(int index)
{
	UpdateControl();
}

void G3RollMenu::EnsureItemVisible(const wxString &name)
{
	UpdateControl();
}

void G3RollMenu::EnsureItemVisible(const G3RollMenuBase &menuBase)
{
	UpdateControl();
}

void G3RollMenu::EnsureItemVisible(int index)
{
	UpdateControl();
}

void G3RollMenu::OnRollMenuEvent( G3RollMenuEvent& event )
{
	if ( event.IsAllowed() )
	{
		wxEventType eventType = event.GetEventType();

		if ( eventType == G3_EVT_ROLLMENU_ITEM_SELECTED )
		{
			//wxMessageBox(wxString::Format("%s, id:%i", event.GetItem()->m_strLabel, event.GetId()));
			wxLogDebug( wxT("G3RollMenu item selected") );
		}
		else if ( eventType == G3_EVT_ROLLMENU_GROUP_OPEN)
		{
			wxLogDebug( wxT("G3RollMenu group open") );
		}
		else if ( eventType == G3_EVT_ROLLMENU_GROUP_CLOSE )
		{
			wxLogDebug( wxT("G3RollMenu group open") );
		}		
	}
}

//////////////////////////////////////////////////////////////////////////

G3RollMenuBase::G3RollMenuBase()
{
}

G3RollMenuBase::G3RollMenuBase(G3RollMenu *mainMenu, const wxString &label, int id, G3RollMenuGroup *parent):
m_pRollMenu(mainMenu),
	m_strLabel(label),
	m_id(id),
	m_pParent(parent),
	m_bmpIcon(wxNullBitmap)
{
}

G3RollMenuBase::~G3RollMenuBase()
{

}

void G3RollMenuBase::SetIcon(const wxBitmap &bmp)
{
	m_bmpIcon=bmp;
}

int G3RollMenuBase::Paint(wxPaintDC &dc, int verticalOffset, int &currentItem)
{
	dc.SetPen(wxPen(wxColor(0, 0, 0)));
	dc.DrawLine(0, verticalOffset, m_pRollMenu->GetClientSize().GetWidth(), verticalOffset);
	dc.SetPen(wxPen(wxColor(60, 60, 60)));
	dc.DrawLine(0, verticalOffset+1, m_pRollMenu->GetClientSize().GetWidth(), verticalOffset+1);

	return 0;
}

void G3RollMenuBase::OnLeftDown( wxMouseEvent& event )
{
	//wxMessageBox(m_strLabel);
	// item nie nalezy do grupy ?
	if(!m_pParent)
	{
		for(size_t i=0;i<m_pRollMenu->m_itemsList.size();i++)
		{
			G3RollMenuGroup *itemGroup=(G3RollMenuGroup*) m_pRollMenu->m_itemsList[i];

			// zwijamy wszystkie grupy
			if(itemGroup)
			{			
				itemGroup->Close();
			}
		}
	}	
}
//////////////////////////////////////////////////////////////////////////

G3RollMenuGroup::G3RollMenuGroup()
{	
}

G3RollMenuGroup::G3RollMenuGroup(G3RollMenu *mainMenu, const wxString &label, int id, bool closed):
G3RollMenuBase(mainMenu, label, id, 0),
	m_bClosed(true)	
{
}

G3RollMenuGroup::~G3RollMenuGroup()
{

}

void G3RollMenuGroup::AddChild(G3RollMenuBase *child)
{
	m_childs.push_back(child);
}

int G3RollMenuGroup::Paint(wxPaintDC &dc, int verticalOffset, int &currentItem)
{
	int totalVerticalSize=G3ROLLMENU_VERTICAL_ITEM_SPACE;
	wxRect rc(45, verticalOffset, m_pRollMenu->GetClientSize().GetWidth(), G3ROLLMENU_VERTICAL_ITEM_SPACE);
		
	if(m_pRollMenu->m_pSelectedItem==this)
	{		
		dc.SetBrush(m_pRollMenu->m_selectedItemBackgroundColor);
		dc.SetPen(*wxTRANSPARENT_PEN);
		dc.DrawRectangle(wxRect(0, verticalOffset, m_pRollMenu->GetClientSize().GetWidth(), G3ROLLMENU_VERTICAL_ITEM_SPACE));

		dc.SetTextForeground(m_pRollMenu->m_labelSelectedItemColour);
	}
	else
		dc.SetTextForeground(m_pRollMenu->m_labelItemColour);

	if(m_bmpIcon.IsOk())
		dc.DrawBitmap(m_bmpIcon, 0, verticalOffset, true);

	dc.SetFont(m_pRollMenu->m_labelMainFont);

	
	dc.DrawLabel(m_strLabel, rc, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL);

	int tmp;
	G3RollMenuBase::Paint(dc, verticalOffset+G3ROLLMENU_VERTICAL_ITEM_SPACE, tmp);

	currentItem++;
	
// 	if(!m_bClosed)
// 	{
// 		wxList::iterator it;
// 		for (it=m_childs.begin();it!=m_childs.end();++it)
// 		{
// 			G3RollMenuBase *pRollMenuBase=(G3RollMenuBase *) (*it);
// 
// 			totalVerticalSize+=pRollMenuBase->Paint(dc, verticalOffset+totalVerticalSize, currentItem);	
// 		}
// 	}
	

	return totalVerticalSize;
}

void G3RollMenuGroup::OnLeftDown( wxMouseEvent& event )
{
	m_bClosed=false;
	if(m_childs.size()>0)
	{
		m_pRollMenu->m_pPreviousSelectedItem=m_pRollMenu->m_pSelectedItem;
		m_pRollMenu->m_pSelectedItem=(G3RollMenuBase*)m_childs[0];
	}

	for(size_t i=0;i<m_pRollMenu->m_itemsList.size();i++)
	{
		G3RollMenuGroup *itemGroup=(G3RollMenuGroup*) m_pRollMenu->m_itemsList[i];

		if(itemGroup)
		{			
			// zwijamy inne grupy
			if(itemGroup->m_id!=m_pRollMenu->m_pSelectedItem->m_id)
				itemGroup->Close();
		}
	}
}

bool G3RollMenuGroup::IsClosed() const
{
	return m_bClosed;
}

void G3RollMenuGroup::Close()
{
	m_bClosed=true;
}
//////////////////////////////////////////////////////////////////////////
G3RollMenuButton::G3RollMenuButton()
{

}

G3RollMenuButton::G3RollMenuButton(G3RollMenu *mainMenu, const wxString &label, int id, G3RollMenuGroup *parent):
G3RollMenuBase(mainMenu, label, id, parent)
{
}

G3RollMenuButton::~G3RollMenuButton()
{

}

int G3RollMenuButton::Paint(wxPaintDC &dc, int verticalOffset, int &currentItem)
{
	if(m_pParent)
	{
		if(m_pParent->IsClosed())
			return 0;
	}

	int horizontalOffset=m_pParent?55:45;

	wxRect rc(horizontalOffset, verticalOffset, m_pRollMenu->GetClientSize().GetWidth(), G3ROLLMENU_VERTICAL_ITEM_SPACE);
	
	if(m_pRollMenu->m_pSelectedItem==this)
	{
		dc.SetBrush(m_pRollMenu->m_selectedItemBackgroundColor);
		dc.SetPen(*wxTRANSPARENT_PEN);
		dc.DrawRectangle(wxRect(0, verticalOffset, m_pRollMenu->GetClientSize().GetWidth(), G3ROLLMENU_VERTICAL_ITEM_SPACE));

		dc.SetTextForeground(m_pRollMenu->m_labelSelectedItemColour);
	}
	else
		dc.SetTextForeground(m_pRollMenu->m_labelItemColour);

	if(m_bmpIcon.IsOk())
		dc.DrawBitmap(m_bmpIcon, 0, verticalOffset, true);
	
	if(m_pParent)
		dc.SetFont(m_pRollMenu->m_labelItemFont);
	else
		dc.SetFont(m_pRollMenu->m_labelMainFont);
	
	dc.DrawLabel(m_strLabel, rc, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL);

	int tmp;
	if(!m_pParent)
	{
		G3RollMenuBase::Paint(dc, verticalOffset, tmp);
		G3RollMenuBase::Paint(dc, verticalOffset+G3ROLLMENU_VERTICAL_ITEM_SPACE, tmp);
	}

	currentItem++;

	return G3ROLLMENU_VERTICAL_ITEM_SPACE;
}

//////////////////////////////////////////////////////////////////////////
G3RollMenuPanel::G3RollMenuPanel()
{

}

G3RollMenuPanel::G3RollMenuPanel(G3RollMenu *mainMenu, const wxString &label, int id, G3RollMenuGroup *parent):
G3RollMenuBase(mainMenu, label, id, parent)
{
	if(parent)
		parent->AddChild(this);
}

G3RollMenuPanel::~G3RollMenuPanel()
{

}

int G3RollMenuPanel::Paint(wxPaintDC &dc, int verticalOffset, int &currentItem)
{	
	if(m_pParent)
	{
		if(m_pParent->IsClosed())
			return 0;
	}

	int horizontalOffset=m_pParent?55:45;

	wxRect rc(horizontalOffset, verticalOffset, m_pRollMenu->GetClientSize().GetWidth(), m_pParent?G3ROLLMENU_VERTICAL_SUB_ITEM_SPACE:G3ROLLMENU_VERTICAL_ITEM_SPACE);
	
	if(m_pRollMenu->m_pSelectedItem==this)
	{
		dc.SetBrush(m_pRollMenu->m_selectedItemBackgroundColor);
		dc.SetPen(*wxTRANSPARENT_PEN);
		dc.DrawRectangle(wxRect(0, verticalOffset, m_pRollMenu->GetClientSize().GetWidth(), G3ROLLMENU_VERTICAL_ITEM_SPACE));

		dc.SetTextForeground(m_pRollMenu->m_labelSelectedItemColour);
	}
	else
		dc.SetTextForeground(m_pRollMenu->m_labelItemColour);

	if(m_bmpIcon.IsOk())
		dc.DrawBitmap(m_bmpIcon, 0, verticalOffset, true);

	if(m_pParent)
		dc.SetFont(m_pRollMenu->m_labelItemFont);
	else
		dc.SetFont(m_pRollMenu->m_labelMainFont);

	
	
	dc.DrawLabel(m_strLabel, rc, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL);

	int tmp;
	if(!m_pParent)
	{
		G3RollMenuBase::Paint(dc, verticalOffset, tmp);
		G3RollMenuBase::Paint(dc, verticalOffset+G3ROLLMENU_VERTICAL_ITEM_SPACE, tmp);
	}

	currentItem++;

	return m_pParent?G3ROLLMENU_VERTICAL_SUB_ITEM_SPACE:G3ROLLMENU_VERTICAL_ITEM_SPACE;
}
//////////////////////////////////////////////////////////////////////////

G3RollMenuSpacer::G3RollMenuSpacer()
{

}

G3RollMenuSpacer::G3RollMenuSpacer(G3RollMenu *mainMenu):
G3RollMenuBase(mainMenu)
{
}

G3RollMenuSpacer::~G3RollMenuSpacer()
{

}

int G3RollMenuSpacer::Paint(wxPaintDC &dc, int verticalOffset, int &currentItem)
{
	//int numNextItems=m_pRollMenu->m_itemsList.size()-currentItem;
	
	currentItem++;
	return 100;
}
//////////////////////////////////////////////////////////////////////////

G3RollMenuEvent::G3RollMenuEvent(wxEventType commandType, int id, G3RollMenuBase *item)
		: wxNotifyEvent(commandType, id)
{
	m_pItem=item;
}

G3RollMenuBase *G3RollMenuEvent::GetItem() const
{
	return m_pItem;
}