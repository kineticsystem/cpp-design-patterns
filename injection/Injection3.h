#ifndef INJECTION_3_H
#define INJECTION_3_H

#include <memory>
#include <iostream>

// POOR MAN'S DEPENDENCY INJECTION ALSO CALLED PURE DEPENDENCY INJECTION
//
// Consider again concrete classes A1,B1,C1,D1 with the following dependency
// structure: A1(B1(D1),C1)
// This time all dependencies are given in terms of interfaces A,B,C,D.
//
// https://blog.ploeh.dk/2014/06/10/pure-di/

namespace Injection3 {

    using namespace std;

    class D {
    public:
        virtual string str() const { return "D"; }
    };

    class C  {
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
        B1(unique_ptr<D> d) : d{move(d)} {}
        virtual string str() const override { return "B1(" + d->str() + ")"; }
    };

    class A1 : public A {
        unique_ptr<B> b;
        unique_ptr<C> c;
    public:
        A1(unique_ptr<B> b, unique_ptr<C> c) : b{move(b)}, c{move(c)} {}
        virtual string str() const override { return "A1(" + b->str() + "," + c->str() + ")"; }
    };

    // This time the structure is loosely coupled by using interfaces and it is
    // easy to swap B1 with any implementation of the interface B without
    // providing the dependency D1.
    // All classes can be easily tested in isolation because we can provide
    // a mock of the interface B without providing a mock of the interface D.
    //
    // The name "Poor Man's Dependency Injection and Pure Dependency Injection"
    // come from the fact that dependencies are injected into the constructor
    // esplicitly without using a Dependency Injection Container.

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

            cout << "PURE DEPENDENCY INJECTION" << endl;

            auto a1 = make_unique<A1>(
                make_unique<B1>(
                    make_unique<D1>()),
                make_unique<C1>());
            cout << a1->str() << endl;

            auto a2 = make_unique<A1>(
                make_unique<B2>(),
                make_unique<C2>());
            cout << a2->str() << endl;

            cout << endl;
        }
    };
}

#endif
