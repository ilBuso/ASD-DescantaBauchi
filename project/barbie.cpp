/**
 * 
 *  Questo file contiene le dichiarazioni
 *  delle funzioni, strutture... che sono
 *  usate nel file main.cpp
 * 
**/

#include "barbie.h"

//----------------------------------

using namespace std;

//----------------------------------

/*
    Constructors
*/
Node::Node(int id){
    this->id = id;
    this->occupied = false;
}

Arch::Arch(Node* b, int w){
    this->b = b;
    this->w = w;
}

Graph::Graph(Node* head, int c, int s){
    this->head = head;
    this->size = c;
    this->n_strade = s;   
}

//----------------------------------

/*
    node functions
*/
void Node::add_arch(Node* a, Node* b, int w){
    //cera arco da A a B di peso W
    Arch arch_one = Arch(b, w);
    //cera arco da B a A di peso W
    Arch arch_two = Arch(a, w);

    //aggiungi arco al vector di A
    a->next.insert(a->next.begin(), arch_one);
    //aggiungi arco al vector di B
    b->next.insert(b->next.begin(), arch_two);
}

//----------------------------------

/*
    Graph functions
*/
Node* Graph::get_node(int id){
    //code
}

//----------------------------------

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

//----------------------------------

//funzione per chioudere tutti gli stream
void chiusura_stream(fstream in, fstream out){

    //messaggio per terminale
    cout << "chiusura streams" << endl;

    //chisura stream input
    in.close();
    //chisura stream output
    out.close();
}

//----------------------------------

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

    //crea barbieland
    Node head = Node(0);
    //crea grafo
    Graph graph = Graph(&head, c, s);

    int a;  //città di partenza
    Node* a_node;
    int b;  //città di arrivo
    Node* b_node;
    int w;  //tempo di percorrenza
    Node* c_node;
    int o; //città occupate



    //aggiungi archi
    for(int i = 0; i < s; i++){


        //prendi dall'input informazioni sull'arco
        in >> a;
        in >> b;
        in >> w;

        //partendo dall'id trovare i nodi se esistono o crearli

        //prendere il puntatore

        //aggiungi arco
        add_arch(a_node, b_node, w);

    }

    //setta le città come occupate
    for(int i; in >> i;){ 
        //code
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