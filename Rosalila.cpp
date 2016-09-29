#include "Rosalila.h"

RosalilaContainer::RosalilaContainer()
{
    this->parser = new RosalilaParser();
    this->utility= new RosalilaUtility();
    this->sound = new RosalilaSound();
    this->receiver = new RosalilaReceiver();
    this->api_integrator = new RosalilaApiIntegrator();
    this->graphics = new RosalilaGraphics();
}

void RosalilaContainer::update()
{
    receiver->updateInputs();
    graphics->updateScreen();
    api_integrator->updateCallbacks();
}

void RosalilaContainer::init()
{
    parser->init();
    utility->init();
    sound->init();
    receiver->init();
    api_integrator->init();
    graphics->init();
}

RosalilaContainer* rosalila_container = new RosalilaContainer();;

RosalilaContainer* rosalila()
{
    return rosalila_container;
}
