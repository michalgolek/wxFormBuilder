#include "G3wxPropertyGridProperty.h"

#include <wx/renderer.h> // wxRendererNative

#include <wx/msgdlg.h> 

#include <typeinfo> //dla specjalizacji szablonu/patrz nizej

CG3PropertyBaseData::CG3PropertyBaseData():
wxObject()
{	
}

CG3PropertyBaseData::~CG3PropertyBaseData()
{

}

template class G3PGProperty<std::string>;
template class G3PGProperty<bool>;
template class G3PGProperty<int>;
template class G3PGProperty<float>;

//using namespace Editor;



//////////////////////////////////////////////////////////////////////////
// BASE CLASS FOD G3PROPERTY

template<typename T>
G3PGProperty<T>::G3PGProperty(wxPGProperty *prop, int variableType):
m_pProperty(prop)
{
	prop->SetAttribute("g3proptype", variableType);

	prop->Enable(false);
}

template<typename T>
G3PGProperty<T>::~G3PGProperty()
{

}

template<typename T>
void G3PGProperty<T>::BeginAddValues()
{
	m_propertyValueList.clear();
	m_propertyDataList.clear();
}

template<typename T>
void G3PGProperty<T>::AddValue(T *val, CG3PropertyBaseData *propData)
{
	m_propertyValueList.push_back(val);
	m_propertyDataList.push_back(propData);
}

template<typename T>
void G3PGProperty<T>::EndAddValues()
{
	m_pProperty->SetAttribute("sameValues", true);

	for (int i=0;i<m_propertyValueList.size();i++)
	{
		if(*m_propertyValueList[0]!=(*m_propertyValueList.at(i)))
		{
			m_pProperty->SetAttribute("sameValues", false);

			break;
		}		
	}	

	if(m_propertyValueList.size()>0)
	{
		if(m_pProperty->GetAttribute("sameValues"))

			m_pProperty->SetValue(*m_propertyValueList.at(0));

		//todo
		//if(!oryginalStateEnabled)
		GetWxProperty()->Enable(true);		
	}
}

template<typename T>
wxPGProperty *G3PGProperty<T>::GetWxProperty() const
{
	return m_pProperty;
}
//////////////////////////////////////////////////////////////////////////

G3MultiStringProperty ::G3MultiStringProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name):
wxStringProperty(label, name),
	G3PGProperty<std::string>(this, G3EPropertyVariableTypes::G3EPVT_STRING)
{	
	propGrid->SetPropertyEditor(this, new G3StringMultiValPGEditor());	
}

G3MultiStringProperty ::~G3MultiStringProperty()
{
}

void G3MultiStringProperty::OnPropertyChangedEvent()
{
	// GetValue() returns wxVariant, but it is converted transparently to
	// wxAny
	wxVariant propValue = GetValue();

	// Also, handle the case where property value is unspecified
	if ( propValue.IsNull() )
		return;

	// zbedne
	//G3StringMultiValPGEditor *pEd=(G3StringMultiValPGEditor *) GetEditorClass();
	for (int i=0;i<m_propertyValueList.size();i++)
	{
		*m_propertyValueList.at(i)=std::string(propValue.GetString()/*.c_str()*/);

		CG3PropertyBaseData *propData=(CG3PropertyBaseData*)  m_propertyDataList.at(i);	
		if(propData)
			propData->DoUpdate();
	}			

	SetAttribute("sameValues", true);

	UpdateAfterOnPropertyChangeEvent();
}

//////////////////////////////////////////////////////////////////////////

G3MultiBoolProperty::G3MultiBoolProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name):
wxBoolProperty(label, name),
	G3PGProperty<bool>(this, G3EPropertyVariableTypes::G3EPVT_BOOL)
{	
	propGrid->SetPropertyEditor(this, new G3BoolMultiValPGEditor());	
}

G3MultiBoolProperty ::~G3MultiBoolProperty()
{
}

void G3MultiBoolProperty::OnPropertyChangedEvent()
{
	// GetValue() returns wxVariant, but it is converted transparently to
	// wxAny
	wxVariant propValue = GetValue();

	// Also, handle the case where property value is unspecified
	if ( propValue.IsNull() )
		return;

	// zbedne
	//G3StringMultiValPGEditor *pEd=(G3StringMultiValPGEditor *) GetEditorClass();
	for (int i=0;i<m_propertyValueList.size();i++)
	{
		*m_propertyValueList.at(i)=propValue.GetBool();

		CG3PropertyBaseData *propData=(CG3PropertyBaseData*)  m_propertyDataList.at(i);	
		if(propData)
			propData->DoUpdate();
	}			

	SetAttribute("sameValues", true);

	UpdateAfterOnPropertyChangeEvent();
}

//////////////////////////////////////////////////////////////////////////

G3MultiFloatProperty ::G3MultiFloatProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name, float spinnerStep):
wxFloatProperty(label, name),
	G3PGProperty<float>(this, G3EPropertyVariableTypes::G3EPVT_FLOAT)
{	
	propGrid->SetPropertyEditor(this, new G3SpinMultiValPGEditor());

	SetAttribute("MotionSpin", true);
	SetAttribute(wxPG_ATTR_SPINCTRL_STEP, spinnerStep);
}

G3MultiFloatProperty ::~G3MultiFloatProperty()
{
}

void G3MultiFloatProperty::OnPropertyChangedEvent()
{
	// GetValue() returns wxVariant, but it is converted transparently to
	// wxAny
	wxVariant propValue = GetValue();

	// Also, handle the case where property value is unspecified
	if ( propValue.IsNull() )
		return;

	G3SpinMultiValPGEditor *pEd=(G3SpinMultiValPGEditor *) GetEditorClass();

	// do debugowania
	// 	if(!pEd->m_bEditedBySpinner)
	// 	{
	// 		wxString ss;
	// 		for (int i=0;i<m_propertyValueList.size();i++)
	// 		{
	// 			ss+=wxString::Format("%f\n", *m_propertyValueList[i]);
	// 
	// 		}
	// 		wxMessageBox(ss);
	// 
	// 	}

	bool sameValue=true;


	for (int i=0;i<m_propertyValueList.size();i++)
	{
		if(pEd)
		{
			if(GetAttribute("sameValues"))
				*m_propertyValueList.at(i)=(float) propValue.GetDouble();
			else
			{
				if(pEd->m_bEditedBySpinner)
				{
					*m_propertyValueList.at(i)+=(float) propValue.GetDouble();

					double vmin=GetAttributeAsDouble(wxPG_ATTR_MIN, 10000.0);

					if(vmin!=10000.0)
					{
						if(*m_propertyValueList.at(i)<vmin)
							*m_propertyValueList.at(i)=vmin;
					}

					double vmax=GetAttributeAsDouble(wxPG_ATTR_MAX, -10000.0);

					if(vmax!=-10000.0)
					{
						if(*m_propertyValueList.at(i)>vmax)
							*m_propertyValueList.at(i)=vmax;
					}

					if(*m_propertyValueList[0]!=*m_propertyValueList.at(i))
						sameValue=false;
				}
				else
					*m_propertyValueList.at(i)=(float) propValue.GetDouble();				
			}
		}
		else
			*m_propertyValueList.at(i)=(float) propValue.GetDouble();	

		CG3PropertyBaseData *propData=(CG3PropertyBaseData*)  m_propertyDataList.at(i);	
		if(propData)
			propData->DoUpdate();
	}

	if(pEd)
	{
		// jesli spinowana wartosc dojdzie do min/max dla wszystkich wartosci to ustawiamy "editor" dla property bez mixu
		if(sameValue)
		{
			SetAttribute("sameValues", true);
		}
		else
			SetValue(0.0);
	}

	UpdateAfterOnPropertyChangeEvent();
}

void G3MultiFloatProperty::SetMinRange(float min)
{
	SetAttribute(wxPG_ATTR_MIN, (double)min);
}

void G3MultiFloatProperty::SetMaxRange(float max)
{
	SetAttribute(wxPG_ATTR_MAX, (double)max);
}

void G3MultiFloatProperty::SetSpinnerStep(float step)
{
	SetAttribute(wxPG_ATTR_SPINCTRL_STEP, (double)step);
}

//////////////////////////////////////////////////////////////////////////

G3MultiIntProperty::G3MultiIntProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name, int spinnerStep):
wxIntProperty(label, name),
	G3PGProperty<int>(this, G3EPropertyVariableTypes::G3EPVT_NUMBER)
{	
	propGrid->SetPropertyEditor(this, new G3SpinMultiValPGEditor());

	SetAttribute("MotionSpin", true);
	SetAttribute(wxPG_ATTR_SPINCTRL_STEP, spinnerStep);
}

G3MultiIntProperty ::~G3MultiIntProperty()
{
}

void G3MultiIntProperty::OnPropertyChangedEvent()
{
	// GetValue() returns wxVariant, but it is converted transparently to
	// wxAny
	wxVariant propValue = GetValue();

	// Also, handle the case where property value is unspecified
	if ( propValue.IsNull() )
		return;

	G3SpinMultiValPGEditor *pEd=(G3SpinMultiValPGEditor *) GetEditorClass();

	bool sameValue=true;
	for (int i=0;i<m_propertyValueList.size();i++)
	{
		if(pEd)
		{
			if(GetAttribute("sameValues"))
				*m_propertyValueList.at(i)=(int) propValue.GetLong();
			else
			{
				if(pEd->m_bEditedBySpinner)
				{
					*m_propertyValueList.at(i)+=(int) propValue.GetLong();

					wxVariant vmin=GetAttribute(wxPG_ATTR_MIN);

					if(!vmin.IsNull())
					{
						if(*m_propertyValueList.at(i)<vmin.GetLong())
							*m_propertyValueList.at(i)=vmin.GetLong();
					}

					wxVariant vmax=GetAttribute(wxPG_ATTR_MAX);

					if(!vmax.IsNull())
					{
						if(*m_propertyValueList.at(i)>vmax.GetLong())
							*m_propertyValueList.at(i)=vmax.GetLong();
					}

					if(*m_propertyValueList[0]!=*m_propertyValueList.at(i))
						sameValue=false;
				}
				else
					*m_propertyValueList.at(i)=(int) propValue.GetLong();				
			}
		}
		else
			*m_propertyValueList.at(i)=(int) propValue.GetLong();	

		CG3PropertyBaseData *propData=(CG3PropertyBaseData*)  m_propertyDataList.at(i);	
		if(propData)
			propData->DoUpdate();
	}			

	if(pEd)
	{
		// jesli spinowana wartosc dojdzie do min/max dla wszystkich wartosci to ustawiamy "editor" dla property bez mixu
		if(sameValue)
		{
			SetAttribute("sameValues", true);
		}
		else
			SetValue(0);
	}

	UpdateAfterOnPropertyChangeEvent();
}

void G3MultiIntProperty::SetMinRange(int min)
{
	SetAttribute(wxPG_ATTR_MIN, min);
}

void G3MultiIntProperty::SetMaxRange(int max)
{
	SetAttribute(wxPG_ATTR_MAX, max);
}

void G3MultiIntProperty::SetSpinnerStep(int step)
{
	SetAttribute(wxPG_ATTR_SPINCTRL_STEP, step);
}


//////////////////////////////////////////////////////////////////////////

// G3MultiFrameProperty ::G3MultiFrameProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name, int faiultFrame):
// wxIntProperty(label, name, defaultFrame),		
// 	G3PGProperty<int>(this)
// {
// 	SetAttribute("MotionSpin", true);
// }
// 
// G3MultiFrameProperty ::~G3MultiFrameProperty ()
// {
// }
// 
// void G3MultiFrameProperty::UpdateAfterOnPropertyChangeEvent()
// {
// 	for (int i=0;i<m_propertyValueList.size();i++)
// 	{
// 	}
// 
// 	// WAZNE, ZAKOMENTOWALEM 18-10-2013
// 	//frameGraphEditor->RebuildKeys();
// }
// 
// void G3MultiFrameProperty::OnPropertyChangedEvent()
// {
// 	// GetValue() returns wxVariant, but it is converted transparently to
// 	// wxAny
// 	wxVariant propValue = GetValue();
// 
// 	// Also, handle the case where property value is unspecified
// 	if ( propValue.IsNull() )
// 		return;
// 
// 	G3SpinMultiValPGEditor *pEd=(G3SpinMultiValPGEditor *) GetEditorClass();
// 
// 	for (int i=0;i<m_propertyValueList.size();i++)
// 	{
// 		if(pEd)
// 		{
// 			if(IsSameValues())
// 				*m_propertyValueList.at(i)=(float) propValue.GetLong()/30.0f;
// 			else
// 			{
// 				if(pEd->m_bEditedBySpinner)
// 					*m_propertyValueList.at(i)+=(float) propValue.GetLong()/30.0f;
// 				else
// 					*m_propertyValueList.at(i)=(float) propValue.GetLong()/30.0f;
// 			}
// 		}
// 		else
// 			*m_propertyValueList.at(i)=(int) propValue.GetLong()/30.0f;
// 	}
// 
// 	if(pEd)
// 	{
// 		if(!IsSameValues())
// 			SetValue(0);
// 	}
// 
// 	UpdateAfterOnPropertyChangeEvent();
// }

//////////////////////////////////////////////////////////////////////////

G3MultiEnumProperty ::G3MultiEnumProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name, wxPGChoices& choices, int value):
wxEnumProperty(label, name, choices, value),		
	G3PGProperty<int>(this, G3EPropertyVariableTypes::G3EPVT_ENUM)
{
	propGrid->SetPropertyEditor(this, new G3EnumMultiValPGEditor());	
}

G3MultiEnumProperty ::~G3MultiEnumProperty()
{
}


void G3MultiEnumProperty::OnPropertyChangedEvent()
{
	// GetValue() returns wxVariant, but it is converted transparently to
	// wxAny
	wxVariant propValue = GetValue();

	// Also, handle the case where property value is unspecified
	if ( propValue.IsNull() )
		return;

	for (int i=0;i<m_propertyValueList.size();i++)
	{
		*m_propertyValueList.at(i)=(int) propValue.GetLong();	

		CG3PropertyBaseData *propData=(CG3PropertyBaseData*)  m_propertyDataList.at(i);	
		if(propData)
			propData->DoUpdate();
	}

	SetAttribute("sameValues", true);

	UpdateAfterOnPropertyChangeEvent();
}

//////////////////////////////////////////////////////////////////////////
G3ContentDataProperty ::G3ContentDataProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name):
wxStringProperty(label, name),
	G3PGProperty<std::string>(this, G3EPropertyVariableTypes::G3EPVT_CONTENT)
{
	G3CustomMultiButtonPGEditor *pgEditor=new G3CustomMultiButtonPGEditor();

	propGrid->SetPropertyEditor(this, pgEditor);
}

G3ContentDataProperty ::~G3ContentDataProperty ()
{
}

void G3ContentDataProperty::OnPropertyChangedEvent()
{
	// GetValue() returns wxVariant, but it is converted transparently to
	// wxAny
	wxVariant propValue = GetValue();

	// Also, handle the case where property value is unspecified
	if ( propValue.IsNull() )
		return;

	// zbedne
	//G3StringMultiValPGEditor *pEd=(G3StringMultiValPGEditor *) GetEditorClass();
	for (int i=0;i<m_propertyValueList.size();i++)
	{
		*m_propertyValueList.at(i)=(std::string) propValue.GetString();	

		CG3PropertyBaseData *propData=(CG3PropertyBaseData*)  m_propertyDataList.at(i);	
		if(propData)
			propData->DoUpdate();
	}			

	SetAttribute("sameValues", true);

	UpdateAfterOnPropertyChangeEvent();
}

void G3ContentDataProperty::UpdateAfterOnPropertyChangeEvent()
{
}

//////////////////////////////////////////////////////////////////////////

G3MultiFrameProperty::G3MultiFrameProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name, int framePerSec):
wxIntProperty(label, name),
	G3PGProperty<float>(this, G3EPropertyVariableTypes::G3EPVT_FRAME),
	m_iFPS(framePerSec)
{	
	propGrid->SetPropertyEditor(this, new G3SpinMultiValPGEditor());

	SetAttribute("MotionSpin", true);
	//SetAttribute(wxPG_ATTR_SPINCTRL_STEP, spinnerStep);
}

G3MultiFrameProperty ::~G3MultiFrameProperty()
{
}

void G3MultiFrameProperty::OnPropertyChangedEvent()
{
	// GetValue() returns wxVariant, but it is converted transparently to
	// wxAny
	wxVariant propValue = GetValue();

	// Also, handle the case where property value is unspecified
	if ( propValue.IsNull() )
		return;

	G3SpinMultiValPGEditor *pEd=(G3SpinMultiValPGEditor *) GetEditorClass();

	bool sameValue=true;
	for (int i=0;i<m_propertyValueList.size();i++)
	{
		if(pEd)
		{
			if(GetAttribute("sameValues"))
				*m_propertyValueList.at(i)=(float) propValue.GetLong()/(float) m_iFPS;
			else
			{
				if(pEd->m_bEditedBySpinner)
				{
					*m_propertyValueList.at(i)+=(float) propValue.GetLong()/(float) m_iFPS;

					// 					wxVariant vmin=GetAttribute(wxPG_ATTR_MIN);
					// 
					// 					if(!vmin.IsNull())
					// 					{
					// 						if(*m_propertyValueList.at(i)<vmin.GetLong())
					// 							*m_propertyValueList.at(i)=vmin.GetLong();
					// 					}
					// 
					// 					wxVariant vmax=GetAttribute(wxPG_ATTR_MAX);
					// 
					// 					if(!vmax.IsNull())
					// 					{
					// 						if(*m_propertyValueList.at(i)>vmax.GetLong())
					// 							*m_propertyValueList.at(i)=vmax.GetLong();
					// 					}

					// sprawdzac jako int ?
					if(*m_propertyValueList[0]!=*m_propertyValueList.at(i))
						sameValue=false;
				}
				else
					*m_propertyValueList.at(i)=(float) propValue.GetLong()/(float) m_iFPS;				
			}
		}
		else
			*m_propertyValueList.at(i)=(float) propValue.GetLong();	

		CG3PropertyBaseData *propData=(CG3PropertyBaseData*)  m_propertyDataList.at(i);	
		if(propData)
			propData->DoUpdate();
	}			

	if(pEd)
	{
		// jesli spinowana wartosc dojdzie do min/max dla wszystkich wartosci to ustawiamy "editor" dla property bez mixu
		if(sameValue)
		{
			SetAttribute("sameValues", true);
		}
		else
			SetValue(0);
	}

	UpdateAfterOnPropertyChangeEvent();
}

void G3MultiFrameProperty::SetMinRange(int min)
{
	SetAttribute(wxPG_ATTR_MIN, min);
}

void G3MultiFrameProperty::SetMaxRange(int max)
{
	SetAttribute(wxPG_ATTR_MAX, max);
}

void G3MultiFrameProperty::SetSpinnerStep(int step)
{
	SetAttribute(wxPG_ATTR_SPINCTRL_STEP, step);
}

void G3MultiFrameProperty::EndAddValues()
{
	m_pProperty->SetAttribute("sameValues", true);

	for (int i=0;i<m_propertyValueList.size();i++)
	{
		int frame0=(*m_propertyValueList.at(0))*m_iFPS;
		int frameNext=(*m_propertyValueList.at(i))*m_iFPS;

		if(frame0!=frameNext)
		{
			m_pProperty->SetAttribute("sameValues", false);

			break;
		}		
	}

	if(m_propertyValueList.size()==1)
	{
		GetWxProperty()->Enable(true);		

		float tempFlt=(*m_propertyValueList.at(0))*30.0f;

		SetValue((int) tempFlt);
	}	
	else
	{
		if(m_propertyValueList.size()>1)
		{	
			GetWxProperty()->Enable(true);		

			if(m_pProperty->GetAttribute("sameValues"))
				SetValue(0);
		}
	}
}