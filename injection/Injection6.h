#ifndef INJECTION_6_H
#define INJECTION_6_H

#include <iostream>
#include <memory>
#include <sstream>

// DEPENDECY INJECTION WITH BUILDERS
//
// Consider again concrete classes A1,B1,C1,D1 with the following dependency
// structure: A1(B1(D1),C1)
// This time all dependencies are given in terms of interfaces A,B,C,D.

namespace Injection6 {

using namespace std;

class D {
public:
  virtual string str() const { return "D"; }
};

class C {
public:
  virtual string str() const { return "C"; }
};

class B {
public:
  virtual string str() const { return "B"; }
};

class A {
public:
  virtual string str() const { return "A"; }
};

// Each concrete class implements the corresponding interface.

class D1 : public D {
public:
  D1() {}
  virtual string str() const override { return "D1"; }
};

class C1 : public C {
public:
  C1() {}
  virtual string str() const override { return "C1"; }
};

class B1 : public B {
  unique_ptr<D> d;

public:
  B1() {}
  void setD(unique_ptr<D> d) { this->d = move(d); }
  virtual string str() const override {
    stringstream ss;
    ss << "B1(";
    if (d)
      ss << d->str();
    ss << ")";
    return ss.str();
  }
};

class A1 : public A {

  unique_ptr<B> b; // optional
  unique_ptr<C> c; // optional

  class Builder {
    unique_ptr<A1> a = make_unique<A1>();

  public:
    auto &setB(unique_ptr<B> b) {
      a->setB(move(b));
      return *this;
    }
    auto &setC(unique_ptr<C> c) {
      a->setC(move(c));
      return *this;
    }
    auto build() { return move(a); }
  };

public:
  A1() {}

  void setB(unique_ptr<B> b) { this->b = move(b); }
  void setC(unique_ptr<C> c) { this->c = move(c); }

  virtual string str() const override {
    stringstream ss;
    ss << "A1(";
    if (b)
      ss << b->str();
    if (b && c)
      ss << ",";
    if (c)
      ss << c->str();
    ss << ")";
    return ss.str();
  }

  static Builder builder() { return {}; }
};

// This time the structure is loosely coupled by using interfaces and it is
// easy to swap B1 with a subclass B2 without necessarily providing the
// dependency D1 or a subclass of D1.

class B2 : public B {
public:
  virtual string str() const override { return "B2"; }
};

class C2 : public C {
public:
  virtual string str() const override { return "C2"; }
};

/* ////////////////////////////////////////////////////////////////////////////
 * Examples.
 */
struct Test {
  static void execute() {

    cout << "DEPENDECY INJECTION WITH BUILDERS" << endl;

    auto a1 = make_unique<A1>();
    cout << a1->str() << endl;

    auto a2 =
        A1::builder().setB(make_unique<B2>()).setC(make_unique<C2>()).build();
    cout << a2->str() << endl;

    cout << endl;
  }
};
} // namespace Injection6

#endif
