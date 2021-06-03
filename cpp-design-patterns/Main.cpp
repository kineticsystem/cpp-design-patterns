#include "builder/StepBuilder1.h"
#include "builder/StepBuilder2.h"
#include "builder/StepBuilder3.h"
#include "factory/Factory1.h"

int main() {

    StepBuilder1::Test::execute();
    StepBuilder2::Test::execute();
    StepBuilder3::Test::execute();
    Factory1::Test::execute();

    return 0;
}
