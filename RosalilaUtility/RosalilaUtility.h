#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;
#define PI 3.14159265

#include "Hitbox.h"
#include "../RosalilaGraphics/RosalilaGraphics.h"
#include "../RosalilaSound/RosalilaSound.h"
#include "../RosalilaInputs/Receiver.h"

class Hitbox;
class RosalilaGraphics;
class RosalilaSound;
class Receiver;

void setRosalilaSound(RosalilaSound*graphics_param);
RosalilaSound* getRosalilaSound();
void setReceiver(Receiver*receiver_param);
Receiver* getReceiver();
void setRosalilaGraphics(RosalilaGraphics*graphics_param);
RosalilaGraphics* getRosalilaGraphics();
bool writeLogLine(std::string text);
bool clearLog();
std::string toString(int number);
bool pointIsInRect(int point_x,int point_y,
              int rect_x,int rect_y,int rect_width,int rect_height);
bool hitboxCollision(int a_x,int a_y,int a_width,int a_height,float a_angle,
              int b_x,int b_y,int b_width,int b_height,float b_angle);
bool hitboxLinesCollision(Line la1,Line la2,Line la3,Line la4,
              Line lb1,Line lb2,Line lb3,Line lb4);
Point* lineIntersection(Line l1,Line l2);
bool segmentIntersection(Line l1,Line l2);
Point rotateAroundPoint(Point point,Point pivot,float angle);
bool collisionCheck(Hitbox* hb_azul,Hitbox* hb_roja);

#endif
