#pragma once
#include "Unigine.h"
#include <UnigineUserInterface.h>
#include <UnigineWidgets.h>
#include <UnigineGui.h>
#include <UnigineJson.h>
#include <map>
#include <fstream>
#include <string>
#include <vector>

using namespace Unigine;
using namespace std;

class aFV : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(aFV, ComponentBase);

	COMPONENT_INIT(Init);
	COMPONENT_UPDATE(Update);

	PROP_PARAM(File, WalkAnim);
	PROP_PARAM(Node, Drobilka);
	PROP_PARAM(File, Json_file);
	PROP_PARAM(File, UI_file);


	//WidgetDialogImagePtr pVSprite;
	PlayerPtr pAnimPlayer;

	ObjectMeshSkinnedPtr objModel;
	void AnimInitAW();
	void GuiInitAW();
	void JsonParser();

	JsonPtr json;

	class Detail
	{
	public:
		Detail() {}
		Detail(string name, string texture, string description)
		{
			this->name = name;
			this->texture = texture;
			this->description = description;
		}
		string name;
		string texture;
		string description;
		string getSrcImg(string name)
		{
			return "png/animFrame/" + name;
		}
	};

	vector<Detail> details;

	float speadAnim;

	void Animation();

	void GuiAnim();
	void UI_Info();

	float PhWidth, PhHeight;
	
	//PlayerPtr player;
	
	// UI
	Math::ivec2 winsize;
	int width;
	int height;

	UserInterfacePtr ui;
	WidgetWindowPtr pWWindow;
	WidgetSpritePtr pWSprite;
	WidgetLabelPtr pWLabelName;
	WidgetLabelPtr pWLabelDesc;
	WidgetSpritePtr pWButtonNext;

	
	//int anim;
	int controlABS;

	//int OnButtonClicked();


protected:
	void Init();
	void Update();
};