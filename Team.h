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
    permutation_t getTeamSpirit() const;
    int getTeamAbility();
    int getTeamPoints();
    bool hasGoalKeeper();
    void gameWasPlayed();
    void addTeamPoints(int);
    int getStrength();
    void outOfGame();
    bool isInGame();
    shared_ptr<Player> getRoot() const;
    int getNumPlayers() const;
    void setNumPlayers(int x);
    void setRoot(shared_ptr<Player> root);
    void addedPlayer(int ability, permutation_t per);
    void resetTeam();
    void bought(shared_ptr<Team> t);
    void setTeamSpirit(permutation_t teamSpirit);
};


#endif //DS_2_TEAM_H
