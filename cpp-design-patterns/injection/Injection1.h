#ifndef EXAMPLE0_H
#define EXAMPLE0_H

#include <memory>
#include <iostream>

/* ////////////////////////////////////////////////////////////////////////////
 * NO DEPENDENCY INJECTION
 */

namespace Injection1 {

    using namespace std;

    // Consider the concrete classes A1,B1,C1,D1 with the following dependency
    // structure: A1(B1(D1),C1)

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
        shared_ptr<D1> d;
    public:
        B1() {
            d = make_shared<D1>();
        }
        virtual string str() const { return "B1(" + d->str() + ")"; }
    };

    class A1 {
        shared_ptr<B1> b;
        shared_ptr<C1> c;
    public:
        A1() {
            b = make_shared<B1>();
            c = make_shared<C1>();
        }
        virtual string str() const { return "A1(" + b->str() + "," + c->str() + ")"; }
    };

    /* ////////////////////////////////////////////////////////////////////////////
     * Examples.
     */
    struct Test {
        static void execute() {

            cout << "NO DEPENDENCY INJECTION" << endl;

            // This structure is highly coupled because all classes create their own
            // dependencies.
            // We cannot change the dependencies and we cannot mock them so testing
            // these classes in isolation is impossible.

            auto a = make_shared<A1>();
            cout << a->str() << endl;

            cout << endl;
        }
    };
}

#endif
