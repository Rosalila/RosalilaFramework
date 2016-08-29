#include "LeaderboardEntry.h"

LeaderboardEntry::LeaderboardEntry(string name, int rank, int score, int details)
{
    this->name=name;
    this->rank=rank;
    this->score=score;
    this->details=details;
    this->data=NULL;
    this->data_size=0;
}
