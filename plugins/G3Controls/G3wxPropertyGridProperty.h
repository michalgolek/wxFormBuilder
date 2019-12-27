#pragma once

#include "G3wxPropertyGrid.h"

#include <wx\propgrid\advprops.h>


#include <wx/object.h> 

#include <vector>
#include <string>

class WXDLLIMPEXP_G3CONTROLS G3PropertyGrid;

enum G3EPropertyVariableTypes
{
	G3EPVT_STRING=0,
	G3EPVT_BOOL,
	G3EPVT_FLOAT,
	G3EPVT_NUMBER,	
	G3EPVT_ENUM,
	G3EPVT_CONTENT,
	G3EPVT_FRAME
};

//////////////////////////////////////////////////////////////////////////

// abstakcyjna klasa!
// tworzyc z niej nowe z roznymi konstruktorami i danymi dla roznych obiektow, np. dla wywolywania metody entity
// dla wywolywania skryptow lua
class WXDLLIMPEXP_G3CONTROLS CG3PropertyBaseData:public wxObject
{
public:
	CG3PropertyBaseData();
	virtual ~CG3PropertyBaseData();

	//	void *m_pUserData;

	virtual void DoUpdate()=0;
};


//////////////////////////////////////////////////////////////////////////
// kazdy nowy attrybut musi dziedziczyc z tej klasy

template<typename T>
class WXDLLIMPEXP_G3CONTROLS G3PGProperty
{
protected:
	std::vector<T *> m_propertyValueList;

	std::vector<CG3PropertyBaseData *> m_propertyDataList;

	wxPGProperty *m_pProperty;	

public:
	G3PGProperty(wxPGProperty *prop, int variableType);
	virtual ~G3PGProperty();

	void BeginAddValues();

	void AddValue(T *val, CG3PropertyBaseData *propData=NULL);

	virtual void EndAddValues();

	wxPGProperty *GetWxProperty() const;

	virtual void OnPropertyChangedEvent()=0;

	virtual void UpdateAfterOnPropertyChangeEvent(){};
};

//////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_G3CONTROLS G3MultiStringProperty:public wxStringProperty, public G3PGProperty<std::string>
{
	//DECLARE_DYNAMIC_CLASS(G3MultiStringProperty )
public:
	// Normal property constructor.
	G3MultiStringProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name=wxPG_LABEL);

	virtual ~G3MultiStringProperty();

	void OnPropertyChangedEvent();
};

//////////////////////////////////////////////////////////////////////////
class WXDLLIMPEXP_G3CONTROLS G3MultiBoolProperty:public wxBoolProperty, public G3PGProperty<bool>
{
	//DECLARE_DYNAMIC_CLASS(G3MultiBoolProperty )
public:
	// Normal property constructor.
	G3MultiBoolProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name=wxPG_LABEL);

	virtual ~G3MultiBoolProperty();

	void OnPropertyChangedEvent();
};

//////////////////////////////////////////////////////////////////////////
class WXDLLIMPEXP_G3CONTROLS G3MultiFloatProperty:public wxFloatProperty, public G3PGProperty<float>
{
	//DECLARE_DYNAMIC_CLASS(G3MultiFloatProperty )
public:
	// Normal property constructor.
	G3MultiFloatProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name=wxPG_LABEL, float stepValue=0.1f);

	virtual ~G3MultiFloatProperty();

	void OnPropertyChangedEvent();

	void SetMinRange(float min);
	void SetMaxRange(float max);
	void SetSpinnerStep(float step);
};

//////////////////////////////////////////////////////////////////////////
class WXDLLIMPEXP_G3CONTROLS G3MultiIntProperty:public wxIntProperty, public G3PGProperty<int>
{
	//DECLARE_DYNAMIC_CLASS(G3MultiIntProperty )
public:
	// Normal property constructor.
	G3MultiIntProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name=wxPG_LABEL, int spinnerStep=1);

	virtual ~G3MultiIntProperty();

	void OnPropertyChangedEvent();

	void SetMinRange(int min);
	void SetMaxRange(int max);
	void SetSpinnerStep(int step);
};

//////////////////////////////////////////////////////////////////////////
class WXDLLIMPEXP_G3CONTROLS G3MultiEnumProperty:public wxEnumProperty, public G3PGProperty<int>
{
	//DECLARE_DYNAMIC_CLASS(G3MultiFloatProperty )
public:	
	// Normal property constructor.
	G3MultiEnumProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name, wxPGChoices& choices, int value = 0);

	virtual ~G3MultiEnumProperty();

	void OnPropertyChangedEvent();


};

class WXDLLIMPEXP_G3CONTROLS G3ContentDataProperty:public wxStringProperty, public G3PGProperty<std::string>
{
	//DECLARE_DYNAMIC_CLASS(G3ContentDataProperty )
public:
	// Normal property constructor.
	G3ContentDataProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name=wxPG_LABEL);

	virtual ~G3ContentDataProperty();

	void OnPropertyChangedEvent();

	void UpdateAfterOnPropertyChangeEvent();
};

class WXDLLIMPEXP_G3CONTROLS G3MultiFrameProperty:public wxIntProperty, public G3PGProperty<float>
{
	//DECLARE_DYNAMIC_CLASS(G3MultiFrameProperty )
protected:
	int m_iFPS;

public:
	// Normal property constructor.
	G3MultiFrameProperty(G3PropertyGrid *propGrid, const wxString& label, const wxString& name=wxPG_LABEL, int framePerSec=30);

	virtual ~G3MultiFrameProperty();

	void OnPropertyChangedEvent();

	void SetMinRange(int min);
	void SetMaxRange(int max);
	void SetSpinnerStep(int step);

	void EndAddValues();
};