#ifndef EXAMPLE4_H
#define EXAMPLE4_H

#include <memory>
#include <iostream>
#include <sstream>



// PROPERTY/SETTER DEPENDECY INJECTION
//
// Consider again concrete classes A1,B1,C1,D1 with the following dependency
// structure: A1(B1(D1),C1)
// This time all dependencies are given in terms of interfaces A,B,C,D.

namespace Injection5 {

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
        B1() {}
        void setD(shared_ptr<D> d) { this->d = d; }
        virtual string str() const override {
            stringstream ss;
            ss << "B1(";
            if (d) ss << d->str();
            ss << ")";
            return ss.str();
        }
    };

    class A1 : public A {
        shared_ptr<B> b; // optional
        shared_ptr<C> c; // optional
    public:
        A1() {}
        void setB(shared_ptr<B> b) { this->b = b; }
        void setC(shared_ptr<C> c) { this->c = c; }
        virtual string str() const override {
            stringstream ss;
            ss << "A1(";
            if (b) ss << b->str();
            if (b && c) ss << ",";
            if (c) ss << c->str();
            ss << ")";
            return ss.str();
        }
    };

    // This time the structure is loosely coupled by using interfaces and it is
    // easy to swap B1 with a subclass B2 without necessarily providing the
    // dependency D1 or a subclass of D1.
    // The property or setter dependency injection is commonly used for optional
    // dependencies and to provide an additional seam for testing.

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

            cout << "PROPERTY/SETTER DEPENDECY INJECTION" << endl;

            {
                auto a = make_shared<A1>();
                cout << a->str() << endl;
            }

            {
                auto a = make_shared<A1>();
                a->setB(make_shared<B2>());
                a->setC(make_shared<C2>());
                cout << a->str() << endl;
            }

            cout << endl;
        }
    };
}

#endif
