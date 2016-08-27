#ifndef LEADERBOARD_ENTRY_H
#define LEADERBOARD_ENTRY_H

#include <iostream>
using namespace std;

class LeaderboardEntry
{
public:
    string name;
    int rank;
    int score;
    int details;
    int data;

    LeaderboardEntry(string name, int rank, int score, int details, int data);
};

#endif
