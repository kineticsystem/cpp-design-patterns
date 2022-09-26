#ifndef INJECTION_2_H
#define INJECTION_2_H

#include <iostream>
#include <memory>

namespace Injection2 {

using namespace std;

// A STEP FORWARD TO DEPENDENCY INJECTION
//
// Consider the concrete classes A1,B1,C1,D1 with the following dependency
// structure: A1(B1(D1),C1)
// In this case all concrete dependencies are given in each constructor.

class D1 {
public:
  D1() {}
  virtual string str() const { return "D1"; }
};

class C1 {
public:
  C1() {}
  virtual string str() const { return "C1"; }
};

class B1 {
  unique_ptr<D1> d;

public:
  explicit B1(unique_ptr<D1> d) : d{move(d)} {}
  virtual string str() const { return "B1(" + d->str() + ")"; }
};

class A1 {
  unique_ptr<B1> b;
  unique_ptr<C1> c;

public:
  explicit A1(unique_ptr<B1> b, unique_ptr<C1> c) : b{move(b)}, c{move(c)} {}
  virtual string str() const { return "A1(" + b->str() + "," + c->str() + ")"; }
};

// The structure is still highly coupled and we cannot swap B1 with a subclass
// without providing the hard-coded dependency D1 or its subclass.
// For the same reason we cannot test these classes in isolation because we
// cannot provide a mock of B1 without providing a mock for D1.

/* ////////////////////////////////////////////////////////////////////////////
 * Examples.
 */
struct Test {
  static void execute() {

    cout << "PARTIAL DEPENDENCY INJECTION" << endl;

    auto a =
        make_unique<A1>(make_unique<B1>(make_unique<D1>()), make_unique<C1>());
    cout << a->str() << endl;

    cout << endl;
  }
};
} // namespace Injection2

#endif
