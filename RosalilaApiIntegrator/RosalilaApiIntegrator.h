#ifndef ROSALILA_API_INTEGRATOR_H
#define ROSALILA_API_INTEGRATOR_H

#include <iostream>
#include "Steam/SteamIntegration.h"

using namespace std;

class RosalilaApiIntegrator
{
public:
    void init();
    void unlockAchievement(string achievement_name);
    void setScore(string leaderboard_name, double score);
    vector<LeaderboardEntry*> getLeaderboard(string leaderboard_name);
    void setStat(string stat_name, double stat);
    double getStat(string stat_name);
    void storeData(string key, string data);
    string getData(string key);
    void updateCallbacks();
    string getState();
};

#endif
