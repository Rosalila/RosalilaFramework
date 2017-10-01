#include "RosalilaApiIntegrator.h"

void RosalilaApiIntegrator::init()
{
	#ifdef STEAM
    steamInit();
	#endif
}

bool RosalilaApiIntegrator::isUsingApi()
{
	bool is_using_api = false;
	#ifdef STEAM
    is_using_api = steamIsUsingApi();
	#endif
	return is_using_api;
}

void RosalilaApiIntegrator::unlockAchievement(string achievement_name)
{
	#ifdef STEAM
    steamUnlockAchievement(achievement_name);
	#endif
}

void RosalilaApiIntegrator::setScore(string leaderboard_name, double score)
{
	#ifdef STEAM
    steamSetScore(leaderboard_name, score);
	#endif
}

void RosalilaApiIntegrator::storeLeaderboardAttachment(string leaderboard_name, char* attachment, int attachment_size)
{
	#ifdef STEAM
    steamStoreLeaderboardAttachment(leaderboard_name, attachment, attachment_size);
	#endif
}

#ifdef STEAM
Leaderboard* RosalilaApiIntegrator::getLeaderboard(string leaderboard_name)
{
	return steamGetLeaderboard(leaderboard_name);
}

void RosalilaApiIntegrator::downloadEntryAttachment(LeaderboardEntry* leaderboard_entry)
{
    steamDownloadEntryAttachment(leaderboard_entry);
}
#endif

void RosalilaApiIntegrator::findLeaderboard(string leaderboard_name)
{
	#ifdef STEAM
    steamFindLeaderboard(leaderboard_name);
	#endif
}

void RosalilaApiIntegrator::setStat(string stat_name, double stat)
{
	#ifdef STEAM
    steamSetStat(stat_name, stat);
	#endif
}

void RosalilaApiIntegrator::storeData(string key, string data)
{
	#ifdef STEAM
    steamStoreData(key, data);
	#endif
}

double RosalilaApiIntegrator::getStat(string stat_name)
{
	double stat = 0;
	#ifdef STEAM
    stat = steamGetStat(stat_name);
	#endif
	return stat;
}

string RosalilaApiIntegrator::getData(string key)
{
	string data = "";
	#ifdef STEAM
    data = steamGetData(key);
	#endif
	return data;
}

void RosalilaApiIntegrator::updateCallbacks()
{
	#ifdef STEAM
    steamUpdateCallbacks();
	#endif
}

string RosalilaApiIntegrator::getState()
{
	string state = "";
	#ifdef STEAM
    state = steamGetState();
	#endif
	return state;
}

void RosalilaApiIntegrator::setCurrentControllerActionSet(string action_set_name)
{
	#ifdef STEAM
    steamSetCurrentControllerActionSet(action_set_name);
	#endif
}

bool RosalilaApiIntegrator::isControllerActionDown(string action_name)
{
	bool is_controller_action_down = false;
	#ifdef STEAM
    is_controller_action_down = steamIsControllerActionDown(action_name);
	#endif
	return is_controller_action_down;
}

bool RosalilaApiIntegrator::isUsingSteamController()
{
	bool is_using_steam_controller = false;
	#ifdef STEAM
    is_using_steam_controller = steamIsUsingSteamController();
	#endif
	return is_using_steam_controller;
}

void RosalilaApiIntegrator::showControllerBindingPanel()
{
	#ifdef STEAM
    steamShowControllerBindingPanel();
	#endif
}
