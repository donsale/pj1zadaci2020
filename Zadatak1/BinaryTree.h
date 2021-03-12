#pragma once

#include <initializer_list>
#include <iomanip>
#include <iostream>

#include "Array.h"
#include "Stack.h"

namespace zadatak1 {
class BinaryTree {
 public:
  explicit BinaryTree(int (*const cmp)(const Array&, const Array&));
  BinaryTree(int (*const cmp)(const Array&, const Array&),
             const std::initializer_list<Array>& arrays);

  BinaryTree(const BinaryTree& other);
  BinaryTree(BinaryTree&& other);

  void AddNode(const Array& arr);
  ~BinaryTree();

  static void Inorder(const BinaryTree& root, void (*)(void*));
  static void Inorder(const BinaryTree& root);

  BinaryTree& operator=(const BinaryTree&) = delete;
  BinaryTree& operator=(BinaryTree&&) = delete;

 private:
  class Node {
   public:
    explicit Node(Array arr);

    Node* getLeft() const;
    Node* getRight() const;
    void setLeft(Node*);
    void setRight(Node*);
    Array getData() const&;
    Array getData() &&;

   private:
    Array data;
    Node* left;
    Node* right;
  };

  Node* root;
  int (*const cmp)(const Array&, const Array&);

  Node* CopyHelper(Node* root);
  void DeleteTree(Node* root);
  static void PrintHex(void*);
  Node* Add(Node* root, const Array& arr);
};
}  // namespace zadatak1
