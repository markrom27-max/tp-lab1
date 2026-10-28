#include "Administrator.h"
#include "Input.h"
#include <iostream>
#include <iomanip>
#include "AppError.h"

Administrator::Administrator()
    : position("Не задано"), responsibility("Не задано") {
    std::cout << "[Administrator] конструктор без параметров\n";
}
Administrator::Administrator(
    const std::string& name,
    const std::string& position,
    const std::string& responsibility)
    : Base(name) {
    setPosition(position);
    setResponsibility(responsibility);
    std::cout << "[Administrator] конструктор с параметрами: "
        << getName() << '\n';
}
Administrator::Administrator(const Administrator& other)
    : Base(other), position(other.position),
      responsibility(other.responsibility) {
    std::cout << "[Administrator] конструктор копирования: "
        << getName() << '\n';
}
Administrator::~Administrator() {
    std::cout << "[Administrator] деструктор: " << getName() << '\n';
}
const std::string& Administrator::getPosition() const {
    return position;
}
void Administrator::setPosition(const std::string& value) {
    Input::checkText(value);
    position = value;
}
const std::string& Administrator::getResponsibility() const {
    return responsibility;
}
void Administrator::setResponsibility(const std::string& value) {
    Input::checkText(value);
    responsibility = value;
}
const char* Administrator::type() const { return "Administrator"; }
Base* Administrator::clone() const { return new Administrator(*this); }
void Administrator::input(std::istream& in, std::ostream& out) {
    std::string newName = Input::text(in, out, "ФИО: ");
    std::string newposition = Input::text(in, out,
        "Должность: ");
    std::string newresponsibility = Input::text(in, out,
        "Область ответственности: ");
    // Применяем изменения после проверки всех полей.
    setName(newName);
    setPosition(newposition);
    setResponsibility(newresponsibility);
}
void Administrator::print(std::ostream& out) const {
    out << "Администрация\nФИО: " << getName()
        << "\nДолжность: " << position
        << "\nОбласть ответственности: " << responsibility << '\n';
}

void Administrator::save(std::ostream& out) const {
    out << std::quoted(getName()) << '\n'
        << std::quoted(position) << '\n'
        << std::quoted(responsibility) << '\n';
}
void Administrator::load(std::istream& in) {
    std::string newname, newposition, newresponsibility;
    if (!(in >> std::quoted(newname)
        >> std::quoted(newposition)
        >> std::quoted(newresponsibility)))
        throw AppError("Недостаточно полей в файле.");
    Input::checkText(newname);
    Input::checkText(newposition);
    Input::checkText(newresponsibility);
    setName(newname);
    setPosition(newposition);
    setResponsibility(newresponsibility);
}
