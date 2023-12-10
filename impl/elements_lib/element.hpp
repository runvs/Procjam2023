#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <nlohmann.hpp>
#include <ostream>
#include <string>
#include <vector>

struct Element {
    std::string name {};
    std::string symbol {};
    int atomic_number { 1 };
    int period { 1 };
    int group { 1 };

    float density { 1.0f };

    float thermal_melting_point {};
    float thermal_boiling_point {};

    float reactivity_pH { 7.0f };
    float reactivity_electronegativity { 0.0f };

    float thermal_conductivity { 0.0f };
    float thermal_capacity { 1.0f };

    float electrical_conductivity { 0.0f };
    float electrical_capacity { 0.0f };

    float magnetic_susceptibility { 0.0f };

    friend std::ostream& operator<<(std::ostream& os, Element const& obj)
    {
        return os << "name: '" << obj.name << "' symbol: '" << obj.symbol
                  << "' atomic_number: " << obj.atomic_number << "\n\tdensity: " << obj.density
                  << "\n\n\t group: " << obj.group << "\n\t period: " << obj.period
                  << "\n\n\t meltingPoint: " << obj.thermal_melting_point
                  << "\n\t boilingPoint: " << obj.thermal_boiling_point
                  << "\n\n\t pH: " << obj.reactivity_pH
                  << "\n\t electronegativity: " << obj.reactivity_electronegativity
                  << "\n\n\t thermal_conductivity: " << obj.thermal_conductivity
                  << "\n\t thermal_capacity: " << obj.thermal_capacity

                  << "\n\n\t electrical_conductivity: " << obj.electrical_conductivity
                  << "\n\t electrical_capacity: " << obj.electrical_capacity
                  << "\n\t magnetic_susceptibility: " << obj.magnetic_susceptibility;
    }
};

void to_json(nlohmann::json& j, Element const& elem);

#endif // ELEMENT_HPP
