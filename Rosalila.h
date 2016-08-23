#ifndef ROSALILA_H
#define ROSALILA_H

#include <iostream>
using namespace std;

//Choose your build platform by defining it:
#ifdef __linux__
#define LINUX
#endif

#ifdef __APPLE__
#define OSX
#endif
#ifdef __MACH__
#define OSX
#endif

#ifdef _WIN32
#define WINDOWS
#endif
#ifdef _WIN64
#define WINDOWS
#endif

#include "RosalilaGraphics/RosalilaGraphics.h"
#include "RosalilaSound/RosalilaSound.h"
#include "RosalilaInputs/RosalilaInputs.h"
#include "RosalilaApiIntegrator/RosalilaApiIntegrator.h"

class RosalilaGraphics;
class RosalilaSound;
class RosalilaReceiver;
class RosalilaApiIntegrator;

const string assets_directory="assets/";

class RosalilaContainer
{
public:
    RosalilaGraphics* Graphics;
    RosalilaSound* Sound;
    RosalilaReceiver* Receiver;
    RosalilaApiIntegrator* ApiIntegrator;
    RosalilaContainer();
};

RosalilaContainer* Rosalila();
void RosalilaInit();


#endif // SYSTEM_H_INCLUDED
