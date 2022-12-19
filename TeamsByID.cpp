//
// Created by mayan on 24-Nov-22.
//

#include "TeamsByID.h"

TeamsByID::TeamsByID() {}

bool TeamsByID::operator() (shared_ptr<Team> team1, shared_ptr<Team> team2, int c) const
{

    bool toRet = false;
    if(!team1 || !team2){
        return false;
    }
    Team t1 = *team1, t2 = *team2;
    switch(c) {
        case 0:
            toRet = (t1.getTeamID() == t2.getTeamID());
            break;
        case 1:
            toRet = (t1.getTeamID() > t2.getTeamID());
            break;
        default:
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            toRet = false;
            break;
    }
    return toRet;
}

bool TeamsByID::operator()(shared_ptr<Team> team1, int team2, int c) const {

    bool toRet = false;
    if(!team1){
        return false;
    }
    Team t1 = *team1;
    switch(c) {
        case 0:
            toRet = (t1.getTeamID() == team2);
            break;
        case 1:
            toRet = (t1.getTeamID() > team2);
            break;
        default:
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            toRet = false;
            break;
    }
    return toRet;
}


