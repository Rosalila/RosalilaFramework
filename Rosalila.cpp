#include "Rosalila.h"

RosalilaContainer::RosalilaContainer()
{
    this->net = new RosalilaNet();
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
    sound->update();
    net->update();
}

void RosalilaContainer::init()
{
    parser->init();
    utility->init();
    sound->init();
    receiver->init();
    api_integrator->init();
    graphics->init();
    //net->init("165.227.107.214", 3069, 512);
    net->init();
}

RosalilaContainer* rosalila_container = new RosalilaContainer();

RosalilaContainer* rosalila()
{
    return rosalila_container;
}
