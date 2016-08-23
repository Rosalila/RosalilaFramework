#include "Rosalila.h"

RosalilaContainer::RosalilaContainer()
{
    this->Utility= new RosalilaUtility();
    this->Sound = new RosalilaSound();
    this->Receiver = new RosalilaReceiver();
    this->Graphics = new RosalilaGraphics();
    this->ApiIntegrator = new RosalilaApiIntegrator();
}


RosalilaContainer*rosalila=NULL;

RosalilaContainer* Rosalila()
{
    return rosalila;
}

void RosalilaInit()
{
    rosalila = new RosalilaContainer();
    rosalila->Utility->init();
    rosalila->Sound->init();
    rosalila->Receiver->init();
    rosalila->Graphics->init();
    rosalila->ApiIntegrator->init();
}
