#include <iostream>
#include <fstream>
#include "llist.h"
using namespace std;


int main()
{
    llist lista;
    
    for (int i = 0; i < 10; i++) {
        lista.appendValueWeight(i, 1);
    }

    for (node *t = lista.getHead(); t != nullptr; t = t->next) {
        cout << t->id << " ";
    }
    cout << endl;

    lista.deleteNode(9);

    for (node *t = lista.getHead(); t != nullptr; t = t->next) {
        cout << t->id << " ";
    }
    cout << endl;

    return 0;
}