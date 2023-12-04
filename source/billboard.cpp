
#include <string>
#include "billboard.h"

REGISTER_COMPONENT(billboard);

WidgetPtr pBillboard;


void billboard::Init() {
    pAnimPlayerM = Game::getPlayer();
    pAnimPlayerM->setViewDirection(Math::vec3(0.0f, -1.0f, 0.0f));
    pObjGui = checked_ptr_cast<ObjectGui>(node);
    pGui = pObjGui->getGui();
    ui = UserInterface::create(pGui, UI_file);
    string nameUi = UI_file.get();
    pBody = ui->getWidget(ui->findWidget("museum"));
    pBody->arrange();
    WidgetSpritePtr wgsp = checked_ptr_cast<WidgetSprite>(ui->getWidget(ui->findWidget("billboard")));
    wgsp->setTexture(b_image);
    pGui->addChild(pBody, Gui::ALIGN_OVERLAP | Gui::ALIGN_CENTER);
}


void billboard::Update() {

}