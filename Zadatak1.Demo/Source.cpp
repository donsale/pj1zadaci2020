#include <iostream>

#include "Array.h"
#include "BinaryTree.h"

using namespace zadatak1;

int cmp(const Array& a, const Array& b) { return a.CompareTo(b); }

int main() {
  Array arr(7);
  Array arr1 = Array(9);
  const Array const_arr(7, {0, 0, 0, 0, 0, 5, 0});

  int errorCode;
  arr.getElementAt(50, errorCode);
  if (errorCode == Array::OUT_OF_BOUNDS) {
    std::cout << "Pristup van opsega niza!" << std::endl;
  }
  arr.getElementAt(6, errorCode) = 0xFF;
  arr1.getElementAt(6, errorCode) = 6;
  std::cout << arr.CompareTo(arr1) << std::endl;
  std::cout << arr.getSize() << std::endl;
  arr.getElementAt(1, errorCode) = 2;
  std::cout << (int)const_arr.getElementAt(6, errorCode) << std::endl;
  std::cout << const_arr.CompareTo(arr1) << std::endl;

  std::cout << std::endl;

  Stack s;
  int a = 1;
  int b = 5;
  s.push(&a);
  s.push(&b);
  Stack const_s({&a, &b});
  std::cout << *static_cast<int*>(s.pop()) << std::endl;
  std::cout << *static_cast<int*>(s.pop()) << std::endl;
  std::cout << s.isEmpty() << std::endl;
  std::cout << *static_cast<int*>(const_s.top()) << std::endl;

  std::cout << std::endl;

  BinaryTree tree(cmp);
  tree.AddNode(arr);
  tree.AddNode(arr1);

  BinaryTree copyTree(tree);
  BinaryTree moveTree =
      std::move(BinaryTree(cmp, {arr1, arr, Array(4, {0x62, 0xf2})}));

  const BinaryTree const_tree(cmp,
                              {Array(3, {0, 1, 2}), Array(2, {0x22, 0xf2})});
  BinaryTree::Inorder(copyTree);
  std::cout << std::endl;
  BinaryTree::Inorder(tree);
  std::cout << std::endl;
  BinaryTree::Inorder(const_tree);
  std::cout << std::endl;
  std::cout << std::endl;
  BinaryTree::Inorder(std::move(moveTree));

  return 0;
}