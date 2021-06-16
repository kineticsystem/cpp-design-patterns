#include "builder/StepBuilder1.h"
#include "builder/StepBuilder2.h"
#include "builder/StepBuilder3.h"
#include "injection/Injection1.h"
#include "injection/Injection2.h"
#include "injection/Injection3.h"
#include "injection/Injection4.h"
#include "injection/Injection5.h"
#include "injection/Injection6.h"
#include "factory/Factory1.h"
#include "pimpl/Car.h"

int main() {

    StepBuilder1::Test::execute();
    StepBuilder2::Test::execute();
    StepBuilder3::Test::execute();

    Injection1::Test::execute();
    Injection2::Test::execute();
    Injection3::Test::execute();
    Injection4::Test::execute();
    Injection5::Test::execute();
    Injection6::Test::execute();

    Factory1::Test::execute();

    Car::Test::execute();

    return 0;
}
