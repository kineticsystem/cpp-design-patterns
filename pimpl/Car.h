#ifndef CAR_H
#define CAR_H

#include <memory>
#include <iostream>

class Car
{
private:
    class CarImpl;
    std::unique_ptr<CarImpl> pimpl;
public:
    Car();
    ~Car();
    void test();

    /* ////////////////////////////////////////////////////////////////////////////
     * Examples.
     */
    struct Test {
        static void execute() {

            std::cout << "PIMPL IDIOM" << std::endl;

            Car car;
            car.test();

            std::cout << std::endl;
        }
    };
};

#endif // CAR_H
