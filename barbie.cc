#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INFTY -1

ifstream in("input.txt");
ofstream out("output.txt");

int C, S, M;

int main() {


    int a, b, w;

    in >> C >> S;

    vector<vector<pair<int,int>>> map;

    map.resize(C);

    for (int i = 0; i < S; i++) {
        in >> a >> b >> w;
        map[a].push_back({b, w});
        map[b].push_back({a, w});
    }


    bool * captured = new bool[C];
    for (w = 0; w < C; w++) {
        captured[w] = false;
    }

    in >> M;

    for (w = 0; w < M; w++) {
        in >> a;
        captured[a] = true;
    }





    /* SOLUTION SOLUTION SOLUTION SOLUTION SOLUTION SOLUTION SOLUTION */

    queue<int> q;
    int * cheapest_path_cost = new int[C];
    int * cheapest_path_parent = new int[C];

    int * shortest_path_distance = new int[C];

    for (a = 0; a < C; a++) {
        shortest_path_distance[a] = INFTY;

        cheapest_path_cost[a] = INFTY;
        cheapest_path_parent[a] = INFTY;
    }

    cheapest_path_cost[0] = 0;
    shortest_path_distance[0] = 0;

    q.push(0);

    while (!q.empty()) {

        a = q.front(); q.pop();

        for (b = 0; b < map[a].size(); b++) {

            if (cheapest_path_cost[map[a][b].first] == INFTY) { //nodo da esplorare
                
                //aggiorna costo e percorso alla dijkstra
                cheapest_path_cost[map[a][b].first] = cheapest_path_cost[a] + map[a][b].second;
                cheapest_path_parent[map[a][b].first] = a;

                //aggiorna distanza minima in archi
                shortest_path_distance[map[a][b].first] = shortest_path_distance[a] + 1;

                q.push(map[a][b].first);

                if (captured[a]) //propaga la cattura
                    captured[map[a][b].first] = true;

            } else if (shortest_path_distance[map[a][b].first] == shortest_path_distance[a] + 1) {
                //nodo gia' scoperto, ma "contemporaneamente" ad uno precedente

                //se lo raggiungi ad un costo minore ricalcola alla dijkstra...
                if(cheapest_path_cost[map[a][b].first] > cheapest_path_cost[a] + map[a][b].second) {
                    
                    cheapest_path_cost[map[a][b].first] = cheapest_path_cost[a] + map[a][b].second;
                    cheapest_path_parent[map[a][b].first] = a;
                    q.push(map[a][b].first);

                    //e pensa di catturare il nodo
                    //o "liberarlo" (questo perche' se
                    //aggiorni il nodo, significa che
                    //da 'a' e' stato trovato un percorso
                    //migliore)
                    captured[map[a][b].first] = captured[a];

                } else if ((cheapest_path_cost[map[a][b].first] == cheapest_path_cost[a] + map[a][b].second) && captured[a]) {
                    //nel caso particolare in cui il costo sia uguale, la citta' viene occupata qualora
                    //quella che propone un costo uguale sia a sua volta occupata
                    captured[map[a][b].first] = true;
                }
            } else if (cheapest_path_cost[map[a][b].first] > cheapest_path_cost[a] + map[a][b].second) {
                //nodo gia' scoperto, ma "dopo" una scoperta precedente, e con tragitto da aggiornare
                cheapest_path_cost[map[a][b].first] = cheapest_path_cost[a] + map[a][b].second;
                cheapest_path_parent[map[a][b].first] = a;
                q.push(map[a][b].first);
            }
        }
    }



    /* CALCOLO DI K CALCOLO DI K CALCOLO DI K CALCOLO DI K */
    if (captured[C - 1]) {
        out << -2 << endl; //per ora non sempre veritiero
    } else {
        //se Algoritmia non viene catturata, si puo' dire con sicurezza che
        //il percorso della graphcruise sara' sicuro (ovvero e' sempre
        //garantito un percorso minimo che passa per citta' libere,
        //qualsiasi sia k)
        out << -1 << endl;
    }




    /* CALCOLO DI UN PERCORSO DI COSTO MINIMO CALCOLO DI UN PERCORSO DI COSTO MINIMO */
    a = 0;
    stack<int> s;
    for (b = C - 1; b != 0; b = cheapest_path_parent[b]) {
        a++;//incrementa numero nodi visitati nel percorso
        s.push(b);
    }
    a++;

    out << a << endl << "0 "; //stampa nodi visitati nel percorso
    while (!s.empty()) {
        out << s.top() << " ";
        s.pop();
    }

    delete [] cheapest_path_cost;
    delete [] cheapest_path_parent;
    delete [] shortest_path_distance;

    delete [] captured;

    return 0;
}