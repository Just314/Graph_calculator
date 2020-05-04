#ifndef WARSHALL_ALG_H
#define WARSHALL_ALG_H
#include "alg.h"

class WarshallAlgo : public IAlg{
    private:
        Graph* g;
        u_short** adj;
        u_short cardinal;
        int** dijkstra_weights;
        std::vector<int> path;
        int counter;
    public:
        WarshallAlgo(){}
        std::string Calculate();
        void Initialize(Graph* g);

};

#endif