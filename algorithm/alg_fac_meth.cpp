#include "alg_fac_meth.h"

using namespace std;

string IALGFM::ExecuteAlgorithm(Graph_io* g){

    IAlg* alg = this->FactoryMethod();
    
    alg->Initialize(g->Read());
    alg->Calculate();

}