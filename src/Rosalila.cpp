#include "Rosalila.h"

//std::string assets_directory="assets/";
std::string CONFIG_FILE_PATH;

RosalilaContainer::RosalilaContainer()
{
  //this->net = new RosalilaNet();
  this->parser = new RosalilaParser();
  this->utility = new RosalilaUtility();
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
  //net->update();

  std::string error = SDL_GetError();
  if (error != "")
    rosalila()->utility->writeLogLine("Error: " + error);
}

void RosalilaContainer::init(std::string config_file_path)
{
  std::cout<<"Config file: "<<config_file_path<<std::endl;
  CONFIG_FILE_PATH = config_file_path;
  this->utility->writeLogLine("Initializing parser.");
  parser->init();

  this->utility->writeLogLine("Parser initialized.");
  this->utility->writeLogLine("Initializing utility.");
  utility->init();
  this->utility->writeLogLine("Utility initialized.");
  this->utility->writeLogLine("Initializing sound.");
  sound->init();
  this->utility->writeLogLine("Sound initialized.");
  this->utility->writeLogLine("Initializing receiver.");
  receiver->init();
  this->utility->writeLogLine("Receiver initialized.");
  this->utility->writeLogLine("Initializing API integrator.");
  api_integrator->init();
  this->utility->writeLogLine("API integrator initialized.");
  this->utility->writeLogLine("Initializing graphics.");
  graphics->init();
  //net->init("165.227.107.214", 3069, 512);
  this->utility->writeLogLine("Parser graphics.");
  this->utility->writeLogLine("Initializing networking.");
  //net->init();
}

RosalilaContainer *rosalila_container = new RosalilaContainer();

RosalilaContainer *rosalila()
{
  return rosalila_container;
}
