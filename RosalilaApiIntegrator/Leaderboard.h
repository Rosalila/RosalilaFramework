#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <vector>
#include "LeaderboardEntry.h"

class Leaderboard
{
public:
    vector<LeaderboardEntry*>top_entries;
    vector<LeaderboardEntry*>near_entries;
    vector<LeaderboardEntry*>entries;
    LeaderboardEntry* leaderboard_self_entry;
    Leaderboard(vector<LeaderboardEntry*>top_entries, vector<LeaderboardEntry*>near_entries, vector<LeaderboardEntry*>entries,LeaderboardEntry* leaderboard_self_entry);
};

#endif
