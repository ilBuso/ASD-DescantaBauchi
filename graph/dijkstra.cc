#include <iostream>
#include <fstream>
#include <queue>
#include "listgraph.h"
using namespace std;

#define INFTY -1

ifstream in("input.txt");
ofstream out("output.txt");

void bfs(listgraph * g, int s, int * &distances, int * &parents);
void printShortestPath(int * parents, int j, int R);

int main() {

    int C, S, a, b, w, M;

    in >> C >> S;

    listgraph map = listgraph(C, S);

    for (int i = 0; i < S; i++) {
        in >> a >> b >> w;
        map.linkWeightedSegment(a, b, w);
    }

    in >> M;
    bool * captured = new bool[C];
    for (int i = 0; i < C; i++) {
        captured[i] = false;
    }

    for (int i = 0; i < M; i++) {
        in >> w;
        captured[w] = true;
    }



    int * p;
    int * d;
    bfs(&map, 0, d, p);

    printShortestPath(p, C - 1, 1);

    delete [] d;
    delete [] p;
    delete [] captured;

    return 0;
}

void printShortestPath(int * parents, int j, int R)
{
    if (j == 0) {
        out << R << endl << j << " ";
    } else {
        printShortestPath(parents, parents[j], R + 1);
        out << j << " ";
    }
}

void bfs(listgraph * g, int s, int * &distances, int * &parents)
{
    int n = g->size();
    int x;
    node * t;

    // visit queue
    queue<int> q;

    // distance and parent vectors
    distances = new int[n];
    parents = new int[n];

    for (int i = 0; i < n; i++) {
        distances[i] = INFTY;
        parents[i] = INFTY;
    }

    distances[s] = 0;
    q.push(s);

    while (!q.empty()) {

        x = q.front(); q.pop();

        // for each node which is adjacent to x...
        for (t = g->adjacentNodes(x)->getHead(); !t->empty(); t = t->next) {
            if (distances[t->id] == INFTY) {
                distances[t->id] = distances[x] + t->weight;
                parents[t->id] = x;
                q.push(t->id);
            } else if (distances[t->id] > distances[x] + t->weight) {
                distances[t->id] = distances[x] + t->weight;
                parents[t->id] = x;
            }
        }
    }
}