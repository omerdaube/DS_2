//
// Created by omerd on 29/11/2022.
//

#ifndef DATASTRUCTSTRY1_TEAMSBYID_H
#include <memory>
using std::shared_ptr;
#include "Team.h"

class TeamsByID {
private:

public:
    TeamsByID();
    bool operator() (shared_ptr<Team> team1, shared_ptr<Team> team2, int c) const;
    bool operator() (shared_ptr<Team> team1, int team2, int c) const;
};


#endif //DATASTRUCTSTRY1_TEAMSBYID_H
