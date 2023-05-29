
#include <iostream>
#include <stdexcept>
#include "doctest.h"
#include "sources/MagicalContainer.hpp"

using namespace std;


TEST_CASE("Check Ascending Iterator ") 
{
    MagicalContainer container;
    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);

    AscendingIterator ascIter(container);

    auto it = ascIter.begin();

    CHECK( (*it) == 2);
    it++;
    CHECK( (*it) == 3);
    it++;
    CHECK( (*it) == 9);
    it++;
    CHECK( (*it) == 17);
    it++;
    CHECK( (*it) == 25);

    AscendingIterator ascIter1(container);

    auto itt = ascIter1.begin();

    CHECK( (*itt) == 2);
    ++itt;
    CHECK( (*itt) == 3);
    ++itt;
    CHECK( (*itt) == 9);
    ++itt;
    CHECK( (*itt) == 17);
    ++itt;
    CHECK( (*itt) == 25);

}

TEST_CASE("Check Cross Iterator")
{
    MagicalContainer container;
    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);

    SideCrossIterator crossIter(container);

    auto itt = crossIter.begin();

    CHECK( (*itt) == 2);
    itt++;
    CHECK( (*itt) == 25);
    itt++;
    CHECK( (*itt) == 3);
    itt++;
    CHECK( (*itt) == 17);
    itt++;
    CHECK( (*itt) == 9);

    SideCrossIterator crossIter1(container);

    auto it = crossIter1.begin();

    CHECK( (*it) == 2);
    ++it;
    CHECK( (*it) == 25);
    ++it;
    CHECK( (*it) == 3);
    ++it;
    CHECK( (*it) == 17);
    ++it;
    CHECK( (*it) == 9);

}

TEST_CASE("Check Prime Iterator")
{
    MagicalContainer container;
    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);

    PrimeIterator primeIter(container);

    auto it = primeIter.begin();

    CHECK( (*it) == 2);
    it++;
    CHECK( (*it) == 3);
    it++;
    CHECK( (*it) == 17);

    PrimeIterator primeIter1(container);

    auto itt = primeIter1.begin();

    CHECK( (*itt) == 2);
    ++itt;
    CHECK( (*itt) == 3);
    ++itt;
    CHECK( (*itt) == 17);
}
