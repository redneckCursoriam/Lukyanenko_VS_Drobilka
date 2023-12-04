#pragma once
#include "Unigine.h"
#include <UnigineUserInterface.h>
#include <UnigineWidgets.h>
#include <UnigineGui.h>

using namespace Unigine;
using namespace std;

class billboard : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(billboard, ComponentBase);

	COMPONENT_INIT(Init);
	COMPONENT_UPDATE(Update);
	PROP_PARAM(String , b_image);
	PROP_PARAM(File, UI_file);
	PROP_PARAM(Int, hidden);
	PlayerPtr pAnimPlayerM;
	ObjectGuiPtr pObjGui;
	GuiPtr pGui;
	WidgetPtr pBody;
	UserInterfacePtr ui;

	WidgetSpritePtr pWSprite;


protected:
	void Init();
	void Update();
};

