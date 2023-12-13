/*
 * Grafo basato su liste di adiacenza.
 * L'array di liste di adiacenza indica,
 * per la posizione i-esima, i nodi del
 * grafo adiacenti ad i, elencati nella
 * rispettiva lista.
 * 
 */

#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "../list/llist.h"


class listgraph {

    private:
        llist ** adj_list; // array di liste di adiacenza
        int n; // numero di nodi
        int m; // numero di lati

    public:
        bool occupied[];

        listgraph(int n, int m);
        ~listgraph();
        int size(); // numero di nodi
        void linkWeightedSegment(int a, int b, int w); // crea arco pesato tra 'a' e 'b'
        llist * adjacentNodes(int n); // restituisci la lista di adiacenza del nodo 'n'
};

#endif