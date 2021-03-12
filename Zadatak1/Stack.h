#pragma once

#include <initializer_list>

namespace zadatak1 {

class Stack {
 public:
  Stack();
  Stack(const std::initializer_list<void *> &list);
  void push(void *);
  void *pop();
  void *top() const;
  bool isEmpty() const;

 private:
  struct List {
    struct Node {
      void *data;
      Node *next;

      explicit Node(void *);
    };

   public:
    List();
    ~List();
    List(const List &other);
    List(List &&);
    void AddToFront(void *data);
    void *GetFront();
    void *PeekFront() const;
    bool isEmpty() const;

    List &operator=(const List &) = delete;
    List &operator=(List &&) = delete;

   private:
    Node *head;
  };

  List list;
};

}  // namespace zadatak1
