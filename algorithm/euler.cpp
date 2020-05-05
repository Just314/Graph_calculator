#include "euler.h"
using namespace std;


void EulerAlgo::Initialize(Graph* g_in){
    //Getting input graph
    g = g_in;

    //The number of vertices in the graph and its adjacency matrix
    cardinality = g->getVertCount();
    adjac = g->Matrix();
}

std::string EulerAlgo::Calculate(){
    //String returned by algorithm as an answer
    string ISEulerian;

    //Adjacency matrix is transformed into dynamic array to work with it
    vector <vector <u_short>> adjacency;
    for (u_short i = 0; i < cardinality; i++) {
        vector <u_short> temp;
        for (u_short j = 0; j < cardinality; j++) {
            temp.insert(temp.begin()+j, adjac[i][j]);
        }
        adjacency.insert(adjacency.begin()+i, temp);
    }

    //Dynamic array of vertices degrees
    vector <u_short> deg (cardinality);
    for (u_short i=0; i < cardinality; ++i) {
        for (u_short j = 0; j < cardinality; ++j) {
            deg[i] += adjacency[i][j];
        }
    }

    //Finding first vertices with non-zero degree
    u_short first = 0;
    while (!deg[first]) {
        ++first;
    }

    //Special flags for tracking whether vertices with odd degrees were met.
    int v1 = -1, v2 = -1;
    bool bad = false;

    //Checking for odd vertices
    for (u_short i = 0; i < cardinality; ++i) {
        if (deg[i] & 1) {
            if (v1 == -1) {
                v1 = i;
            }
            else if (v2 == -1) {
                v2 = i;
            }

            /*If this command is executed, it means that graph contains more 
            than two vertices of odd degree and hence it does not have neither Eulerian cycle, nor path*/
            else {
                bad = true;
            }
        }
    }

    //Dynamic array for storing vertices of path
    vector<u_short> res;
    if (!bad) {
        /*If v1 is not equal to -1 it means that vertices v1 and v2 are odd,
        so it is needed to create an imaginary edge between them to make graph Eulerian.*/
        if (v1 != -1) {
            ++adjacency[v1][v2];
            ++adjacency[v2][v1];
        }

        
        //Stack for tracking current vertex and vertices proceeded. At the beginning first vertex with nonzero degree is added.
	    stack<u_short> st;
	    st.push (first);


        while (!st.empty()) {
		    u_short v = st.top();
		    u_short i;
		    for (i=0; i < cardinality; ++i) {
                //if there is at least edge between vertices v and i, algorithm proceeds this pair of edges
                if (adjacency[v][i]){
                    break;
                }
            }
            //If i becomes equal to the number of vertices, it means that degree of vertex v is zero and it can be added to an answer
		    if (i == cardinality) {
			    res.push_back (v);
			    st.pop();
		    }

            //Otherwise, an edge between vertices v and i is removed and vertice i is added to stack.
		    else {
			    --adjacency[v][i];
			    --adjacency[i][v];
			    st.push (i);
		    }
	    }


        /*If v1 is not -1, it means that, vector res contains extra edge which is created 
        to make graph Eulerian. Hence it should deleted by copying the res vector into res2 vector and 
        then by removing  extra edge.*/
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
        //Here algorithm checks wheter all edges are visited. If some edge is still not visited. 
        //If graph contains several connected components, algorithm detects it.
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
        //If the first and last elements of res vector are equal, it means that path is also an cycle
        if (res[0] == res[res.size()-1]) ISEulerian = "Graph is Eulerian. Circuit is: ";
        for (size_t i=0; i<res.size(); ++i) {
            ISEulerian += to_string(res[i]+1);
            ISEulerian += " ";
        }
        ISEulerian += "\n";
    }

    return ISEulerian;
}