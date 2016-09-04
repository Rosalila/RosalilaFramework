#include "Leaderboard.h"

Leaderboard::Leaderboard(vector<LeaderboardEntry*>top_entries,
                            vector<LeaderboardEntry*>near_entries,
                            vector<LeaderboardEntry*>entries,
                            LeaderboardEntry* leaderboard_self_entry)
{
    this->top_entries=top_entries;
    this->near_entries=near_entries;
    this->entries=entries;
    this->leaderboard_self_entry=leaderboard_self_entry;
}
