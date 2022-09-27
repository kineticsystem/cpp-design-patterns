#ifndef EXPECTED_H
#define EXPECTED_H

#include <string>
#include <iostream>
#include <variant>

namespace expected {

enum Code {
  Ok = 0,
  Error = 1,
  Unknown = 2
};

class Status
{
public:
    Status() {}
    explicit Status(expected::Code errorCode, std::string errorMessage)
        : m_errorCode{errorCode}, m_errorMessage{errorMessage} {
    }

    [[nodiscard]] bool ok() const {
        return m_errorCode == Code::Ok;
    }

    [[nodiscard]] int errorCode() const {
        return m_errorCode;
    }
    [[nodiscard]] std::string errorMessage() const {
        return m_errorMessage;
    }

private:
    Code m_errorCode = Code::Unknown;
    std::string m_errorMessage;
};

template <class T>
class Result
{
public:
    Result(const T &value) : m_value{value} {}
    Result(const Status &status) : m_value{status} {}

    // Returns true if the internal value stores a T, false if it stores a Status.
    [[nodiscard]] bool ok() const {
        bool value{true};
        std::visit([&value] (auto&& arg) {
            using Type = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<Type, Status>) {
                value = false;
            }
        },
        m_value);
        return value;
    }

    // Returns a reference to our status.
    // If this contains a T, then returns Status::OK.
    [[nodiscard]] Status status() const {
        return ok() ? Status{} : std::get<Status>(m_value);
    }

    // Returns a reference to our current value.
    [[nodiscard]] T value() const {
        return std::get<T>(m_value);
    }

private:
    std::variant<T, Status> m_value;
};

/* ////////////////////////////////////////////////////////////////////////////
 * Examples.
 */
struct Test {

    struct Something {
        Something(const std::string text) : text{text} {}
        const std::string text;
    };

    //function

    static expected::Result<Something> func1() {
        return {Status{Code::Error, "Ops, a problem in func1"}};
    }

    static expected::Result<Something> func2() {
        return {Something{"FUNC2"}};
    }

    static expected::Result<Something> func3() {
        auto result1 = func1(); if (!result1.ok()) {return result1;}
        auto result2 = func2(); if (!result2.ok()) {return result2;}
        return result1;
    }

    static void execute() {
        auto result1 = func1();
        auto result2 = func2();
        auto result3 = func3();
        if (result3.ok()) {
            std::cout << result3.value().text << std::endl;
        } else {
            std::cout << result3.status().errorMessage() << std::endl;
        }
    }
};

} // namespace expected


#endif // EXPECTED_H
