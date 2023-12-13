#include <iostream>
#include <fstream>
#include <queue>
#include "listgraph.h"
using namespace std;

#define INFTY -1

ifstream in("input.txt");
ofstream out("output.txt");

void dijkstra(listgraph * g, int s, int * &distances, int * &parents, bool * captured);
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
    dijkstra(&map, 0, d, p, captured);

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


void computeK(int * no_weight_parents, int * parents, bool * captured, int n, int no_weight_cost, int weight_cost)
{
    int weight_edges = 0;
    int no_weight_edges = 0;

    bool no_weight_captured = false;
    bool weight_captured = false;

    //cout << "Peso del percorso con meno archi: " << no_weight_cost[n - 1] << endl;
    for (int i = n - 1; i != 0; i = no_weight_parents[i]) { //scorri a ritroso il percorso
        no_weight_edges++;
        if (captured[i]) {
            no_weight_captured = true;
        }
    }

    for (int i = n - 1; i != 0; i = parents[i]) {
        weight_edges++;
        if (captured[i]) {
            weight_captured = true;
        }
    }




    if (weight_captured && no_weight_captured)
        out << -2 << endl;
    else if (!weight_captured && no_weight_captured)
        out << ( (no_weight_cost - weight_cost - 1) / (weight_edges - no_weight_edges) ) << endl;
    else
        out << -1 << endl;
}


void dijkstra(listgraph * g, int s, int * &distances, int * &parents, bool * captured)
{
    int n = g->size();
    int x;
    node * t;

    // visit queue
    queue<int> q;

    // distance and parent vectors
    distances = new int[n];
    parents = new int[n];

    // vettore distanze con meno lati e
    // peso per arrivare al i-esimo nodo
    // utilizzando percorsi di quel tipo
    int * no_weight_cost = new int[n];
    int * no_weight_parents = new int[n];

    for (int i = 0; i < n; i++) {
        distances[i] = INFTY;
        parents[i] = INFTY;

        no_weight_parents[i] = INFTY;
    }

    no_weight_cost[s] = 0;

    distances[s] = 0;
    q.push(s);

    while (!q.empty()) {

        x = q.front(); q.pop();

        // for each node which is adjacent to x...
        for (t = g->adjacentNodes(x)->getHead(); !t->empty(); t = t->next) {
            if (distances[t->id] == INFTY) {
                
                //segna il costo necessario per usare il percorso con meno archi
                no_weight_cost[t->id] = no_weight_cost[x] + t->weight;
                no_weight_parents[t->id] = x; //e segna da dove sei venuto
                

                distances[t->id] = distances[x] + t->weight;
                parents[t->id] = x;
                q.push(t->id);
            } else if (distances[t->id] > distances[x] + t->weight) {
                distances[t->id] = distances[x] + t->weight;
                parents[t->id] = x;
            }
        }
    }

    computeK(no_weight_parents, parents, captured, n, no_weight_cost[n], distances[n]);

    delete [] no_weight_cost;
    delete [] no_weight_parents;
}