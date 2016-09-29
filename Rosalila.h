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
#include "RosalilaUtility/RosalilaUtility.h"
#include "RosalilaParser/RosalilaParser.h"
#include "RosalilaApiIntegrator/RosalilaApiIntegrator.h"

class RosalilaGraphics;
class RosalilaSound;
class RosalilaReceiver;
class RosalilaUtility;
class RosalilaParser;
class RosalilaApiIntegrator;

const string assets_directory="assets/";

class RosalilaContainer
{
public:
    RosalilaGraphics* graphics;
    RosalilaSound* sound;
    RosalilaReceiver* receiver;
    RosalilaApiIntegrator* api_integrator;
    RosalilaUtility* utility;
    RosalilaParser* parser;
    RosalilaContainer();
    void init();
    void update();
};

RosalilaContainer* rosalila();

#endif // SYSTEM_H_INCLUDED
