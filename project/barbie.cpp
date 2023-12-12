/**
 * 
 *  Questo file contiene le dichiarazioni delle funzioni, strutture... che sono usate nel file main.cpp
 * 
**/

#include "barbie.h"

using namespace std;


/*
    gestione degli stream
*/
struct in_out{
    fstream in;
    fstream out;
};

in_out apertura_stream(int argc, char* argv[]){

    //controllo file
    if(argc!=3){
        //input corretto
        cerr<<"Usage: ./a.out <source> <target>"<<endl;
        //uscita causa errore
        exit(1);
    }

    //creazione streams
    fstream in, out;
    //apertura stream entrata
    in.open(argv[1], ios::in);
    //apertura stream uscita
    out.open(argv[2], ios::out);

    //controllo file
    if(in.fail() || out.fail()){
        //messagio di errore 
        cerr<<"Errore dell'apertura degli stream"<<endl; 
        //uscita causa errore    
        exit(2);
    }

    struct in_out io;
    io -> in = in;
    io -> out = out;
}

void chiusura_stream(fstream in, fstream out){
    //chisura stream input
    in.close();
    //chisura stream output
    out.close();
}


/*
    gestione di input e output
*/
void input(fstream in){

    //variabili
    int c;  //numero città
    in >> c;
    int s;  //numero strade
    in >> s;

    int a;  //città di partenza
    int b;  //città di arrivo
    int w;  //tempo di percorrenza

    int o; //città occupate

    int array_citta[c] = {};  //----- da fare meglio una volta capito come funziona
}