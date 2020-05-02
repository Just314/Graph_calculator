#ifndef EULER_ALG_H
#define EULER_ALG_H
#include "alg.h"

class EulerAlgo : public IAlg{
    private:
        Graph* g;

    public:
        EulerAlgo(){}
        std::string Calculate();
        void Initialize(Graph* g);
};
#endif