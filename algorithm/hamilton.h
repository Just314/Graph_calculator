#ifndef HAMILTON_ALG_H
#define HAMILTON_ALG_H
#include "alg.h"

class HamiltonAlgo : public IAlg{
    private:
        Graph* g;
        u_short **adjac;
        u_short cardinality;
        std::vector<bool> visited;
        std::vector<u_short> path;
        bool ispath;
    public:
        HamiltonAlgo(){}
        std::string Calculate();
        void Initialize(Graph* g);
        bool Hamilton(u_short current);
};

#endif