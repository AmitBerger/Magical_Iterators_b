#include "MagicalContainer.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>

namespace ariel {

// Helper function to check if a number is prime
bool isPrime(int num) {
  if (num <= 1)
    return false;

  for (int i = 2; i <= sqrt(num); ++i) {
    if (num % i == 0)
      return false;
  }

  return true;
}

void MagicalContainer::addElement(int element) {
  for (int element_ : sortedElements) {
    if (element_ == element)
      return;
  }
  sortedElements.push_back(element);
  std::sort(sortedElements.begin(), sortedElements.end());
  prime_pointers.clear();
  for (unsigned long i = 0; i < sortedElements.size(); i++) {
    if (isPrime(sortedElements.at(i))) {
      prime_pointers.push_back(&sortedElements.at(i));
    }
  }
}

void MagicalContainer::removeElement(int element) {
  auto it = std::find(sortedElements.begin(), sortedElements.end(), element);
  if (it != sortedElements.end()) {
    sortedElements.erase(it);
  } else {
    throw std::runtime_error("Element not found");
  }
}

int MagicalContainer::size() const { return sortedElements.size(); }

// AscendingIterator
MagicalContainer::AscendingIterator::AscendingIterator(
    const AscendingIterator &other)
    : container(other.container), currentIndex(other.currentIndex) {}

MagicalContainer::AscendingIterator::~AscendingIterator() {}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &cont,
                                                       std::size_t index)
    : container(cont), currentIndex(index) {}

MagicalContainer::AscendingIterator &
MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {
  if (&container != &other.container) {
    throw std::runtime_error("Iterators belong to different containers");
  }
  currentIndex = other.currentIndex;
  return *this;
}

bool MagicalContainer::AscendingIterator::operator==(
    const AscendingIterator &other) const {
  return currentIndex == other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator!=(
    const AscendingIterator &other) const {
  return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(
    const AscendingIterator &other) const {
  return container.sortedElements[currentIndex] >
         container.sortedElements[other.currentIndex];
}

bool MagicalContainer::AscendingIterator::operator<(
    const AscendingIterator &other) const {
  return container.sortedElements[currentIndex] <
         container.sortedElements[other.currentIndex];
}

int MagicalContainer::AscendingIterator::operator*() const {
  return container.sortedElements[currentIndex];
}

MagicalContainer::AscendingIterator &
MagicalContainer::AscendingIterator::operator++() {
  ++currentIndex;
  if (currentIndex > container.sortedElements.size()) {
    throw std::runtime_error("Iterator out of range");
  }
  return *this;
}

MagicalContainer::AscendingIterator
MagicalContainer::AscendingIterator::begin() const {
  return AscendingIterator(container, 0);
}

MagicalContainer::AscendingIterator
MagicalContainer::AscendingIterator::end() const {
  return AscendingIterator(container, (unsigned long)container.size());
}

// SideCrossIterator
MagicalContainer::SideCrossIterator::SideCrossIterator(
    const SideCrossIterator &other)
    : container(other.container), currentIndex(other.currentIndex),
      reverse(other.reverse) {}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &cont,
                                                       std::size_t index,
                                                       bool rev)
    : container(cont), currentIndex(index), reverse(rev) {}

MagicalContainer::SideCrossIterator &
MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
  if (&container != &other.container) {
    throw std::runtime_error("Iterators belong to different containers");
  }
  currentIndex = other.currentIndex;
  reverse = other.reverse;
  return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(
    const SideCrossIterator &other) const {
  return currentIndex == other.currentIndex && reverse == other.reverse;
}

bool MagicalContainer::SideCrossIterator::operator!=(
    const SideCrossIterator &other) const {
  return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(
    const SideCrossIterator &other) const {
  return (*this).operator*() > (other).operator*();
}

bool MagicalContainer::SideCrossIterator::operator<(
    const SideCrossIterator &other) const {
  return (*this).operator*() < (other).operator*();
}

int MagicalContainer::SideCrossIterator::operator*() const {
  if (reverse)
    return container
        .sortedElements[(unsigned long)container.size() - currentIndex - 1];
  else
    return container.sortedElements[currentIndex];
}

MagicalContainer::SideCrossIterator &
MagicalContainer::SideCrossIterator::operator++() {
  number_steps++;
  if (number_steps == container.size() + 1) {
    throw std::runtime_error("Iterator out of range");
  }
  if (reverse) {
    ++currentIndex;
  }

  reverse = !reverse;
  return *this;
}

MagicalContainer::SideCrossIterator
MagicalContainer::SideCrossIterator::begin() const {
  return SideCrossIterator(container, 0, false);
}

MagicalContainer::SideCrossIterator
MagicalContainer::SideCrossIterator::end() const {
  if (container.sortedElements.size() % 2 == 0) {
    return SideCrossIterator(container, (container.sortedElements.size() / 2),
                             false);
  } else {
    return SideCrossIterator(container, ((container.sortedElements.size() / 2)),
                             true);
  }
}

// PrimeIterator
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
    : container(other.container), currentIndex(other.currentIndex) {}

MagicalContainer::PrimeIterator::~PrimeIterator() {}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &cont,
                                               std::size_t index)
    : container(cont), currentIndex(index) {}

MagicalContainer::PrimeIterator &
MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
  if (&container != &other.container) {
    throw std::runtime_error("Iterators belong to different containers");
  }
  currentIndex = other.currentIndex;
  return *this;
}

bool MagicalContainer::PrimeIterator::operator==(
    const PrimeIterator &other) const {
  return currentIndex == other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator!=(
    const PrimeIterator &other) const {
  return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(
    const PrimeIterator &other) const {
  return currentIndex > other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator<(
    const PrimeIterator &other) const {
  return currentIndex < other.currentIndex;
}

int &MagicalContainer::PrimeIterator::operator*() const {
  return *container.prime_pointers.at(currentIndex);
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {

  if (currentIndex >= container.prime_pointers.size()) {
    throw std::runtime_error("Iterator out of range");
  }
  if (*this == end()) {
    throw std::runtime_error("Iterator out of range");
  }
  currentIndex++;
  return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
  return PrimeIterator(container, 0);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
  return PrimeIterator(container, container.prime_pointers.size());
}

} // namespace ariel
