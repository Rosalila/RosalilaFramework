#include "Rosalila.h"

RosalilaContainer::RosalilaContainer()
{
    this->Parser = new RosalilaParser();
    this->Utility= new RosalilaUtility();
    this->Sound = new RosalilaSound();
    this->Receiver = new RosalilaReceiver();
    this->ApiIntegrator = new RosalilaApiIntegrator();
    this->Graphics = new RosalilaGraphics();
}

void RosalilaContainer::update()
{
    Receiver->updateInputs();
    Graphics->updateScreen();
    ApiIntegrator->updateCallbacks();
}

void RosalilaContainer::init()
{
    Parser->init();
    Utility->init();
    Sound->init();
    Receiver->init();
    ApiIntegrator->init();
    Graphics->init();
}

RosalilaContainer* rosalila = new RosalilaContainer();;

RosalilaContainer* Rosalila()
{
    return rosalila;
}
