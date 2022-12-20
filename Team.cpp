//
// Created by omerd on 19/12/2022.
//

#include "Team.h"

Team::Team(int id) : teamID(id), points(0), sumAbility(0), teamSpirit(permutation_t(def_per)), gamesPlayedAsTeam(0),
                     removed(false), numPlayers(0), numGoalKeepers(0){}

int Team::getTeamID()
{
    return teamID;
}

permutation_t Team::getTeamSpirit() const
{
    return this->teamSpirit;
}

shared_ptr<Player> Team::getRoot() const
{
    return this->root;
}

int Team::getNumPlayers() const
{
    return this->numPlayers;
}

void Team::setRoot(shared_ptr<Player> root)
{
    this->root = root;
}
void Team::setNumPlayers(int numPlayers)
{
    this->numPlayers = numPlayers;
}

int Team::getTeamAbility() {
    return sumAbility;
}

int Team::getTeamPoints() {
    return points;
}

bool Team::hasGoalKeeper() {
    return (numGoalKeepers > 0);
}

void Team::gameWasPlayed() {
    gamesPlayedAsTeam++;
}

void Team::addTeamPoints(int x) {
    points += x;
}

int Team::getStrength() {
    return teamSpirit.strength();
}

void Team::setTeamSpirit(permutation_t teamSpirit)
{
    this->teamSpirit = teamSpirit;
}