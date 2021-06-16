#include "Car.h"
#include "CarImpl.h"

Car::Car() : pimpl(new CarImpl)
{

}

Car::~Car() = default;

void Car::test()
{
    pimpl->test();
}


