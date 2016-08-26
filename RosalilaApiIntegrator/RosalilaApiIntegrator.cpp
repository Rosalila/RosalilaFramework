#include "RosalilaApiIntegrator.h"

void RosalilaApiIntegrator::init()
{
    steamInit();
}

void RosalilaApiIntegrator::unlockAchievement(string achievement_name)
{
    steamUnlockAchievement(achievement_name);
}

void RosalilaApiIntegrator::setScore(string leaderboard_name, double score)
{
    steamSetScore(leaderboard_name, score);
}

void RosalilaApiIntegrator::setStat(string stat_name, double stat)
{
    steamSetStat(stat_name, stat);
}

void RosalilaApiIntegrator::storeData(string key, string data)
{
    steamStoreData(key, data);
}

string RosalilaApiIntegrator::retreiveData(string key)
{
    return steamRetreiveData(key);
}
