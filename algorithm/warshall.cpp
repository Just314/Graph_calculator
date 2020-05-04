#include "warshall.h"
using namespace std;

void WarshallAlgo::Initialize(Graph* g_in){
    g = g_in;
    adj = g->MatrixWeighted();
    cardinal = g->getVertCount();
}

std::string WarshallAlgo::Calculate(){
    string Shortestlength;
    int a, b;
    int INF = 65535;
    cout << "Enter number of edges between which path is needed to be found:\n";
    cin >> a >> b;
    a--;
    b--;
    int dist[cardinal][cardinal];
    for (int i = 0; i < cardinal; i++) {
        for (int j = 0; j < cardinal; j++) {
            if (i == j) dist[i][j] = 0;
            else if (adj[i][j]) dist[i][j] = adj[i][j];
            else dist[i][j] = INF;
        }   
    }
    for (int k = 0; k < cardinal; k++) {
        for (int i = 0; i < cardinal; i++) {
            for (int j = 0; j < cardinal; j++) {
                dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
    Shortestlength = to_string(dist[a][b]);
    return Shortestlength;
}