#include "demo3.h"
#include <string>
#include <vector>
#include <sstream>

REGISTER_COMPONENT(demo3);

int anim4 = -1;
bool isReversed3 = false;
void trigger_enter3(BodyPtr body)
{
	isReversed3 = false;
	anim4 = 1;
}


void trigger_leave3(BodyPtr body)
{
	isReversed3 = true;
}

void demo3::AnimInitAW()
{

	const char* Walk = FileSystem::getGUID(WalkAnim.getRaw()).getFileSystemString();

	// Node Drobilka to ObjectMeshSkinned
	objModel = checked_ptr_cast<ObjectMeshSkinned>(node);

	anim4 = -1;
	speadAnim = 0.0f;
}

void demo3::Init() {
	pAnimPlayer = Game::getPlayer();
	AnimInitAW();

	Visualizer::setEnabled(true);
	bool t = Visualizer::isEnabled;
	Log::message(t ? "t1" : "t0");
	//WidgetWindowPtr window = WidgetWindow::create(ui);

	physical_trigger4 = PhysicalTrigger::create(Shape::SHAPE_BOX, Math::vec3(1.5f, 3.0f, 1.5f));
	physical_trigger4->setPosition(Math::Vec3(-0.39128f, -7.08943f, 1.63787f));
	physical_trigger4->addEnterCallback(MakeCallback(&trigger_enter3));
	physical_trigger4->addLeaveCallback(MakeCallback(&trigger_leave3));
}

void demo3::Animation()
{


	if (anim4 == 1 && objModel->getFrame(0) < 715) {
		if (speadAnim == 0.0f)	speadAnim += Game::getIFps() * 30.0f;

		if (!isReversed3)
			objModel->setFrame(0, objModel->getFrame(0) + speadAnim, 0, 715);
		else
			objModel->setFrame(0, objModel->getFrame(0) - speadAnim, 0, 715);

		
	}
	
	
}

void demo3::Update() {

	// key down Y

	physical_trigger4->renderVisualizer();
	Animation();
}