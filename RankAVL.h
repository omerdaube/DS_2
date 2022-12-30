//
// Created by omerd on 23/11/2022.
//

#ifndef RankAVL_H
#include <memory>
#include <stdio.h>
#include <math.h>

using std::max;
using std::shared_ptr;

template<class Data, class Cond>
class RankAVL {

protected:
    Data nodeData;
    int nodeHeight;
    int w;
    RankAVL* left;
    RankAVL* right;
    RankAVL* father;

public:
    RankAVL() : nodeData(), nodeHeight(0), w(0), left(nullptr), right(nullptr), father(nullptr) {
        //printf("g");
    }
    RankAVL(Data d, RankAVL* f) : nodeData(d), nodeHeight(0), w(1), left(nullptr), right(nullptr), father(f) {}
    explicit RankAVL(RankAVL* me) : nodeData(me->nodeData), nodeHeight(me->nodeHeight), w(me->w), left(me->left), right(me->right), father(me->father) {}

    virtual ~RankAVL() {
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
        if(this == nullptr || nodeData == NULL){
            return;
        }
        left->deleteAll2();
        right->deleteAll2();
        deleteThis();
    }

    Data select(int k){
        if(this == nullptr){
            return Data();
        }
        int checkWleft = 0;
        if(this->left != nullptr){
            checkWleft = this->left->w;
        }
        if(checkWleft == k-1){
            return this->nodeData;
        }
        if(checkWleft > k-1){
            return this->left->select(k);
        }
        else{
            return this->right->select(k - checkWleft - 1);
        }

    }
    void setData(Data d){
        this->nodeData = d;
    }
    RankAVL* getLeft(){
        return this->left;
    } //v

    RankAVL* getRight(){
        return this->right;
    } //v

    RankAVL* getFather(){
        return this->father;
    }

    Data getData(){
        return this->nodeData;
    } //v

    void add(Data data) {
        if (this->nodeData == NULL){
            this->nodeData = data;
            this->w = 1;
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
                this->left = new RankAVL(data, this);

            }
            else {
                this->nodeHeight = this->left->heightCalc() + 1;
                this->left->add(data);
            }
        }
        else {
            if (!this->right) {
                right = new RankAVL(data, this);

            } else {
                this->nodeHeight = this->right->heightCalc() + 1;
                this->right->add(data);
            }
        }
        int sumW = 1;
        if(this->left != nullptr){
            sumW += left->w;
        }
        if(this->right != nullptr){
            sumW += right->w;
        }
        this->w = sumW;
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
                    this->w = 0;
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
                    RankAVL *tempL = left->left, *tempR = left->right;
                    this->replaceData(this->left);
                    delete left;
                    left = tempL;
                    right = tempR;
                    this->nodeHeight = heightCalc();
                }
                else{
                    RankAVL *tempL = right->left, *tempR = right->right;
                    this->replaceData(this->right);
                    delete right;
                    left = tempL;
                    right = tempR;
                    this->nodeHeight = heightCalc();
                }
            }
            else { //2 sons
                RankAVL *next = getNextInorder();
                this->replaceData(next);
                this->right->remove(data); //pass new path
            }
        } else if (c(this->nodeData, data, 1) && this->left != nullptr) {
            this->left->remove(data);
        } else if (c(data, this->nodeData, 1) && this->right != nullptr){
            this->right->remove(data);
        }
        int sumW = 1;
        if(this->left != nullptr){
            sumW += left->w;
        }
        if(this->right != nullptr){
            sumW += right->w;
        }
        this->w = sumW;
        this->nodeHeight = heightCalc();
        this->rotate(); //for whole path
    } //v

    RankAVL* getNextInorder() {
        RankAVL* current = this, *parent;
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

    RankAVL* getPrevInorder() {
        RankAVL* current = this, *parent;
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
            if (this->left->BF() >= 0) {
                LL();
                //printf("LL%d ", this->nodeData);
                if(right != nullptr) {
                    calcW(right);
                }
                if(left != nullptr) {
                    calcW(left);
                }
                calcW(this);
                if(father != nullptr) {
                    calcW(father);
                }
            }
            else {
                LR();
                if(right != nullptr) {
                    calcW(right);
                }
                if(left != nullptr) {
                    calcW(left);
                }
                //printf("LR%d ", this->nodeData);
                calcW(this);
                if(father != nullptr) {
                    calcW(this->father->left);
                }
                calcW(this->father);
            }
        } else {
            if (this->right->BF() <= 0) {
                RR();
                //printf("RR%d ", this->nodeData);
                if(right != nullptr) {
                    calcW(right);
                }
                if(left != nullptr) {
                    calcW(left);
                }
                calcW(this);
                if(father != nullptr) {
                    calcW(father);
                }
            }
            else {
                RL();
                if(right != nullptr) {
                    calcW(right);
                }
                if(left != nullptr) {
                    calcW(left);
                }
                //printf("RL%d ", this->nodeData);
                calcW(this);
                if(father!= nullptr){
                    calcW(this->father->right);
                }
                calcW(this->father);
            }
        }
    } //V

    void calcW(RankAVL *calc){
        if(calc == nullptr){
            return;
        }
        int sumW = 1;
        if(calc->left != nullptr){
            sumW += calc->left->w;
        }
        if(calc->right != nullptr){
            sumW += calc->right->w;
        }
        calc->w = sumW;
    }

    void replaceData(RankAVL *toReplace) {
        Data tempData = this->nodeData;
        this->nodeData = toReplace->nodeData;
        toReplace->nodeData = tempData;
    } //V

    void LL() {
        RankAVL * toReplace = this->left;
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
        RankAVL * toReplace = this->right;
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

//    RankAVL* getClosestAndBigger(int i){
//        RankAVL* a = search(i);
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

    RankAVL* search(int d)
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
    RankAVL* searchByData(Data d)
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

    RankAVL* getMostRight()
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
};

#endif

