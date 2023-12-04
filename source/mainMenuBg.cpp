#include "mainMenuBg.h"
#include <string>
#include <vector>
#include <sstream>

REGISTER_COMPONENT(mainMenuBg);

bool aFlagMM = true;
void mainMenuBg::AnimInitAW()
{

	const char* Walk = FileSystem::getGUID(WalkAnim.getRaw()).getFileSystemString();

	// Node Drobilka to ObjectMeshSkinned
	objModel = checked_ptr_cast<ObjectMeshSkinned>(node);


	speadAnim = 0.0f;
}

void mainMenuBg::Init() {
	pAnimPlayer = Game::getPlayer();
	AnimInitAW();
	Console::setInt("render_dof", 1);
	Console::setInt("render_dof_quality", 1);
	Console::setInt("render_dof_bokeh_mode", 0); 
	
	Render::setDOFFocalDistance(1);
	Render::setDOFBlur(2);
	Render::setDOFChromaticAberration(1);
	//WidgetWindowPtr window = WidgetWindow::create(ui);
}

void mainMenuBg::Animation()
{
	if ( aFlagMM) {
		if (speadAnim < 0.3f)	speadAnim = 0.474f;

		objModel->setFrame(0, objModel->getFrame(0) + speadAnim, 0, 715);
		if (objModel->getFrame(0) >= 714) { 
			aFlagMM = false; 
		}
	}
	else if (!aFlagMM) {
		if (speadAnim == 0.0f)	speadAnim += Game::getIFps() * 30.0f;

		objModel->setFrame(0, objModel->getFrame(0) - speadAnim, 0, 715);
		if (objModel->getFrame(0) <= 2) {
			aFlagMM = true;
	}
	}

}

void mainMenuBg::Update() {
	pAnimPlayer->setTransform(objModel->getBoneWorldTransform(73));
	// key down Y
	/*if (Input::isKeyDown(Input::KEY_F)) {
		anim1 *= -1;
	}*/

	Animation();
}