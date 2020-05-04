#ifndef WARSHALL_ALG_H
#define WARSHALL_ALG_H
#include "alg.h"

class WarshallAlgo : public IAlg{
    private:
        Graph* g;
        u_short** adj;
        u_short cardinal;;
    public:
        WarshallAlgo(){}
        std::string Calculate();
        void Initialize(Graph* g);
};

#endif