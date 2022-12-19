//
// Created by mayan on 24-Nov-22.
//

#include "PlayersByID.h"
#include <memory>

bool PlayersByID::operator() (shared_ptr<Player> player1, shared_ptr<Player> player2, int c) const
{
    bool toRet = false;
    int id1, id2;
    bool isP1empty = (player1 == nullptr);
    bool isP2empty = (player2 == nullptr);

    if (isP1empty || isP2empty){
        switch (c) {
            case 0:
                if (isP1empty && isP2empty)
                    toRet = true;
                break;
            case 1:
                if (isP2empty)
                    toRet = true;
                break;
            default:
                break;
        }
    }
    else {
        Player p1 = *player1, p2 = *player2;
        id1 = p1.getPlayerID();
        id2 = p2.getPlayerID();
        switch (c) {
            case 0:
                toRet = (id1 == id2);
                break;
            case 1:
                toRet = (id1 > id2);
                break;
            default:
                /////////////////////////////////////////////////////////////////////////////////////////////////////////////
                toRet = false;
                break;
        }
    }
    return toRet;
}

bool PlayersByID::operator() (shared_ptr<Player> player1, int player2, int c) const
{
    bool toRet = false;
    int id1, id2;
    bool isP1empty = (player1 == nullptr);
    if (!isP1empty){
        Player p1 = *player1;
        id1 = p1.getPlayerID();
        id2 = player2;
        switch (c) {
            case 0:
                toRet = (id1 == id2);
                break;
            case 1:
                toRet = (id1 > id2);
                break;
            default:
                /////////////////////////////////////////////////////////////////////////////////////////////////////////////
                toRet = false;
                break;
        }
    }
    return toRet;
}