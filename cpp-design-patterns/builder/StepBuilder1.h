#ifndef STEP_BUILDER_H
#define STEP_BUILDER_H

#include <memory>
#include <iostream>

/* ////////////////////////////////////////////////////////////////////////////
 * STEP BUILDER WITH CHAINED EXTENSION
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
            float weight;
            uint8_t legs;
            uint8_t pad[3];
        } m_data;

        // Private constructor.
        Animal(const Data &data) : m_data{data} {}

        // STEP BUILDER
        // Protected chained class extension.
        // The disavangage of this method is that we cannot change the order of
        // the setter classes, even is we forward declare all classes before,
        // making the builder more difficult to read.

        struct AnimalBuilder : protected Data {
            std::unique_ptr<Animal> build() {
                return std::unique_ptr<Animal>(new Animal{*this});
            }
        };

        struct LegsBuilder : protected AnimalBuilder {
            AnimalBuilder &withLegs(uint8_t legs) {
                this->legs = legs;
                return *this;
            }
        };

        struct WeightBuilder : protected LegsBuilder {
            LegsBuilder &withWeight(float weight) {
                this->weight = weight;
                return *this;
            }
        };

        struct Builder : protected WeightBuilder {
            WeightBuilder &withName(const std::string &name) {
                this->name = name;
                return *this;
            }
        };

    public:

        static Builder builder() {
            return {};
        }

        // Getter methods.
        std::string name() const;
        float weight() const;
        uint8_t legs() const;
        std::string toString() const;
    };

    /* ////////////////////////////////////////////////////////////////////////////
     * Step builder examples.
     */
    struct Test {
        static void execute() {

            std::cout << "STEP BUILDER WITH CHAINED EXTENSION" << std::endl;
            auto dog = Animal::builder()
                .withName("dog")
                .withWeight(5.2f)
                .withLegs(4)
                .build();
            std::cout << dog->toString() << std::endl;

            auto goose = *Animal::builder()
                .withName("goose")
                .withWeight(2.1f)
                .withLegs(2)
                .build();
            std::cout << goose.toString() << std::endl;
            std::cout << std::endl;
        }
    };
}

#endif // STEP_BUILDER_H
