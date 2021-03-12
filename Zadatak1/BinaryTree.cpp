#include "BinaryTree.h"

namespace zadatak1 {

BinaryTree::Node::Node(Array data)
    : data(data), left(nullptr), right(nullptr) {}

BinaryTree::Node* BinaryTree::Node::getLeft() const { return this->left; }

BinaryTree::Node* BinaryTree::Node::getRight() const { return this->right; }

void BinaryTree::Node::setLeft(Node* l) { this->left = l; }

void BinaryTree::Node::setRight(Node* r) { this->right = r; }

Array BinaryTree::Node::getData() const& { return data; }

Array BinaryTree::Node::getData() && { return std::move(data); }

BinaryTree::BinaryTree(int (*const cmp)(const Array&, const Array&))
    : root(nullptr), cmp(cmp) {}

BinaryTree::BinaryTree(int (*const cmp)(const Array&, const Array&),
                       const std::initializer_list<Array>& arrays)
    : BinaryTree(cmp) {
  for (auto arr : arrays) this->AddNode(arr);
}

BinaryTree::BinaryTree(const BinaryTree& other) : BinaryTree(other.cmp) {
  this->root = CopyHelper(other.root);
}

BinaryTree::Node* BinaryTree::CopyHelper(Node* root) {
  if (root == nullptr) return nullptr;

  Node* tmp = new Node(root->getData());
  tmp->setLeft(CopyHelper(root->getLeft()));
  tmp->setRight(CopyHelper(root->getRight()));

  return tmp;
}

BinaryTree::BinaryTree(BinaryTree&& other) : BinaryTree(other.cmp) {
  this->root = other.root;
  other.root = nullptr;
}

BinaryTree::~BinaryTree() { DeleteTree(this->root); }

void BinaryTree::Inorder(const BinaryTree& tree) { Inorder(tree, PrintHex); }

void BinaryTree::PrintHex(void* n) {
  int errorCode;
  Node* node = static_cast<Node*>(n);
  //Array arr = std::move(*node).getData();
  auto arr = std::move(node->getData());
  int len = arr.getSize();
  for (int i = len - 1; i >= 0; i--) {
    int el = arr.getElementAt(i, errorCode);
    if (errorCode == Array::OK)
      std::cout << std::setfill('0') << std::setw(2) << std::right << std::hex
                << el;
  }
  std::cout << std::endl;
}

void BinaryTree::Inorder(const BinaryTree& tree, void (*f)(void*)) {
  Stack s;
  Node* currentNode = tree.root;

  while (currentNode != nullptr || !s.isEmpty()) {
    while (currentNode != nullptr) {
      s.push(currentNode);
      currentNode = currentNode->getLeft();
    }
    currentNode = static_cast<Node*>(s.pop());
    f(currentNode);
    currentNode = currentNode->getRight();
  }
}

void BinaryTree::DeleteTree(Node* root) {
  if (root == nullptr) return;
  DeleteTree(root->getRight());
  DeleteTree(root->getLeft());

  delete root;
}

void BinaryTree::AddNode(const Array& arr) {
  this->root = Add(this->root, arr);
}

BinaryTree::Node* BinaryTree::Add(Node* root, const Array& arr) {
  if (root == nullptr) return new Node(arr);

  Array curr = root->getData();
  if (cmp(curr, arr) > 0)
    root->setLeft(Add(root->getLeft(), arr));
  else
    root->setRight(Add(root->getRight(), arr));

  return root;
}
}  // namespace zadatak1