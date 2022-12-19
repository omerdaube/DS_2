//
// Created by omerd on 23/11/2022.
//

#ifndef AVL_H
#include <memory>
#include <stdio.h>
#include <math.h>

using std::max;
using std::shared_ptr;

template<class Data, class Cond>
class AVL {

protected:
    Data nodeData;
    int nodeHeight;
    AVL* left;
    AVL* right;
    AVL* father;

public:
    AVL() : nodeData(), nodeHeight(0), left(nullptr), right(nullptr), father(nullptr) {
        //printf("g");
    }
    AVL(Data d, AVL* f) : nodeData(d), nodeHeight(0), left(nullptr), right(nullptr), father(f) {}
    explicit AVL(AVL* me) : nodeData(me->nodeData), nodeHeight(me->nodeHeight), left(me->left), right(me->right), father(me->father) {}

    virtual ~AVL() {
        //deleteAll2();
        //delete this;
    }  //V

    void deleteThis(){
        if(left)
            delete left;
        if(right)
            delete right;
    }
    void deleteAll2(){
        if(this == nullptr || nodeData == Data()){
            return;
        }
        left->deleteAll2();
        right->deleteAll2();
        deleteThis();
    }

    void setData(Data d){
        this->nodeData = d;
    }
    AVL* getLeft(){
        return this->left;
    } //v

    AVL* getRight(){
        return this->right;
    } //v

    AVL* getFather(){
        return this->father;
    }

    Data getData(){
        return this->nodeData;
    } //v

    void add(Data data) {
        if (this->nodeData == Data()){
            this->nodeData = data;
            return;
        }
        Cond c;
        if (c(data, this->nodeData, 0)) {
            return;
        }
//        if (Cond(Data(), this->nodeData, 0)()) {
//
//        }
        if (c(this->nodeData, data, 1)) {
            if (!this->left) {
                this->left = new AVL(data, this);
            }
            else {
                this->nodeHeight = this->left->heightCalc() + 1;
                this->left->add(data);
            }
        }
        else {
            if (!this->right) {
                right = new AVL();
                this->right->father = this;
                this->right->nodeData = data;
            } else {
                this->nodeHeight = this->right->heightCalc() + 1;
                this->right->add(data);
            }
        }
        this->rotate(); //for the whole path
    } //V

    int degree() {
        if ((this->left != nullptr) && (this->right != nullptr)) {
            return 2;
        }
        if ((this->left == nullptr) && (this->right == nullptr)) {
            return 0;
        }
        return 1;
    } //V

    int heightCalc() { //V
        if (degree() == -1)
            return -1;
        else if (degree() == 0)
            return 0;
        else if (degree() == 1) {
            if (this->left != nullptr) {
                return this->left->nodeHeight + 1;
            }
            return this->right->nodeHeight + 1;
        }
        return max(this->left->nodeHeight + 1, this->right->nodeHeight + 1);
    } //v

    void remove(Data data){
        Cond c;
        if (this == nullptr) { ////////////////////////////////////
            return; ///////////////////////////////////////////////
        } /////////////////////////////////////////////////////////
        if (c(data, this->nodeData, 0)){
            if(degree() == 0) {
                if (this->father == nullptr){
                    this->nodeData = Data();
                    return;
                }
                if (this->father->left != nullptr && this->father->left == this) {
                    this->father->left = nullptr;
                }
                else {
                    this->father->right = nullptr;
                }
                this->father->nodeHeight = this->father->heightCalc();
                //this->nodeData = Data();
                delete this;
                return;
            }
            else if(degree() == 1){
                if (this->right == nullptr) {
                    AVL *tempL = left->left, *tempR = left->right;
                    this->replaceData(this->left);
                    delete left;
                    left = tempL;
                    right = tempR;
                    this->nodeHeight = heightCalc();
                }
                else{
                    AVL *tempL = right->left, *tempR = right->right;
                    this->replaceData(this->right);
                    delete right;
                    left = tempL;
                    right = tempR;
                    this->nodeHeight = heightCalc();
                }
            }
            else { //2 sons
                AVL *next = getNextInorder();
                this->replaceData(next);
                this->right->remove(data); //pass new path
            }
        } else if (c(this->nodeData, data, 1) && this->left != nullptr) {
            this->left->remove(data);
        } else if (c(data, this->nodeData, 1) && this->right != nullptr){
            this->right->remove(data);
        }

        this->nodeHeight = heightCalc();
        this->rotate(); //for whole path
    } //v

//    void removeFromBinTree(Data data){
//        if(this->degree() == 0){
//            delete this;
//            return;
//        }
//        if(this->degree() == 1){
//            if(this->left != nullptr){
//                if(this->father->right == this){
//                    this->father->right = this->left;
//                    this->left->father = this->father;
//                    delete this;
//                    return;
//                }
//                else{
//                    this->father->left = this->left;
//                    this->left->father = this->father;
//                    delete this;
//                    return;
//                }
//            }
//            else{
//                if(this->father->right == this){
//                    this->father->right = this->right;
//                    this->right->father = this->father;
//                    delete this;
//                    return;
//                }
//                else{
//                    this->father->left = this->right;
//                    this->right->father = this->father;
//                    delete this;
//                    return;
//                }
//            }
//        }
//        AVL* a = this->getNextInorder();
//        replaceData(a);
//        removeFromBinTree(a->nodeData);
//    } //V

//    AVL* getNextInorder(){
//        AVL* curr = this;
//        if(curr->right == nullptr){
//            return nullptr;
//        }
//        curr = curr->right;
//        while(curr->left != nullptr){
//            curr = curr->left;
//        }
//        return curr;
//    } //V

    AVL* getNextInorder() {
        AVL* current = this, *parent;
        if (current->right != nullptr) {
            current = current->right;
            while (current->left) {
                current = current->left;
            }
            return current;
        }
        parent = current->father;
        while (parent != nullptr) {
            if (current == parent->left) {
                break;
            }
            current = parent;
            parent = current->father;
        }
        return parent;
    }

    AVL* getPrevInorder() {
        AVL* current = this, *parent;
        if (current->left != nullptr) {
            current = current->left;
            while (current->right) {
                current = current->right;
            }
            return current;
        }
        parent = current->father;
        while (parent != nullptr) {
            if (current == parent->right) {
                break;
            }
            current = parent;
            parent = current->father;
        }
        return parent;
    }

    int BF(){
        int n1, n2;
        if(this->left == nullptr){
            n1 = -1;
        }
        else{
            n1 = this->left->nodeHeight;
        }
        if(this->right == nullptr){
            n2 = -1;
        }
        else{
            n2 = this->right->nodeHeight;
        }
        return n1 - n2;
    } //V

    void rotate() {
        this->nodeHeight = heightCalc();
        if (abs(this->BF()) <= 1) return;

        if (this->BF() == 2) {
            if (this->left->BF() >= 0)
                LL();
            else
                LR();
        } else {
            if (this->right->BF() <= 0)
                RR();
            else
                RL();
        }
    } //V

    void replaceData(AVL *toReplace) {
        Data tempData = this->nodeData;
        this->nodeData = toReplace->nodeData;
        toReplace->nodeData = tempData;
    } //V

    void LL() {
        AVL * toReplace = this->left;
        if (father) {
            left = toReplace->right;
            if (left) {
                left->father = this;
            }
            if (father->left && father->left == this) { //ch
                father->left = toReplace;
            }
            else {
                father->right = toReplace;
            }
            toReplace->father = father;
            toReplace->right = this;
            father = toReplace;
            nodeHeight = heightCalc();
            toReplace->nodeHeight = toReplace->heightCalc();
        }
        else
        {
            left = toReplace->left;
            toReplace->left->father = this;
            toReplace->left = toReplace->right;
            toReplace->right = right;
            if (right) {
                right->father = toReplace;
            }
            right = toReplace;
            toReplace->replaceData(this);
            father = nullptr;
            toReplace->father = this;
            toReplace->nodeHeight = toReplace->heightCalc();
            nodeHeight = heightCalc();
        }
    }

    void RR() {
        AVL * toReplace = this->right;
        if (father)
        {
            right = toReplace->left;
            if (toReplace->left) {
                toReplace->left->father = this;
            }
            if (father->left && father->left == this) {
                father->left = toReplace;
            }
            else {
                father->right = toReplace;
            }
            toReplace->father = father;
            toReplace->left = this;
            father = toReplace;
            nodeHeight = heightCalc();
            toReplace->nodeHeight = toReplace->heightCalc();
        }
        else
        {
            right = toReplace->right;
            if(toReplace->right){
                toReplace->right->father = this;
            }
            toReplace->right = toReplace->left;
            toReplace->left = left;
            if (left) {
                left->father = toReplace;
            }
            left = toReplace;
            replaceData(toReplace);
            father = nullptr;
            toReplace->father = this;
            toReplace->nodeHeight = toReplace->heightCalc();
            nodeHeight = heightCalc();
        }
    }

    void LR() {
        this->left->RR();
        LL();
    } //V

    void RL() {
        this->right->LL();
        RR();
    } //V

//    AVL* getClosestAndBigger(int i){
//        AVL* a = search(i);
//        if(a != nullptr) {
//            return a;
//        }
//        a = this;
//        while(true){
//            if(a->nodeData < i){
//                if(a->right == nullptr){
//                    break;
//                }
//                a = a->right;
//            }
//            else{
//                if(a->left == nullptr){
//                    break;
//                }
//                a = a->left;
//            }
//        }
//        int j;
//        while(true){
//            if(!a){
//                return nullptr;
//            }
//            j = a->nodeData;
//            if(j < i){
//                a = a->father;
//                i = a->father->nodeData;
//            }
//            return a;
//        }
//    } //need mayan help - c add 4 ->2

    AVL* search(int d)
    {
        Cond c;
        bool chk0 = c(nodeData, d, 0);
        bool chk1 = c(nodeData, d, 1);
        if(chk0) {
            return this;
        }
        else if (chk1 && left) {
            return left->search(d);
        }
        else if (right){
            return right->search(d);
        }
        return nullptr;
    }
    //v
    AVL* searchByData(Data d)
    {
        Cond c;
        bool chk0 = c(nodeData, d, 0);
        bool chk1 = c(nodeData, d, 1);
        if(chk0) {
            return this;
        }
        else if (chk1 && left) {
            return left->searchByData(d);
        }
        else if (right){
            return right->searchByData(d);
        }
        return nullptr;
    }
    //v

    AVL* getMostRight()
    {
        if (this == nullptr) {
            return nullptr;
        }
        if (this->right == nullptr) {
            return this;
        }
        return (this->right)->getMostRight();
    } //v

    void updateHeights(){
        if(!this)
            return;
        this->left->updateHeights();
        this->right->updateHeights();
        this->nodeHeight = this->heightCalc();
    }


    bool isEmpty(){
        Cond c;
        return (c(nodeData, Data(), 0));
    }

    AVL** avlToArr(){
        int n = getSize(this);
        int count = 0;
        int *counter = &count;
        AVL** arr = new AVL*[sizeof(AVL*) * n];
        addToArr(arr, counter);
        return arr;
    }//v

    int getSize(AVL* a){
        Cond c;
        if(a == nullptr || c(a->nodeData, Data(), 0))
            return 0;
        return getSize(a->left) + getSize(a->right) + 1;
    }//v

    void addToArr(AVL** arr, int* counter){
        if(this == nullptr || this->isEmpty())
            return;
        this->left->addToArr(arr, counter);
        AVL* a = new AVL(this);
        arr[*counter] = a;
        *counter += 1;
        this->right->addToArr(arr, counter);
    }//v
};

#endif

