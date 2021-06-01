#ifndef FACTORY_1_H
#define FACTORY_1_H

#include <memory>
#include <iostream>

/*/////////////////////////////////////////////////////////////////////////////
 * Resource Injection + Covariance + Name Hiding
 * to make a factory return a smart pointer of a sub class.
 * @see https://www.fluentcpp.com/2017/09/12/how-to-return-a-smart-pointer-and-use-covariance/
 */
namespace Factory1 {

    // Base abstract class and its sub-classes.

    class Animal {
    public:
        virtual ~Animal() = default;
        virtual void identify() const = 0;
    };

    class Dog : public Animal {
    public:
        virtual ~Dog() override = default;
        virtual void identify() const override {
            std::cout << "I'm a dog." << std::endl;
        }
    };

    class Cat : public Animal {
    public:
        virtual ~Cat() override = default;
        virtual void identify() const override {
            std::cout << "I'm a cat." << std::endl;
        }
    };

    // Base abstract factory and its sub-classes.

    class AnimalFactory {
    public:
        virtual ~AnimalFactory() = default;
        std::unique_ptr<Animal> create() const {
            return std::unique_ptr<Animal>(createImpl());
        }
    private:
        virtual Animal * createImpl() const = 0;
    };

    class DogFactory : public AnimalFactory {
    public:
        virtual ~DogFactory() override = default;
    private:
        virtual Dog * createImpl() const override {
            return new Dog;
        }
    };

    class CatFactory : public AnimalFactory {
    public:
        virtual ~CatFactory() override = default;
    private:
        virtual Cat * createImpl() const override {
            return new Cat;
        }
    };

    // A client using a generic animal factory.

    class Client {
    public:
        Client(std::unique_ptr<AnimalFactory> factory)
            : m_factory{std::move(factory)}
        {}
        void print() const {
            auto animal = m_factory->create();
            animal->identify();
        }
    private:
        std::unique_ptr<AnimalFactory> m_factory;
    };

    /* ////////////////////////////////////////////////////////////////////////////
     * Examples.
     */
    struct Test {
        static void execute() {

            auto client1 = std::make_unique<Client>(
                std::make_unique<DogFactory>()
            );
            client1->print();

            auto client2 = std::make_unique<Client>(
                std::make_unique<CatFactory>()
            );
            client2->print();
        }
    };
}

#endif // FACTORY_1_H
