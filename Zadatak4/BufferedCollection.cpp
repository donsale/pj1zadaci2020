#include "BufferedCollection.h"

namespace zadatak4 {
// Ako se u konstruktoru desi izuzetak ništa se nije alociralo, nema se šta ni
// osloboditi, imamo samo tu jednu alokaciju
BufferedCollection::Node::Node(size_t k) noexcept(false)
    : buff(new std::weak_ptr<Complex>[k]), next(nullptr), k(k) {}

BufferedCollection::Node::Node(const Node &other) noexcept(false) {
  copy(other);
}

BufferedCollection::Node::Node(Node &&other) noexcept {
  move(std::move(other));
}

BufferedCollection::Node &BufferedCollection::Node::operator=(
    const Node &other) noexcept(false) {
  if (this != &other) {
    dispose();
    copy(other);
  }
  return *this;
}

BufferedCollection::Node &BufferedCollection::Node::operator=(
    Node &&other) noexcept {
  if (this != &other) {
    dispose();
    move(std::move(other));
  }
  return *this;
}

BufferedCollection::Node::~Node() noexcept { dispose(); }

void BufferedCollection::Node::copy(const Node &other) noexcept(false) {
  k = other.k;
  buff = new std::weak_ptr<Complex>[k];  // isto kao i za konstruktor
  next = nullptr;
  for (size_t i = 0; i < k; i++) buff[i] = other.buff[i];
}

void BufferedCollection::Node::move(Node &&other) noexcept {
  buff = other.buff;
  next = other.next;
  k = other.k;
  other.buff = nullptr;
  other.next = nullptr;
}

void BufferedCollection::Node::dispose() noexcept {
  delete[] buff;
  k = 0;
}

BufferedCollection::BufferedCollection(int k) noexcept
    : head(nullptr), n(0), k(k) {}

BufferedCollection::BufferedCollection(
    int k,
    const std::initializer_list<std::weak_ptr<Complex>> &list) noexcept(false)
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

BufferedCollection::~BufferedCollection() noexcept { dispose(); }

BufferedCollection::BufferedCollection(
    const BufferedCollection &other) noexcept(false) {
  copy(other);
}

BufferedCollection::BufferedCollection(BufferedCollection &&other) noexcept {
  move(std::move(other));
}

BufferedCollection &BufferedCollection::operator=(
    const BufferedCollection &other) noexcept(false) {
  if (this != &other) {
    dispose();
    copy(other);
  }
  return *this;
}

BufferedCollection &BufferedCollection::operator=(
    BufferedCollection &&other) noexcept {
  if (this != &other) {
    dispose();
    move(std::move(other));
  }
  return *this;
}

void BufferedCollection::Add(const std::weak_ptr<Complex> &value) noexcept(
    false) {
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

void BufferedCollection::Remove(
    const std::weak_ptr<Complex> &toRemove) noexcept {
  for (size_t i = 0; i < n; i++) {
    if (getElement(i).lock() == toRemove.lock()) {
      for (size_t j = i; j < n - 1; j++) getElement(j) = getElement(j + 1);
      getElement(n - 1) =
          std::weak_ptr<Complex>();  // prepisujemo posljednji clan, da ne
                                     // ostane višak weak referenca
      i--;  // posto smo pomjerili sve unazad, da ne preskocimo onaj koji dolazi
            // na trenutnu poziciju
      n--;
    }
  }
}

// Posto se poziva Remove() ne mozemo imati const verziju operator[]
std::weak_ptr<Complex> &BufferedCollection::operator[](size_t index) noexcept(
    false) {
  if (index < 0 || index >= n) throw range_error(index);

  std::weak_ptr<Complex> &wp = getElement(index);
  std::shared_ptr<Complex> sp = wp.lock();
  if (sp) {
    return wp;
  } else {
    Remove(wp);
    throw invalid_pointer();
  }
}

void BufferedCollection::copy(const BufferedCollection &other) noexcept(false) {
  n = other.n;
  k = other.k;
  head = nullptr;

  if (n > 0) {
    head = new Node(
        *other.head);  // prva alokacija, ako ne uspije nema šta osloboditi

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

void BufferedCollection::move(BufferedCollection &&other) noexcept {
  head = other.head;
  n = other.n;
  k = other.k;
  other.head = nullptr;
}

void BufferedCollection::dispose() noexcept {
  while (head) {
    Node *tmp = head->next;
    delete head;
    head = tmp;
  }
}

// Ako ovdje new baci izuzetak propagirace se do pozivajuceg koda i tamo ce biti
// uhvacen, pa onda ne hvatam ovdje, ako alokacija cvora ne uspije objekat ce
// ostati u upotrebljivom stanju
void BufferedCollection::AddNode() noexcept(false) {
  if (head == nullptr) {
    head = new Node(k);
    return;
  }

  Node *tmp = head;
  while (tmp->next) tmp = tmp->next;
  tmp->next = new Node(k);
}

std::weak_ptr<Complex> &BufferedCollection::getElement(
    size_t index) const noexcept {
  size_t listIndex = index / k;

  Node *tmp = head;
  for (size_t i = 0; i < listIndex; i++) tmp = tmp->next;

  return tmp->buff[index % k];
}
}  // namespace zadatak4