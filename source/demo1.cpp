#include "demo1.h"
#include <string>
#include <vector>
#include <sstream>

REGISTER_COMPONENT(demo1);

int anim2 = -1;
bool isReversed = false;
void trigger_enter(BodyPtr body)
{
	isReversed = false;
	anim2 = 1;
}

void trigger_leave(BodyPtr body)
{
	isReversed = true;
}

void demo1::AnimInitAW()
{

	const char* Walk = FileSystem::getGUID(WalkAnim.getRaw()).getFileSystemString();

	// Node Drobilka to ObjectMeshSkinned
	objModel = checked_ptr_cast<ObjectMeshSkinned>(node);

	anim2 = -1;
	speadAnim = 0.0f;
}

void demo1::Init() {
	pAnimPlayer = Game::getPlayer();
	AnimInitAW();

	Visualizer::setEnabled(true);
	bool t = Visualizer::isEnabled;
	Log::message(t ? "t1" : "t0");
	//WidgetWindowPtr window = WidgetWindow::create(ui);

	//—оздать зону
	physical_trigger = PhysicalTrigger::create(Shape::SHAPE_BOX, Math::vec3(1.5f, 3.0f, 1.5f));
	physical_trigger->setPosition(Math::Vec3(-0.39128f, -0.01932f, 1.63787f));
	physical_trigger->addEnterCallback(MakeCallback(&trigger_enter));
	physical_trigger->addLeaveCallback(MakeCallback(&trigger_leave));
}

void demo1::Animation()
{
	if (anim2 == 1 && objModel->getFrame(0) < 715) {
		if (speadAnim == 0.0f)	speadAnim += Game::getIFps() * 30.0f;

	if(!isReversed)
		objModel->setFrame(0, objModel->getFrame(0) + speadAnim, 0, 715);
	else
		objModel->setFrame(0, objModel->getFrame(0) - speadAnim, 0, 715);
	}
}

void demo1::Update() {
	
	// key down Y
	/*if (Input::isKeyDown(Input::KEY_U)) {
		anim2 *= -1;
	}*/

	//¬ход выход зона
	physical_trigger->renderVisualizer();
	Animation();
}