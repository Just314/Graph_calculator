#include "dijkstra.h"
using namespace std;
int INF = INT_MAX;

void DijkstraAlgo::Initialize(Graph* g_in){
    //Getting input graph 
    g = g_in;

    //Getting its weighted adjacency matrix and the number of vertices
    adj = g->MatrixWeighted();
    cardinal = g->getVertCount();

    //Counter of vertices in path and their order
    counter = 0;
}

std::string DijkstraAlgo::Calculate(){
    //Checking whether graph given is weighted
    if(!g->hasVW()) return "Bad input. Please enter weighted graph.\n";

    //String returned as an answer
    string Shortestlength = "The shortest path is:";

    int init, end;
    //Initialising matrix of vertice labels to INF (defined as 2^31-1) or to zero if i = j
    int dijkstra_weights[cardinal][cardinal];
    for (int i = 0; i < cardinal; i++) {
        for (int j = 0; j < cardinal; j++) {
            if (i != j) dijkstra_weights[i][j] = INF;
            else dijkstra_weights[i][j] = 0;
        }
    }

    //Boolean array to mark visited vertices. Initially it is zero
    bool visited[cardinal];
    memset(visited, false, sizeof(visited));

    //Getting from user initial and final vertices of path
    cout << "Enter number of edges between which path is needed to be found:\n";
    cin >> init >> end;
    init--;
    end--;

    //Until final vertex is not visited graph is traversed and labels are updated
    while (!visited[end]) {

        /*Here algorithm finds vertex with minimal label 
        (where label is the distance from initial vertex to it)
        and adds it to vector path which contains vertices of shortest path and marks it as visited*/
        int min_index;
        int MIN = INF;        
        for (int i = 0; i < cardinal; i++) {
            if (!visited[i] && dijkstra_weights[init][i] <= MIN) {
                MIN = dijkstra_weights[init][i];
                min_index = i;
            }   
        }
        visited[min_index] = true;
        path.insert(path.begin()+counter, min_index);

        /*Here algorithm updates labels of vertices changing
        them to minimal paths from initial vertex.*/
        for (int i = 0; i < cardinal; i++) {
            if (!visited[i] && adj[min_index][i] && dijkstra_weights[init][min_index] != INF && dijkstra_weights[init][min_index] + adj[min_index][i] < dijkstra_weights[init][i]) {
                dijkstra_weights[init][i] = dijkstra_weights[init][min_index] + adj[min_index][i];
                dijkstra_weights[i][init] = dijkstra_weights[init][i];
            }
        }

        //Incrreasing counter of the vertices in path
        counter++;
    }

    /*If label of final vertex is not 2^31-1, there exists path to this vertex 
    and algorithm updates the answer string and prints path and its length*/ 
    if (dijkstra_weights[init][end] != INF) {
        for (int i = 0; i < counter; i++) {
            Shortestlength = Shortestlength + " " + to_string(path[i]+1);
        }
        Shortestlength = Shortestlength + ". Its length is " + to_string(dijkstra_weights[init][end]) + "\n";
    }
    else {
        Shortestlength = "Path does not exist.\n";
    }
    return Shortestlength;
}