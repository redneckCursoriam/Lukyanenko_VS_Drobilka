#pragma once
#include "Unigine.h"
#include <UnigineGui.h>

using namespace Unigine;

class myTool : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(myTool, ComponentBase);

	PROP_PARAM(String, Type);
	PROP_PARAM(String, Name);
	PROP_PARAM(String, BackgroundColor, "#B4C3D4");
	PROP_PARAM(Int, integers);
	PROP_PARAM(String, ImgSrc1);
	PROP_PARAM(String, ImgSrc2);
	PROP_PARAM(String, ImgSrc3);
	PROP_PARAM(String, Description1);
	PROP_PARAM(String, Description2);
	PROP_PARAM(String, Description3);
	PROP_PARAM(String, ButtonText1);
	PROP_PARAM(String, ButtonText2);
	PROP_PARAM(String, ButtonText3);
	//PROP_PARAM(File, file, NULL);

};

