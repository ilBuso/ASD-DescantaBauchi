#ifndef barbie_h
#define barbie_h

#include <iostream>
#include <fstream>

/*
 * Nodo della lista di adiacenza
 * contiene informazioni sui nodi
 * adiacenti ad un certo nodo dato,
 * quali id (intero da 0 a n - 1),
 * peso dell'arco (NON DIRETTO)
 * che li collega, e puntatore al
 * nodo successivo della lista
 */
class node {
    public:
        int id;      //numero del nodo (chiave/id)
        int weight;  //peso dell'arco
        
        node * next; //puntatore al nodo successivo della lista

        node(int v, int w); //crea un nodo con id 'v' e arco di peso 'w'
        ~node(); //distruttore del nodo
        bool empty(); //verifica se il nodo della lista e' vuoto (nil)
};

/*
 * Lista concatenata che rappresenta la lista di adiacenza.
 * Una lista raccoglie, dentro a oggetti di tipo nodo, definito
 * sopra, i nodi adiacenti ad un nodo (del grafo) dato, quindi
 * l'id, il peso dell'arco che li collega e il puntatore al
 * nodo successivo della lista, in modo da poterla scorrere.
 * L'ultimo nodo della lista e' un nodo vuoto (null). Se la
 * lista e' vuota, la testa della lista e' vuota (null).
 */
class llist {
    private:
        node * head; //testa della lista (primo nodo della lista)

    public:
        llist(); //costruttore (crea lista vuota, i.e. con testa null)
        ~llist(); //distruttore (dealloca tutti i nodi della lista)
        bool empty(); //verifica se la lista e' vuota (se la testa e' nil)
        void appendValueWeight(int v, int w); //aggiunge in testa alla lista un nuovo nodo, specificando id e peso del nodo del grafo 'v'
        node * getHead(); //ritorna la testa della lista (utile per scorrerla)
};

/*
 * Grafo implementato con liste di adiacenza. Contiene un array
 * di liste concatenate. La posizione i-esima dell'array contiene
 * i nodi adiacenti all'i-esimo nodo nel grafo dato.
 * Contiene anche un array di 'occupazione', che indica se il
 * nodo i-esimo (nella posizione di quell'array) e' occupato
 * o no (vedi problema barbie).
 */
class listgraph {
    private:
        llist **adj_list; //array di liste di adiacenza
        int n; //numero di nodi
        int m; //numero di archi (probabilmente servira' poco)

    public:
        bool * occupied;

        listgraph(int n, int m); //inizializza il grafo con n nodi e m archi
        ~listgraph(); //distruttore (dealloca lista di adiacenza e altro)
        int size(); //ritorna n (numero di nodi del grafo)
        void linkWeightedSegment(int a, int b, int w); //crea arco (non diretto) con peso w tra nodi a e b del grafo
        llist * adjacentNodes(int n); //restituisci la lista di adiacenza del nodo n
};

struct in_out{
    fstream in;
    fstream out;
};

#endif