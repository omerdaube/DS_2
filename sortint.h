//
// Created by omerd on 18/12/2022.
//

#ifndef DS_2_SORTINT_H
#define DS_2_SORTINT_H


class sortint {
public:
    bool operator() (int i, int j, int x){
        if(x == 0)
            return i==j;
        if(x==1)
            return i>j;
        return false;
    }
};


#endif //DS_2_SORTINT_H
