#include <bits/stdc++.h> 
#include "conn_alg.h"

using namespace std; 
int n, a, counter = 0;
vector <int> adj[101];
bool visited[101];

void dfs(int s) {
    if (visited[s]) return;
    counter++;
    visited[s] = true;
    for (auto u: adj[s]) {
    	dfs(u);
    }
}


void Connectedness_check::Calculate() {
    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> a;
                if (a >= 1 && i != j) {
                    adj[i].push_back(j);
                }
            }
        }
        dfs(1);
        if (counter == n) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
        memset(visited, false, sizeof visited);
        memset(adj, 0,sizeof adj);
    }
}