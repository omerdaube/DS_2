//
// Created by omerd on 29/11/2022.
//

#ifndef DATASTRUCTSTRY1_PLAYERSBYID_H
#include <memory>
using std::shared_ptr;
#include "Player.h"

class PlayersByID {
public:
    bool operator() (shared_ptr<Player> player1, shared_ptr<Player> player2, int c) const;
    bool operator() (shared_ptr<Player> player1, int player2, int c) const;
};


#endif //DATASTRUCTSTRY1_PLAYERSBYID_H
