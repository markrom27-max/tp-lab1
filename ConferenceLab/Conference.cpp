#include "Conference.h"
#include "Input.h"
#include "Factory.h"
#include "AppError.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <iomanip>
#include <filesystem>

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


void Conference::save(const std::string& path) const {
    Input::checkText(path);
    std::ofstream file(std::filesystem::u8path(path));
    if (!file) throw AppError("Не удалось открыть файл для записи.");
    file << "CONFERENCE 1\n" << std::quoted(name) << '\n';
    records.save(file);
    file.close();
    if (!file) throw AppError("Ошибка записи или закрытия файла.");
}

void Conference::load(const std::string& path) {
    Input::checkText(path);
    std::ifstream file(std::filesystem::u8path(path));
    if (!file) throw AppError("Не удалось открыть файл для чтения.");
    std::string signature;
    std::getline(file, signature);
    if (signature != "CONFERENCE 1")
        throw AppError("Неверный формат или версия файла.");
    std::string newName;
    if (!(file >> std::quoted(newName)))
        throw AppError("Не удалось прочитать название конференции.");
    // Читаем во временный объект: ошибка не затронет текущие данные.
    Conference loaded(newName);
    loaded.records.load(file);
    file >> std::ws;
    if (!file.eof()) throw AppError("Лишние данные в конце файла.");
    name.swap(loaded.name);
    records.swap(loaded.records);
}
