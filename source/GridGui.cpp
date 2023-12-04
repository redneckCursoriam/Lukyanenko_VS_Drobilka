#include "GridGui.h"
#include <string>
#include <UnigineStreams.h>
#include <iostream>
#include <fstream>
#include <format>

REGISTER_COMPONENT(GridGui);

void GridGui::my_xml_print(XmlPtr xml, int offset = 0)
{
	// creating indents
	for (int i = 0; i < offset; i++)
		Log::message(" ");

	//printing xml info
	Log::message("%s: ", xml->getName());

	for (int i = 0; i < xml->getNumArgs(); i++)
	{
		Log::message("%s=%s ", xml->getArgName(i), xml->getArgValue(i));
		string s = xml->getArgName(i);
		if (s == "name")
			xmlMap.insert(make_pair(xml->getArgValue(i), xml));
	}

	Log::message(": %s\n", xml->getData());

	for (int i = 0; i < xml->getNumChildren(); i++)
		my_xml_print(XmlPtr(xml->getChild(i)), offset + 1);
}

void GridGui::Init() {
	Log::message("grid gui init");
	player = Game::getPlayer();

	winsize = WindowManager::getMainWindow()->getSize();
	width = winsize.x;
	height = winsize.y;

	pObjGui = checked_ptr_cast<ObjectGui>(node);
	pGui = pObjGui->getGui();

	PhHeight = pObjGui->getPhysicalHeight();
	PhWidth = pObjGui->getPhysicalWidth();

	//auto pGui = Gui::getCurrent();
	ui = UserInterface::create(pGui, UI_file);
	string nameUi = UI_file.get();

	string xmlFile;

	XmlPtr xml_dialog = Xml::create();
	bool a = xml_dialog->load(("..\\data\\" + nameUi).c_str());
	xmlFile = xml_dialog->getFormattedSubTree();

	my_xml_print(xml_dialog);


	pBody = ui->getWidget(ui->findWidget("vbox2"));
	pBody->arrange();

	pGui->addChild(pBody, Gui::ALIGN_OVERLAP | Gui::ALIGN_CENTER);

}

void GridGui::Update() {
	WorldIntersectionPtr intersection = WorldIntersection::create();

	Math::Vec3 p0, p1;

	int mouse_x = width / 2;
	int mouse_y = height / 2;

	player->getDirectionFromScreen(p0, p1, mouse_x, mouse_y, 0, 0, width, height);

	WorldIntersectionNormalPtr wi = WorldIntersectionNormal::create();

	obj = World::getIntersection(p0, p1, 1, wi);
	if (obj && obj->getNumProperties() > 0) {

		if (String(obj->getPropertyName()) == "myTool") {

			if (Math::distance((Math::vec3)node->getWorldPosition(), (Math::vec3)obj->getWorldPosition()) > 
				obj->getWorldBoundBox().getSize().z * 0.75f + pBody->getHeight() / 2.3 * 0.00264583333f) {
				node->setWorldPosition(obj->getWorldBoundSphere().center);
			}
			pObjGui->setPhysicalSize(
				Math::lerp(pObjGui->getPhysicalWidth(), PhWidth * 5, 5.0f * Game::getIFps()),
				Math::lerp(pObjGui->getPhysicalHeight(), PhHeight * 3.6f, 5.0f * Game::getIFps())
			);
			//pObjGui->setPhysicalSize(3.0f,3.0f);

			node->setWorldPosition(
				Math::lerp(node->getWorldPosition(),
					obj->getWorldBoundBox().getCenter() + (Math::Vec3)Math::vec3(0.0f, 0.0f, obj->getWorldBoundBox().getSize().z * 0.75f + pBody->getHeight() / 2.3 * 0.00264583333f),
					5.0f * Game::getIFps())+0.8f);
		}

	}
	else {
		pObjGui->setPhysicalSize(
			Math::lerpZero(pObjGui->getPhysicalWidth(), 5.0f * Game::getIFps()),
			Math::lerpZero(pObjGui->getPhysicalHeight(), 5.0f * Game::getIFps())
		);
	}
}