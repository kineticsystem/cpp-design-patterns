#include "StepBuilder2.h"

#include <sstream>

using namespace StepBuilder2;

std::string Animal::name() const
{
    return m_data.name;
}

double Animal::weight() const
{
    return m_data.weight;
}

int Animal::legs() const
{
    return m_data.legs;
}

std::string Animal::toString() const
{
    std::ostringstream buffer;
    buffer << "Animal[name=" << m_data.name << ", weight=" << m_data.weight << ", legs=" << m_data.legs << "]";
    return buffer.str();
}
