#include <iostream>
#include <queue>
#include "listgraph.h"
using namespace std;

#define INFTY -1

int * bfs(listgraph * g, int s, int * &p);

int main() {

    int n = 4, m = 4;
    int * par;
    listgraph mappa = listgraph(n, m);


    /*
    mappa.linkWeightedSegment(0, 1, 5);
    mappa.linkWeightedSegment(0, 2, 1);
    mappa.linkWeightedSegment(1, 2, 6);
    mappa.linkWeightedSegment(2, 3, 1);
    mappa.linkWeightedSegment(1, 3, 3);
    mappa.linkWeightedSegment(1, 5, 6);
    mappa.linkWeightedSegment(3, 4, 1);
    mappa.linkWeightedSegment(4, 5, 1);
    */

    mappa.linkWeightedSegment(0, 1, 1000);
    mappa.linkWeightedSegment(0, 2, 1000);
    mappa.linkWeightedSegment(0, 3, 1);
    mappa.linkWeightedSegment(3, 1, 1);

    int * distanze = bfs(&mappa, 0, par);
    cout << "distanze minime da 0: ";
    for (int i = 0; i < n; i++) {
        cout << distanze[i] << " ";
    }
    cout << endl;

    cout << "provenienza: ";
    for (int i = 0; i < n; i++) {
        cout << par[i] << " ";
    }
    cout << endl;

    cout << "percorso piu' corto per arrivare da 0 a " << n - 1 << ": ";
    for (int j = n - 1; j != 0; j = par[j]) {
        cout << j << " ";
    }
    cout << " 0" << endl;

    delete [] distanze;
    delete [] par;

    return 0;
}

int * bfs(listgraph * g, int s, int * &p)
{
    int n = g->size();
    int x;
    node * t;

    // visit queue
    queue<int> q;

    // distance and parent vectors
    int * distance = new int[n];
    int * parent = new int[n];

    for (int i = 0; i < n; i++) {
        distance[i] = INFTY;
        parent[i] = INFTY;
    }

    distance[s] = 0;
    q.push(s);

    while (!q.empty()) {

        x = q.front(); q.pop();

        // for each node which is adjacent to x...
        for (t = g->adjacentNodes(x)->getHead(); !t->empty(); t = t->next) {
            if (distance[t->id] == INFTY) {
                distance[t->id] = distance[x] + t->weight;
                parent[t->id] = x;
                q.push(t->id);
            } else if (distance[t->id] > distance[x] + t->weight) {
                distance[t->id] = distance[x] + t->weight;
                parent[t->id] = x;
            }
        }
    }

    p = parent;
    return distance;
}