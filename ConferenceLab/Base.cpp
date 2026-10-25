#include "Base.h"
#include "Input.h"
#include <iostream>

Base::Base() : name("Не задано") {
    std::cout << "[Base] конструктор без параметров\n";
}
Base::Base(const std::string& value) {
    setName(value);
    std::cout << "[Base] конструктор с параметрами: " << name << '\n';
}
Base::Base(const Base& other) : name(other.name) {
    std::cout << "[Base] конструктор копирования: " << name << '\n';
}
Base::~Base() {
    std::cout << "[Base] деструктор: " << name << '\n';
}
Base& Base::operator=(const Base& other) {
    if (this != &other) name = other.name;
    return *this;
}
const std::string& Base::getName() const { return name; }
void Base::setName(const std::string& value) {
    Input::checkText(value);
    name = value;
}
std::ostream& operator<<(std::ostream& out, const Base& object) {
    object.print(out);
    return out;
}
