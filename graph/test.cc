#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#include <vector>
using namespace std;

#define INFTY -1

ifstream in("input.txt");
ofstream out("output.txt");

class node {

    public:
        int id;
        int weight;
        node * next;

        node(int v, int w); // crea un nodo con id v e arco di peso w
        ~node(); // distruttore del nodo (per eliminare i nodi)
        bool empty();
};

class llist {

    private:
        node * head;
    
    public:
        llist();
        ~llist();
        bool empty();
        void appendValueWeight(int v, int w);
        void deleteNode(int v);
        node * getHead();
};

node::node(int v, int w)
{
    this->id = v;
    this->weight = w;
    this->next = nullptr;
}

node::~node()
{
    this->next = nullptr;
}

bool node::empty()
{
    return (this == nullptr);
}



llist::llist()
{
    head = nullptr;
}

llist::~llist()
{
    node * tmp;

    while (!this->empty()) {
        tmp = this->head;
        this->head = this->head->next;
        delete tmp;
    }
}

bool llist::empty()
{
    return (this->head)->empty();
}

void llist::appendValueWeight(int v, int w)
{
    node * n = new node(v, w);

    n->next = this->head;
    this->head = n;
}

static void detachNode(node * parent)
{
    node * tmp = parent->next;
    parent->next = tmp->next;
    delete tmp;
}

void llist::deleteNode(int v)
{
    node * p = this->head;

    bool found = false;

    while (!found && p != nullptr && p->next != nullptr) {
        if (p->next->id == v) {
            found = true;
            detachNode(p);
        } else {
            p = p->next;
        }
    }

    if (!found && this->head != nullptr && this->head->id == v) {
        p = this->head;
        this->head = p->next;
        delete p;
    }
}

node * llist::getHead()
{
    return this->head;
}

class listgraph {

    private:
        llist ** adj_list; // array di liste di adiacenza
        int n; // numero di nodi
        int m; // numero di lati

    public:
        bool * captured;

        listgraph(int n, int m);
        ~listgraph();
        int size(); // numero di nodi
        void linkWeightedSegment(int a, int b, int w); // crea arco pesato tra 'a' e 'b'
        llist * adjacentNodes(int n); // restituisci la lista di adiacenza del nodo 'n'
};

listgraph::listgraph(int n, int m)
{
    this->n = n;
    this->m = m;
    this->adj_list = new llist*[n];
    this->captured = new bool[n];

    for (int i = 0; i < n; i++) {
        this->adj_list[i] = new llist;
        this->captured[i] = false;
    }
}

listgraph::~listgraph()
{
    int n = this->n;

    for (int i = 0; i < n; i++)
        delete this->adj_list[i];
    delete [] this->adj_list;
    delete [] this->captured;
}


void listgraph::linkWeightedSegment(int a, int b, int w)
{
    this->adj_list[a]->appendValueWeight(b, w);
    this->adj_list[b]->appendValueWeight(a, w);
}

llist * listgraph::adjacentNodes(int n)
{
    return this->adj_list[n];
}

int listgraph::size()
{
    return this->n;
}








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

    for (int i = 0; i < M; i++) {
        in >> w;
        map.captured[w] = true;
    }

    int * p;
    int * d;
    dijkstra(&map, 0, d, p, map.captured);

    out << -1 << endl;
    printShortestPath(p, C - 1, 1);

    delete [] d;
    delete [] p;

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
    //int * no_weight_cost = new int[n];
    //int * no_weight_parents = new int[n];

    for (int i = 0; i < n; i++) {
        distances[i] = INFTY;
        parents[i] = INFTY;

        //no_weight_parents[i] = INFTY;
    }

    //no_weight_cost[s] = 0;

    distances[s] = 0;
    q.push(s);

    while (!q.empty()) {

        x = q.front(); q.pop();

        // for each node which is adjacent to x...



        for (t = g->adjacentNodes(x)->getHead(); !t->empty(); t = t->next) {




            if (distances[t->id] == INFTY) {
                
                //segna il costo necessario per usare il percorso con meno archi
                //no_weight_cost[t->id] = no_weight_cost[x] + t->weight;
                //no_weight_parents[t->id] = x; //e segna da dove sei venuto
                

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