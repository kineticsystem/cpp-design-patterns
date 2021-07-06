#ifndef STEP_BUILDER_H
#define STEP_BUILDER_H

#include <memory>
#include <iostream>
#include <sstream>

/* ////////////////////////////////////////////////////////////////////////////
 * STEP BUILDER WITH CHAINED EXTENSION
 */

namespace StepBuilder1 {

    /* This is the object we want to build. */
    class Animal
    {
        // This represents the internal state of the object to build as well
        // as the internal state of the builder.
        // This structure is not required but reduces code duplication.
        // We can use its default copy constructor to transfer the state of
        // the builder to the object being built.
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
        // The disadvantage of this method is that we cannot change the order of
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

        std::string name() const {
            return m_data.name;
        }

        float weight() const {
            return m_data.weight;
        }

        uint8_t legs() const {
            return m_data.legs;
        }

        std::string toString() const {
            std::ostringstream buffer;
            buffer << "Animal[name=" << m_data.name << ", weight=" << m_data.weight << ", legs=" << unsigned(m_data.legs) << "]";
            return buffer.str();
        }
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
