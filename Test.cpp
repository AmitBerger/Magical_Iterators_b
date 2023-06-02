
#include "doctest.h"
#include "sources/MagicalContainer.hpp"
using namespace ariel;

TEST_SUITE("MagicalContainer Tests") {
  TEST_CASE("Adding and Removing Elements") {
    MagicalContainer container;

    CHECK(container.size() == 0);

    container.addElement(5);
    container.addElement(10);
    container.addElement(15);

    CHECK(container.size() == 3);

    container.removeElement(10);

    CHECK(container.size() == 2);
  }

  TEST_CASE("AscendingIterator") {
    ariel::MagicalContainer container;
    container.addElement(5);
    container.addElement(10);
    container.addElement(15);

    MagicalContainer::AscendingIterator ascIter(container);

    auto it = ascIter.begin();
    auto end = ascIter.end();

    CHECK(*it == 5);
    CHECK(it != end);

    ++it;
    CHECK(*it == 10);

    ++it;
    CHECK(*it == 15);

    ++it;
    CHECK(it == end);
  }

  TEST_CASE("SideCrossIterator") {
    ariel::MagicalContainer container;
    container.addElement(5);
    container.addElement(10);
    container.addElement(15);
    MagicalContainer::SideCrossIterator crossIter(container);
    auto it = crossIter.begin();
    auto end = crossIter.end();

    CHECK(*it == 5);
    CHECK(it != end);

    ++it;
    CHECK(*it == 15);

    ++it;
    CHECK(*it == *end);
  }

  TEST_CASE("PrimeIterator") {
    ariel::MagicalContainer container;
    container.addElement(2);
    container.addElement(4);
    container.addElement(5);
    container.addElement(7);
    MagicalContainer::PrimeIterator primeIter(container);
    auto it = primeIter.begin();
    auto end = primeIter.end();

    CHECK(*it == 2);
    CHECK(it != end);

    ++it;
    CHECK(*it == 5);

    ++it;
    CHECK(*it == 7);

    ++it;
    CHECK(it == end);
  }

  TEST_CASE("Empty Container") {
    ariel::MagicalContainer container;

    CHECK(container.size() == 0);

    // Test AscendingIterator with an empty container
    MagicalContainer::AscendingIterator ascIter(container);

    auto it = ascIter.begin();
    auto end = ascIter.end();

    CHECK(it == end);

    // Test SideCrossIterator with an empty container
    MagicalContainer::SideCrossIterator crossIter(container);
    auto itC = crossIter.begin();
    auto endC = crossIter.end();

    CHECK(itC == endC);

    // Test PrimeIterator with an empty container
    MagicalContainer::PrimeIterator primeIter(container);
    auto itP = primeIter.begin();
    auto endP = primeIter.end();

    CHECK(itP == endP);
  }

  TEST_CASE("Removing Nonexistent Element") {
    ariel::MagicalContainer container;
    container.addElement(5);
    container.addElement(10);

    CHECK(container.size() == 2);

    // Try to remove a nonexistent element
    CHECK_THROWS(container.removeElement(15));

    CHECK(container.size() == 2);
  }

  TEST_CASE("Iterating over an Empty Range") {
    ariel::MagicalContainer container;

    // Test AscendingIterator with an empty range
    MagicalContainer::AscendingIterator ascIter(container);

    auto it = ascIter.begin();
    auto end = ascIter.end();

    CHECK(it == end);

    // Test SideCrossIterator with an empty range
    MagicalContainer::SideCrossIterator crossIter(container);
    auto itC = crossIter.begin();
    auto endC = crossIter.end();

    CHECK(itC == endC);

    // Test PrimeIterator with an empty range
    MagicalContainer::PrimeIterator primeIter(container);
    auto itP = primeIter.begin();
    auto endP = primeIter.end();

    CHECK(itP == endP);
  }

  TEST_CASE("Iterating over a Single Element") {
    ariel::MagicalContainer container;
    container.addElement(7);

    // Test AscendingIterator with a single element
    MagicalContainer::AscendingIterator ascIter(container);

    auto it = ascIter.begin();
    auto end = ascIter.end();

    CHECK(*it == 7);
    CHECK(it != end);

    ++it;
    CHECK(it == end);

    // Test SideCrossIterator with a single element
    MagicalContainer::SideCrossIterator crossIter(container);
    auto itC = crossIter.begin();
    auto endC = crossIter.end();

    CHECK(*itC == 7);
    // CHECK(itC != endC);

    ++itC;
    CHECK(*itC == *endC);

    // Test PrimeIterator with a single element
    MagicalContainer::PrimeIterator primeIter(container);
    auto itP = primeIter.begin();
    auto endP = primeIter.end();

    CHECK(*itP == 7);
    CHECK(itP != endP);

    ++itP;
    CHECK(*itP == *endP);
  }
}
