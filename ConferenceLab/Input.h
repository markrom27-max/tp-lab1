#pragma once
#include <iosfwd>
#include <string>

namespace Input {
    std::string text(std::istream& in, std::ostream& out,
        const std::string& prompt);
    int number(std::istream& in, std::ostream& out,
        const std::string& prompt, int low, int high);
    void checkText(const std::string& value);
    void checkTime(const std::string& value);
}
