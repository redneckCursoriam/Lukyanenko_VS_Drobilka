#include "aFV.h"
#include <sstream>

REGISTER_COMPONENT(aFV);

int anim1 = -1;
bool aFlag = true;

WidgetPtr pBody;

int frameUiSteps[4] = {100, 300, 400, 500};
int stepUiCounter = 0;

void OnButtonNextClicked()
{
	Console::message("click");
	anim1 = 1;
	pBody->setHidden(1);
	stepUiCounter++;
}

void aFV::JsonParser()
{
	const char* js = Json_file.get();

	json = Json::create();
	json->load(js);

	JsonPtr json_details = json->getChild("details");
	for (int i = 0; i < json_details->getNumChildren(); i++)
	{
		JsonPtr json_detail = json_details->getChild(i);
		string name = json_detail->read("name");
		string texture = json_detail->read("texture");
		string description = json_detail->read("description");
		details.push_back(Detail(name, texture, description));
	}
}

void aFV::AnimInitAW()
{
	
	const char* Walk = FileSystem::getGUID(WalkAnim.getRaw()).getFileSystemString();

	// Node Drobilka to ObjectMeshSkinned
	objModel = checked_ptr_cast<ObjectMeshSkinned>(node);

	anim1 = -1;
	speadAnim = 0.0f;

}

void aFV::GuiInitAW()
{
	winsize = WindowManager::getMainWindow()->getSize();
	width = winsize.x;
	height = winsize.y;

	ui = UserInterface::create(Gui::getCurrent(), UI_file);
	string nameUi = UI_file.get();

	pBody = ui->getWidget(ui->findWidget("museum"));
	pBody->arrange();
	Gui::getCurrent()->addChild(pBody, Gui::ALIGN_OVERLAP | Gui::ALIGN_RIGHT | Gui::ALIGN_TOP);

	pWLabelName = checked_ptr_cast<WidgetLabel>(ui->getWidget(ui->findWidget("name")));
	pWLabelDesc = checked_ptr_cast<WidgetLabel>(ui->getWidget(ui->findWidget("description")));

	pWWindow = checked_ptr_cast<WidgetWindow>(ui->getWidget(ui->findWidget("image_window")));
	pWWindow->setBorderColor(Math::vec4(255, 255, 255, 255));
	pWSprite = checked_ptr_cast<WidgetSprite>(ui->getWidget(ui->findWidget("detail_img")));
	int width = pWSprite->getWidth();
	int height = pWSprite->getHeight();
	pWButtonNext = checked_ptr_cast<WidgetSprite>(ui->getWidget(ui->findWidget("next")));
	pWButtonNext->addCallback(Gui::CLICKED, MakeCallback(OnButtonNextClicked));

	pBody->setHidden(1);
}

void aFV::Init() {
	pAnimPlayer = Game::getPlayer();
	AnimInitAW();

	Visualizer::setEnabled(true);
	bool t = Visualizer::isEnabled;
	Log::message(t ? "t1" : "t0");
	//WidgetWindowPtr window = WidgetWindow::create(ui);
	
	GuiInitAW();
	JsonParser();
}

void aFV::UI_Info()
{
	anim1 = -1;
	pBody->setHidden(0);
	pWLabelName->setText(details[stepUiCounter].name.c_str());
	pWLabelDesc->setText(details[stepUiCounter].description.c_str());
	pWSprite->setTexture(details[stepUiCounter].getSrcImg(details[stepUiCounter].texture).c_str());
}

void aFV::GuiAnim()
{
	int length = *(&frameUiSteps + 1) - frameUiSteps;
	if (stepUiCounter < length && objModel->getFrame(0) >= frameUiSteps[stepUiCounter])
	{
		UI_Info();
	}
}

void aFV::Animation()
{
	if (anim1 == 1 && aFlag) {
		if (speadAnim == 0.0f)	speadAnim = 0.115f;
		objModel->setFrame(0, objModel->getFrame(0) + speadAnim, 0, 715);
		if (objModel->getFrame(0) >= 714) aFlag = false;
	}
	else if (anim1 == 1 && !aFlag){
		if (speadAnim == 0.0f)	speadAnim = Game::getIFps() * 8.0f;
		objModel->setFrame(0, objModel->getFrame(0) - speadAnim, 0, 715);
	}
}

void aFV::Update() {
	pAnimPlayer->setTransform(objModel->getBoneWorldTransform(73));
	if (Input::isKeyDown(Input::KEY_F)) {
		anim1 *= -1;
	}
	GuiAnim();
	Animation();
}