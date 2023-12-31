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

#ifdef DEQUE_IMPLEMENTATION
#include <stdlib.h>

Node *Node_create(void *val) {
  Node *self = calloc(1, sizeof(Node));
  self->val = val;
  return self;
}

void Node_destroy(Node *self) { free(self); }

Deque *Deque_create() {
  Node *head = Node_create(NULL);
  Node *tail = Node_create(NULL);
  head->next = tail;
  tail->prev = head;

  Deque *self = calloc(1, sizeof(Deque));
  self->front = head;
  self->back = tail;
  return self;
}

void Deque_destroy(Deque *self) {
  Node *node = self->front->next;
  for (int i = 0; i < self->size; i++) {
    node = node->next;
    Node_destroy(node->prev);
  }
  Node_destroy(self->front);
  Node_destroy(self->back);
  free(self);
}

void *Deque_at(Deque *self, int index) {
  Node *node = self->front->next;
  for (int i = 0; i < index; i++) {
    node = node->next;
  }
  return node->val;
}

int Deque_size(Deque *self) { return self->size; }

void *Deque_front(Deque *self) { return self->front->next->val; }

void *Deque_back(Deque *self) { return self->back->prev->val; }

void Deque_pushfront(Deque *self, void *val) {
  self->size += 1;
  Node *node = Node_create(val);
  node->next = self->front->next;
  node->prev = self->front;
  self->front->next->prev = node;
  self->front->next = node;
}

void Deque_pushback(Deque *self, void *val) {
  self->size += 1;
  Node *node = Node_create(val);
  node->next = self->back;
  node->prev = self->back->prev;
  self->back->prev->next = node;
  self->back->prev = node;
}

void *Deque_popfront(Deque *self) {
  self->size -= 1;
  Node *target = self->front->next;
  void *val = target->val;
  target->next->prev = target->prev;
  target->prev->next = target->next;
  Node_destroy(target);
  return val;
}

void *Deque_popback(Deque *self) {
  self->size -= 1;
  Node *target = self->back->prev;
  void *val = target->val;
  target->next->prev = target->prev;
  target->prev->next = target->next;
  Node_destroy(target);
  return val;
}

void Deque_destroy_values(Deque *self) {
  for (int i = Deque_size(self); i--;) {
    free(Deque_popfront(self));
  }
}
#endif // !DEQUE_IMPLEMENTATION
