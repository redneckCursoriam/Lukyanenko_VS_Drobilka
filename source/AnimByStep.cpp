#include "AnimByStep.h"
#include <string>
#include <vector>
#include <sstream>
REGISTER_COMPONENT(AnimByStep);

const char* answ = "";
int stepFrame = -1;
bool leftAnim = false;
bool rightAnim = false;
int stepNum = 0;
WidgetButtonPtr pWButton;
//int frameSteps[20] = {45, 75, 140,165,225,255,305,335,395,455,515,545,590,695,785,815, 845,875,905,965};//620 670 680
int frameSteps[20] = {90, 140, 155,175,195,220,270,295,320,395,405,420,485,515,545,575, 620,640};//620 670 680
int anim = -1;
string currSurfNamesurfaceArray[20];
int stepCounter=0;
int currStepLastFrame = -1;
vector<string> expectedSurfaceNames;
ObjectPtr  obj;
bool helper = true;

int OnButtonClicked()
{
	Log::message("Button clicked\n");

	
	anim = anim * -1;
	if (anim == -1)
		pWButton->setTexture("./data/png/resume.png");
	else
		pWButton->setTexture("./data/png/pause.png");

	return 1;
}

int OnButtonLeftPressed()
{
	leftAnim = true;
	rightAnim = false;

	return 1;
}

int OnButtonLeftReleased()
{
	leftAnim = false;
	return 1;
}

int OnButtonRightPressed()
{
	rightAnim = true;
	leftAnim = false;

	return 1;
}

int OnButtonRightReleased()
{
	rightAnim = false;
	return 1;
}
vector<string> split(const string& s, char delim) {
	stringstream ss(s);
	string item;
	vector<string> elems;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}
void AnimByStep::AnimInitAW()
{
	const char* Walk = FileSystem::getGUID(WalkAnim.getRaw()).getFileSystemString();

	// Node Drobilka to ObjectMeshSkinned
	objModel = checked_ptr_cast<ObjectMeshSkinned>(node);

	anim = -1;
	speadAnim = 0.0f;

	/*objModel->setNumLayers(2);

	int WalkNum = objModel->addAnimation(Walk);

	objModel->setAnimation(0, WalkNum);

	objModel->setLayer(0, true, 1);*/
}

void AnimByStep::GuiInitAW()
{
	ui = UserInterface::create(Gui::getCurrent(), UI_file);
	string nameUi = UI_file.get();

	pBody = ui->getWidget(ui->findWidget("mainFrame"));
	pBody->arrange();
	Gui::getCurrent()->addChild(pBody, Gui::ALIGN_OVERLAP | Gui::ALIGN_RIGHT | Gui::ALIGN_TOP);

	pWButton = checked_ptr_cast<WidgetButton>(ui->getWidget(ui->findWidget("resume")));
	pWButton->addCallback(Gui::CLICKED, MakeCallback(OnButtonClicked));


	pWButtonLeft = checked_ptr_cast<WidgetButton>(ui->getWidget(ui->findWidget("doubleLeft")));
	pWButtonLeft->addCallback(Gui::PRESSED, MakeCallback(OnButtonLeftPressed));
	pWButtonLeft->addCallback(Gui::RELEASED, MakeCallback(OnButtonLeftReleased));


	pWButtonRight = checked_ptr_cast<WidgetButton>(ui->getWidget(ui->findWidget("doubleRight")));
	pWButtonRight->addCallback(Gui::PRESSED, MakeCallback(OnButtonRightPressed));
	pWButtonRight->addCallback(Gui::RELEASED, MakeCallback(OnButtonRightReleased));



	controlABS = 1;
}

void SurfaceInit() {
	currSurfNamesurfaceArray[0] = "Material.003 Material.001";
	currSurfNamesurfaceArray[1] = "64,64,64 190,188,186";
	currSurfNamesurfaceArray[2] = "Material.004_0 Material.004_1 Material.004_2 Material.004_3 Material.006";
	currSurfNamesurfaceArray[3] = "Material.014 Material.015";
	currSurfNamesurfaceArray[4] = "Material.016";
	currSurfNamesurfaceArray[5] = "Material.017 Material.018";
	currSurfNamesurfaceArray[6] = "190,188,186.001 Material.019 Material.018 189,189,189";
	currSurfNamesurfaceArray[7] = "Material.006";
	currSurfNamesurfaceArray[8] = "Material.028 Material.026 Material.027";
	currSurfNamesurfaceArray[9] = "Material.029";
	currSurfNamesurfaceArray[10] = "Material.042 Material.041";
	currSurfNamesurfaceArray[11] = "189,189,189";
	currSurfNamesurfaceArray[12] = "Material.043_0 Material.043_1 Material.043_2 Material.044_0 Material.044_1 Material.044_2";
	currSurfNamesurfaceArray[13] = "Material.043_0 Material.043_1 Material.043_2 Material.044_0 Material.044_1 Material.044_2";
	currSurfNamesurfaceArray[14] = "Material.043_0 Material.043_1 Material.043_2 Material.044_0 Material.044_1 Material.044_2";
	currSurfNamesurfaceArray[15] = "Material.043_0 Material.043_1 Material.043_2 Material.044_0 Material.044_1 Material.044_2";
	currSurfNamesurfaceArray[16] = "Material.043_0 Material.043_1 Material.043_2 Material.044_0 Material.044_1 Material.044_2";
	currSurfNamesurfaceArray[17] = "189,189,189";
	currSurfNamesurfaceArray[18] = "Material.008";

}
void AnimByStep::Init() {
	pAnimPlayer = Game::getPlayer();
	NodePtr nObj = World::getNodeByID(1899105725);
	if (nObj->isObject()) {
		obj = static_ptr_cast<Object>(node);
	}

	SurfaceInit();
	//GuiInitAW();
	AnimInitAW();
	expectedSurfaceNames = split(currSurfNamesurfaceArray[stepNum], ' ');

	//WidgetWindowPtr window = WidgetWindow::create(ui);
}

void AnimByStep::Animation()
{
	if (objModel->getFrame(0) > currStepLastFrame) anim = -1;
	
	if (anim == 1 && objModel->getFrame(0) < 964){
		//if (speadAnim == 0.0f)	speadAnim += Game::getIFps() * 30.0f;
		if (speadAnim == 0.0f)	speadAnim = 0.47f;
		
		objModel->setFrame(0, objModel->getFrame(0) + speadAnim, 0, 965);
	}
	
}

void AnimByStep::Update() {
	// key down Y

	if (Input::isKeyDown(Input::KEY_Y))
	{
		if (controlABS == 1)
			controlABS = 0;
		else
			controlABS = 1;
		pBody->setHidden(controlABS);
	}
	if(helper)
	for each (string var in expectedSurfaceNames)
	{
		int sNum = obj->findSurface(var.c_str());
		//Console::message("%vec4", Game::getRandomColor());
		//Visualizer::renderObjectSurfaceBoundSphere(obj, sNum, Math::vec4_blue , 1, false);
		//Visualizer::renderSolidObjectSurface(obj, sNum, Math::vec4_green , 0.1f);
		Visualizer::renderObjectSurface(obj, sNum, Math::vec4_green , 0.1f);
	}
	
	

	if (Input::isMouseButtonDown(Input::MOUSE_BUTTON_LEFT)) {

		WorldIntersectionPtr intersection = WorldIntersection::create();
		World::getIntersection(
			pAnimPlayer->getPosition(),
			pAnimPlayer->getPosition() + 
			(Math::Vec3)pAnimPlayer->getDirection() * 10,
			1,
			intersection);
		
		
		int currSurface = intersection->getSurface();
		string s = to_string(currSurface);



		if (currSurface == -1) {
			Log::message("currSurfName =-1");
		}
		else {
			
			
			if (helper)
			Visualizer::renderSolidObjectSurface(obj, currSurface, Math::vec4_red, 1);
	
	
			const char* currSurfName = obj->getSurfaceName(currSurface);
			
			
			if (find(expectedSurfaceNames.begin(), expectedSurfaceNames.end(), (string)currSurfName)
				!= expectedSurfaceNames.end())
			{
				anim = anim * -1;
				
				currStepLastFrame = frameSteps[stepNum]-1;
				if (stepNum<19)	stepNum++;

				expectedSurfaceNames.clear();
				expectedSurfaceNames = split(currSurfNamesurfaceArray[stepNum], ' ');
				
			}
			
		}
			
			
		
	}
	if (Input::isKeyDown(Input::KEY_H)) {
		helper = !helper;
	}

	Animation();
}



