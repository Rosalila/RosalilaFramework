#include "LeaderboardEntry.h"

LeaderboardEntry::LeaderboardEntry(string name, int rank, int score, int details, int data)
{
    this->name=name;
    this->rank=rank;
    this->score=score;
    this->details=details;
    this->data=data;
}
