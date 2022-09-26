#ifndef STEPBUILDER_4_H
#define STEPBUILDER_4_H

#include <memory>
#include <iostream>
#include <sstream>

/* ////////////////////////////////////////////////////////////////////////////
 * STEP BUILDER WITH DEPENDENCY INJECTION
 */

namespace stepbuilder4 {

    /* This is the object we want to inject. */
    class Tag {
        uint16_t m_number;
    public:
        Tag(uint16_t number) : m_number{number} {}
        uint16_t number() const {
            return m_number;
        }
    };

    /* This is the object we want to build. */
    class Animal
    {
        // This represents the internal state of the object to build as well
        // as the internal state of the builder.
        // This structure is not required but reduces code duplication.
        // Because we have a unique pointer, we define a custom copy
        // constructor to transfer the state of the builder to the object being
        // built.
        struct Data {

            mutable std::unique_ptr<Tag> tag;
            std::string name;
            float weight;
            uint8_t legs;
            uint8_t pad[3];

            Data() = default;
            Data(const Data &other) : // Shallow copy.
                tag{std::move(other.tag)},
                name{other.name},
                weight{other.weight},
                legs{other.legs} {}

        } m_data;

        // Private constructor.
        Animal(const Data &data) : m_data{data} {}

        // STEP BUILDER WITH DEPENDENCY INJECTION
        // Private extension of a common class and use of reinterpret_cast.
        // One advantage of this method is that we can change the order of the
        // setter classes to make the builder easier to read.
        // Another advantage is that we can also use the return type auto.

        struct TagBuilder : private Data {
            auto &withTag(std::unique_ptr<Tag> tag) {
                this->tag = std::move(tag);
                return reinterpret_cast<NameBuilder&>(*this);
            }
        };

        struct NameBuilder : private Data {
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

        static TagBuilder builder() {
            return {};
        }

        // Getter methods.

        Tag &tag() const {
            return *m_data.tag;
        }

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
            buffer << "Animal[tag=" << m_data.tag->number()
                   << ",name=" << m_data.name
                   << ", weight=" << m_data.weight
                   << ", legs=" << unsigned(m_data.legs) << "]";
            return buffer.str();
        }
    };

    /* ////////////////////////////////////////////////////////////////////////////
     * Step builder examples.
     */
    struct Test {
        static void execute() {

            std::cout << "STEP BUILDER WITH DEPENDENCY INJECTION" << std::endl;
            auto fish = Animal::builder()
                .withTag(std::make_unique<Tag>(333))
                .withName("fish")
                .withWeight(1.0f)
                .withLegs(0)
                .build();
            std::cout << fish->toString() << std::endl;

            auto crab = *Animal::builder()
                .withTag(std::make_unique<Tag>(213))
                .withName("crab")
                .withWeight(0.5f)
                .withLegs(8)
                .build();
            std::cout << crab.toString() << std::endl;
            std::cout << std::endl;
        }
    };
}

#endif // STEPBUILDER_4_H
