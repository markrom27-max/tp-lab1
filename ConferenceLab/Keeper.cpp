#include "Keeper.h"
#include "AppError.h"
#include <iostream>
#include <utility>
#include <memory>
#include "Factory.h"

Keeper::Keeper() : items(nullptr), count(0), capacity(0) {
    std::cout << "[Keeper] конструктор без параметров\n";
}
Keeper::Keeper(int size) : items(nullptr), count(0), capacity(0) {
    if (size < 0) throw AppError("Ёмкость не может быть отрицательной.");
    reserve(size);
    std::cout << "[Keeper] конструктор с параметрами\n";
}
Keeper::Keeper(const Keeper& other)
    : items(nullptr), count(0), capacity(0) {
    try {
        reserve(other.capacity);
        for (int i = 0; i < other.count; ++i) {
            items[count] = other.items[i]->clone();
            ++count;
        }
    } catch (...) {
        clear();
        delete[] items;
        throw;
    }
    std::cout << "[Keeper] конструктор копирования\n";
}
Keeper::~Keeper() {
    clear();
    delete[] items;
    std::cout << "[Keeper] деструктор\n";
}
Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        Keeper copy(other);
        swap(copy);
    }
    return *this;
}
void Keeper::swap(Keeper& other) noexcept {
    std::swap(items, other.items);
    std::swap(count, other.count);
    std::swap(capacity, other.capacity);
}
void Keeper::reserve(int size) {
    if (size <= capacity) return;
    Base** bigger = new Base*[size]{};
    for (int i = 0; i < count; ++i) bigger[i] = items[i];
    delete[] items;
    items = bigger;
    capacity = size;
}
int Keeper::getCount() const { return count; }
int Keeper::getCapacity() const { return capacity; }
void Keeper::add(Base* object) {
    if (!object) throw AppError("Нельзя добавить пустой указатель.");
    for (int i = 0; i < count; ++i)
        if (items[i] == object)
            throw AppError("Этот объект уже принадлежит контейнеру.");
    if (count == capacity) reserve(capacity == 0 ? 2 : capacity * 2);
    items[count++] = object;
}
void Keeper::remove(int index) {
    // operator[] сначала проверяет индекс.
    delete &(*this)[index];
    for (int i = index; i + 1 < count; ++i) items[i] = items[i + 1];
    items[--count] = nullptr;
}
void Keeper::clear() noexcept {
    for (int i = 0; i < count; ++i) {
        delete items[i];
        items[i] = nullptr;
    }
    count = 0;
}
const Base& Keeper::operator[](int index) const {
    if (index < 0 || index >= count)
        throw AppError("Объект с таким номером отсутствует.");
    return *items[index];
}
Base& Keeper::operator[](int index) {
    return const_cast<Base&>(static_cast<const Keeper&>(*this)[index]);
}


void Keeper::save(std::ostream& out) const {
    out << count << '\n';
    for (int i = 0; i < count; ++i) {
        out << items[i]->type() << '\n';
        items[i]->save(out);
    }
    if (!out) throw AppError("Не удалось записать контейнер.");
}

void Keeper::load(std::istream& in) {
    int size;
    if (!(in >> size) || size < 0)
        throw AppError("Неверное количество записей в файле.");
    Keeper loaded;
    for (int i = 0; i < size; ++i) {
        std::string type;
        if (!(in >> type)) throw AppError("Файл неожиданно закончился.");
        std::unique_ptr<Base> item(createObject(type));
        item->load(in);
        loaded.add(item.get());
        item.release();
    }
    swap(loaded);
}
