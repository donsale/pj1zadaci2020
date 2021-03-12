#pragma once
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "IPrintable.h"

namespace zadatak5 {
class range_error : public std::out_of_range {
 public:
  range_error(size_t index)
      : index(index),
        std::out_of_range("Invalid index: " + std::to_string(index)) {}

 private:
  size_t index;
};

template <typename T>
concept Addable = requires(const T &a, const T &b) {
  { a + b }
  ->std::convertible_to<T>;
};

template <class T>
concept Comparable = requires(const T &a, const T &b) {
  std::three_way_comparable<T>;
};

template <class T>
concept Printable = requires(std::ostream &stream, const T &a) {
  { stream << a }
  ->std::convertible_to<decltype(stream)>;
};

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> class BufferedCollection
    : virtual public IPrintable {
  static_assert(std::is_constructible<T>::value,
                "Type must be default-constructible.");
  static_assert(std::is_copy_constructible<T>::value,
                "Type must be copy-constructible.");
  static_assert(std::is_move_constructible<T>::value,
                "Type must be move-constructible.");
  static_assert(std::is_copy_assignable<T>::value,
                "Type must be copy-assignable.");
  static_assert(std::is_move_assignable<T>::value,
                "Type must be move-assignable.");

 public:
  explicit BufferedCollection(int k) noexcept;
  explicit BufferedCollection(int k,
                              const std::initializer_list<T> &) noexcept(false);
  ~BufferedCollection() noexcept;
  BufferedCollection(const BufferedCollection &) noexcept(false);
  BufferedCollection(BufferedCollection &&) noexcept;

  BufferedCollection &operator=(const BufferedCollection &) noexcept(false);
  BufferedCollection &operator=(BufferedCollection &&) noexcept;

  void Add(const T &) noexcept(false);
  void Remove(const T &) noexcept;
  T &operator[](size_t index) noexcept(false);
  const T &operator[](size_t index) const noexcept(false);

  T sum() const noexcept;

 protected:
  virtual void print(std::ostream &) const noexcept override;

 private:
  struct Node {
    T *buff;
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
  T &getElement(size_t index) const noexcept;
};
}  // namespace zadatak5