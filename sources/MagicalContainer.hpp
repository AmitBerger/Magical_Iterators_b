#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <vector>

namespace ariel {

// Helper function to check if a number is prime
bool isPrime(int num);

class MagicalContainer {
private:
  std::vector<int> sortedElements;

public:
  void addElement(int element);
  void removeElement(int element);
  int size() const;

  class AscendingIterator {
  private:
    MagicalContainer &container;
    std::size_t currentIndex;

  public:
    // Move constructor
    AscendingIterator(AscendingIterator &&other) = default;

    // Move assignment operator
    AscendingIterator &operator=(AscendingIterator &&other) noexcept {
      if (this != &other) {
        container = other.container;
        currentIndex = other.currentIndex;
      }
      return *this;
    }

    // Copy constructor
    AscendingIterator(const AscendingIterator &other);

    // Destructor
    ~AscendingIterator();

    // Constructor
    AscendingIterator(MagicalContainer &cont, std::size_t index = 0);

    // Copy assignment operator
    AscendingIterator &operator=(const AscendingIterator &other);

    // Comparison operators
    bool operator==(const AscendingIterator &other) const;
    bool operator!=(const AscendingIterator &other) const;
    bool operator>(const AscendingIterator &other) const;
    bool operator<(const AscendingIterator &other) const;

    // Dereference operator
    int operator*() const;

    // Increment operator
    AscendingIterator &operator++();

    // Iterator begin and end functions
    AscendingIterator begin() const;
    AscendingIterator end() const;
  };

  class SideCrossIterator {
  private:
    MagicalContainer &container;
    std::size_t currentIndex;
    bool reverse;

  public:
    // Move constructor
    SideCrossIterator(SideCrossIterator &&other) = default;

    // Move assignment operator
    SideCrossIterator &operator=(SideCrossIterator &&other) noexcept {
      if (this != &other) {
        container = other.container;
        currentIndex = other.currentIndex;
        reverse = other.reverse;
      }
      return *this;
    }

    // Copy constructor
    SideCrossIterator(const SideCrossIterator &other);

    // Destructor
    ~SideCrossIterator();

    // Constructor
    SideCrossIterator(MagicalContainer &cont, std::size_t index = 0,
                      bool rev = false);

    // Copy assignment operator
    SideCrossIterator &operator=(const SideCrossIterator &other);

    // Comparison operators
    bool operator==(const SideCrossIterator &other) const;
    bool operator!=(const SideCrossIterator &other) const;
    bool operator>(const SideCrossIterator &other) const;
    bool operator<(const SideCrossIterator &other) const;

    // Dereference operator
    int operator*() const;

    // Increment operator
    SideCrossIterator &operator++();

    // Iterator begin and end functions
    SideCrossIterator begin() const;
    SideCrossIterator end() const;
  };

  class PrimeIterator {
  private:
    MagicalContainer &container;
    std::size_t currentIndex;

  public:
    // Move constructor
    PrimeIterator(PrimeIterator &&other) = default;

    // Move assignment operator
    PrimeIterator &operator=(PrimeIterator &&other) noexcept;

    // Copy constructor
    PrimeIterator(const PrimeIterator &other);

    // Destructor
    ~PrimeIterator();

    // Constructor
    PrimeIterator(MagicalContainer &cont, std::size_t index = 0);

    // Copy assignment operator
    PrimeIterator &operator=(const PrimeIterator &other);

    // Comparison operators
    bool operator==(const PrimeIterator &other) const;
    bool operator!=(const PrimeIterator &other) const;
    bool operator>(const PrimeIterator &other) const;
    bool operator<(const PrimeIterator &other) const;

    // Dereference operator
    int operator*() const;

    // Increment operator
    PrimeIterator &operator++();

    // Iterator begin and end functions
    PrimeIterator begin() const;
    PrimeIterator end() const;
  };
};

} // namespace ariel

#endif /* MAGICALCONTAINER_HPP */
