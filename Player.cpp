//
// Created by mayan on 19-Dec-22.
//

#include "Player.h"


int Player::getPlayerID() {
    return playerID;
}
Player::Player(int playerID, int teamID, int gamesPlayed, permutation_t spirit, int ability, int cards,
               bool goalKeeper) : playerID(playerID), teamID(teamID), gamesPlayed(gamesPlayed), spirit(spirit),
                                  ability(ability), cards(cards), goalKeeper(goalKeeper) {}

int Player::getExtraGames() const { return this->extraGames; };
void Player::setExtraGames(int extraGames) { this->extraGames = extraGames; }

int Player::getCards() {
    return cards;
};