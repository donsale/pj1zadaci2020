#include "BufferedCollectionHeader.h"

namespace zadatak5 {
template <class T>
requires Addable<T> &&Comparable<T>
    &&Printable<T> BufferedCollection<T>::Node::Node(size_t k) noexcept(false)
    : buff(new T[k]), next(nullptr), k(k) {}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T>
BufferedCollection<T>::Node::Node(const Node &other) noexcept(false) {
  copy(other);
}

template <class T>
requires Addable<T> &&Comparable<T>
    &&Printable<T> BufferedCollection<T>::Node::Node(Node &&other) noexcept {
  move(std::move(other));
}

template <class T>
requires Addable<T> &&Comparable<T>
    &&Printable<T> typename BufferedCollection<T>::Node &
    BufferedCollection<T>::Node::operator=(const Node &other) noexcept(false) {
  if (this != &other) {
    dispose();
    copy(other);
  }
  return *this;
}

template <class T>
requires Addable<T> &&Comparable<T>
    &&Printable<T> typename BufferedCollection<T>::Node &
    BufferedCollection<T>::Node::operator=(Node &&other) noexcept {
  if (this != &other) {
    dispose();
    move(std::move(other));
  }
  return *this;
}

template <class T>
requires Addable<T> &&Comparable<T>
    &&Printable<T> BufferedCollection<T>::Node::~Node() noexcept {
  dispose();
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> void
BufferedCollection<T>::Node::copy(const Node &other) noexcept(false) {
  k = other.k;
  buff = new T[k];
  next = nullptr;
  for (size_t i = 0; i < k; i++) buff[i] = other.buff[i];
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> void
BufferedCollection<T>::Node::move(Node &&other) noexcept {
  buff = other.buff;
  next = other.next;
  k = other.k;
  other.buff = nullptr;
  other.next = nullptr;
}

template <class T>
requires Addable<T> &&Comparable<T>
    &&Printable<T> void BufferedCollection<T>::Node::dispose() noexcept {
  delete[] buff;
  k = 0;
}

template <class T>
requires Addable<T> &&Comparable<T>
    &&Printable<T> BufferedCollection<T>::BufferedCollection(int k) noexcept
    : head(nullptr), n(0), k(k) {}

template <class T>
requires Addable<T> &&Comparable<T>
    &&Printable<T> BufferedCollection<T>::BufferedCollection(
        int k, const std::initializer_list<T> &list) noexcept(false)
    : BufferedCollection(k) {
  for (auto &v : list) {
    try {
      Add(v);
    } catch (const std::exception &ex) {
      dispose();
      throw;
    }
  }
}

template <class T>
requires Addable<T> &&Comparable<T>
    &&Printable<T> BufferedCollection<T>::~BufferedCollection() noexcept {
  dispose();
}

template <class T>
requires Addable<T> &&Comparable<T>
    &&Printable<T> BufferedCollection<T>::BufferedCollection(
        const BufferedCollection &other) noexcept(false) {
  copy(other);
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T>
BufferedCollection<T>::BufferedCollection(BufferedCollection &&other) noexcept {
  move(std::move(other));
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> BufferedCollection<T>
    &BufferedCollection<T>::operator=(const BufferedCollection &other) noexcept(
        false) {
  if (this != &other) {
    dispose();
    copy(other);
  }
  return *this;
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> BufferedCollection<T>
    &BufferedCollection<T>::operator=(BufferedCollection &&other) noexcept {
  if (this != &other) {
    dispose();
    move(std::move(other));
  }
  return *this;
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> void
BufferedCollection<T>::Add(const T &value) noexcept(false) {
  if (head == nullptr) AddNode();

  Node *tmp = head;
  size_t nodeCount = 1;
  while (tmp->next) {
    tmp = tmp->next;
    nodeCount++;
  }

  size_t expectedCount = n / k + 1;
  if (nodeCount < expectedCount) AddNode();

  tmp->buff[n % k] = value;
  n++;
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> void
BufferedCollection<T>::Remove(const T &toRemove) noexcept {
  for (size_t i = 0; i < n; i++) {
    if (getElement(i) == toRemove) {
      for (size_t j = i; j < n - 1; j++) getElement(j) = getElement(j + 1);
      i--;
      n--;
    }
  }
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> T &
BufferedCollection<T>::operator[](size_t index) noexcept(false) {
  if (index < 0 || index >= n) throw range_error(index);
  return getElement(index);
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> const T &
BufferedCollection<T>::operator[](size_t index) const noexcept(false) {
  if (index < 0 || index >= n) throw range_error(index);
  return getElement(index);
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> T
BufferedCollection<T>::sum() const noexcept {
  T tmp = T();
  for (size_t i = 0; i < n; i++) tmp = tmp + (*this)[i];
  return tmp;
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> void
BufferedCollection<T>::print(std::ostream &stream) const noexcept {
  std::vector<T> vec;
  for (size_t i = 0; i < n; i++) vec.push_back((*this)[i]);
  std::sort(vec.begin(), vec.end());
  for (size_t i = 0; i < n; i++) stream << vec.at(i) << std::endl;
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> void
BufferedCollection<T>::copy(const BufferedCollection &other) noexcept(false) {
  n = other.n;
  k = other.k;
  head = nullptr;

  if (n > 0) {
    head = new Node(*other.head);

    Node *tmpThis = head;
    Node *tmpOther = other.head->next;
    while (tmpOther) {
      try {
        tmpThis->next = new Node(*tmpOther);
      } catch (const std::exception &ex) {
        dispose();
        throw;
      }
      tmpOther = tmpOther->next;
      tmpThis = tmpThis->next;
    }
  }
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> void
BufferedCollection<T>::move(BufferedCollection &&other) noexcept {
  head = other.head;
  n = other.n;
  k = other.k;
  other.head = nullptr;
}

template <class T>
requires Addable<T> &&Comparable<T>
    &&Printable<T> void BufferedCollection<T>::dispose() noexcept {
  while (head) {
    Node *tmp = head->next;
    delete head;
    head = tmp;
  }
}

template <class T>
requires Addable<T> &&Comparable<T>
    &&Printable<T> void BufferedCollection<T>::AddNode() noexcept(false) {
  if (head == nullptr) {
    head = new Node(k);
    return;
  }

  Node *tmp = head;
  while (tmp->next) tmp = tmp->next;
  tmp->next = new Node(k);
}

template <class T>
requires Addable<T> &&Comparable<T> &&Printable<T> T &
BufferedCollection<T>::getElement(size_t index) const noexcept {
  size_t listIndex = index / k;

  Node *tmp = head;
  for (size_t i = 0; i < listIndex; i++) tmp = tmp->next;

  return tmp->buff[index % k];
}
}  // namespace zadatak5