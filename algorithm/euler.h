#ifndef EULER_ALG_H
#define EULER_ALG_H
#include "alg.h"

class EulerAlgo : public IAlg{
    private:
        Graph* g;
        std::vector<std::vector<u_short>> adjacencylistout;        
        std::vector<std::vector<u_short>> adjacencylistinto;
        u_short cardinality;
        bool transpose;
    public:
        EulerAlgo(){}
        std::string Calculate();
        void Initialize(Graph* g);
        bool HasEulerianCycle();
        bool ISConnected();
        void DFS(u_short nonzero, bool *was);
        void DFSTranspose(u_short nonzero, bool *was);
        void Transpose();
};
#endif