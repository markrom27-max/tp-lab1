#include "Conference.h"
#include "Input.h"
#include "Factory.h"
#include "AppError.h"
#include <iostream>
#include <memory>

Conference::Conference() : name("Без названия") {
    std::cout << "[Conference] конструктор без параметров\n";
}
Conference::Conference(const std::string& value) : records(2) {
    setName(value);
    std::cout << "[Conference] конструктор с параметрами: "
        << name << '\n';
}
Conference::Conference(const Conference& other)
    : name(other.name), records(other.records) {
    std::cout << "[Conference] конструктор копирования: "
        << name << '\n';
}
Conference::~Conference() {
    std::cout << "[Conference] деструктор: " << name << '\n';
}
Conference& Conference::operator=(const Conference& other) {
    if (this != &other) {
        Conference copy(other);
        name.swap(copy.name);
        records.swap(copy.records);
    }
    return *this;
}
const std::string& Conference::getName() const { return name; }
void Conference::setName(const std::string& value) {
    Input::checkText(value);
    name = value;
}
Keeper& Conference::getRecords() { return records; }
const Keeper& Conference::getRecords() const { return records; }
void Conference::print(std::ostream& out, int filter) const {
    out << "Конференция: " << name << '\n';
    const char* types[] = {"", "Speaker", "Administrator", "ProgramItem"};
    if (filter < 0 || filter > 3) throw AppError("Неизвестный фильтр.");
    bool found = false;
    for (int i = 0; i < records.getCount(); ++i) {
        if (filter == 0 || std::string(records[i].type()) == types[filter]) {
            out << "--- Запись " << i + 1 << " ---\n" << records[i];
            found = true;
        }
    }
    if (!found) out << "Записей нет.\n";
}
