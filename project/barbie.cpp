/**
 * 
 *  Questo file contiene le dichiarazioni
 *  delle funzioni, strutture... che sono
 *  usate nel file main.cpp
 * 
**/

#include "barbie.h"

using namespace std;


/*
    gestione degli stream
*/
//funzione per aprire tutti gli stram
in_out apertura_stream(int argc, char* argv[]){

    //controllo file
    if(argc != 3){
        //input corretto
        cerr << "Usage: ./a.out <source> <target>" << endl;
        //uscita causa errore
        exit(1);
    }

    //messaggio per terminale
    cout << "apertura streams" << endl;

    //creazione streams
    in_out io;
    //apertura stream entrata
    io.in.open(argv[1], ios::in);
    //apertura stream uscita
    io.out.open(argv[2], ios::out);

    //controllo file
    if(io.in.fail() || io.out.fail()){
        //messagio di errore 
        cerr << "Errore dell'apertura degli stream" << endl; 
        //uscita causa errore    
        exit(2);
    }

    //end
    return io;
}

//funzione per chioudere tutti gli stream
void chiusura_stream(fstream in, fstream out){

    //messaggio per terminale
    cout << "chiusura streams" << endl;

    //chisura stream input
    in.close();
    //chisura stream output
    out.close();
}


/*
    gestione di input e output
*/
//funzione per ottenere e organizzare tutt i dati in input
void input(fstream in){

    //messaggio per terminale
    cout << "prendendo dati in input" << endl;

    //variabili
    int c;  //numero città
    in >> c;
    int s;  //numero strade
    in >> s;

    listgraph map = listgraph(c, s); //inizializza grafo (non ha archi)

    int a;  //città di partenza
    int b;  //città di arrivo
    int w;  //tempo di percorrenza

    int o; //città occupate

    //node citys_array[1000];  //----- da fare meglio


    //aggiungi archi
    for(int i = 0; i < s; i++){

        //prendi dall'input informazioni sull'arco
        in >> a;
        in >> b;
        in >> w;

        //code

        map.linkWeightedSegment(a, b, w);
    }

    in >> o; //leggi numero citta occupate

    //setta le città come occupate
    for (int i = 0; i < o; i++) {
        in >> a; //leggi numero citta' occupata
        map.occupied[a] = true; //settala ad occupata = true
    }
}

//funzione per fornire l'uotput
void output(fstream out, int k, int r, int a[]){

    //messaggio per terminale
    cout << "fornendo i dati in output" << endl;

    //stampa valore di K
    out << k << endl;

    //stampa del valore di r
    out << r << endl;

    //stampa dei nodi attraversati
    for(int i = 0; i < sizeof(a); i++){
        out << a[i] << " ";  
    }
}



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

node * llist::getHead()
{
    return this->head;
}


listgraph::listgraph(int n, int m)
{
    this->n = n;
    this->m = m;
    this->adj_list = new llist*[n];
    this->occupied = new bool[n];

    for (int i = 0; i < n; i++) {
        this->adj_list[i] = new llist;
        this->occupied[i] = false;
    }
}

listgraph::~listgraph()
{
    int n = this->n;

    for (int i = 0; i < n; i++)
        delete this->adj_list[i];
    delete [] this->adj_list;
    delete [] this->occupied;
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