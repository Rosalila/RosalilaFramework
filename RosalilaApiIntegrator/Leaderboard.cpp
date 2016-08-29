#include "Leaderboard.h"

Leaderboard::Leaderboard(vector<LeaderboardEntry*>top_entries,
                            vector<LeaderboardEntry*>near_entries,
                            vector<LeaderboardEntry*>entries)
{
    this->top_entries=top_entries;
    this->near_entries=near_entries;
    this->entries=entries;
}
