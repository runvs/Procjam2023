#include "element_factory.hpp"

#include "system_helper.hpp"
#include <random/random.hpp>
#include <strutils.hpp>
#include <algorithm>

template <class C, class T>
auto contains(C const& v, T const& x) -> decltype(end(v), true)
{
    return end(v) != std::find(begin(v), end(v), x);
}

ElementFactory::ElementFactory()
{
    vowels = { "a", "e", "i", "o", "u" };
    consonants = { "b", "c", "d", "f", "g", "h", "k", "l", "m", "n", "p", "q", "r", "s", "t", "v",
        "w", "x", "y", "z" };
}

std::string ElementFactory::makeName(Element& e)
{
    if (e.group == 15) {
        return e.symbol + "on";
    }
    auto const choice = jt::Random::getInt(0, 6);
    if (choice == 0 || choice == 1 || choice == 2) {
        return e.symbol
            + jt::SystemHelper::select_randomly(std::vector { "", "t", "s", "m", "r", "l" })
            + jt::SystemHelper::select_randomly(
                std::vector { "", "in", "int", "at", "ath", "ant", "anth", "s", "r" })
            + jt::SystemHelper::select_randomly(std::vector { "ium", "ium", "on" });
    }
    if (choice == 3 || choice == 4) {
        if (contains(vowels, std::string { e.symbol.back() })) {
            return e.symbol + jt::SystemHelper::select_randomly(consonants)
                + jt::SystemHelper::select_randomly(std::vector { "gon", "son", "rine" });
        } else {
            return e.symbol + jt::SystemHelper::select_randomly(vowels)
                + jt::SystemHelper::select_randomly(std::vector { "gon", "son", "rine" });
        }
    }
    if (choice == 5) {
        return e.symbol + jt::SystemHelper::select_randomly(std::vector { "ran", "ron", "rum" });
    }
    if (choice == 6) {
        if (contains(vowels, std::string { e.symbol.back() })) {
            return e.symbol + "ckel";
        } else {
            return e.symbol + "tium";
        }
    }

    return "";
}

void ElementFactory::makeElementalProperties(Element& e)
{
    e.density
        = static_cast<float>(std::pow(e.atomic_number, 1.5f)) * jt::Random::getFloat(0.5f, 1.5f);

    e.thermal_melting_point = calculateMeltingPoint(e);
    e.thermal_boiling_point = std::clamp(e.thermal_melting_point
            + jt::Random::getFloatGauss(
                e.thermal_melting_point * 0.5f, e.thermal_melting_point * 0.2f),
        25.0f, std::numeric_limits<float>::max());

    e.reactivity_pH = jt::Random::getFloat(0.1f, 13.9f);
    if (e.group == 15) {
        e.reactivity_pH = 7.0f;
    }

    e.thermal_conductivity = jt::Random::getFloat(0.05f, 500.0f);
    e.thermal_capacity = jt::Random::getFloat(0.1f, sqrt(e.density));

    e.electrical_conductivity = std::clamp(
        jt::Random::getFloatGauss(0.0f, 300.0f), 0.0f, std::numeric_limits<float>::max());

    if (e.electrical_conductivity == 0) {
        e.electrical_capacity = std::clamp(
            jt::Random::getFloatGauss(20, 10), 0.0f, std::numeric_limits<float>::max());
    }

    e.magnetic_susceptibility = jt::Random::getFloatGauss(0, 10.0f);

    e.reactivity_electronegativity = calculateElektronegativity(e);
}

Element ElementFactory::makeRandomElement(PeriodicSystem& system)
{
    Element e;
    e.symbol = makeRandomSymbol();
    e.atomic_number = m_currentAtmicNumber;
    e.period = system.getCurrentPeriod();
    e.group = system.getCurrentGroup();

    // make elements in the upper periods be on the left and right side
    int const max_elements_per_period = std::pow(2, e.period);
    if (e.group > max_elements_per_period / 2) {
        if (e.period == 1) {
            e.group = e.group + 13;
        } else if (e.period == 2) {
            e.group = e.group + 11;
        } else if (e.period == 3) {
            e.group = e.group + 7;
        }
    }

    e.name = makeName(e);

    m_currentAtmicNumber++;

    makeElementalProperties(e);

    return e;
}

float ElementFactory::calculateElektronegativity(Element const& e)
{
    // 0.5 - 5.0
    if (e.group == 15) {
        return 0.0f;
    } else {
        float const elements_per_period = 16;
        auto group_factor = std::clamp((e.group) / elements_per_period, 0.0f, 1.0f);
        auto period_factor = std::clamp((10.0f - e.period) / 10.0f, 0.0f, 1.0f);
        return group_factor * period_factor * 4.5f + 0.5f;
    }
}

float ElementFactory::calculateMeltingPoint(Element& e)
{
    auto v = 0.0f;
    if (e.group == 1 || e.group == 15) {
        if (e.period == 1) {
            v = jt::Random::getFloat(20.0f, 70.0f);
        } else {
            v = jt::Random::getFloatGauss(300.0f + 10.0f * e.period, 50.0f);
        }
    } else if (e.group == 2 || e.group == 3 || e.group == 4 || e.group == 5 || e.group == 6) {
        auto const g = e.group - 2.0f;
        auto const mu = 800.0f + g * 250.0f;
        auto const periodoffset = e.period * (50.0f + (30 * g));
        v = jt::Random::getFloatGauss(mu, 100.0f) + periodoffset;
    } else if (e.group == 7 || e.group == 8 || e.group == 9) {
        auto const g = 10 - e.group;
        auto const mu = 800.0f + g * 250.0f;
        auto const periodoffset = e.period * (50.0f + (30 * g));
        v = jt::Random::getFloatGauss(mu, 100.0f) + periodoffset;
    } else {
        v = jt::Random::getFloat(50.0f, 1000.0f)
            + jt::Random::getFloatGauss(e.period * 30.0, e.period * 5.0f);
    }

    v += jt::Random::getFloatGauss(0, std::abs(e.thermal_melting_point * 0.3f) + 1.0f);

    return std::clamp(v, 1.0f, std::numeric_limits<float>::max());
}

std::string ElementFactory::makeRandomSymbol()
{
    std::string symbol;

    if (jt::Random::getChance(0.75f)) {
        symbol = strutil::to_upper(jt::SystemHelper::select_randomly(consonants))
            + jt::SystemHelper::select_randomly(vowels);
    } else {
        symbol = strutil::to_upper(jt::SystemHelper::select_randomly(vowels))
            + jt::SystemHelper::select_randomly(consonants);
    }

    if (symbol.at(0) == 'T' || symbol.at(0) == 'K' || symbol.at(0) == 'R' || symbol.at(0) == 'S') {
        if (jt::Random::getChance(0.75f)) {
            symbol = std::string { symbol.at(0) } + 'h' + std::string { symbol.at(1) };
        }
    }

    if (m_createdSymbols.contains(symbol)) {
        return makeRandomSymbol();
    }
    m_createdSymbols.insert(symbol);
    return symbol;
}
