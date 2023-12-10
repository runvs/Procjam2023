#ifndef ELEMENT_FACTORY_HPP
#define ELEMENT_FACTORY_HPP

#include <elements_lib/element.hpp>
#include <elements_lib/periodic_system.hpp>
#include <set>
#include <string>
#include <vector>

class ElementFactory {
public:
    ElementFactory();
    std::string makeName(Element& e);
    void makeElementalProperties(Element& e);
    Element makeRandomElement(PeriodicSystem& system);

private:
    std::vector<std::string> consonants {};
    std::vector<std::string> vowels {};
    int m_currentAtmicNumber { 1 };

    std::set<std::string> m_createdSymbols;

    std::string makeRandomSymbol();
    float calculateElektronegativity(Element const& e);
    float calculateMeltingPoint(Element& e);
};

#endif // ELEMENT_FACTORY_HPP
