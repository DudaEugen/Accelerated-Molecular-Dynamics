#include "tests.hpp"
#include "constants/Elements.hpp"

using namespace md;

namespace testElementFunctions
{
    void testElementToString()
    {
        assert(elementToString(element::H) == "H");
        assert(elementToString(element::He) == "He");
        assert(elementToString(element::Al) == std::string("Al"));
        assert(elementToString(element::Ar) == std::string("Ar"));
    }

    void testParseElement()
    {
        assert(element::H == parseElement("H"));
        assert(element::Ti == parseElement("Ti"));
        assert(element::Ag == parseElement(std::string("Ag")));
        assert(element::Cu == parseElement(std::string("Cu")));
    }

    void testAtomicNumber()
    {
        assert(atomicNumber(element::H) == 1);
        assert(atomicNumber(element::O) == 8);
        assert(atomicNumber(element::Ni) == 28);
        assert(atomicNumber(element::Au) == 79);
    }

    void testAtomicMassAverage()
    {
        assert(atomicMass(element::H).average() == 1);
        assert(atomicMass(element::He).average() == 4);
        assert(atomicMass(element::Li).average() == 7);
        assert(atomicMass(element::Zn).average() == 65);
    }

    void testAtomicMassRandom()
    {
        assert(atomicMass(element::Al).random() == 27);
        assert(contain({16, 17, 18}, atomicMass(element::O).random()));
        assert(contain({36, 38, 40}, atomicMass(element::Ar).random()));
        assert(contain({58, 60, 61, 62, 64}, atomicMass(element::Ni).random()));
    }

    void testException()
    {
        bool isCatched = false;
        try
        {
            parseElement("Hh");
        }
        catch(const ElementException& e)
        {
            isCatched = true;
        }
        assert(isCatched);
    }
}

void testElement()
{
    testElementFunctions::testElementToString();
    testElementFunctions::testParseElement();
    testElementFunctions::testAtomicNumber();
    testElementFunctions::testAtomicMassAverage();
    testElementFunctions::testAtomicMassRandom();
    testElementFunctions::testException();
}
