//
// Created by omerd on 19/12/2022.
//

#include "TeamsByAbility.h"
//
// Created by mayan on 24-Nov-22.
//

TeamsByAbility::TeamsByAbility() {}

bool TeamsByAbility::operator() (shared_ptr<Team> team1, shared_ptr<Team> team2, int c) const {

    bool toRet = false;
    if (!team1 || !team2) {
        return false;
    }
    Team t1 = *team1, t2 = *team2;
    switch (c) {
        case 0:
            toRet = (t1.getTeamID() == t2.getTeamID());
            break;
        case 1:
            if(t1.getTeamAbility() > t2.getTeamAbility()) {
                toRet = true;
            }
            else if(t1.getTeamAbility() == t2.getTeamAbility()) {
                if (t1.getTeamID() > t2.getTeamID()) {
                    toRet = true;
                }
            }
            break;
        default:
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            toRet = false;
            break;
    }
    return toRet;
}