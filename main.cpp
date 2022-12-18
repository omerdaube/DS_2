#include "UnionFind.h"

int main()
{
    //int arrTree[5] = {};
    //int arrSet[5] = {};
    UnionFind<int, int> uniFin = UnionFind<int, int>();
    TreeRoot<int, int>* set1p = uniFin.makeSet(0, 0, 1, 1);
    TreeRoot<int, int>* set2p = uniFin.makeSet(1, 3, 2, 4);
    uniFin.Find(0);
    uniFin.Find(1);
    uniFin.Union(set1p, set2p);

    return 0;
}