#ifndef ALG_BASIS_H
#define ALG_BASIS_H

class IAlg
{   
public:
   virtual ~IAlg(){}
   virtual std::string Calculate() = 0;
   virtual void Initialize(Graph* g) = 0;
};

#endif