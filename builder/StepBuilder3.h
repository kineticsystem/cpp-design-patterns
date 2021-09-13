#ifndef STEPBUILDER_3_H
#define STEPBUILDER_3_H

#include <memory>
#include <iostream>
#include <sstream>

/* ////////////////////////////////////////////////////////////////////////////
 * STEP BUILDER DATA COPY
 */

namespace StepBuilder3 {

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

        // STEP BUILDER USING DATA COPY
        // At each step a new Data extension copy is returned.
        // Copy elision is not guaranteed.

        struct Builder : public Data {
            auto withName(const std::string& name) {
                this->name = name;
                return WeightBuilder{*this};
            }
        };

        struct WeightBuilder : public Data {
            auto withWeight(float weight) {
                this->weight = weight;
                return LegsBuilder{*this};
            }
        };

        struct LegsBuilder : public Data {
           auto withLegs(uint8_t legs) {
                this->legs = legs;
                return AnimalBuilder{*this};
            }
        };

        struct AnimalBuilder : public Data {
            auto build() {
                return std::unique_ptr<Animal>(new Animal{*this});
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

            std::cout << "STEP BUILDER WITH DATA COPY" << std::endl;
            auto hen = Animal::builder()
                .withName("hen")
                .withWeight(10.5f)
                .withLegs(2)
                .build();
            std::cout << hen->toString() << std::endl;

            auto duck = *Animal::builder()
                .withName("duck")
                .withWeight(10.5f)
                .withLegs(2)
                .build();
            std::cout << duck.toString() << std::endl;
            std::cout << std::endl;
        }
    };
}

#endif // STEPBUILDER_3_H
