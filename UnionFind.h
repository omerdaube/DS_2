//
// Created by mayan on 18-Dec-22.
//

#ifndef DS_2_UNIONFIND_H
#define DS_2_UNIONFIND_H

class Set;

template <class TreeData>
class Tree {
public:
    Tree(TreeData data, Tree* father) : data(data), father(father) {};
    TreeData getData() const { return this->data; };
    Tree* getFather() const { return this->father; };
    void setData(TreeData data) { this->data = data; };
    void setFather(Tree* father) { this->father = father; };

private:
    Data data;
    Tree* father;
};

template <class TreeData, class SetData>
class TreeRoot:Tree<TreeData> {
public:
    TreeRoot(TreeData data, Set* set) : Tree<TreeData>(data, nullptr), set(set);
    Set<SetData>* getSet() const { return this->set; };
    void setSet(Set<SetData>* set) { this->set= set; };
private:
    Set* set;
};

template <class SetData>
class Set{
public:
    Set(SetData data) : data(data), root(nullptr), num(1){};
    SetData getSetData() const { return this->data; };
    TreeRoot* getTreeRoot() const { return this->root; };
    int getNum() const { return this->num; };
    void setSetData(SetData data) { this->data = data; };
    void setRoot(TreeRoot* root) { this->root = root; };
    void setNum(int num) { this->num = num; };
private:
    SetData data;
    TreeRoot* root;
    int num;
};

template <class TreeData, class SetData>
class UnionFind {
{
private:
    Tree<TreeData>* treesArr;
    Set<SetData>* setsArr;
public:
    UnionFind() {};

    Set<SetData>* makeSet(int treeIdx, int setIdx, TreeData treeData, SetData setData)
    {
        Set<SetData>* set = new Set<SetData>(setData);
        TreeRoot* root = new TreeRoot(treeData, set);
        set->setTreeRoot(root);
        treesArr[treeIdx] = root;
        setsArr[setIdx] = set;
        return set;
    }

    Set<SetData>* Find(treeIdx)
    {
        Tree* root = treesArr[treeIdx];
        while ((root) && (root->getFather())) {
            root = root->getFather();
        }
        Tree* tree = treesArr[treeIdx];
        while ((root) && (root->getFather())) {
            tree->setFather(root);
        }
        return root->getSet();
    }

    void removeSet(Set<SetData>* set, int setIdx)
    {
        set->setData(NULL);
    }

    void Union(TreeRoot* r1, TreeRoot* r2)
    {
        if (r1 == r2) {
            return;
        }
        if (r1->getNum() > r2->getNum()) {
            r2->setFather(r1);
            removeSet(r2->getSet());
            r2->setSet(nullptr);
        }
        else {
            r1->setFather(r2);
            removeSet(r1->getSet());
            r1->setSet(nullptr);
        }
    }
};

#endif //DS_2_UNIONFIND_H