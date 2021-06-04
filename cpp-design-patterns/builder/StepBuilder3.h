#ifndef STEPBUILDER_3_H
#define STEPBUILDER_3_H

#include <memory>
#include <iostream>

/* ////////////////////////////////////////////////////////////////////////////
 * Step Builder implementation.
 */

namespace StepBuilder3 {

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
        // This represents the internal status of the object to build. It is
        // used to simplify the exchange of information with the builder and
        // avoid duplication.
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

        // STEP BUILDER WITH UNIQUE POINTERS
        // Private extension of a common class and use of reinterpret_cast.
        // One advantage of this method is that we can change the order of the
        // setter classes.
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
        Tag &tag() const;
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

            std::cout << "STEP BUILDER WITH UNIQUE POINTERS" << std::endl;
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

#endif // STEPBUILDER_3_H
