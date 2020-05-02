#ifndef ALG_H
#define ALG_H

#include "alg.h"

class Connectedness_check : public IAlg{
    private:
        Graph *g;
        u_short cardinal;
        std::vector<bool> visitedOut;
        u_short counterOut;
        std::vector<bool> visitedIn;
        u_short counterIn;
        bool strongly_connected;
        bool weakly_connected;
        
    public:
        Connectedness_check(){}
        std::string Calculate();
        void Initialize(Graph* g);
        void Depth_Fist_SearchOut(u_short s);
        void Depth_Fist_SearchIn(u_short s);
        bool Is_Strongly_Connected() {return strongly_connected;}
        bool Is_Weakly_Connected() {return weakly_connected;}
};


#endif