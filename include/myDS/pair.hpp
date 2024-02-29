#ifndef PAIR_H
#define PAIR_H

#include <iostream>

namespace azh
{
    template<class T1,class T2=T1>
    class Pair
    {
        public:
            T1 first;
            T2 second;

            Pair() {  }
            Pair(const T1& v1,const T2& v2): first(v1), second(v2) {  }
            Pair(const Pair& pair): first(pair.first), second(pair.second) {  }
    };
};

#endif /* PAIR_H */