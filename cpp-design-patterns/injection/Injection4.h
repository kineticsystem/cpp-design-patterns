#ifndef EXAMPLE3_H
#define EXAMPLE3_H

#include <memory>
#include <iostream>

// BASTARD DEPENDENCY INJECTION
//
// Consider again concrete classes A1,B1,C1,D1 with the following dependency
// structure: A1(B1(D1),C1)
// All dependencies are given in terms of interfaces A,B,C,D with the benefits
// we explained in Example 2.
// This time we also provide a default constructor for each class which
// provide a default implementations of all dependencies.
//
// An additional constructor is used to swap the dependency and it is mostly
// used for testing.
//
// https://blogs.cuttingedge.it/steven/posts/2013/di-anti-pattern-multiple-constructors/
// https://stackoverflow.com/questions/7099406/what-is-the-real-difference-between-bastard-injection-and-poor-mans-injectio
//

namespace Injection4 {

    using namespace std;

    class D {
    public:
        virtual ~D() = default;
        virtual string str() const { return "D"; }
    };

    class C  {
    public:
        virtual ~C() = default;
        virtual string str() const { return "C"; }
    };

    class B {
    public:
        virtual ~B() = default;
        virtual string str() const { return "B"; }
    };

    class A {
    public:
        virtual ~A() = default;
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
        shared_ptr<D> d;
    public:
        B1() : d{make_shared<D1>()} {}
        B1(shared_ptr<D> d) : d{d} {}
        virtual string str() const override { return "B1(" + d->str() + ")"; }
    };

    class A1 : public A {
        shared_ptr<B> b;
        shared_ptr<C> c;
    public:
        A1() : b{make_shared<B1>()}, c{make_shared<C1>()} {}
        A1(shared_ptr<B> b, shared_ptr<C> c) : b{b}, c{c} {}
        virtual string str() const override { return "A1(" + b->str() + "," + c->str() + ")"; }
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

            cout << "BASTARD DEPENDENCY INJECTION" << endl;

            {
                auto a = make_shared<A1>();
                cout << a->str() << endl;
            }

            {
                auto a = make_shared<A1>(
                    make_shared<B2>(),
                    make_shared<C2>());
                cout << a->str() << endl;
            }

            cout << endl;
        }
    };
}

#endif
