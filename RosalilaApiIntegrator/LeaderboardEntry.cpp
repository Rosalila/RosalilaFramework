#include "LeaderboardEntry.h"

LeaderboardEntry::LeaderboardEntry(string name, int rank, int score, int details)
{
    this->name=name;
    this->rank=rank;
    this->score=score;
    this->details=details;
    this->attachment=NULL;
    this->attachment_size=0;
    this->attachment_state="not loaded";
}
