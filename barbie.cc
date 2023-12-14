#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;

#define INFTY -1
#define FREE 0
#define SEIZED -1
#define SAFE 1

ifstream in("input.txt");
ofstream out("output.txt");

int C, S, M;


void solve(vector<vector<pair<int,int>>> graph, bool * captured);

//void leastEdges(vector<vector<pair<int,int>>> graph);

int main() {

    int a, b, w;

    in >> C >> S;

    vector<vector<pair<int, int>>> grafo;

    grafo.resize(C);

    for (int i = 0; i < S; i++) {
        in >> a >> b >> w;
        grafo[a].push_back({b, w});
        grafo[b].push_back({a, w});
    }



    bool * captured = new bool[C];
    for (int i = 0; i < C; i++) {
        captured[i] = false;
    }

    in >> M;

    for (int i = 0; i < M; i++) {
        in >> a;
        captured[a] = true;
    }




    /* BFS ALGORITHM */
    solve(grafo, captured);



    delete [] captured;

    return 0;
}

// start from 0
/*
void leastEdges(vector<vector<pair<int,int>>> graph)
{
    bool arrived = false;

    int i, j, k;

    queue<int> q;
    int * distance = new int[C];
    int * cost = new int[C];

    for (int i = 0; i < C; i++) {
        distance[i] = -1;
    }

    distance[0] = 0;
    cost[0] = 0;
    q.push(0);

    while (!q.empty() && !arrived) {
        i = q.front(); q.pop();

        for (j = 0; j < graph[i].size(); j++) {

            k = graph[i][j].first;

            if (distance[k] == -1) {

                distance[k] = distance[i] + 1;
                cost[k] = cost[i] + graph[i][j].second;

                if (k == C - 1)
                    arrived = true;
                else
                    q.push(k);
            }
        }
    }

    cout << "Least-edges path length: " << distance[C - 1] << endl;
    cout << "Cost: " << cost[C - 1] << endl;

    delete [] distance;
    delete [] cost;
}
*/

// start from 0
void solve(vector<vector<pair<int,int>>> graph, bool * captured)
{
    int i, j, k, cost; //temporary

    queue<int> q;
    int * distance = new int[C]; //distance[C - 1] contains the cost of the cheapest path
    int * parent = new int[C]; //record the path of the cheapest one (ritroso da C - 1, distance[C - 1], ...)

    for (i = 0; i < C; i++) {
        distance[i] = INFTY;
        parent[i] = INFTY;
    }


    //stores the distance (number of edges)
    //of the least-edges path, plus its
    //total cost of those edges
    int * least_edges_distance = new int[C];
    int * least_edges_cost = new int[C];

    least_edges_distance[0] = 0;
    least_edges_cost[0] = 0;

    distance[0] = 0;
    q.push(0);

    while (!q.empty()) {
        
        i = q.front(); q.pop();

        for (j = 0; j < graph[i].size(); j++) {

            k = graph[i][j].first;
            cost = graph[i][j].second;

            if (distance[k] == INFTY) {
                least_edges_distance[k] = least_edges_distance[i] + 1; //calcolo per path piu' corto
                least_edges_cost[k] = least_edges_cost[i] + cost; //segna il costo

                distance[k] = distance[i] + cost;
                parent[k] = i;
                q.push(k);
            } else if (distance[k] > distance[i] + cost) { //ricalcolo per il path meno costoso
                distance[k] = distance[i] + cost;
                parent[k] = i;
                q.push(k);
            }
        }
    }




    //CALCOLA NUMERO DI NODI DEL PERCORSO MENO COSTOSO
    //E PREPARATI PER LA STAMPA DEL TRAGITTO
    bool cheapest_captured = false;
    k = 0; //variabile temp. per calcolo del numero di nodi
    stack<int> s;
    for (i = C - 1; i != 0; i = parent[i]) {
        if (captured[i]) {
            cheapest_captured = true;
        }
        k++;
        s.push(i);
    }
    k++;




    //CALCOLO DI K
    if (C - 2 == M || cheapest_captured) { //tutte citta' occupate: nulla da fare (k introvabile)
        out << -2 << endl;
    } else if (M == 0) { //nessuna citta' occupata: k illimitato
        out << -1 << endl;
    } else {
        out << -1 << endl;
    }






/*
    if (cheapest_captured) {
        cout << -2 << endl;
    } else if (shortest_captured) {
        (least_edges_cost[C - 1] - distance[C - 1] - 1) / (cheapest_edges - least_edges_distance[C - 1])
    } else {
        cout << - 1 << endl;
    }
*/



    //STAMPA DELLA LUNGHEZZA DEL PERCORSO MENO COSTOSO
    //E TRAGITTO ANNESSO
    out << k << endl;

    out << "0 ";
    while (!s.empty()) {
        out << s.top() << " ";
        s.pop();
    }

    //deinizializzazioni (mannaggia a C++ con 'sti puntatori)
    delete [] distance;
    delete [] parent;

    delete [] least_edges_distance;
    delete [] least_edges_cost;
}