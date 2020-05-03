#include "euler.h"
using namespace std;


void EulerAlgo::Initialize(Graph* g_in){
    g = g_in;
    cardinality = g->getVertCount();
    adjac = g->Matrix();
}

std::string EulerAlgo::Calculate(){
    string ISEulerian;
    vector <vector <u_short>> adjacency;
    for (u_short i = 0; i < cardinality; i++) {
        vector <u_short> temp;
        for (u_short j = 0; j < cardinality; j++) {
            temp.insert(temp.begin()+j, adjac[i][j]);
        }
        adjacency.insert(adjacency.begin()+i, temp);
    }
    vector <u_short> deg (cardinality);
    for (u_short i=0; i < cardinality; ++i) {
        for (u_short j = 0; j < cardinality; ++j) {
            deg[i] += adjacency[i][j];
        }
    }
    u_short first = 0;
    while (!deg[first]) {
        ++first;
    }
    int v1 = -1, v2 = -1;
    bool bad = false;
    for (u_short i = 0; i < cardinality; ++i) {
        if (deg[i] & 1) {
            if (v1 == -1) {
                v1 = i;
            }
            else if (v2 == -1) {
                v2 = i;
            }
            else {
                bad = true;
            }
        }
    }
    vector<u_short> res;
    if (!bad) {
        if (v1 != -1) {
            ++adjacency[v1][v2];
            ++adjacency[v2][v1];
        }
	    stack<u_short> st;
	    st.push (first);
        while (!st.empty()) {
		    u_short v = st.top();
		    u_short i;
		    for (i=0; i < cardinality; ++i) {
                if (adjacency[v][i]){
                    break;
                }
            }
		    if (i == cardinality) {
			    res.push_back (v);
			    st.pop();
		    }
		    else {
			    --adjacency[v][i];
			    --adjacency[i][v];
			    st.push (i);
		    }
	    }
        if (v1 != -1) {
            for (size_t i=0; i+1<res.size(); ++i) {
                if (res[i] == v1 && res[i+1] == v2 || res[i] == v2 && res[i+1] == v1) {
				    vector<u_short> res2;
				    for (size_t j=i+1; j<res.size(); ++j)
					    res2.push_back (res[j]);
				    for (size_t j=1; j<=i; ++j)
					    res2.push_back (res[j]);
				    res = res2;
				    break;
			    }
            }
        }
        for (u_short i = 0; i < cardinality; ++i)
		    for (int j = 0; j < cardinality; ++j)
			    if (adjacency[i][j])
				    bad = true;
    }
    if (bad) {
		ISEulerian = "Graph is not Eulerian";
    }
	else {
        ISEulerian = "Graph is Semi-Eulerian. Path is: ";
        for (size_t i=0; i<res.size(); ++i) {
            if (res.front() == res.back()) ISEulerian = "Graph is Eulerian. Circuit is: ";
            ISEulerian += to_string(res[i]+1);
            ISEulerian += " ";
        }
        ISEulerian += "\n";
    }

    return ISEulerian;
}