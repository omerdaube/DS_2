//
// Created by mayan on 18-Dec-22.
//

#ifndef DS_2_UNIONFIND_H
#define DS_2_UNIONFIND_H

template <class TreeData, class SetData>
class Set;

template <class TreeData, class SetData>
class Tree {
public:
    Tree(TreeData data, Tree* father, Set<TreeData, SetData>* set) : data(data), father(father), set(set) {};
    TreeData getData() const { return this->data; };
    Tree* getFather() const { return this->father; };
    void setData(TreeData data) { this->data = data; };
    void setFather(Tree* father) { this->father = father; };
    Set<TreeData, SetData>* getSet() const { return this->set; };
    void setSet(Set<TreeData, SetData>* set) { this->set= set; };

private:
    TreeData data;
    Tree* father;
    Set<TreeData, SetData>* set;
};

/*
template <class TreeData, class SetData>
class TreeRoot:Tree<TreeData> {
public:
    TreeRoot(TreeData data, Set<TreeData, SetData>* set) : Tree<TreeData>(data, nullptr), set(set) {};
    Set<TreeData, SetData>* getSet() const { return this->set; };
    void setSet(Set<TreeData, SetData>* set) { this->set= set; };
private:
    Set<TreeData, SetData>* set;
};
*/

template <class TreeData, class SetData>
class Set{
public:
    //Set() : data(SetData()), root(nullptr), num(0) {};
    Set(SetData data) : data(data), root(nullptr), num(1){};
    SetData getSetData() const { return this->data; };
    Tree<TreeData, SetData>* getTreeRoot() const { return this->root; };
    int getNum() const { return this->num; };
    void setSetData(SetData data) { this->data = data; };
    void setTreeRoot(Tree<TreeData, SetData>* root) { this->root = root; };
    void setNum(int num) { this->num = num; };
private:
    SetData data;
    Tree<TreeData, SetData>* root;
    int num;
};

template <class TreeData, class SetData>
class UnionFind {
private:
    Tree<TreeData, SetData>** treesArr;
    Set<TreeData, SetData>** setsArr;
public:
    UnionFind(Tree<TreeData, SetData>** treesArr, Set<TreeData, SetData>** setsArr) : treesArr(treesArr), setsArr(setsArr) {};

    Tree<TreeData, SetData>* makeSet(int treeIdx, int setIdx, TreeData treeData, SetData setData)
    {
        Set<TreeData, SetData>* set = new Set<TreeData, SetData>(setData);
        Tree<TreeData, SetData>* root = new Tree<TreeData, SetData>(treeData, nullptr, set);
        set->setTreeRoot(root);
        treesArr[treeIdx] = root;
        setsArr[setIdx] = set;
        return root;
    }

    Set<TreeData, SetData>* Find(int treeIdx)
    {
        Tree<TreeData, SetData>* root = treesArr[treeIdx];
        while ((root) && (root->getFather())) {
            root = root->getFather();
        }
        Tree<TreeData, SetData>* tree = treesArr[treeIdx];
        Tree<TreeData, SetData>* prevFather;
        while ((tree) && (tree->getFather())) {
            prevFather = tree->getFather();
            tree->setFather(root);
            tree = prevFather;
        }
        return root->getSet();
    }

    void removeSet(Set<TreeData, SetData>* set, int setIdx)
    {
        set->setSetData(SetData());                          //////////////////////////////////////////////////////////////
        set->setTreeRoot(nullptr);
    }

    void Union(Tree<TreeData, SetData>* r1, Tree<TreeData, SetData>* r2, int set2idx, int set1idx)
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