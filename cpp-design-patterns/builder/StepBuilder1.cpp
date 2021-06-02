#include "StepBuilder1.h"

#include <sstream>

using namespace StepBuilder1;

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
    buffer << "Animal[name=" << m_data.name << ", weight=" << m_data.weight << ", legs=" << unsigned(m_data.legs) << "]";
    return buffer.str();
}
