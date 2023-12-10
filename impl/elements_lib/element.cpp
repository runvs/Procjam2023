
#include "element.hpp"

void to_json(nlohmann::json& j, Element const& elem)
{
    j = nlohmann::json { { "name", elem.name }, { "symbol", elem.symbol },
        { "atomic_number", elem.atomic_number }, { "period", elem.period }, { "group", elem.group },
        { "density", elem.density }, { "thermal_melting_point", elem.thermal_melting_point },
        { "thermal_boiling_point", elem.thermal_boiling_point },
        { "reactivity_pH", elem.reactivity_pH },
        { "reactivity_electronegativity", elem.reactivity_electronegativity },
        { "thermal_conductivity", elem.thermal_conductivity },
        { "thermal_capacity", elem.thermal_capacity },
        { "electrical_conductivity", elem.electrical_conductivity },
        { "electrical_capacity", elem.electrical_capacity },
        { "magnetic_susceptibility", elem.magnetic_susceptibility } };
}
