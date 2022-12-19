//
// Created by omerd on 19/12/2022.
//

#include "Team.h"

int Team::getTeamID() {
    return teamID;
}

Team::Team(int id) : teamID(id), points(0), sumAbility(0), teamSpirit(permutation_t(def_per)), gamesPlayedAsTeam(0),
                     removed(false), numPlayers(0), numGoalKeepers(0){}