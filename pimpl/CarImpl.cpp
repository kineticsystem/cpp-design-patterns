#include "Car.h"
#include "CarImpl.h"
#include <iostream>

Car::CarImpl::CarImpl()
{

}

Car::CarImpl::~CarImpl()
{

}

void Car::CarImpl::test()
{
    std::cout << "I am a car" << std::endl;
}
