#pragma once
#include "Unigine.h"
#include <UnigineUserInterface.h>
#include <UnigineWidgets.h>
#include <UnigineGui.h>

using namespace Unigine;
using namespace std;

class mainMenuBg : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(mainMenuBg, ComponentBase);

	COMPONENT_INIT(Init);
	COMPONENT_UPDATE(Update);

	PROP_PARAM(File, WalkAnim);
	PROP_PARAM(Node, Drobilka);

	ObjectGuiPtr pObjGui;
	GuiPtr pGui;
	WidgetPtr pBody;
	UserInterfacePtr ui;

	WidgetLabelPtr pWLabelName, pWLabelAnsw;
	WidgetVBoxPtr pVBox;
	WidgetCheckBoxPtr pWCheckBox;
	WidgetButtonPtr pWButtonLeft, pWButtonRight;
	//WidgetDialogImagePtr pVSprite;
	PlayerPtr pAnimPlayer;

	ObjectMeshSkinnedPtr objModel;
	void AnimInitAW();
	void GuiInitAW();

	float speadAnim;

	void Animation();

	float PhWidth, PhHeight;

	//int anim;
	int controlABS;

	//int OnButtonClicked();

protected:
	void Init();
	void Update();
};