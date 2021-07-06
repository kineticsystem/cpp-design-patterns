#ifndef INJECTION_7_H
#define INJECTION_7_H

#include <iostream>
#include <sstream>

// DEPENDECY INJECTION WITH TEMPLATES
//
// Consider again concrete classes A1,B1,C1,D1 with the following dependency
// structure: A1(B1(D1),C1)
// This time all dependencies are given as template parameters.

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
        string str() const {
            stringstream ss;
            ss << "B(";
            ss << d.str();
            ss << ")";
            return ss.str();
        }
    };

    template <class T1 = B<>, class T2 = C>
    class A  {
        T1 b;
        T2 c;
    public:
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

            A a1;
            cout << a1.str() << endl;

            A<B<D1>, C1> a2;
            cout << a2.str() << endl;

            cout << endl;
        }
    };
}

#endif // INJECTION_7_H
