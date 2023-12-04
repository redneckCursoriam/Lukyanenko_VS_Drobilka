#pragma once
#include "Unigine.h"
#include <UnigineUserInterface.h>
#include <UnigineWidgets.h>
#include <UnigineGui.h>
#include <map>
#include <string>

using namespace Unigine;
using namespace std;

class GridGui : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(GridGui, ComponentBase);

	COMPONENT_INIT(Init);
	COMPONENT_UPDATE(Update);

	PROP_PARAM(File, UI_file);

	ObjectGuiPtr pObjGui;
	GuiPtr pGui;
	WidgetPtr pBody;
	UserInterfacePtr ui;

	WidgetGridBoxPtr pGridBox;
	WidgetDialogImagePtr pVSprite;
	//WidgetDialogImagePtr pVSprite;
	PlayerPtr pPlayer;

	WidgetButtonPtr pWButtonTest;

	WidgetButtonPtr pWButton1;
	WidgetButtonPtr pWButton2;
	WidgetButtonPtr pWButton3;

	WidgetLabelPtr pWLabel1;
	WidgetLabelPtr pWLabel2;
	WidgetLabelPtr pWLabel3;

	float PhWidth, PhHeight;
	map <string, XmlPtr> xmlMap;

	void my_xml_print(XmlPtr xml, int offset);

	//int OnButtonClicked();

	Unigine::PlayerPtr player;
	Unigine::ObjectPtr obj;

	std::string nameNode;

	bool grab = false;

	// informations data tol hui tip
	Unigine::Math::ivec2 winsize;
	int width;
	int height;
	float lastVector;
	Unigine::Math::vec3 deltaObject;

protected:
	void Init();
	void Update();
};

