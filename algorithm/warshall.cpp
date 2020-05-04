#include "warshall.h"
using namespace std;
int INF = INT_MAX;

void WarshallAlgo::Initialize(Graph* g_in){
    g = g_in;
    adj = g->MatrixWeighted();
    cardinal = g->getVertCount();
    
    counter = 0;
}

std::string WarshallAlgo::Calculate(){
    string Shortestlength = "The shortest path is: ";
    int init, end;
    int dijkstra_weights[cardinal][cardinal];
    for (int i = 0; i < cardinal; i++) {
        for (int j = 0; j < cardinal; j++) {
            if (i != j) dijkstra_weights[i][j] = INF;
            else dijkstra_weights[i][j] = 0;
        }
    }
    bool visited[cardinal];
    memset(visited, false, sizeof(visited));
    cout << "Enter number of edges between which path is needed to be found:\n";
    cin >> init >> end;
    init--;
    end--;
    while (!visited[end]) {
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
        for (int i = 0; i < cardinal; i++) {
            if (!visited[i] && adj[min_index][i] && dijkstra_weights[init][min_index] != INF && dijkstra_weights[init][min_index] + adj[min_index][i] < dijkstra_weights[init][i]) {
                dijkstra_weights[init][i] = dijkstra_weights[init][min_index] + adj[min_index][i];
                dijkstra_weights[i][init] = dijkstra_weights[init][i];
            }
        }
        counter++;
    }
    for (int i = 0; i < counter; i++) {
        Shortestlength = Shortestlength + " " + to_string(path[i]+1);
    }
    Shortestlength = Shortestlength + ". Its length is " + to_string(dijkstra_weights[init][end]) + "\n";
    return Shortestlength;
}