/*
 * Lista concatenata per le liste di adiacenza.
 * Ogni nodo e' caratterizzato da id numerico e
 * peso del lato nel grafo. Nella lista, i nodi
 * hanno anche un puntatore al nodo successivo.
 * 
 * Ogni lista rappresenta l'insieme di nodi che
 * nel grafo sono adiacenti ad un certo nodo.
 */

#ifndef LLIST_H
#define LLIST_H


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

#endif