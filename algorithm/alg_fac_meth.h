#ifndef ALG_FACT_H
#define ALG_FACT_H

#include "../data/graph_io.h"
#include "alg.h"
#include "conn_alg.h"

class IALGFM
{
public:
    virtual ~IALGFM(){}
    virtual IAlg* FactoryMethod() = 0;
    virtual std::string ExecuteAlgorithm(Graph_io* g);
};

class BuildConnectedness: public IALGFM{
    public:
        IAlg* FactoryMethod() override{
            return new Connectedness_check();
        }
};

#endif