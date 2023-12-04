#include "demo2.h"
#include <string>
#include <vector>
#include <sstream>

REGISTER_COMPONENT(demo2);

int anim3 = -1;
bool isReversed2 = false;
void trigger_enter2(BodyPtr body)
{
	isReversed2 = false;
	anim3 = 1;
}


void trigger_leave2(BodyPtr body)
{
	isReversed2 = true;
}

void demo2::AnimInitAW()
{

	const char* Walk = FileSystem::getGUID(WalkAnim.getRaw()).getFileSystemString();

	// Node Drobilka to ObjectMeshSkinned
	objModel = checked_ptr_cast<ObjectMeshSkinned>(node);

	anim3 = -1;
	speadAnim = 0.0f;
}

void demo2::Init() {
	pAnimPlayer = Game::getPlayer();
	AnimInitAW();

	Visualizer::setEnabled(true);
	bool t = Visualizer::isEnabled;
	Log::message(t ? "t1" : "t0");
	//WidgetWindowPtr window = WidgetWindow::create(ui);

	physical_trigger3 = PhysicalTrigger::create(Shape::SHAPE_BOX, Math::vec3(1.5f, 3.0f, 1.5f));
	physical_trigger3->setPosition(Math::Vec3(-0.39128f, -3.46355f, 1.63787f));
	physical_trigger3->addEnterCallback(MakeCallback(&trigger_enter2));
	physical_trigger3->addLeaveCallback(MakeCallback(&trigger_leave2));
}

void demo2::Animation()
{


	if (anim3 == 1 && objModel->getFrame(0) < 715) {
		if (speadAnim == 0.0f)	speadAnim += Game::getIFps() * 30.0f;

		if (!isReversed2)
			objModel->setFrame(0, objModel->getFrame(0) + speadAnim, 0, 715);
		else
			objModel->setFrame(0, objModel->getFrame(0) - speadAnim, 0, 715);

		
	}
}
	


void demo2::Update() {

	// key down Y
	/*if (Input::isKeyDown(Input::KEY_G)) {
		anim3 *= -1;
	}*/

	physical_trigger3->renderVisualizer();
	Animation();
}