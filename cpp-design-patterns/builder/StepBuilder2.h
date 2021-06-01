#ifndef STEPBUILDER_2_H
#define STEPBUILDER_2_H

#include <memory>
#include <iostream>

/* ////////////////////////////////////////////////////////////////////////////
 * Step Builder implementation.
 */

namespace StepBuilder2 {

    /* This is the object we want to build. */
    class Animal
    {

        // This represents the internal status of the object to build. It is
        // used to simplify the exchange of information with the builder and
        // avoid duplication.
        struct Data {
            std::string name;
            double weight;
            int legs;
        } m_data;

        // Private constructor.
        Animal(const Data &data) : m_data{data} {};

        // STEP BUILDER
        // Private extension of a common class and use of reinterpret_cast.

        struct AnimalBuilder : private Data {
            std::unique_ptr<Animal> build() {
                return std::unique_ptr<Animal>(new Animal{*this});
            }
        };

        struct LegsBuilder : private Data {
           AnimalBuilder &withLegs(int legs) {
                this->legs = legs;
                return reinterpret_cast<AnimalBuilder&>(*this);
            }
        };

        struct WeightBuilder : private Data {
            LegsBuilder &withWeight(double weight) {
                this->weight = weight;
                return reinterpret_cast<LegsBuilder&>(*this);
            }
        };

        struct Builder : private Data {
            WeightBuilder& withName(const std::string& name){
                this->name = name;
                return reinterpret_cast<WeightBuilder&>(*this);
            }
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

            auto panter = Animal::builder()
                .withName("panter")
                .withWeight(10.5)
                .withLegs(4)
                .build();
            std::cout << panter->toString() << std::endl;

            auto lion = *Animal::builder()
                .withName("panter")
                .withWeight(10.5)
                .withLegs(4)
                .build();
            std::cout << lion.toString() << std::endl;
        }
    };
}

#endif // STEPBUILDER_2_H
