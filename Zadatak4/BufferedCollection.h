#pragma once
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>

#include "Complex.h"

namespace zadatak4 {
class range_error : public std::out_of_range {
 public:
  range_error(size_t index)
      : index(index),
        std::out_of_range("Invalid index: " + std::to_string(index)) {}

 private:
  size_t index;
};

class invalid_pointer : public std::bad_weak_ptr {
 public:
  invalid_pointer() : message("Pointer to original object expired.") {}

  virtual const char *what() const noexcept override { return message.c_str(); }

 private:
  std::string message;
};

class BufferedCollection {
 public:
  explicit BufferedCollection(int k) noexcept;
  explicit BufferedCollection(
      int k,
      const std::initializer_list<std::weak_ptr<Complex>> &) noexcept(false);
  ~BufferedCollection() noexcept;
  BufferedCollection(const BufferedCollection &) noexcept(false);
  BufferedCollection(BufferedCollection &&) noexcept;

  BufferedCollection &operator=(const BufferedCollection &) noexcept(false);
  BufferedCollection &operator=(BufferedCollection &&) noexcept;

  void Add(const std::weak_ptr<Complex> &) noexcept(false);
  void Remove(const std::weak_ptr<Complex> &) noexcept;
  std::weak_ptr<Complex> &operator[](size_t index) noexcept(false);

 private:
  struct Node {
    std::weak_ptr<Complex> *buff;
    Node *next;
    size_t k;

    Node(size_t k) noexcept(false);
    Node(const Node &) noexcept(false);
    Node(Node &&) noexcept;
    Node &operator=(const Node &) noexcept(false);
    Node &operator=(Node &&) noexcept;
    ~Node() noexcept;

   private:
    void copy(const Node &) noexcept(false);
    void move(Node &&) noexcept;
    void dispose() noexcept;
  };

  Node *head;
  size_t k;
  size_t n;

  void copy(const BufferedCollection &) noexcept(false);
  void move(BufferedCollection &&) noexcept;
  void dispose() noexcept;
  void AddNode() noexcept(false);
  std::weak_ptr<Complex> &getElement(size_t index) const noexcept;
};
}  // namespace zadatak4