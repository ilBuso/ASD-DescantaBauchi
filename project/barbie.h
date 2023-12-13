#ifndef barbie_h
    #define barbie_h

    //----------------------------------
    
    #include <iostream>
    #include <fstream>
    #include <vector>

    //----------------------------------

    //nodo del grafo
    struct Node{
        int id;  //id del nodo
        vector<Arch> next; //vector che contiene i puntatori hai nodi e il peso
        bool occupied;  //stato del nodo

        Node(int id); //crea un nodo
        void add_arch(Node* a, Node* b, int w);  //crea un arco
    };

    //----------------------------------

    struct Arch{
        Node* b;
        int w;

        Arch(Node* b, int w);
    };

    //----------------------------------

    //grafo
    struct Graph{
        Node* head;  //testa del grafo
        int size;  //numero di nodi
        int n_strade;  //numero di strade

        Graph(Node* head, int c, int s);
        vector<int> shortest_path(int id); //restitusce il percorso più corto per raggiungere la città con l'id specificato
        Node* get_node(int id);  //return pointer of specific node
    };

    //----------------------------------

    //struct per facilitare le funzioni di input e output
    struct in_out{
        fstream in;
        fstream out;
    };

#endif