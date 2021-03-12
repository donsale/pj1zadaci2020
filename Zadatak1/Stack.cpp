#include "Stack.h"

namespace zadatak1 {

Stack::Stack() {}

Stack::Stack(const std::initializer_list<void*>& values) {
  for (auto v : values) this->push(v);
}

void Stack::push(void* data) { list.AddToFront(data); }

void* Stack::pop() { return list.GetFront(); }

void* Stack::top() const { return list.PeekFront(); }

bool Stack::isEmpty() const { return list.isEmpty(); }

Stack::List::List() : head(nullptr) {}

Stack::List::~List() {
  Node* tmp;
  while (this->head != nullptr) {
    tmp = this->head->next;
    delete this->head;
    this->head = tmp;
  }
}

Stack::List::List(const List& other) {
  if (other.head == nullptr) {
    this->head = nullptr;
    return;
  }

  this->head = new Node(other.head->data);

  Node* tmpLocal = this->head;
  Node* tmpOther = other.head;

  tmpOther = tmpOther->next;
  while (tmpOther != nullptr) {
    tmpLocal->next = new Node(tmpOther->data);
    tmpLocal = tmpLocal->next;
    tmpOther = tmpOther->next;
  }
}

Stack::List::List(List&& other) {
  this->head = other.head;
  other.head = nullptr;
}

void Stack::List::AddToFront(void* data) {
  if (data == nullptr) return;

  Node* tmp = new Node(data);

  if (this->head == nullptr) {
    this->head = tmp;
  } else {
    tmp->next = this->head;
    this->head = tmp;
  }
}

void* Stack::List::GetFront() {
  if (this->head == nullptr) return nullptr;

  Node* tmp = this->head;
  void* data = this->head->data;
  this->head = this->head->next;
  delete tmp;

  return data;
}

void* Stack::List::PeekFront() const {
  if (this->head == nullptr) return nullptr;
  return this->head->data;
}

bool Stack::List::isEmpty() const { return this->head == nullptr; }

Stack::List::Node::Node(void* data) : data(data), next(nullptr) {}

}  // namespace zadatak1