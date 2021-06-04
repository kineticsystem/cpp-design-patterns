#ifndef EXAMPLE5_H
#define EXAMPLE5_H

#include <memory>
#include <iostream>
#include <sstream>

// Consider again concrete classes A1,B1,C1,D1 with the following dependency
// structure: A1(B1(D1),C1)
// This time all dependencies are given in terms of interfaces A,B,C,D.

namespace Injection6 {

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

    class A1Builder {
        unique_ptr<A1> a = make_unique<A1>();
    public:
        A1Builder& setB(shared_ptr<B> b) {
            a->setB(b);
            return *this;
        }
        A1Builder& setC(shared_ptr<C> c) {
            a->setC(c);
            return *this;
        }
        shared_ptr<A1> build() {
            return move(a);
        }
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

            {
                auto a = make_shared<A1>();
                cout << a->str() << endl;
            }

            {
                auto a = A1Builder().setB(make_shared<B2>()).setC(make_shared<C2>()).build();
                cout << a->str() << endl;
            }

            cout << endl;
        }
    };
}

#endif
