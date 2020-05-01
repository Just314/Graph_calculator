#ifndef ALG_H
#define ALG_H
#include <bits/stdc++.h>
#include "../data/graph.h"
#include "alg.h"

class Connectedness_check : public IAlg{
    private:
        Graph *g;
        u_short cardinal;
        std::vector<bool> visited;
    public:
        Connectedness_check(){}
        std::string Calculate();
        void Initialize(Graph* g);
        void Depth_Fist_Search(u_short s);
};


#endif