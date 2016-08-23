#include "Rosalila.h"

RosalilaContainer::RosalilaContainer()
{
    this->Sound = new RosalilaSound();
    this->Receiver = new RosalilaReceiver();
    this->Graphics = new RosalilaGraphics();
    this->ApiIntegrator = new RosalilaApiIntegrator();
}


RosalilaContainer*rosalila=NULL;

RosalilaContainer* Rosalila()
{
    if(!rosalila)
        rosalila = new RosalilaContainer();
    return rosalila;
}

void RosalilaInit()
{
    rosalila = new RosalilaContainer();
}
