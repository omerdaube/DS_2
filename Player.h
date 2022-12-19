//
// Created by mayan on 19-Dec-22.
//

#ifndef DS_2_PLAYER_H
#define DS_2_PLAYER_H
#include "wet2util.h"
#include "Team.h"
#include <memory>

using std::shared_ptr;

class Team;

class Player {
private:
    int playerID;
    shared_ptr<Team> team;
    shared_ptr<Player> father;
    int gamesPlayed;
    permutation_t extraSpirit;
    int ability;
    int cards;
    bool goalKeeper;
    int extraGames;
public:
    Player(int playerID, shared_ptr<Team> team, int gamesPlayed, permutation_t spirit, int ability, int cards, bool goalKeeper);
    int getPlayerID();
    Player(int playerID, int teamID, int gamesPlayed, permutation_t spirit, int ability, int cards, bool goalKeeper);
    int getExtraGames() const;
    permutation_t getExtraSpirit() const;
    shared_ptr<Team> getTeam() const { return this->team; };
    shared_ptr<Player> getFather() const {return this->father; };
    void setExtraGames(int extraGames);
    void setExtraSpirit(permutation_t extraSpirit);
    void setTeam(shared_ptr<Team> team) {this->team = team; };
    void setFather(shared_ptr<Player> father) {this->father = father; };
    int getCards();
};

#endif //DS_2_PLAYER_H
