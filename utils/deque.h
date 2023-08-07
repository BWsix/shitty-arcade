#ifndef DEQUE_H
#define DEQUE_H

typedef struct Node {
  void *val;
  struct Node *prev;
  struct Node *next;
} Node;

Node *Node_create(void *val);
void Node_destroy(Node *node);

typedef struct Deque {
  int size;
  Node *front;
  Node *back;
} Deque;

Deque *Deque_create();
void Deque_destroy(Deque *self);

void *Deque_at(Deque *self, int index);
int Deque_size(Deque *self);
void *Deque_front(Deque *self);
void *Deque_back(Deque *self);

void Deque_pushfront(Deque *self, void *val);
void Deque_pushback(Deque *self, void *val);
void *Deque_popfront(Deque *self);
void *Deque_popback(Deque *self);
void Deque_destroy_values(Deque *self);

#endif // !DEQUE_H
