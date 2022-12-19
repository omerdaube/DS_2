//
// Created by omerd on 19/12/2022.
//

#ifndef DS_2_TEAM_H
#define DS_2_TEAM_H
#include "wet2util.h"
#include "Player.h"
#include <memory>

using std::shared_ptr;

class Player;

class Team {
private:
    const int def_per[5] = {1, 2, 3, 4, 5};
    shared_ptr<Player> root;
    int teamID;
    int points;
    int sumAbility;
    permutation_t teamSpirit;
    int gamesPlayedAsTeam;
    bool removed;
    int numPlayers;
    int numGoalKeepers;
public:

    Team(int id);
    int getTeamID();
    int getTeamAbility();
    int getTeamPoints();
    bool hasGoalKeeper();
    void gameWasPlayed();
    void addTeamPoints(int);
    int getStrength();
    shared_ptr<Player> getRoot() const;
    int getNumPlayers() const;
    void setRoot(shared_ptr<Player> root);
    void setNumPlayers(int numPlayers);
};


#endif //DS_2_TEAM_H
