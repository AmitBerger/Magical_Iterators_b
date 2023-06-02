#include "MagicalContainer.hpp"
#include <algorithm>
#include <cmath>
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
  elements.push_back(element);
  sortedElements.push_back(element);
  std::sort(sortedElements.begin(), sortedElements.end());
}

void MagicalContainer::removeElement(int element) {
  auto it = std::find(elements.begin(), elements.end(), element);
  if (it != elements.end()) {
    elements.erase(it);
  } else {
    throw std::runtime_error("Element not found");
  }
}

int MagicalContainer::size() const { return elements.size(); }

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
  if (currentIndex >= (container.sortedElements.size()/2)+1) {
    throw std::runtime_error("Iterator out of range");
  }

  if (reverse) {
    ++currentIndex;
  }

  reverse = !reverse;
  if (currentIndex >= (container.sortedElements.size()/2)+1) {
    throw std::runtime_error("Iterator out of range");
  }
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
    return SideCrossIterator(
        container, ((container.sortedElements.size() / 2)), true);
  }
}


// PrimeIterator
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
    : container(other.container), currentIndex(other.currentIndex) {}

MagicalContainer::PrimeIterator::~PrimeIterator() {}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &cont,
                                               std::size_t index)
    : container(cont), currentIndex(index) {
  while (currentIndex < (unsigned long)container.size() &&
         !isPrime(container.sortedElements[currentIndex])) {
    ++currentIndex;
  }
}

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
  return container.sortedElements[currentIndex] >
         container.sortedElements[other.currentIndex];
}

bool MagicalContainer::PrimeIterator::operator<(
    const PrimeIterator &other) const {
  return container.sortedElements[currentIndex] <
         container.sortedElements[other.currentIndex];
}

int MagicalContainer::PrimeIterator::operator*() const {
  return container.sortedElements[currentIndex];
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
  ++currentIndex;
  while (currentIndex < container.sortedElements.size() &&
         !isPrime(container.sortedElements[currentIndex])) {
    ++currentIndex;
  }
  if (currentIndex > container.sortedElements.size()) {
    throw std::runtime_error("Iterator out of range");
  }
  return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
  size_t startIndex = 0;
  while (startIndex < (unsigned long)container.size() &&
         !isPrime(container.sortedElements[startIndex])) {
    ++startIndex;
  }
  return PrimeIterator(container, startIndex);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
  return PrimeIterator(container, (unsigned long)container.size());
}

} // namespace ariel
