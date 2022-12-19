#include "UnionFind.h"

int main()
{
    /*
    Tree<int, int>* arrTrees[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    Set<int, int>* arrSets[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    UnionFind<int, int> uniFin = UnionFind<int, int>(arrTrees, arrSets);
    Tree<int, int>* set1p = uniFin.makeSet(0, 0, 1, 1);
    Tree<int, int>* set2p = uniFin.makeSet(1, 3, 2, 4);
    Set<int, int>* f1 = uniFin.Find(0);
    Set<int, int>* f2 = uniFin.Find(1);
    uniFin.Union(set1p, set2p, 0, 3);
     */

    Tree<int, int>* arrTrees[17] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    Set<int, int>* arrSets[17] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    UnionFind<int, int> uniFin = UnionFind<int, int>(arrTrees, arrSets);
    Tree<int, int>* set19p = uniFin.makeSet(0, 0, 19, 190);
    Tree<int, int>* set81p = uniFin.makeSet(9, 9, 81, 810);
    Tree<int, int>* set82p = uniFin.makeSet(10, 10, 82, 820);
    Tree<int, int>* set9p = uniFin.makeSet(2, 2, 9, 90);
    Tree<int, int>* set4p = uniFin.makeSet(7,7, 4, 40);
    Tree<int, int>* set100p = uniFin.makeSet(11, 11, 100, 1000);
    Tree<int, int>* set101p = uniFin.makeSet(12, 12, 101, 1010);
    Tree<int, int>* set102p = uniFin.makeSet(13, 13, 102, 1020);
    uniFin.Union(set9p, set19p, 2, 0);
    uniFin.Union(set19p, set81p, 0, 9);
    uniFin.Union(set82p, set19p, 10, 0);
    Tree<int, int>* set15p = uniFin.makeSet(1,1, 15, 150);
    uniFin.Union(set100p, set15p, 11, 1);
    uniFin.Union(set101p, set15p, 12, 1);
    uniFin.Union(set102p, set15p, 13, 1);
    Tree<int, int>* set23p = uniFin.makeSet(5,5, 23, 230);
    uniFin.Union(set19p, set4p, 0, 7);
    Tree<int, int>* set13p = uniFin.makeSet(8,8, 13, 130);
    Tree<int, int>* set5p = uniFin.makeSet(4,4, 5, 50);
    Tree<int, int>* set2p = uniFin.makeSet(6,6,2, 20);
    uniFin.Union(set13p, set23p, 8, 5);
    uniFin.Union(set2p, set5p, 6, 4);
    uniFin.Union(set5p, set23p, 4, 5);
    uniFin.Union(set23p, set15p, 5, 1);
    Tree<int, int>* set191p = uniFin.makeSet(14, 14, 191, 1910);
    Tree<int, int>* set192p = uniFin.makeSet(15, 15, 192, 1920);
    Tree<int, int>* set193p = uniFin.makeSet(16, 16, 193, 1930);
    uniFin.Union(set191p, set19p, 14, 0);
    uniFin.Union(set192p, set19p, 15, 0);
    uniFin.Union(set193p, set19p, 16, 0);
    uniFin.Union(set15p, set19p, 1, 0);
    Set<int, int>* f1 = uniFin.Find(6);

    return 0;
}