//
// Created by mayan on 18-Dec-22.
//

#ifndef DS_2_UNIONFIND_H
#define DS_2_UNIONFIND_H

template <class TreeData, class SetData>
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
    TreeData data;
    Tree* father;
};

template <class TreeData, class SetData>
class TreeRoot:Tree<TreeData> {
public:
    TreeRoot(TreeData data, Set<TreeData, SetData>* set) : Tree<TreeData>(data, nullptr), set(set) {};
    Set<TreeData, SetData>* getSet() const { return this->set; };
    void setSet(Set<TreeData, SetData>* set) { this->set= set; };
private:
    Set<TreeData, SetData>* set;
};

template <class TreeData, class SetData>
class Set{
public:
    Set(SetData data) : data(data), root(nullptr), num(1){};
    SetData getSetData() const { return this->data; };
    TreeRoot<TreeData, SetData>* getTreeRoot() const { return this->root; };
    int getNum() const { return this->num; };
    void setSetData(SetData data) { this->data = data; };
    void setTreeRoot(TreeRoot<TreeData, SetData>* root) { this->root = root; };
    void setNum(int num) { this->num = num; };
private:
    SetData data;
    TreeRoot<TreeData, SetData>* root;
    int num;
};

template <class TreeData, class SetData>
class UnionFind {
private:
    Tree<TreeData>* treesArr;
    Set<TreeData, SetData>* setsArr;
public:
    UnionFind() {};

    TreeRoot<TreeData, SetData>* makeSet(int treeIdx, int setIdx, TreeData treeData, SetData setData)
    {
        Set<TreeData, SetData>* set = new Set<TreeData, SetData>(setData);
        TreeRoot<TreeData, SetData>* root = new TreeRoot(treeData, set);
        set->setTreeRoot(root);
        treesArr[treeIdx] = root;
        setsArr[setIdx] = set;
        return root;
    }

    Set<TreeData, SetData>* Find(int treeIdx)
    {
        Tree<TreeData>* root = treesArr[treeIdx];
        while ((root) && (root->getFather())) {
            root = root->getFather();
        }
        Tree<TreeData>* tree = treesArr[treeIdx];
        while ((root) && (root->getFather())) {
            tree->setFather(root);
        }
        return root->getSet();
    }

    void removeSet(Set<TreeData, SetData>* set, int setIdx)
    {
        set->setData(nullptr);                          //////////////////////////////////////////////////////////////
    }

    void Union(TreeRoot<TreeData, SetData>* r1, TreeRoot<TreeData, SetData>* r2)
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