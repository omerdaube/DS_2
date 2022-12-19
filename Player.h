//
// Created by mayan on 19-Dec-22.
//

#ifndef DS_2_PLAYER_H
#define DS_2_PLAYER_H
#include "wet2util.h"
class Player {
private:
    int playerID;
    int teamID;
    int gamesPlayed;
    permutation_t spirit;
    int ability;
    int cards;
    bool goalKeeper;
    int extraGames;
public:
    int getPlayerID();
    Player(int playerID, int teamID, int gamesPlayed, permutation_t spirit, int ability, int cards, bool goalKeeper);
    int getExtraGames() const;
    void setExtraGames(int extraGames);
    int getCards();
};

#endif //DS_2_PLAYER_H
