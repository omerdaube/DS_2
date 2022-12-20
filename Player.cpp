//
// Created by mayan on 19-Dec-22.
//

#include "Player.h"
#include "Team.h"

int Player::getPlayerID() {
    return playerID;
}
Player::Player(int playerID, shared_ptr<Team> team, int gamesPlayed, permutation_t spirit, int ability, int cards,
               bool goalKeeper) : playerID(playerID), team(team),father(nullptr), extraSpirit(spirit),
                                  ability(ability), cards(cards), goalKeeper(goalKeeper), extraGames(gamesPlayed)
                                   {}

int Player::getExtraGames() const { return this->extraGames; };
permutation_t Player::getExtraSpirit() const { return this->extraSpirit; };
void Player::setExtraGames(int extraGames) { this->extraGames = extraGames; };
void Player::setExtraSpirit(permutation_t extraSpirit) { this->extraSpirit = extraSpirit; };

int Player::getCards() {
    return cards;
}

void Player::resetPlayer() {
    if(team != nullptr){
        team->resetTeam();
    }
    team = nullptr;
    father = nullptr;
}

void Player::addCards(int c) {
    cards += c;
}

void Player::increaseGames() {
    extraGames++;
}
