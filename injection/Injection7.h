#ifndef INJECTION_7_H
#define INJECTION_7_H

#include <iostream>
#include <sstream>

// DEPENDECY INJECTION WITH TEMPLATES
//
// This time all dependencies are given as template parameters.

// This approach has the benefit of setting the dependencies at compile time
// without incurring in the extra runtime overhead due to virtual functions.
// The disadvantage is that dependencies cannot be changed at runtime.

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

    class C  {
    public:
        string str() const { return "C"; }
    };

    class C1  {
    public:
        string str() const { return "C1"; }
    };

    template <class T = D>
    class B {
        T d;
    public:
        B() {}
        B(const T &d) : d{d} {}
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

    template <class T1 = B<>, class T2 = C>
    class A  {
        T1 b;
        T2 c;
    public:
        A() {};
        A(const T1 &b, T2 const &c) : b{b}, c{c} {}
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

            // Injecting using template.
            A a1;
            cout << a1.str() << endl;

            // Injecting using template.
            A<B<D1>, C1> a2;
            cout << a2.str() << endl;

            // Injecting using template.
            A<B1, C1> a3;
            cout << a3.str() << endl;

            // Injecting using constructor.
            B1 b1;
            C1 c1;
            A a4{b1, c1};
            cout << a4.str() << endl;

            // Injecting using constructor.
            B{D1{}};
            A a5{B{D1{}}, C1{}};
            cout << a5.str() << endl;

            cout << endl;
        }
    };
}

#endif // INJECTION_7_H
