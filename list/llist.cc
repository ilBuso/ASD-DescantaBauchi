#include "llist.h"

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