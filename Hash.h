//
// Created by omerd on 18/12/2022.
//

#ifndef DS_2_HASH_H
#define DS_2_HASH_H
#include "AVL.h"

template<class Data, class Cond>
class Hash {
private:
    int currentSize;
    int maxSize;
    AVL<Data, Cond> ** array;
    int (*getID)(Data);
public:
    Hash(int (*getID)(Data)) : currentSize(), maxSize(2), array(new AVL<Data, Cond>*[maxSize]), getID(getID)
    {
        for (int i = 0; i < maxSize; ++i) {
            array[i] = new AVL<Data, Cond>();
        }
    }
    void add(Data toAdd){
        AVL<Data,Cond>* p = static_cast<AVL<Data,Cond>*>(array[h(getID(toAdd))]);
        p->add(toAdd);
        currentSize++;
        if(currentSize >= maxSize){
            enlarge();
        }
    }
    AVL<Data, Cond> ** getArray(){
        return array;
    }

    int getSize(){
        return maxSize;
    }
//    void remove(Data toAdd){
//        AVL<Data,Cond>* p = static_cast<AVL<Data,Cond>*>(array[h(getID(toAdd))]);
//        p->remove(toAdd);
//        currentSize--;
//    }

    ~Hash(){
        for (int i = 0; i < maxSize; ++i) {
            static_cast<AVL<Data,Cond>*>(array[i])->deleteAll2();
            delete array[i];
        }
        delete[] array;
    }

    Data find(int id){
        AVL<Data,Cond>* p = static_cast<AVL<Data,Cond>*>(array[h(id)])->search(id);
        if(p != nullptr){
            return p->getData();
        }
        return Data();
    }

    void enlarge(){ //mem chk
        maxSize *= 2;
        AVL<Data, Cond> ** newAVL = new AVL<Data, Cond>*[maxSize]; //need to add: reset at first like in c`tor
        for (int i = 0; i < maxSize; ++i) {
            newAVL[i] = new AVL<Data, Cond>();
        }
        for (int i = 0; i < maxSize / 2; ++i) {
            AVL<Data, Cond>** a = static_cast<AVL<Data, Cond>*>(array[i])->avlToArr();
            int s = static_cast<AVL<Data, Cond>*>(array[i])->getSize(array[i]);
            for (int j = 0; j < s; ++j) {
                static_cast<AVL<Data, Cond>*>(newAVL[h(getID(static_cast<AVL<Data, Cond>*>(a[j])->getData()))])->add(static_cast<AVL<Data, Cond>*>(a[j])->getData());
                delete a[j];
            }
            delete[] a;
        }
        for (int i = 0; i < maxSize/2; ++i) {
            static_cast<AVL<Data,Cond>*>(array[i])->deleteAll2();
            delete array[i];
        }
        delete[] array;
        array = newAVL;
    }

    int h(int x){
        return x % maxSize;
    }
};


#endif //DS_2_HASH_H
