//
// Created by mayan on 19-Dec-22.
//

#include "Player.h"


int Player::getPlayerID() {
    return playerID;
}
Player::Player(int playerID, shared_ptr<Team> team, int gamesPlayed, permutation_t spirit, int ability, int cards,
               bool goalKeeper) : playerID(playerID), team(team), gamesPlayed(gamesPlayed), extraSpirit(extraSpirit),
                                  ability(ability), cards(cards), goalKeeper(goalKeeper),
                                  father(shared_ptr<Player>()) {};

int Player::getExtraGames() const { return this->extraGames; };
permutation_t Player::getExtraSpirit() const { return this->extraSpirit; };
void Player::setExtraGames(int extraGames) { this->extraGames = extraGames; };
void Player::setExtraSpirit(permutation_t extraSpirit) { this->extraSpirit = extraSpirit; };

int Player::getCards() {
    return cards;
};