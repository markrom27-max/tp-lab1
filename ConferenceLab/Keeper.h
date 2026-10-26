#pragma once
#include "Base.h"

class Keeper {
private:
    Base** items;
    int count;
    int capacity;
    void reserve(int newCapacity);
public:
    Keeper();
    explicit Keeper(int capacity);
    Keeper(const Keeper& other);
    ~Keeper();
    Keeper& operator=(const Keeper& other);
    void swap(Keeper& other) noexcept;
    int getCount() const;
    int getCapacity() const;
    // После успешного add контейнер владеет указателем.
    void add(Base* object);
    void remove(int index);
    void clear() noexcept;
    Base& operator[](int index);
    const Base& operator[](int index) const;
};
