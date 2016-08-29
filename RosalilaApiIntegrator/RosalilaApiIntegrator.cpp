#include "RosalilaApiIntegrator.h"

void RosalilaApiIntegrator::init()
{
    steamInit();
}

void RosalilaApiIntegrator::unlockAchievement(string achievement_name)
{
    steamUnlockAchievement(achievement_name);
}

void RosalilaApiIntegrator::setScore(string leaderboard_name, double score, char* data, int data_size)
{
    steamSetScore(leaderboard_name, score, data, data_size);
}

Leaderboard* RosalilaApiIntegrator::getLeaderboard(string leaderboard_name)
{
    return steamGetLeaderboard(leaderboard_name);
}

void RosalilaApiIntegrator::setStat(string stat_name, double stat)
{
    steamSetStat(stat_name, stat);
}

void RosalilaApiIntegrator::storeData(string key, string data)
{
    steamStoreData(key, data);
}

double RosalilaApiIntegrator::getStat(string stat_name)
{
    return steamGetStat(stat_name);
}

string RosalilaApiIntegrator::getData(string key)
{
    return steamGetData(key);
}

void RosalilaApiIntegrator::updateCallbacks()
{
    steamUpdateCallbacks();
}

string RosalilaApiIntegrator::getState()
{
    return steamGetState();
}
