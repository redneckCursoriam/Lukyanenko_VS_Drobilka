#pragma once
#include "Unigine.h"
#include <UnigineUserInterface.h>
#include <UnigineWidgets.h>
#include <UnigineGui.h>
#include <vector>

using namespace Unigine;
using namespace std;

class WorldLoaderMenu : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(WorldLoaderMenu, ComponentBase);
	COMPONENT_INIT(Init);
	COMPONENT_UPDATE(Update);
	PROP_PARAM(File, UI_file);
	PROP_PARAM(File, UI_file2);
	PROP_PARAM(File, UI_file3);
	PROP_PARAM(File, Json_file);
	PROP_PARAM(Int, hidden);
	PROP_PARAM(File, UI_aim);

	UserInterfacePtr uiAim;
	ObjectGuiPtr pObjGui;
	GuiPtr pGui;
	UserInterfacePtr ui;
	WidgetLabelPtr pWLabelName, pWLabelAnsw;
	WidgetVBoxPtr pVBox;
	WidgetCheckBoxPtr pWCheckBox;
	WidgetSpritePtr pWButtonMuseumWorld, pWButtonTestWorld, pWButtonMainWorld, pWButtonTest, pWButtonStepAnim, pWExit, pWDocs;
	PlayerPtr pPlayer;
	ObjectMeshSkinnedPtr objModel;

	JsonPtr json;
	
	void JsonTest();
	void GuiInit();
	void AimInit();
	
	float speadAnim;
	float PhWidth, PhHeight;

	int controlWLM;

protected:
	void Init();
	void Update();
};

