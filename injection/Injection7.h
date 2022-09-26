#ifndef INJECTION_7_H
#define INJECTION_7_H

#include <iostream>
#include <sstream>

// DEPENDECY INJECTION WITH TEMPLATES
//
// This time all dependencies are given as template parameters.
//
// This approach has the benefit of setting the dependencies at compile time
// without incurring extra runtime overhead due to virtual functions.
// The disadvantage is that dependencies cannot be changed at runtime.
//
// Another advantage is that we can inject totally unrelated classes as long as
// they have methods with the same signature. Injected classes do not need to
// implement the same interface.
//
// See https://www.youtube.com/watch?v=yVogS4NbL6U

namespace Injection7 {

using namespace std;

class D {
public:
  string str() const { return "D"; }
};

class D1 {
public:
  string str() const { return "D1"; }
};

class C {
public:
  string str() const { return "C"; }
};

class C1 {
public:
  string str() const { return "C1"; }
};

template <class D> class B {
  D d;

public:
  explicit B(const D &d) : d{d} {}
  string str() const {
    stringstream ss;
    ss << "B(";
    ss << d.str();
    ss << ")";
    return ss.str();
  }
};

class B1 {
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

    C c;
    C c1;
    D d;
    D d1;

    B<decltype(c)> b{c};
    B1 b1;

    // Injecting using template.
    A<decltype(b), decltype(c)> a{b, c};
    cout << a.str() << endl;

    // Injecting using template.
    A<decltype(b1), decltype(c1)> a1{b1, c1};
    cout << a1.str() << endl;

    // Injecting using template.
    A<decltype(b), decltype(c1)> a3{b, c1};
    cout << a3.str() << endl;

    cout << endl;
  }
};
} // namespace Injection7

#endif // INJECTION_7_H
