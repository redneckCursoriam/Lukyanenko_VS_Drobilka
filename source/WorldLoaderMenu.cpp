
#include <string>
#include "WorldLoaderMenu.h"

REGISTER_COMPONENT(WorldLoaderMenu);

bool isWindowDraged = false;
WidgetSpritePtr pwbSv;
int isSvernut = 1;
WidgetPtr pWorldLoaderMenu, pDocs, pTest;
UserInterfacePtr ui2, ui3;
String nameUI2;
WidgetSpritePtr pWNext, pWImg, pWExitDocs;
WidgetSpritePtr pWNextTest, pWBackTest, pWImgTest, pWExitTest;
WidgetPtr pAim;

WidgetLabelPtr lNumberQuestion, lQuestion;
WidgetCheckBoxPtr Rb1, Rb2, Rb3, Rb4;

vector<int> answTest;
vector<int> opTest;
int numTest = 0;

class Question {
public:
	Question() {}
	Question(String question, vector<String> answer, String type, int rightAnswer) {
		this->question = question;
		this->answer = answer;
		this->rightAnswer = rightAnswer;
		this->type = type;
	}
	String question;
	String type;
	vector<String> answer;
	int rightAnswer; // Если захочешь сделать checkbox, то сделай в виде массива, а в функции сравнения, проверяй все значения
};

vector<Question> questions;

int exitApp() {
	exit(0);
}

void WorldLoaderMenu::JsonTest()
{
	const char* js = Json_file.get();

	json = Json::create();
	json->load(js);

	JsonPtr json_questions = json->getChild("questions");

	int count = json_questions->getNumChildren();

	for (int i = 0; i < json_questions->getNumChildren(); i++)
	{
		JsonPtr json_question = json_questions->getChild(i);
		String question = json_question->read("question");
		String type = json_question->read("type");
		int rightAnswer;
		json_question->read("correct", rightAnswer);

		JsonPtr json_answer = json_question->getChild("answers");
		vector<String> answer;

		String answerStr = json_answer->read("1");
		answer.push_back(answerStr);
		answerStr = json_answer->read("2");
		answer.push_back(answerStr);
		answerStr = json_answer->read("3");
		answer.push_back(answerStr);
		answerStr = json_answer->read("4");
		answer.push_back(answerStr);

		questions.push_back(Question(question, answer, type, rightAnswer));
	}
}

int OnButtonHideShowWML()
{
	Unigine::Math::ivec2 main_window = Unigine::WindowManager::getMainWindow()->getSize();
	int px = pWorldLoaderMenu->getWidth();
	int py = pWorldLoaderMenu->getHeight();
	isSvernut = isSvernut * -1;
	if (isSvernut == -1) {
		pwbSv->setTexture("./data/sourceUI/right.png");
		pWorldLoaderMenu->setPosition(-310, main_window.y / 2 - py / 2);
	}
	else {
		pWorldLoaderMenu->setPosition(main_window.x / 2 - px / 2, main_window.y / 2 - py / 2);
		pwbSv->setTexture("./data/sourceUI/left.png");
	}
	return 1;
}

int OnButtonMainWorldClicked()
{
	Console::run("world_load Lukyanenko_VS_Drobilka");
		OnButtonHideShowWML();
		pAim->setHidden(1);
	return 1;
}
int OnButtonStepAnimWorldClicked()
{
	Console::run("world_load StepAnim");
	OnButtonHideShowWML();
	pAim->setHidden(0);
	return 1;
}

int OnButtonMuseumWorldPressed()
{
	Console::run("world_load museumWorld2");
	OnButtonHideShowWML();
	pAim->setHidden(1);
	return 1;
}

int OnButtonTestWorldPressed()
{
	Console::run("world_load razborkasborka");
	OnButtonHideShowWML();
	pAim->setHidden(1);
	return 1;
}

void WorldLoaderMenu::AimInit()
{
	uiAim = UserInterface::create(Gui::getCurrent(), UI_aim);
	string nameUiAim = UI_aim.get();

	pAim = uiAim->getWidget(uiAim->findWidget("vbox2"));
	pAim->arrange();

	Unigine::Math::ivec2 main_window = Unigine::WindowManager::getMainWindow()->getSize();
	int px = pAim->getWidth();
	int py = pAim->getHeight();
	pAim->setPosition(main_window.x / 2 - px / 2, main_window.y / 2 - py / 2);

	Gui::getCurrent()->addChild(pAim, Gui::ALIGN_OVERLAP);

	pAim->setHidden(1);
}

void changeImg() {
	pWImg = checked_ptr_cast<WidgetSprite>(ui2->getWidget(ui2->findWidget("img")));
	// if (pWNext->getTexture())
	String a = pWNext->getTexture();
	if (a == "sourceUI/btn_next.png" || a == "./data/sourceUI/btn_next.png") {
		pWImg->setTexture("./data/sourceUI/doc2.png");
		pWNext->setTexture("./data/sourceUI/back.png");
	} else {
		pWImg->setTexture("./data/sourceUI/doc1.png");
		pWNext->setTexture("./data/sourceUI/btn_next.png");
	}
}

void RefreshTest()
{
	String indexTest = u8"Вопрос: ";
	indexTest += String::itoa(numTest + 1) + u8" / " + String::itoa(questions.size());

	lNumberQuestion->setText(indexTest);
	lQuestion->setText(questions[numTest].question);
	Rb1->setText(questions[numTest].answer[0]);
	Rb2->setText(questions[numTest].answer[1]);
	Rb3->setText(questions[numTest].answer[2]);
	Rb4->setText(questions[numTest].answer[3]);

	if (numTest == 0)
	{
		pWBackTest->setEnabled(0);
		pWNextTest->setTexture("./data/sourceUI/btn_next.png");
	}
	else if (numTest == questions.size() - 1)
	{
		// pWNextTest->setEnabled(0); // Потом здесь будет смена кнопки
		pWNextTest->setTexture("./data/sourceUI/btn_send_170.png");
	}
	else
	{
		String x = pWNextTest->getTexture();
		if (x != "./data/sourceUI/btn_next.png")
			pWNextTest->setTexture("./data/sourceUI/btn_next.png");
		pWBackTest->setEnabled(1);
		pWNextTest->setEnabled(1);
	}

	// Правильно отображение
	if (opTest[numTest] == 0)
		Rb1->setChecked(1);
	if (opTest[numTest] == 1)
		Rb2->setChecked(1);
	if (opTest[numTest] == 2)
		Rb3->setChecked(1);
	if (opTest[numTest] == 3)
		Rb4->setChecked(1);
}

void CheckTest()
{
	bool x[4] = { Rb1->isChecked(), Rb2->isChecked(), Rb3->isChecked(), Rb4->isChecked() };

	// index of answer in bool x[4]
	int index = -1;
	for (int i = 0; i < 4; i++)
	{
		if (x[i])
		{
			index = i;
			break;
		}
	}
	
	opTest[numTest] = index;
	
	if (x[questions[numTest].rightAnswer - 1])
	{
		answTest[numTest] = 1;
	}
	else
	{
		answTest[numTest] = 0;
	}	
}

void nextTests() {
	CheckTest();

	if (numTest == questions.size() - 1)
	{
		int countOfRightAnsw = 0;

		for (int i = 0; i < answTest.size(); i++)
		{
			if (answTest[i] == 1)
				countOfRightAnsw++;
		}

		String rightAnswers = u8"Правильных ответов: ";
		rightAnswers += String::itoa(countOfRightAnsw) + u8" из " + String::itoa(answTest.size());

		lNumberQuestion->setText(rightAnswers);

		Console::message(String::itoa(countOfRightAnsw));
	}
	else
	{
		Console::message("nextTests");
		numTest++;

		RefreshTest();
	}
}

void backTests() {
	Console::message("backTests");
	CheckTest();
	numTest--;
	
	RefreshTest();
}

void hideDocs() {
	ControlsApp::setMouseHandle(Input::MOUSE_HANDLE_GRAB);
	pDocs->setHidden(1);
	OnButtonHideShowWML();
}

void hideTest() {
	ControlsApp::setMouseHandle(Input::MOUSE_HANDLE_GRAB);
	pTest->setHidden(1);
	OnButtonHideShowWML();
}

int OnButtonTestClicked()
{
	if (!pTest) {
		pTest = ui3->getWidget(ui3->findWidget("doc"));
		pTest->arrange();

		Unigine::Math::ivec2 main_window = Unigine::WindowManager::getMainWindow()->getSize();
		int px = pTest->getWidth();
		int py = pTest->getHeight();
		pTest->setPosition(main_window.x / 2 - px / 2, main_window.y / 2 - py / 2);

		Gui::getCurrent()->addChild(pTest, Gui::ALIGN_OVERLAP);
		
		pWBackTest = checked_ptr_cast<WidgetSprite>(ui3->getWidget(ui3->findWidget("back")));
		pWBackTest->addCallback(Gui::CLICKED, MakeCallback(backTests));

		pWNextTest = checked_ptr_cast<WidgetSprite>(ui3->getWidget(ui3->findWidget("next")));
		pWNextTest->addCallback(Gui::CLICKED, MakeCallback(nextTests));

		pWExitTest = checked_ptr_cast<WidgetSprite>(ui3->getWidget(ui3->findWidget("exit")));
		pWExitTest->addCallback(Gui::CLICKED, MakeCallback(hideTest));

		ControlsApp::setMouseHandle(Input::MOUSE_HANDLE_USER);
		OnButtonHideShowWML();

		lNumberQuestion = checked_ptr_cast<WidgetLabel>(ui3->getWidget(ui3->findWidget("numberQuestion")));
		lQuestion = checked_ptr_cast<WidgetLabel>(ui3->getWidget(ui3->findWidget("question")));
		Rb1 = checked_ptr_cast<WidgetCheckBox>(ui3->getWidget(ui3->findWidget("radiobutton")));
		Rb2 = checked_ptr_cast<WidgetCheckBox>(ui3->getWidget(ui3->findWidget("radiobutton2")));
		Rb3 = checked_ptr_cast<WidgetCheckBox>(ui3->getWidget(ui3->findWidget("radiobutton3")));
		Rb4 = checked_ptr_cast<WidgetCheckBox>(ui3->getWidget(ui3->findWidget("radiobutton4")));

		RefreshTest();
	}
	else {
		pTest->setHidden(0);
		OnButtonHideShowWML();
	}

	return 1;
}

void showDocs() {
	if (!pDocs) {
		pDocs = ui2->getWidget(ui2->findWidget("doc"));
		pDocs->arrange();

		Unigine::Math::ivec2 main_window = Unigine::WindowManager::getMainWindow()->getSize();
		int px = pDocs->getWidth();
		int py = pDocs->getHeight();
		pDocs->setPosition(main_window.x/2-px/2,main_window.y/2-py/2);
		
		Gui::getCurrent()->addChild(pDocs, Gui::ALIGN_OVERLAP);

		pWNext = checked_ptr_cast<WidgetSprite>(ui2->getWidget(ui2->findWidget("next")));
		pWNext->addCallback(Gui::CLICKED, MakeCallback(changeImg));

		pWExitDocs = checked_ptr_cast<WidgetSprite>(ui2->getWidget(ui2->findWidget("exit")));
		pWExitDocs->addCallback(Gui::CLICKED, MakeCallback(hideDocs));

		ControlsApp::setMouseHandle(Input::MOUSE_HANDLE_USER);
		OnButtonHideShowWML();
	}
	else {
		pDocs->setHidden(0);
		OnButtonHideShowWML();
	}
}

void WorldLoaderMenu::GuiInit()
{
	ui = UserInterface::create(Gui::getCurrent(), UI_file);
	ui2 = UserInterface::create(Gui::getCurrent(), UI_file2);
	ui3 = UserInterface::create(Gui::getCurrent(), UI_file3);
	string nameUI2 = UI_file2.get();
	string nameUi = UI_file.get();

	pWorldLoaderMenu = ui->getWidget(ui->findWidget("vbox2"));
	pWorldLoaderMenu->arrange();

	Unigine::Math::ivec2 main_window = Unigine::WindowManager::getMainWindow()->getSize();
	int px = pWorldLoaderMenu->getWidth();
	int py = pWorldLoaderMenu->getHeight();
	pWorldLoaderMenu->setPosition(main_window.x/2-px/2,main_window.y/2-py/2);
	Gui::getCurrent()->addChild(pWorldLoaderMenu, Gui::ALIGN_OVERLAP);
	
	pWButtonMainWorld = checked_ptr_cast<WidgetSprite>(ui->getWidget(ui->findWidget("mainWorld")));
	pWButtonMainWorld->addCallback(Gui::CLICKED, MakeCallback(OnButtonMainWorldClicked));

	pWButtonMuseumWorld = checked_ptr_cast<WidgetSprite>(ui->getWidget(ui->findWidget("museumWorld")));
	pWButtonMuseumWorld->addCallback(Gui::CLICKED, MakeCallback(OnButtonMuseumWorldPressed));

	pWButtonTestWorld = checked_ptr_cast<WidgetSprite>(ui->getWidget(ui->findWidget("testWorld")));
	pWButtonTestWorld->addCallback(Gui::CLICKED, MakeCallback(OnButtonTestWorldPressed));

	pWButtonStepAnim = checked_ptr_cast<WidgetSprite>(ui->getWidget(ui->findWidget("stepAnimWorld")));
	pWButtonStepAnim->addCallback(Gui::CLICKED, MakeCallback(OnButtonStepAnimWorldClicked));

	pWButtonTest = checked_ptr_cast<WidgetSprite>(ui->getWidget(ui->findWidget("test")));
	pWButtonTest->addCallback(Gui::CLICKED, MakeCallback(OnButtonTestClicked));
	
	pwbSv = checked_ptr_cast<WidgetSprite>(ui->getWidget(ui->findWidget("svernut")));
	pwbSv->addCallback(Gui::CLICKED, MakeCallback(OnButtonHideShowWML));

	pWExit = checked_ptr_cast<WidgetSprite>(ui->getWidget(ui->findWidget("exit")));
	pWExit->addCallback(Gui::CLICKED, MakeCallback(exitApp));

	pWDocs = checked_ptr_cast<WidgetSprite>(ui->getWidget(ui->findWidget("docs")));
	pWDocs->addCallback(Gui::CLICKED, MakeCallback(showDocs));

	controlWLM = hidden;
	if (controlWLM == 1)
		OnButtonHideShowWML();
}


void WorldLoaderMenu::Init() {
	if (!pWorldLoaderMenu)GuiInit();
	if (!pAim)AimInit();
	JsonTest();
	if (answTest.size() == 0) {
		for (int i = 0; i < questions.size(); i++) {
			answTest.push_back(0);
			opTest.push_back(0);
		}
	}
}


void WorldLoaderMenu::Update() {
	if (Input::isKeyDown(Input::KEY_Z))
	{
		if (controlWLM == 1)controlWLM = 0;
		else controlWLM = 1;
		pWorldLoaderMenu->setHidden(controlWLM);
	}
	
	if (Input::isKeyDown(Input::KEY_ESC))
		OnButtonHideShowWML();
}