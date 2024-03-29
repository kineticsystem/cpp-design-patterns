#include "builder/StepBuilder1.h"
#include "builder/StepBuilder2.h"
#include "builder/StepBuilder3.h"
#include "builder/StepBuilder4.h"
#include "expected/Expected.h"
#include "factory/Factory1.h"
#include "injection/Injection1.h"
#include "injection/Injection2.h"
#include "injection/Injection3.h"
#include "injection/Injection4.h"
#include "injection/Injection5.h"
#include "injection/Injection6.h"
#include "injection/Injection7.h"
#include "injection/Injection8.h"
#include "mvc/ModelViewController1.h"
#include "mvc/ModelViewController2.h"
#include "pimpl/Label.h"
#include "pimpl/Widget.h"

class Expected {
public:
  bool ok() { return true; }
};

Expected funct1() { return {}; }

int main() {

  if (auto result = funct1(); !result.ok()) {
    return 1;
  } else if (result = funct1(); !result.ok()) {
  }

  stepbuilder1::Test::execute();
  stepbuilder2::Test::execute();
  stepbuilder3::Test::execute();
  stepbuilder4::Test::execute();

  Injection1::Test::execute();
  Injection2::Test::execute();
  Injection3::Test::execute();
  Injection4::Test::execute();
  Injection5::Test::execute();
  Injection6::Test::execute();
  Injection7::Test::execute();
  Injection8::Test::execute();

  Factory1::Test::execute();

  DPointer::Test::execute();

  ModelViewController1::Test::execute();
  ModelViewController2::Test::execute();

  expected::Test::execute();

  return 0;
}
