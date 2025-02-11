#ifndef ALG_FACT_H
#define ALG_FACT_H

#include "../data/graph_io.h"
#include "alg.h"
#include "conn_alg.h"
#include "euler.h"
#include "dijkstra.h"
#include "hamilton.h"

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

class CheckEuler: public IALGFM{
    public:
    IAlg* FactoryMethod() override{
        return new EulerAlgo();
    }
};


class ShortestPath: public IALGFM{
    public:
    IAlg* FactoryMethod() override{
        return new DijkstraAlgo();
    }
};

class Hamiltonian: public IALGFM{
    public:
    IAlg* FactoryMethod() override{
        return new HamiltonAlgo();
    }
};

#endif


/////INterface principle flow chart///////////
/*
    Algo1----\
    Algo2  ----IAlg interface ---- IALGFM (IAlg Factory method) 
    Algo3----/                        |
    .....                             |
    .                             /   |   \
    .                           /     |     \
    .                       FM1      FM2     FM3
    .                         \       |       /
    .                            \    |    /
    .                         IALGFM alg = new FM#
    .                                 |
    .                      alg.Execute method for all FM 
    .
*/