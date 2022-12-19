//
// Created by mayan on 19-Dec-22.
//

#ifndef DS_2_WORLDCUPUNIONFIND_H
#define DS_2_WORLDCUPUNIONFIND_H

#include "Player.h"
#include "Team.h"
#include "UnionFind.h"

class WorldCupUnionFind : UnionFind<Player, Team> {
    WorldCupUnionFind();

    int CalcExtraGames(int treeIdx);

    int CalcExtraSpirit(int treeIdx);

};

#endif //DS_2_WORLDCUPUNIONFIND_H