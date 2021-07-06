#ifndef STEPBUILDER_2_H
#define STEPBUILDER_2_H

#include <memory>
#include <iostream>
#include <sstream>

/* ////////////////////////////////////////////////////////////////////////////
 * STEP BUILDER WITH REINTERPRED_CAST
 */

namespace StepBuilder2 {

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

        // STEP BUILDER USING REINTERPRET_CAST
        // Private extension of a common class and use of reinterpret_cast.
        // One advantage of this method is that we can change the order of the
        // setter classes to make the builder easier to read.
        // Another advantage is that we can also use the return type auto.

        struct Builder : private Data {
            auto &withName(const std::string& name) {
                this->name = name;
                return reinterpret_cast<WeightBuilder&>(*this);
            }
        };

        struct WeightBuilder : private Data {
            auto &withWeight(float weight) {
                this->weight = weight;
                return reinterpret_cast<LegsBuilder&>(*this);
            }
        };

        struct LegsBuilder : private Data {
           auto &withLegs(uint8_t legs) {
                this->legs = legs;
                return reinterpret_cast<AnimalBuilder&>(*this);
            }
        };

        struct AnimalBuilder : private Data {
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

            std::cout << "STEP BUILDER WITH REINTERPRED_CAST" << std::endl;
            auto panter = Animal::builder()
                .withName("panter")
                .withWeight(10.5f)
                .withLegs(4)
                .build();
            std::cout << panter->toString() << std::endl;

            auto lion = *Animal::builder()
                .withName("lion")
                .withWeight(10.5f)
                .withLegs(4)
                .build();
            std::cout << lion.toString() << std::endl;
            std::cout << std::endl;
        }
    };
}

#endif // STEPBUILDER_2_H
