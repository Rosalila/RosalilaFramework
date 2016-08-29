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
    char* data;
    int data_size;

    LeaderboardEntry(string name, int rank, int score, int details);
};

#endif
