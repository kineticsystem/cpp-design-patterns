#include "StepBuilder3.h"

#include <sstream>

using namespace StepBuilder3;

Tag &Animal::tag() const
{
    return *m_data.tag;
}

std::string Animal::name() const
{
    return m_data.name;
}

float Animal::weight() const
{
    return m_data.weight;
}

uint8_t Animal::legs() const
{
    return m_data.legs;
}

std::string Animal::toString() const
{
    std::ostringstream buffer;
    buffer << "Animal[tag=" << m_data.tag->number()
           << ",name=" << m_data.name
           << ", weight=" << m_data.weight
           << ", legs=" << unsigned(m_data.legs) << "]";
    return buffer.str();
}
