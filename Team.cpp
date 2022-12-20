//
// Created by omerd on 19/12/2022.
//

#include "Team.h"
#include "Player.h"
Team::Team(int id) : teamID(id), points(0), sumAbility(0), teamSpirit(), gamesPlayedAsTeam(0),
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

void Team::resetTeam() {
    root = nullptr;
}

void Team::addedPlayer(int ability, permutation_t per) {
    numPlayers++;
    if(numPlayers <= 1){
        teamSpirit = per;
    }
    else{
        teamSpirit = teamSpirit * per;
    }
    sumAbility += ability;
}

void Team::outOfGame() {
    removed = true;
}

bool Team::isInGame() {
    return !removed;
}

void Team::bought(shared_ptr<Team> t) {
    points += t->points;
    sumAbility += t->sumAbility;
    teamSpirit = teamSpirit * t->teamSpirit;
    numPlayers += t->numPlayers;
}



void Team::setTeamSpirit(permutation_t teamSpirit)
{
    this->teamSpirit = teamSpirit;
}

void Team::setNumPlayers(int x) {
    numPlayers = x;
}
