//
// Created by omerd on 29/11/2022.
//

#ifndef DATASTRUCTSTRY1_TEAMSBYAbility_H
#include <memory>
using std::shared_ptr;
#include "Team.h"

class TeamsByAbility {
private:

public:
    TeamsByAbility();
    bool operator() (shared_ptr<Team> team1, shared_ptr<Team> team2, int c) const;
    bool operator() (shared_ptr<Team> team1, int team2, int c) const;
};


#endif
