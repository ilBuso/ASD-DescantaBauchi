#include "listgraph.h"

listgraph::listgraph(int n, int m)
{
    this->n = n;
    this->m = m;
    this->adj_list = new llist*[n];

    for (int i = 0; i < n; i++) {
        this->adj_list[i] = new llist;
    }
}

listgraph::~listgraph()
{
    int n = this->n;

    for (int i = 0; i < n; i++) {
        delete this->adj_list[i];
    }
    delete [] this->adj_list;
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