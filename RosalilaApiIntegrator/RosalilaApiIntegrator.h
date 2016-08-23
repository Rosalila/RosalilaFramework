#ifndef ROSALILA_API_INTEGRATOR_H
#define ROSALILA_API_INTEGRATOR_H

#include <iostream>
using namespace std;

class RosalilaApiIntegrator
{
public:
    RosalilaApiIntegrator();
    void unlockAchievement(string achievement_name);
    void setScore(string leaderboard_name, double score);
    void setStat(string stat_name, double stat);
    void storeData(string key, string data);
    string retreiveData(string key);
};

#endif
