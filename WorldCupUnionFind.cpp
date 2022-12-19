//
// Created by mayan on 19-Dec-22.
//

#include "WorldCupUnionFind.h"

//#include "UnionFind.h"

//Tree<Player, Team>** treesArr;

WorldCupUnionFind::WorldCupUnionFind() : UnionFind<Player, Team>() {};

int WorldCupUnionFind::CalcExtraGames(int treeIdx)
{
    int extraGames = 0;
    Tree<Player, Team>* root = treesArr[treeIdx];
    while ((root) && (root->getFather())) {
        extraGames += root->getData().getExtraGames();
        root = root->getFather();
    }
    Tree<Player, Team>* tree = treesArr[treeIdx];
    if (tree != root) {
        tree->getData().setExtraGames(extraGames);
    }
    Tree<Player, Team>* prevFather;
    while ((tree) && (tree->getFather())) {
        prevFather = tree->getFather();
        tree->setFather(root);
        tree = prevFather;
    }
    return extraGames + root->getData().getExtraGames();
}