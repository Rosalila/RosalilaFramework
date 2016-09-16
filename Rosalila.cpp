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


RosalilaContainer*rosalila=NULL;

RosalilaContainer* Rosalila()
{
    return rosalila;
}

void RosalilaInit()
{
    rosalila = new RosalilaContainer();
    rosalila->Parser->init();
    rosalila->Utility->init();
    rosalila->Sound->init();
    rosalila->Receiver->init();
    rosalila->ApiIntegrator->init();
    rosalila->Graphics->init();
}
