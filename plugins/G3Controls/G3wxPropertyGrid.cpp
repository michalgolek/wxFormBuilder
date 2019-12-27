#include "G3wxPropertyGrid.h"
//#include <wx\propgrid\propgrid.h>

//using namespace Editor;

//////////////////////////////////////////////////////////////////////////

#define wxPG_PIXELS_PER_UNIT 2
#define IN_CELL_EXPANDER_BUTTON_X_ADJUST    2
#define wxPG_FL_CUR_USES_CUSTOM_IMAGE       0x0100
#define wxPG_FL_FOCUSED                     0x0008

bool G3PGCellRenderer::Render( wxDC& dc, const wxRect& rect,
	const wxPropertyGrid* propertyGrid, wxPGProperty* property,
	int column, int item, int flags ) const
{
	const wxPGEditor* editor = NULL;
	const wxPGCell* cell = NULL;

	wxString text;
	bool isUnspecified = property->IsValueUnspecified();

	if ( column == 1 && item == -1 )
	{
		int cmnVal = property->GetCommonValue();
		if ( cmnVal >= 0 )
		{
			// Common Value
			if ( !isUnspecified )
			{
				text = propertyGrid->GetCommonValueLabel(cmnVal);
				DrawText( dc, rect, 0, text );
				if ( !text.empty() )
					return true;
			}
			return false;
		}
	}

	int imageWidth = 0;
	int preDrawFlags = flags;
	bool res = false;

	property->GetDisplayInfo(column, item, flags, &text, &cell);

	imageWidth = PreDrawCell( dc, rect, *cell, preDrawFlags );

	if ( column == 1 )
	{
		editor = property->GetColumnEditor(column);		

		if ( !isUnspecified )
		{
			// Regular property value

			wxSize imageSize = propertyGrid->GetImageSize(property, item);

			wxPGPaintData paintdata;
			paintdata.m_parent = propertyGrid;
			paintdata.m_choiceItem = item;

			if ( imageSize.x > 0 )
			{
				wxRect imageRect(rect.x + wxPG_CONTROL_MARGIN + wxCC_CUSTOM_IMAGE_MARGIN1,
					rect.y+wxPG_CUSTOM_IMAGE_SPACINGY,
					wxPG_CUSTOM_IMAGE_WIDTH,
					rect.height-(wxPG_CUSTOM_IMAGE_SPACINGY*2));

				dc.SetPen( wxPen(propertyGrid->GetCellTextColour(), 1, wxSOLID) );

				paintdata.m_drawnWidth = imageSize.x;
				paintdata.m_drawnHeight = imageSize.y;

				property->OnCustomPaint( dc, imageRect, paintdata );

				imageWidth = paintdata.m_drawnWidth;
			}

			text = property->GetValueAsString();

			// Add units string?
			if ( propertyGrid->GetColumnCount() <= 2 )
			{
				wxString unitsString = property->GetAttribute(wxPGGlobalVars->m_strUnits, wxEmptyString);
				if ( !unitsString.empty() )
					text = wxString::Format(wxS("%s %s"), text.c_str(), unitsString.c_str() );
			}
		}

		if ( text.empty() )
		{
			text = property->GetHintText();
			if ( !text.empty() )
			{
				res = true;

				const wxColour& hCol =
					propertyGrid->GetCellDisabledTextColour();
				dc.SetTextForeground(hCol);

				// Must make the editor NULL to override its own rendering
				// code.
				editor = NULL;
			}
		}
		else
		{
			res = true;
		}
	}

	int imageOffset = property->GetImageOffset(imageWidth);

	//ziper
	// RYSOWANIA TLA POD ETYKIETA PROPERTY(KOLUMNA 0) lub EDYTORA(KOLUMNA 1)
	if(column==0 )
	{		
		dc.SetPen(*wxTRANSPARENT_PEN);

		if(property->IsCategory())
		{
			
			//dc.SetBrush(propertyGrid->GetCellBackgroundColour());
			//dc.DrawRectangle(rect);

			//opryg bez zaokraglonych category
 			dc.SetBrush(wxBrush(wxColour(80, 80, 80)));	


 			dc.DrawRectangle(rect);
			// LUB
			// 			if(property->IsExpanded())
// 				dc.GradientFillLinear(rect, wxColour(30, 30, 30), wxColour(130, 130, 130), wxSOUTH);
// 			else
// 				dc.GradientFillLinear(rect, wxColour(50, 50, 50), wxColour(160, 160, 160), wxNORTH);
// 			
			

			//dc.DrawRectangle(rect.GetLeft(), rect.GetTop(), rect.GetWidth(), 2);

			// zakonczenie marginesu dla poprzedniej kategorii
// 			rect2.SetWidth(rect.GetWidth());
// 			rect2.SetHeight(rect.GetHeight());
// 			rect2.SetTop(-rect.GetHeight()+1);
// 			dc.DrawRoundedRectangle(rect2, 5);
// 
// 			rect2.SetWidth(30);
// 			dc.DrawRectangle(rect2);
		}
		else
		{		
			if(flags & Selected)
			{
				// RECT DLA KOLUMNY 0 PODZAS SELEKCJI
				dc.SetBrush(wxBrush(wxColour(230, 230, 200)));

				dc.DrawRectangle(rect);

				// rect dla szerokiego marginesu, dla property ktore ma duzo dzieci np, normnalnie renderowany byl rect o kolorze tla wxpropgrida
				wxRect rc=rect;
				rc.SetLeft(0);
				rc.SetWidth(rect.GetLeft());
				dc.DrawRectangle(rc);
			}
			else
			{
				if(m_iIndex%2)
				{
					dc.SetBrush(wxBrush(wxColour(210, 210, 210)));
				}
				else
				{
					dc.SetBrush(wxBrush(wxColour(220, 220, 220)));
				}

				dc.DrawRectangle(rect);

				// rect dla szerokiego marginesu, dla property ktore ma duzo dzieci np, normnalnie renderowany byl rect o kolorze tla wxpropgrida
				wxRect rc=rect;
				rc.SetLeft(0);
				rc.SetWidth(rect.GetLeft());
				dc.DrawRectangle(rc);				
			}			

			
			//dc.DrawRoundedRectangle(rect, 6);
			
			
			

			//
			//dc.GradientFillLinear(rect, wxColour(180, 180, 180), wxColour(250, 250, 250));
// 			if(flags & Selected)
// 				dc.GradientFillLinear(rect, wxColour(150, 150, 150), wxColour(200, 200, 200));
// 			else
// 				dc.GradientFillLinear(rect, wxColour(170, 170, 170), wxColour(220, 220, 220));
			
				
			//dc.GradientFillLinear(rect, wxColour(250, 250, 250), wxColour(180, 180, 180));

			//dc.SetPen(wxPen(*wxYELLOW, 1));
		}
	}
	else
	{
 		if(m_iIndex%2)
 		{
 			dc.SetBrush(wxBrush(wxColour(210, 210, 210)));
 			dc.SetPen(wxPen(wxColour(210, 210, 210)));
 		}
 		else
 		{
 			dc.SetBrush(wxBrush(wxColour(220, 220, 220)));
 			dc.SetPen(wxPen(wxColour(220, 220, 220)));
 		}
		wxRect m_rcEditorRealRect=rect;
		m_rcEditorRealRect.x+=imageOffset;
		m_rcEditorRealRect.width-=imageOffset;
 		dc.DrawRectangle(m_rcEditorRealRect);
		//dc.GradientFillLinear(rect, wxColour(200, 200, 200), wxColour(180, 180, 180));		
		
	}

	if(column==0)
	{
		if(property->IsCategory())
		{
			dc.SetTextForeground(wxColour(250, 250, 250));
		}
		else
		{
			if ( flags & Selected )
				dc.SetTextForeground(wxColour(50, 50, 50));
			else
				dc.SetTextForeground(wxColour(20, 20, 20));
		}
	}
	else
	{
		if ( flags & Selected )
			dc.SetTextForeground(wxColour(50, 50, 50));
		else
			dc.SetTextForeground(wxColour(20, 20, 20));
		
	}
	
	if(!property->IsEnabled())
		dc.SetTextForeground(wxColour(200, 200, 200));

	// oryg, renderowanie etykiet i edytora
	DrawEditorValue( dc, rect, imageOffset, text, property, editor );

// 	int yOffset = ((rect.height-dc.GetCharHeight())/2);
// 
// 	if ( editor )
// 	{
// 		wxRect rect2(rect);
// 		rect2.x += imageOffset;
// 		rect2.y += yOffset;d
// 		rect2.height -= yOffset;
// 		editor->DrawValue( dc, rect2, property, text );
// 	}
// 	else
// 	{
// // 		dc.DrawText( text,
// // 			rect.x+imageOffset+wxPG_XBEFORETEXT,
// // 			rect.y+yOffset );
// 		wxRect rectLabel(rect);
// 		if(property->IsCategory())
// 		{
// 			rectLabel.x+=15;
// 			rectLabel.width-=15;
// 		}
// 		else
// 		{
// 			rectLabel.x+=5;
// 			rectLabel.width-=5;
// 		}
// 		dc.DrawLabel(text, rectLabel, wxALIGN_LEFT|wxALIGN_CENTRE_VERTICAL);
// 	}
// 	


	// active caption gets nice dotted rectangle
	if ( property->IsCategory() && column == 0 )
	{
		if ( flags & Selected )
		{
			if ( imageOffset > 0 )
			{
				imageOffset -= DEFAULT_IMAGE_OFFSET_INCREMENT;
				imageOffset += wxCC_CUSTOM_IMAGE_MARGIN2 + 4;
			}

			// kropkowany obrys etykiety zaznaczonej kategorii
// 			DrawCaptionSelectionRect( dc,
// 				rect.x+wxPG_XBEFORETEXT-wxPG_CAPRECTXMARGIN+imageOffset,
// 				rect.y-wxPG_CAPRECTYMARGIN+1,
// 				((wxPropertyCategory*)property)->GetTextExtent(propertyGrid,
// 				wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Arial")
// 				/*propertyGrid->GetCaptionFont()*/)
// 				+(wxPG_CAPRECTXMARGIN*2),
// 				propertyGrid->GetFontHeight()+(wxPG_CAPRECTYMARGIN*2) );
		}
	}

	PostDrawCell(dc, propertyGrid, *cell, preDrawFlags);

	return res;
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(G3PropertyGrid, wxPropertyGrid);

IMPLEMENT_DYNAMIC_CLASS(G3PropertyGridEvent, wxNotifyEvent);

DEFINE_EVENT_TYPE(G3_EVT_PROPERTYGRID_PROPERTY_CHANGED)
DEFINE_EVENT_TYPE(G3_EVT_PROPERTYGRID_PROPERTY_BUTTON)
DEFINE_EVENT_TYPE(G3_EVT_PROPERTYGRID_PROPERTY_TOGGLE)

BEGIN_EVENT_TABLE(G3PropertyGrid, wxPropertyGrid)
END_EVENT_TABLE()


G3PropertyGrid::G3PropertyGrid()
{

}

G3PropertyGrid::G3PropertyGrid(wxWindow *parent, wxWindowID id, 
	const wxPoint &pos, const wxSize &size, 
	long style, const wxString &name):
wxPropertyGrid(parent, wxID_ANY,pos, size, style, name)
{	
	Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( G3PropertyGrid::OnPropertyGridChanged ), NULL, this );

	Connect( wxID_ANY, G3_EVT_PROPERTYGRID_PROPERTY_CHANGED, G3PropertyGridEventHandler( G3PropertyGrid::OnPropertyGridEvent ));
	Connect( wxID_ANY, G3_EVT_PROPERTYGRID_PROPERTY_BUTTON, G3PropertyGridEventHandler( G3PropertyGrid::OnPropertyGridEvent ));		
	Connect( wxID_ANY, G3_EVT_PROPERTYGRID_PROPERTY_TOGGLE, G3PropertyGridEventHandler( G3PropertyGrid::OnPropertyGridEvent ));		

}
// 
// #define wxPG_PIXELS_PER_UNIT 2
// #define IN_CELL_EXPANDER_BUTTON_X_ADJUST    2
// #define wxPG_FL_CUR_USES_CUSTOM_IMAGE       0x0100
// #define wxPG_FL_FOCUSED                     0x0008

G3PropertyGrid::~G3PropertyGrid()
{	
	Disconnect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( G3PropertyGrid::OnPropertyGridChanged ), NULL, this );

	Disconnect( wxID_ANY, G3_EVT_PROPERTYGRID_PROPERTY_CHANGED, G3PropertyGridEventHandler( G3PropertyGrid::OnPropertyGridEvent ));
	Disconnect( wxID_ANY, G3_EVT_PROPERTYGRID_PROPERTY_BUTTON, G3PropertyGridEventHandler( G3PropertyGrid::OnPropertyGridEvent ));
	Disconnect( wxID_ANY, G3_EVT_PROPERTYGRID_PROPERTY_TOGGLE, G3PropertyGridEventHandler( G3PropertyGrid::OnPropertyGridEvent ));
}

void G3PropertyGrid::ProcessButtonEventEditor(int controlID, wxPGProperty *prop)
{
	G3PropertyGridEvent eventButton( G3_EVT_PROPERTYGRID_PROPERTY_BUTTON, 0, prop, controlID);
	eventButton.SetEventObject(this);
	GetEventHandler()->ProcessEvent(eventButton);
}

void G3PropertyGrid::ProcessToggleButtonEventEditor(int controlID, wxPGProperty *prop)
{
	G3PropertyGridEvent eventButton( G3_EVT_PROPERTYGRID_PROPERTY_TOGGLE, 0, prop, controlID);
	eventButton.SetEventObject(this);
	GetEventHandler()->ProcessEvent(eventButton);
}

int G3PropertyGrid::DoDrawItems(wxDC& dc, const wxRect* itemsRect, bool isBuffered ) const
{
	//return wxPropertyGrid::DoDrawItems(dc, itemsRect, isBuffered);

	const wxPGProperty* firstItem;
    const wxPGProperty* lastItem;

    firstItem = DoGetItemAtY(itemsRect->y);
    lastItem = DoGetItemAtY(itemsRect->y+itemsRect->height-1);

    if ( !lastItem )
        lastItem = GetLastItem( wxPG_ITERATE_VISIBLE );

    if (IsFrozen() || m_height < 1 || firstItem == NULL )
        return itemsRect->y;

	//ToDo: odkomentowac
    //wxCHECK_MSG( !m_pState->m_itemsAdded, itemsRect->y, "no items added" );
    wxASSERT( m_pState->DoGetRoot()->GetChildCount() );

    int lh = m_lineHeight;

    int firstItemTopY;
    int lastItemBottomY;

    firstItemTopY = itemsRect->y;
    lastItemBottomY = itemsRect->y + itemsRect->height;

    // Align y coordinates to item boundaries
    firstItemTopY -= firstItemTopY % lh;
    lastItemBottomY += lh - (lastItemBottomY % lh);
    lastItemBottomY -= 1;

    // Entire range outside scrolled, visible area?
    if ( firstItemTopY >= (int)m_pState->GetVirtualHeight() ||
         lastItemBottomY <= 0 )
        return itemsRect->y;

    wxCHECK_MSG( firstItemTopY < lastItemBottomY,
                 itemsRect->y,
                 "invalid y values" );

    /*
    wxLogDebug("  -> DoDrawItems ( \"%s\" -> \"%s\"
               "height=%i (ch=%i), itemsRect = 0x%lX )",
        firstItem->GetLabel().c_str(),
        lastItem->GetLabel().c_str(),
        (int)(lastItemBottomY - firstItemTopY),
        (int)m_height,
        (unsigned long)&itemsRect );
    */

    wxRect r;

    long windowStyle = m_windowStyle;

    int xRelMod = 0;

    //
    // For now, do some manual calculation for double buffering
    // - buffer's y = 0, so align itemsRect and coordinates to that
    //
    // TODO: In future use wxAutoBufferedPaintDC (for example)
    //
    int yRelMod = 0;

    wxRect cr2;

    if ( isBuffered )
    {
        xRelMod = itemsRect->x;
        yRelMod = itemsRect->y;

        //
        // itemsRect conversion
        cr2 = *itemsRect;
        cr2.x -= xRelMod;
        cr2.y -= yRelMod;
        itemsRect = &cr2;
        firstItemTopY -= yRelMod;
        lastItemBottomY -= yRelMod;
    }

    int x = m_marginWidth - xRelMod;

    wxFont normalFont = GetFont();

    bool reallyFocused = (m_iFlags & wxPG_FL_FOCUSED) != 0;

    bool isPgEnabled = IsEnabled();

    //
    // Prepare some pens and brushes that are often changed to.
    //

    wxBrush marginBrush(m_colMargin);
    wxPen marginPen(m_colMargin);
    wxBrush capbgbrush(m_colCapBack,wxSOLID);
    wxPen linepen(m_colLine,4,wxSOLID);

    wxColour selBackCol;
    if ( isPgEnabled )
        selBackCol = m_colSelBack;
    else
        selBackCol = m_colMargin;

    // pen that has same colour as text
    wxPen outlinepen(m_colPropFore,1,wxSOLID);

    //
    // Clear margin with background colour
    //
    dc.SetBrush( marginBrush );
	// jeszcez inne krawedzie obok marginesu		
    if ( !(windowStyle & wxPG_HIDE_MARGIN) )
    {
        dc.SetPen( *wxTRANSPARENT_PEN );	
    }

    const wxPGProperty* firstSelected = GetSelection();
    const wxPropertyGridPageState* state = m_pState;

    // TODO: Only render columns that are within clipping region.

    dc.SetFont(normalFont);

    wxPropertyGridConstIterator it( state, wxPG_ITERATE_VISIBLE, firstItem );
    int endScanBottomY = lastItemBottomY + lh;
    int y = firstItemTopY;

    //
    // Pregenerate list of visible properties.
    wxArrayPGProperty visPropArray;
    visPropArray.reserve((m_height/m_lineHeight)+6);

    for ( ; !it.AtEnd(); it.Next() )
    {
        const wxPGProperty* p = *it;

        if ( !p->HasFlag(wxPG_PROP_HIDDEN) )
        {
            visPropArray.push_back((wxPGProperty*)p);

            if ( y > endScanBottomY )
                break;

            y += lh;
        }
    }

    visPropArray.push_back(NULL);

    wxPGProperty* nextP = visPropArray[0];

    int gridWidth = state->GetVirtualWidth();

    y = firstItemTopY;
    for ( unsigned int arrInd=1;
          nextP && y <= lastItemBottomY;
          arrInd++ )
    {
        wxPGProperty* p = nextP;
        nextP = visPropArray[arrInd];

		int rowHeight=m_fontHeight+(m_spacingy*2)+1;		
		
        int textMarginHere = x;
        int renderFlags = 0;

        int greyDepth = m_marginWidth;
		//ToDo: odkomentowac
        //if ( !(windowStyle & wxPG_HIDE_CATEGORIES) )
        //    greyDepth = (((int)p->m_depthBgCol)-1) * m_subgroup_extramargin + m_marginWidth;

        int greyDepthX = greyDepth - xRelMod;

        // Use basic depth if in non-categoric mode and parent is base array.
        if ( !(windowStyle & wxPG_HIDE_CATEGORIES) || p->GetParent() != m_pState->DoGetRoot())
        {
            textMarginHere += ((unsigned int)((p->GetDepth() -1)*m_subgroup_extramargin));
        }

        // Paint margin area
		//ziper
		//TUTAJ RYSUJEMY MARGINES
        //dc.SetBrush(marginBrush);
		
        //dc.SetPen(marginPen);
        if(p->IsCategory())
		{
 			dc.SetBrush(wxBrush(wxColour(80, 80, 80)));
 			dc.SetPen(wxPen(wxColour(80, 80, 80)));
 			dc.DrawRectangle( -xRelMod, y, greyDepth, lh );		

			//LUB
// 			if(p->IsExpanded())
// 				dc.GradientFillLinear(wxRect(-xRelMod, y, greyDepth, lh), wxColour(30, 30, 30), wxColour(130, 130, 130), wxSOUTH);
// 			else
// 				dc.GradientFillLinear(wxRect(-xRelMod, y, greyDepth, lh), wxColour(50, 50, 50), wxColour(160, 160, 160), wxNORTH);
		}
		else
		{
			// ten sam kolor co w kolumnie 1(editor)
			dc.SetBrush(wxBrush(wxColour(180, 180, 180)));
			dc.SetPen(wxPen(wxColour(180, 180, 180)));
			
			dc.DrawRectangle( -xRelMod, y, greyDepth, lh );

			int g3PropType=(int ) p->GetAttributeAsLong("g3proptype", -1);

			if(!p->HasFlag(wxPG_PROP_COMPOSED_VALUE) && g3PropType!=-1)
			{	
				//#####################################
				//RYSOWAC JAKO IKONY ???????????



				const wxFont &curFont=dc.GetFont();		
				const wxColour &curTextForegroundColor=dc.GetTextForeground();
				
				dc.SetTextForeground(*wxWHITE);
								
				//dc.SetFont(wxFont(7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial"));
				//#####################################
				switch(g3PropType)
				{
				case G3EPropertyVariableTypes::G3EPVT_STRING:
					dc.SetTextForeground(wxColour(80,80,80));
					dc.DrawLabel("str", wxRect(-xRelMod, y, greyDepth, lh), wxALIGN_CENTER);
					dc.SetTextForeground(*wxWHITE);
					dc.DrawLabel("str", wxRect(-xRelMod-1, y-1, greyDepth, lh), wxALIGN_CENTER);				
					break;
				case G3EPropertyVariableTypes::G3EPVT_BOOL:
					dc.SetTextForeground(wxColour(80,80,80));
					dc.DrawLabel("?", wxRect(-xRelMod+1, y+1, greyDepth, lh), wxALIGN_CENTER);
					dc.SetTextForeground(*wxWHITE);
					dc.DrawLabel("?", wxRect(-xRelMod, y, greyDepth, lh), wxALIGN_CENTER);
					break;
				case G3EPropertyVariableTypes::G3EPVT_FLOAT:
					dc.SetTextForeground(wxColour(80,80,80));
					dc.DrawLabel("flt", wxRect(-xRelMod, y, greyDepth, lh), wxALIGN_CENTER);
					dc.SetTextForeground(*wxWHITE);
					dc.DrawLabel("flt", wxRect(-xRelMod-1, y-1, greyDepth, lh), wxALIGN_CENTER);
					break;
				case G3EPropertyVariableTypes::G3EPVT_NUMBER:
					dc.SetTextForeground(wxColour(80,80,80));
					dc.DrawLabel("num", wxRect(-xRelMod, y, greyDepth, lh), wxALIGN_CENTER);
					dc.SetTextForeground(*wxWHITE);
					dc.DrawLabel("num", wxRect(-xRelMod-1, y-1, greyDepth, lh), wxALIGN_CENTER);
					break;
				case G3EPropertyVariableTypes::G3EPVT_ENUM:
					dc.SetTextForeground(wxColour(80,80,80));
					dc.DrawLabel("enu", wxRect(-xRelMod, y, greyDepth, lh), wxALIGN_CENTER);
					dc.SetTextForeground(*wxWHITE);
					dc.DrawLabel("enu", wxRect(-xRelMod-1, y-1, greyDepth, lh), wxALIGN_CENTER);
					break;
				case G3EPropertyVariableTypes::G3EPVT_CONTENT:
					dc.SetTextForeground(wxColour(80,80,80));
					dc.DrawLabel("con", wxRect(-xRelMod, y, greyDepth, lh), wxALIGN_CENTER);
					dc.SetTextForeground(*wxWHITE);
					dc.DrawLabel("con", wxRect(-xRelMod-1, y-1, greyDepth, lh), wxALIGN_CENTER);
					break;
				case G3EPropertyVariableTypes::G3EPVT_FRAME:
					dc.SetTextForeground(wxColour(80,80,80));
					dc.DrawLabel("frm", wxRect(-xRelMod, y, greyDepth, lh), wxALIGN_CENTER);
					dc.SetTextForeground(*wxWHITE);
					dc.DrawLabel("frm", wxRect(-xRelMod-1, y-1, greyDepth, lh), wxALIGN_CENTER);
					break;
				}
				//dc.SetFont(curFont); 
				dc.SetTextForeground(curTextForegroundColor);
				
				
			}
		}
		//dc.GradientFillLinear(wxRect(-xRelMod, y, greyDepth, lh), *wxRED, *wxBLUE);

        // dc.SetPen( linepen );
	    dc.SetPen(wxPen(wxColour(180, 180, 180)));

        int y2 = y + lh;

#ifdef __WXMSW__
        // Margin Edge
        // Modified by JACS to not draw a margin if wxPG_HIDE_MARGIN is specified, since it
        // looks better, at least under Windows when we have a themed border (the themed-window-specific
        // whitespace between the real border and the propgrid margin exacerbates the double-border look).

        // Is this or its parent themed?
        bool suppressMarginEdge = (GetWindowStyle() & wxPG_HIDE_MARGIN) &&
            (((GetWindowStyle() & wxBORDER_MASK) == wxBORDER_THEME) ||
            (((GetWindowStyle() & wxBORDER_MASK) == wxBORDER_NONE) && ((GetParent()->GetWindowStyle() & wxBORDER_MASK) == wxBORDER_THEME)));
#else
        bool suppressMarginEdge = false;
#endif
		// linia rysowana pomiedzy marginesem a kolumna 0
         if (!suppressMarginEdge)
             dc.DrawLine( greyDepthX, y, greyDepthX, y2 );
         else
         {
             // Blank out the margin edge
             dc.SetPen(wxPen(GetBackgroundColour()));
             dc.DrawLine( greyDepthX, y, greyDepthX, y2 );
             dc.SetPen( linepen );
         }

        // Splitters
        unsigned int si;
        int sx = x;

        for ( si=0; si<state->GetColumnCount(); si++ )
        {
            sx += state->GetColumnWidth(si);
			//ziper
			// glowny pionowy splitter
			dc.SetPen(wxColour(200, 200, 200));			
			//dc.SetPen(*wxBLACK_PEN);			
            dc.DrawLine( sx, y, sx, y2 );
        }

        // Horizontal Line, below
        //   (not if both this and next is category caption)
		//LINIA POMIEDZY ZAMKNIETYMI KATEGORIAMI
        if ( p->IsCategory() &&
             nextP && nextP->IsCategory() )
		{

			//oryg
			//dc.SetPen(m_colCapBack);

			dc.SetPen(wxPen(wxColour(50,50,50)));
		}

        dc.DrawLine( greyDepthX, y2-1, gridWidth-xRelMod, y2-1 );

        //
        // Need to override row colours?
        wxColour rowFgCol;
        wxColour rowBgCol;

        bool isSelected = state->DoIsPropertySelected(p);

        if ( !isSelected )
        {
            // Disabled may get different colour.
            if ( !p->IsEnabled() )
            {
                renderFlags |= wxPGCellRenderer::Disabled |
                               wxPGCellRenderer::DontUseCellFgCol;
                rowFgCol = m_colDisPropFore;
            }
        }
        else
        {
            renderFlags |= wxPGCellRenderer::Selected;

            if ( !p->IsCategory() )
            {
                renderFlags |= wxPGCellRenderer::DontUseCellFgCol |
                               wxPGCellRenderer::DontUseCellBgCol;

                if ( reallyFocused && p == firstSelected )
                {
                    rowFgCol = m_colSelFore;
                    rowBgCol = selBackCol;
                }
                else if ( isPgEnabled )
                {
                    rowFgCol = m_colPropFore;
                    if ( p == firstSelected )
                        rowBgCol = m_colMargin;
                    else
                        rowBgCol = selBackCol;
                }
                else
                {
                    rowFgCol = m_colDisPropFore;
                    rowBgCol = selBackCol;
                }
            }
        }



        wxBrush rowBgBrush;

        if ( rowBgCol.IsOk() )
            rowBgBrush = wxBrush(rowBgCol);

        if ( HasInternalFlag(wxPG_FL_CELL_OVERRIDES_SEL) )
            renderFlags = renderFlags & ~wxPGCellRenderer::DontUseCellColours;

        //
        // Fill additional margin area with background colour of first cell
        if ( greyDepthX < textMarginHere )
        {
            if ( !(renderFlags & wxPGCellRenderer::DontUseCellBgCol) )
            {
                wxPGCell& cell = p->GetCell(0);
                rowBgCol = cell.GetBgCol();
                rowBgBrush = wxBrush(rowBgCol);
            }
            dc.SetBrush(rowBgBrush);
            dc.SetPen(rowBgCol);
            dc.DrawRectangle(greyDepthX+1, y,
                             textMarginHere-greyDepthX, lh-1);
        }

        bool fontChanged = false;

        // Expander button rectangle
        wxRect butRect( ((p->GetDepth() - 1) * m_subgroup_extramargin) - xRelMod,
                        y,
                        m_marginWidth,
                        lh );

        // Default cell rect fill the entire row
        wxRect cellRect(greyDepthX, y,
                        gridWidth - greyDepth + 2, rowHeight-1 );

        bool isCategory = p->IsCategory();

        if ( isCategory )
        {
            dc.SetFont(m_captionFont);
			//ziper
			dc.SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Arial"));
            fontChanged = true;

            if ( renderFlags & wxPGCellRenderer::DontUseCellBgCol )
            {
                dc.SetBrush(rowBgBrush);
                dc.SetPen(rowBgCol);
            }

            if ( renderFlags & wxPGCellRenderer::DontUseCellFgCol )
            {
                dc.SetTextForeground(rowFgCol);
            }
        }
        else
        {
            // Fine tune button rectangle to actually fit the cell
            if ( butRect.x > 0 )
                butRect.x += IN_CELL_EXPANDER_BUTTON_X_ADJUST;

            if ( p->GetFlags() & wxPG_PROP_MODIFIED &&
                 (windowStyle & wxPG_BOLD_MODIFIED) )
            {
                dc.SetFont(m_captionFont);
                fontChanged = true;
            }

            // Magic fine-tuning for non-category rows
            cellRect.x += 1;
        }

        int firstCellWidth = state->GetColumnWidth(0) - (greyDepthX - m_marginWidth);
        int firstCellX = cellRect.x;

        // Calculate cellRect.x for the last cell
        unsigned int ci = 0;
        int cellX = x + 1;
        for ( ci=0; ci<state->GetColumnCount(); ci++ )
            cellX += state->GetColumnWidth(ci);
        cellRect.x = cellX;

        // Draw cells from back to front so that we can easily tell if the
        // cell on the right was empty from text
        bool prevFilled = true;
        ci = state->GetColumnCount();
        do
        {
            ci--;

            int textXAdd = 0;

            if ( ci == 0 )
            {
                textXAdd = textMarginHere - greyDepthX;
                cellRect.width = firstCellWidth;
                cellRect.x = firstCellX;
            }
            else
            {
                int colWidth = state->GetColumnWidth(ci);
                cellRect.width = colWidth;
                cellRect.x -= colWidth;
            }

            // Merge with column to the right?
            if ( !prevFilled && isCategory )
            {
                cellRect.width += state->GetColumnWidth(ci+1);
            }

            if ( !isCategory )
                cellRect.width -= 1;

            wxWindow* cellEditor = NULL;
            int cellRenderFlags = renderFlags;

            // Tree Item Button (must be drawn before clipping is set up)
            if ( ci == 0 && !HasFlag(wxPG_HIDE_MARGIN) && p->HasVisibleChildren() )
                DrawExpanderButton( dc, butRect, p );

            // Background
            if ( isSelected && (ci == 1 || ci == m_selColumn) )
            {
                if ( p == firstSelected )
                {
                    if ( ci == 1 && m_wndEditor )
                        cellEditor = m_wndEditor;
                    else if ( ci == m_selColumn && m_labelEditor )
                        cellEditor = m_labelEditor;
                }

                if ( cellEditor )
                {
					// ziper, kolor tla w komorce POD "edytorem"
                    wxColour editorBgCol =
                        cellEditor->GetBackgroundColour();
                    dc.SetBrush(editorBgCol);
                    dc.SetPen(editorBgCol);
                    dc.SetTextForeground(m_colPropFore);
                    dc.DrawRectangle(cellRect);

                    if ( m_dragStatus != 0 ||
                         (m_iFlags & wxPG_FL_CUR_USES_CUSTOM_IMAGE) )
                        cellEditor = NULL;
                }
                else
                {
                    dc.SetBrush(m_colPropBack);
                    dc.SetPen(m_colPropBack);
                    if ( p->IsEnabled() )
                        dc.SetTextForeground(m_colPropFore);
                    else
                        dc.SetTextForeground(m_colDisPropFore);
                }
            }
            else
            {
                if ( renderFlags & wxPGCellRenderer::DontUseCellBgCol )
                {
                    dc.SetBrush(rowBgBrush);
                    dc.SetPen(rowBgCol);
                }

                if ( renderFlags & wxPGCellRenderer::DontUseCellFgCol )
                {
                    dc.SetTextForeground(rowFgCol);
                }
            }

            dc.SetClippingRegion(cellRect);

            cellRect.x += textXAdd;
            cellRect.width -= textXAdd;

			
            // Foreground
            if ( !cellEditor )
            {
                G3PGCellRenderer* renderer=new G3PGCellRenderer();
				renderer->m_iIndex=arrInd;				
                int cmnVal = p->GetCommonValue();
                if ( cmnVal == -1 || ci != 1 )
                {
                    // renderer = p->GetCellRenderer(ci);
                     prevFilled = renderer->Render(dc, cellRect, this,
                                                   p, ci, -1,
                                                   cellRenderFlags );
                }
                else
                {
                    // renderer = GetCommonValue(cmnVal)->GetRenderer();
                     prevFilled = renderer->Render(dc, cellRect, this,
                                                   p, ci, -1,
                                                   cellRenderFlags );
                }
            }
            else
            {
                prevFilled = true;
            }

			if ( ci == 0 && !HasFlag(wxPG_HIDE_MARGIN) && p->HasVisibleChildren() )
				DrawExpanderButton( dc, butRect, p );

            dc.DestroyClippingRegion(); // Is this really necessary?
        }
        while ( ci > 0 );

        if ( fontChanged )
            dc.SetFont(normalFont);

        y += rowHeight;
    }

    return y;
}

void G3PropertyGrid::DrawExpanderButton( wxDC& dc, const wxRect& rect, wxPGProperty* property ) const
{
	dc.SetBrush(*wxBLACK_BRUSH);
	dc.SetPen(*wxTRANSPARENT_PEN);
	if ( property->IsExpanded() )
	{
		wxPoint pnt[]={wxPoint(0, 0), wxPoint(m_iconWidth, 0), wxPoint(m_iconWidth/2, m_iconWidth)};
		dc.DrawPolygon(3, pnt, rect.GetLeft()+m_gutterWidth, rect.GetTop()+m_buttonSpacingY);
	}
	else
	{
		wxPoint pnt[]={wxPoint(0, 0), wxPoint(0, m_iconWidth), wxPoint(m_iconWidth, m_iconWidth/2)};
		dc.DrawPolygon(3, pnt, rect.GetLeft()+m_iconWidth, rect.GetTop()+m_buttonSpacingY);
	}
}

wxPGProperty *G3PropertyGrid::AddCategory(const wxString& label, const wxString& name)
{
	return Append(new wxPropertyCategory(label, name));
}

wxPGProperty *G3PropertyGrid::AddComposed(const wxString& label, const wxString& name)
{
	return Append(new wxStringProperty(label, name, _("<composed>") ));
}

G3MultiStringProperty *G3PropertyGrid::AddStringProperty(wxPGProperty *parent, const wxString& label, const wxString& name)
{
	G3MultiStringProperty *pgProperty=new G3MultiStringProperty(this, label);

	if(parent==0)
		Append(pgProperty);
	else
		AppendIn(parent, pgProperty);

	return pgProperty;
}

G3MultiBoolProperty *G3PropertyGrid::AddBoolProperty(wxPGProperty *parent, const wxString& label, const wxString& name)
{
	G3MultiBoolProperty *pgProperty=new G3MultiBoolProperty(this, label);

	if(parent==0)
		Append(pgProperty);
	else
		AppendIn(parent, pgProperty);

	return pgProperty;
}

G3MultiFloatProperty *G3PropertyGrid::AddFloatProperty(wxPGProperty *parent, const wxString& label, const wxString& name, float spinnerStep)
{
	G3MultiFloatProperty *pgProperty=new G3MultiFloatProperty(this, label, name, spinnerStep);

	if(parent==0)
		Append(pgProperty);
	else
		AppendIn(parent, pgProperty);

	return pgProperty;
}

G3MultiIntProperty *G3PropertyGrid::AddIntProperty(wxPGProperty *parent, const wxString& label, const wxString& name, int spinnerStep)
{
	G3MultiIntProperty *pgProperty=new G3MultiIntProperty(this, label, name, spinnerStep);

	if(parent==0)
		Append(pgProperty);
	else
		AppendIn(parent, pgProperty);

	return pgProperty;
}
// 
// G3MultiColorProperty *G3PropertyGrid::AddMultiColorProperty(wxPGProperty *parent, const wxString& label, const wxString& name=wxPG_LABEL)
// {
// 
// }

G3MultiEnumProperty *G3PropertyGrid::AddEnumProperty(wxPGProperty *parent, const wxString& label, wxPGChoices &choices, int defaultSelected, const wxString& name)
{
	G3MultiEnumProperty *pgProperty=new G3MultiEnumProperty(this, label, name, choices, defaultSelected);

	if(parent==0)
		Append(pgProperty);
	else
		AppendIn(parent, pgProperty);

	return pgProperty;
}

G3ContentDataProperty *G3PropertyGrid::AddContentDataProperty(wxPGProperty *parent, const wxString& label, const wxString& name)
{
	G3ContentDataProperty *pgProperty=new G3ContentDataProperty(this, label, name);

	if(parent==0)
		Append(pgProperty);
	else
		AppendIn(parent, pgProperty);

	return pgProperty;
}

G3MultiFrameProperty *G3PropertyGrid::AddFrameProperty(wxPGProperty *parent, const wxString& label, const wxString& name, int framePerSec)
{
	G3MultiFrameProperty *pgProperty=new G3MultiFrameProperty(this, label, name, framePerSec);

	if(parent==0)
		Append(pgProperty);
	else
		AppendIn(parent, pgProperty);

	return pgProperty;
}

void G3PropertyGrid::EnableProperty(wxPGProperty *property)
{
	property->Enable(true);
}

void G3PropertyGrid::DisableProperty(wxPGProperty *property)
{
	property->Enable(false);
}

void G3PropertyGrid::OnPropertyGridChanged( wxPropertyGridEvent& event)
{
	wxPGProperty* property = event.GetProperty();

	// Do nothing if event did not have associated property
	if ( !property )
		return;

	// GetValue() returns wxVariant, but it is converted transparently to
	// wxAny
	wxVariant propValue = property->GetValue();

	// Also, handle the case where property value is unspecified
	if ( propValue.IsNull() )
		return;
		
	if(propValue.GetType()=="string")
	{
		G3MultiStringProperty *pMultiStringProperty=dynamic_cast<G3MultiStringProperty *>(property);

		if(pMultiStringProperty)
		{
			pMultiStringProperty->OnPropertyChangedEvent();
		}
		else
		{
			G3ContentDataProperty *pMultiContentProperty=dynamic_cast<G3ContentDataProperty *>(property);
			if(pMultiContentProperty)
			{
				pMultiContentProperty->OnPropertyChangedEvent();
			}
			else//STANDARDOWY PROP
			{
				if(!property->HasFlag(wxPG_PROP_COMPOSED_VALUE))
					wxASSERT_MSG(0, _("Propertygrid standard string property"));
			}

		}
	}

	if(propValue.GetType()=="long")
	{
		G3MultiEnumProperty *pMultiEnumProperty=dynamic_cast<G3MultiEnumProperty *>(property);
		if(pMultiEnumProperty)
		{
			pMultiEnumProperty->OnPropertyChangedEvent();			
		}
		else
		{
			G3MultiIntProperty *pMultiIntProperty=dynamic_cast<G3MultiIntProperty *>(property);
			if(pMultiIntProperty)
			{
			 	pMultiIntProperty->OnPropertyChangedEvent();
			}
			else
			{
				G3MultiEnumProperty *pMultiEnumProperty=dynamic_cast<G3MultiEnumProperty *>(property);
				if(pMultiEnumProperty)
				{
					pMultiEnumProperty->OnPropertyChangedEvent();
				}
				else
				{
					G3MultiFrameProperty *pMultiFrameProperty=dynamic_cast<G3MultiFrameProperty *>(property);
					if(pMultiFrameProperty)
					{
						pMultiFrameProperty->OnPropertyChangedEvent();
					}
					else //STANDARDOWY PROP
					{
						wxASSERT_MSG(0, _("Propertygrid standard long property"));
					}
				}
			}			
		}
			 
		property->RefreshEditor();
	}

	//////////////////////////////////////////////////////////////////////////

	if(propValue.GetType()=="double")
	{
		G3MultiFloatProperty *pMultiFloatProperty=dynamic_cast<G3MultiFloatProperty *>(property);

		if(pMultiFloatProperty)
		{
			pMultiFloatProperty->OnPropertyChangedEvent();
		}	
		else //STANDARDOWY PROP
		{
			wxASSERT_MSG(0, _("Propertygrid standard double property"));
		}
	}

	//Todo
// 	if(propValue.GetType()=="wxColour")
// 	{
// 		wxAny any=propValue;
// 
// 		wxColour rgb=any.As<wxColour>();
// 
// 		CVector4 *variablePointer=(CVector4*) propData->m_pUserData;
// 
// 		if(variablePointer)
// 		{
// 			*variablePointer=CVector4(rgb.Red()/(float)255.0f, rgb.Green()/(float)255.0f, rgb.Blue()/(float)255.0f, (*variablePointer).w);
// 		}
// 	}
// 
// 	if(propValue.GetType()=="wxColourPropertyValue")
// 	{
// 		wxColourPropertyValue v;
// 		v << property->GetValue();
// 
// 		wxColour rgb=v.m_colour;
// 
// 		CVector4 *variablePointer=(CVector4*) propData->m_pUserData;
// 
// 		if(variablePointer)
// 		{
// 			*variablePointer=CVector4(rgb.Red()/(float)255.0f, rgb.Green()/(float)255.0f, rgb.Blue()/(float)255.0f, (*variablePointer).w);
// 		}
// 	}

	G3PropertyGridEvent eventButton( G3_EVT_PROPERTYGRID_PROPERTY_CHANGED, GetId(), property, -1);
	eventButton.SetEventObject(this);
	GetEventHandler()->ProcessEvent(eventButton);
}

void G3PropertyGrid::OnPropertyGridEvent( G3PropertyGridEvent& event )
{
	if ( event.IsAllowed() )
	{
		wxEventType eventType = event.GetEventType();

		if ( eventType == G3_EVT_PROPERTYGRID_PROPERTY_CHANGED)
		{
			wxLogDebug( wxT("G3PropertyGrid property changed") );			
		}
		else if ( eventType == G3_EVT_PROPERTYGRID_PROPERTY_BUTTON )
		{
			wxLogDebug( wxT("G3PropertyGrid button") );
		}	
		else if ( eventType == G3_EVT_PROPERTYGRID_PROPERTY_TOGGLE )
		{
			wxLogDebug( wxT("G3PropertyGrid toggle") );
		}	
	}
}

//////////////////////////////////////////////////////////////////////////

G3PropertyGridEvent::G3PropertyGridEvent(wxEventType commandType, int id, wxPGProperty *prop, int button)
	: wxNotifyEvent(commandType, id),
	m_pProperty(prop),	
	m_iButton(button)
{
}

wxPGProperty *G3PropertyGridEvent::GetProperty() const
{
	return m_pProperty;
}

int G3PropertyGridEvent::GetButton() const
{
	return m_iButton;
}