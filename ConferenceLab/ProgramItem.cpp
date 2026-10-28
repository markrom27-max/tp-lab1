#include "ProgramItem.h"
#include "Input.h"
#include <iostream>
#include <iomanip>
#include "AppError.h"

ProgramItem::ProgramItem()
    : day("Не задано"), time("00:00") {
    std::cout << "[ProgramItem] конструктор без параметров\n";
}
ProgramItem::ProgramItem(
    const std::string& name,
    const std::string& day,
    const std::string& time)
    : Base(name) {
    setDay(day);
    setTime(time);
    std::cout << "[ProgramItem] конструктор с параметрами: "
        << getName() << '\n';
}
ProgramItem::ProgramItem(const ProgramItem& other)
    : Base(other), day(other.day),
      time(other.time) {
    std::cout << "[ProgramItem] конструктор копирования: "
        << getName() << '\n';
}
ProgramItem::~ProgramItem() {
    std::cout << "[ProgramItem] деструктор: " << getName() << '\n';
}
const std::string& ProgramItem::getDay() const {
    return day;
}
void ProgramItem::setDay(const std::string& value) {
    Input::checkText(value);
    day = value;
}
const std::string& ProgramItem::getTime() const {
    return time;
}
void ProgramItem::setTime(const std::string& value) {
    Input::checkTime(value);
    time = value;
}
const char* ProgramItem::type() const { return "ProgramItem"; }
Base* ProgramItem::clone() const { return new ProgramItem(*this); }
void ProgramItem::input(std::istream& in, std::ostream& out) {
    std::string newName = Input::text(in, out, "Наименование выступления: ");
    std::string newday = Input::text(in, out,
        "День (например, 25.10.2026): ");
    std::string newtime = Input::text(in, out,
        "Время (ЧЧ:ММ): ");
    Input::checkTime(newtime);
    // Применяем изменения после проверки всех полей.
    setName(newName);
    setDay(newday);
    setTime(newtime);
}
void ProgramItem::print(std::ostream& out) const {
    out << "Программа\nНаименование выступления: " << getName()
        << "\nДень (например, 25.10.2026): " << day
        << "\nВремя (ЧЧ:ММ): " << time << '\n';
}

void ProgramItem::save(std::ostream& out) const {
    out << std::quoted(getName()) << '\n'
        << std::quoted(day) << '\n'
        << std::quoted(time) << '\n';
}
void ProgramItem::load(std::istream& in) {
    std::string newname, newday, newtime;
    if (!(in >> std::quoted(newname)
        >> std::quoted(newday)
        >> std::quoted(newtime)))
        throw AppError("Недостаточно полей в файле.");
    Input::checkTime(newtime);
    Input::checkText(newname);
    Input::checkText(newday);
    Input::checkText(newtime);
    setName(newname);
    setDay(newday);
    setTime(newtime);
}
