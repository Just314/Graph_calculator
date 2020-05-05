#include "conn_alg.h"
using namespace std; 


//Here algorithm traverses graph ignoring directions and counts the number of vertices which are somehow connected.
void Connectedness_check::Depth_Fist_SearchUnderlying(u_short s) {
    //Checking whether vertex was visited before
    if (visitedOut[s]) return;

    //Increasing counter of visited vertices
    counterUnd++;

    //<arking current vertice as visited 
    visitedOut[s] = true; 
    visitedIn[s] = true;

    for (u_short u = 0; u < cardinal; u++) { 

        //Algorithm checks whether there is either an edge from vertex s to vertex u or edge from u to s.
        //If it is able to find such an edge, vertex u is proceeded. 
        //If no such vertex if found, it means that no vertex is proceeded and algorithm returns to main part.
        if (adjacency[s][u] > 0) { 
    	    Depth_Fist_SearchUnderlying(u);
        }
        else if (adjacency[u][s] > 0) {
    	    Depth_Fist_SearchUnderlying(u);
        }
    }
}


/*Here algorithm traverses graph by its outer directed edges.
It counts the number of vertices to which it is possible to enter starting from the first.
Logic is exactly the same as in an underlying traversal, 
except that now vertex is proceeded if and only there is and edge to it from current vertex */
void Connectedness_check::Depth_Fist_SearchOut(u_short s) {
    if (visitedOut[s]) return;
    counterOut++;
    visitedOut[s] = true;
    for (u_short u = 0; u < cardinal; u++) {
        if (adjacency[s][u] > 0) {
    	    Depth_Fist_SearchOut(u);
        }
    }
}

/*Here traverses transpose of graph (it into directed edges).
it counts the number of vertices from which it is possible to enter the first vertex.
Vertex is proceeded if and only there is and edge from it to the current vertex */
void Connectedness_check::Depth_Fist_SearchIn(u_short s) {
    if (visitedIn[s]) return;
    counterIn++;
    visitedIn[s] = true;
    for (u_short u = 0; u < cardinal; u++) {
        if (adjacency[u][s] > 0) {
    	    Depth_Fist_SearchIn(u);
        }
    }
}

void Connectedness_check::Initialize(Graph* g_in){
    //Getting input graph
    this->g = g_in;

    //The number of vertices in graph (cardinality of its vertices set)
    cardinal =  g->getVertCount();

    //Counters for visited vertices
    counterOut = 0;
    counterIn = 0;
    counterUnd = 0;

    //Getting adjacency matrix of graph
    adjacency = g->Matrix();
   
    //Dynamic arrays to track visited vertices
    visitedOut.assign(cardinal, false);
    visitedIn.assign(cardinal, false);
}

string Connectedness_check::Calculate() {
    //String that is returned by algorithm as an answer
    string Is_Connected;
    
    //Proceeding traversal of underlying graph
    Depth_Fist_SearchUnderlying(0);
    
    /*If the number of vertices visited in traversal of underlying graph is equal 
    to the number of vertices in graph, graph is weakly connected and algorithm proceeds. 
    Otherwise graph is not connected.*/
    if (counterUnd == cardinal) {
        //Reassigning arrays of visited vertices
        visitedIn.assign(cardinal, false);    
        visitedOut.assign(cardinal, false);
        
        //Proceeding traversals of leaving and entering edges
        Depth_Fist_SearchOut(0);
        Depth_Fist_SearchIn(0);

        weakly_connected = true; 
        Is_Connected = "Graph is weakly connected.\n";
        /*If all traversals give the same resulst graph is strongly connected.*/
        if (counterOut == cardinal && counterIn == cardinal) {
            strongly_connected = true;
            Is_Connected = "Graph is connected.\n";
        }
    }
    else {
        Is_Connected = "Graph is not connected.\n";
    }
    return Is_Connected;
}