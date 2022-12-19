//
// Created by mayan on 19-Dec-22.
//

#ifndef DS_2_WCUNIONFIND_H
#define DS_2_WCUNIONFIND_H

#include "Hash.h"
#include "Player.h"
#include "Team.h"
#include "PlayersByID.h"
#include "TeamsByID.h"

/*
class Set;

class Tree {
public:
    Tree(shared_ptr<Player> data, Tree* father, Set* set) : data(data), father(father), set(set) {};
    shared_ptr<Player> getData() const { return this->data; };
    Tree* getFather() const { return this->father; };
    void setData(shared_ptr<Player> data) { this->data = data; };
    void setFather(Tree* father) { this->father = father; };
    Set* getSet() const { return this->set; };
    void setSet(Set* set) { this->set= set; };

private:
    shared_ptr<Player> data;
    Tree* father;
    Set* set;
};


template <class shared_ptr<Player>>, class shared_ptr<Player>>
class TreeRoot:Tree<shared_ptr<Player>>> {
public:
    TreeRoot(shared_ptr<Player>> data, Set<shared_ptr<Player>>, shared_ptr<Player>>* set) : Tree<shared_ptr<Player>>>(data, nullptr), set(set) {};
    Set<shared_ptr<Player>>, shared_ptr<Player>>* getSet() const { return this->set; };
    void setSet(Set<shared_ptr<Player>>, shared_ptr<Player>>* set) { this->set= set; };
private:
    Set<shared_ptr<Player>>, shared_ptr<Player>>* set;
};


class Set{
public:
    //Set() : data(shared_ptr<Player>()), root(nullptr), num(0) {};
    Set(shared_ptr<Player> data) : data(data), root(nullptr), num(1){};
    shared_ptr<Player> getData() const { return this->data; };
    Tree* getTreeRoot() const { return this->root; };
    int getNum() const { return this->num; };
    void setData(shared_ptr<Player> data) { this->data = data; };
    void setTreeRoot(Tree* root) { this->root = root; };
    void setNum(int num) { this->num = num; };
private:
    shared_ptr<Player> data;
    Tree* root;
    int num;
};

*/
class UnionFind {
private:
    Hash<shared_ptr<Player>, PlayersByID> treesArr;
    //Hash<shared_ptr<Team>, shared_ptr<Player>>sByID> treesArr;
    //Hash<shared_ptr<Player>, shared_ptr<Player>sByID> setsArr;
    //Tree<shared_ptr<Player>>, shared_ptr<Player>>* treesArr[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    //Set<shared_ptr<Player>>, shared_ptr<Player>>* setsArr[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
public:
    UnionFind() : treesArr(Hash<shared_ptr<Player>, PlayersByID>(&(Player::getPlayerID))) {};
    //UnionFind(Tree<shared_ptr<Player>>, shared_ptr<Player>>** treesArr, Set<shared_ptr<Player>>, shared_ptr<Player>>** setsArr) : treesArr(treesArr), setsArr(setsArr) {};
    //UnionFind() : treesArr(Hash<shared_ptr<shared_ptr<Player>>>, shared_ptr<Player>>sByID>(&(shared_ptr<Player>>::getshared_ptr<Player>>ID))),
    //               setsArr(Hash<shared_ptr<Player>, shared_ptr<Player>sByID>(&(shared_ptr<Player>::getshared_ptr<Player>ID))) {};
    shared_ptr<Team> makeSet(/*int treeIdx, int setIdx,*/ shared_ptr<Player> player, shared_ptr<Team> team)
    {
        //Set<shared_ptr<Player>>, shared_ptr<Player>>* set = new Set<shared_ptr<Player>>, shared_ptr<Player>>(shared_ptr<Player>);
        //Tree<shared_ptr<Player>>, shared_ptr<Player>>* root = new Tree<shared_ptr<Player>>, shared_ptr<Player>>(shared_ptr<Player>>, nullptr, set);
        //set->setTreeRoot(root);
        team->setRoot(player);
        team->setNumPlayers(1);
        //setshared_ptr<Player>>TreeP(shared_ptr<Player>>, root);
        //shared_ptr<Player>.setshared_ptr<Player>>SetP(shared_ptr<Player>, set);
        treesArr.add(shared_ptr<Player>>);//[treeIdx] = root;
        //setsArr.add(shared_ptr<Player>);//[setIdx] = set;
        return root;
    }

    Set<shared_ptr<Player>>, shared_ptr<Player>>* Find(int id)//int treeIdx)
    {
        Tree<shared_ptr<Player>>, shared_ptr<Player>>* root = treesArr.find(id);//treesArr[treeIdx];
        while ((root) && (root->getFather())) {
            root = root->getFather();
        }
        Tree<shared_ptr<Player>>, shared_ptr<Player>>* tree = treesArr//[treeIdx];
        Tree<shared_ptr<Player>>, shared_ptr<Player>>* prevFather;
        while ((tree) && (tree->getFather())) {
            prevFather = tree->getFather();
            tree->setFather(root);
            tree = prevFather;
        }
        return root->getSet();
    }

    void removeSet(Set<shared_ptr<Player>>, shared_ptr<Player>>* set, int setIdx)
    {
        set->setshared_ptr<Player>(shared_ptr<Player>());                          //////////////////////////////////////////////////////////////
        set->setTreeRoot(nullptr);
    }

    void Union(Tree<shared_ptr<Player>>, shared_ptr<Player>>* r1, Tree<shared_ptr<Player>>, shared_ptr<Player>>* r2, int set2idx, int set1idx)
    {
        if (r1 == r2) {
            return;
        }
        if (r1->getSet()->getNum() > r2->getSet()->getNum()) {
            r2->setFather(r1);
            r1->getSet()->setNum(r1->getSet()->getNum() + r2->getSet()->getNum());
            r2->getSet()->setNum(0);
            removeSet(r2->getSet(), set2idx);
            r2->setSet(nullptr);
        }
        else {
            r1->setFather(r2);
            r2->getSet()->setNum(r2->getSet()->getNum() + r1->getSet()->getNum());
            r1->getSet()->setNum(0);
            removeSet(r1->getSet(), set1idx);
            r1->setSet(nullptr);
        }
    }
};

#endif //DS_2_UNIONFIND_H


#endif //DS_2_WCUNIONFIND_H
