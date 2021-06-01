#ifndef STEP_BUILDER_H
#define STEP_BUILDER_H

#include <memory>
#include <iostream>

/* ////////////////////////////////////////////////////////////////////////////
 * Step Builder implementation.
 */

namespace StepBuilder1 {

    /* This is the object we want to build. */
    class Animal
    {

        // This represents the internal status of the object to build. It is used
        // to simplify the exchange of information with the builder and avoid
        // duplication.
        struct Data {
            std::string name;
            double weight;
            int legs;
        } m_data;

        // Private constructor.
        Animal(const Data &data) : m_data{data} {};

        // STEP BUILDER
        // Protected chained class extension.

        struct AnimalBuilder : protected Data {
            std::unique_ptr<Animal> build() {
                return std::unique_ptr<Animal>(new Animal{*this});
            }
        };

        struct LegsBuilder : protected AnimalBuilder {
            AnimalBuilder &withLegs(int legs) {
                this->legs = legs;
                return *this;
            };
        };

        struct WeightBuilder : protected LegsBuilder {
            LegsBuilder &withWeight(double weight) {
                this->weight = weight;
                return *this;
            }
        };

        struct Builder : protected WeightBuilder {
            WeightBuilder &withName(const std::string &name) {
                this->name = name;
                return *this;
            };
        };

    public:

        static Builder builder() {
            return {};
        }

        // Getter methods.
        std::string name() const;
        double weight() const;
        int legs() const;
        std::string toString() const;
    };

    /* ////////////////////////////////////////////////////////////////////////////
     * Step builder examples.
     */
    struct Test {
        static void execute() {

            auto dog = Animal::builder()
                .withName("dog")
                .withWeight(5.2)
                .withLegs(4)
                .build();
            std::cout << dog->toString() << std::endl;

            auto goose = *Animal::builder()
                .withName("goose")
                .withWeight(2.1)
                .withLegs(2)
                .build();
            std::cout << goose.toString() << std::endl;
        }
    };
}

#endif // STEP_BUILDER_H
