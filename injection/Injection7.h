#ifndef INJECTION_7_H
#define INJECTION_7_H

#include <iostream>
#include <sstream>

// DEPENDECY INJECTION WITH TEMPLATES
//
// This time all dependencies are given as template arguments.
//
// This approach has the benefit of setting the dependencies at compile time
// without incurring extra runtime overhead due to virtual functions.
// The disadvantage is that dependencies cannot be changed at runtime.
//
// We can enforce template argument types using static asserts or we can inject
// totally unrelated classes as long as they have methods with the same
// signature.
// Injected classes do not necessarily need to implement the same interface.
// This is particularly interesting in testing because we are not required
// a base interface to mock.
//
// See https://www.youtube.com/watch?v=yVogS4NbL6U

namespace Injection7 {

using namespace std;

class D {
  virtual string str() const = 0;
};

// D1 and D2 extends D.

class D1 : public D {
public:
  string str() const override { return "D1"; }
};

class D2 : public D {
public:
  string str() const override { return "D2"; }
};

// C1 and C2 are unrelated concrete classes having methods with the same
// signature.

class C1 {
public:
  string str() const { return "C1"; }
};

class C2 {
public:
  string str() const { return "C2"; }
};

// B1 and B2 are unrelated classes having methods with the same signature.

template <typename T> class B1 {
  T d;

public:
  explicit B1(const T &d) : d{d} {
    static_assert(std::is_base_of<D, T>::value,
                  "Template argument T must override class D");
  }
  string str() const {
    stringstream ss;
    ss << "B(";
    ss << d.str();
    ss << ")";
    return ss.str();
  }
};

class B2 {
public:
  string str() const {
    stringstream ss;
    ss << "B1";
    return ss.str();
  }
};

template <class B, class C> class A {
  B b;
  C c;

public:
  explicit A(const B &b, C const &c) : b{b}, c{c} {}
  string str() const {
    stringstream ss;
    ss << "A(";
    ss << b.str();
    ss << ",";
    ss << c.str();
    ss << ")";
    return ss.str();
  }
};

/* ////////////////////////////////////////////////////////////////////////////
 * Examples.
 */
struct Test {
  static void execute() {

    cout << "TEMPLATE DEPENDECY INJECTION" << endl;

    C1 c1;
    C2 c2;
    D1 d1;

    B1 b1{d1};
    B2 b2;

    // Injecting using template.
    A a1{b1, c1};
    cout << a1.str() << endl;

    // Injecting using template.
    A a2{b2, c1};
    cout << a2.str() << endl;

    // Injecting using template.
    A a3{b1, c2};
    cout << a3.str() << endl;

    cout << endl;
  }
};
} // namespace Injection7

#endif // INJECTION_7_H
