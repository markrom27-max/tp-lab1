#pragma once
#include "Keeper.h"
#include <string>
#include <iosfwd>

class Conference {
private:
    std::string name;
    Keeper records;
public:
    Conference();
    explicit Conference(const std::string& name);
    Conference(const Conference& other);
    ~Conference();
    Conference& operator=(const Conference& other);
    const std::string& getName() const;
    void setName(const std::string& value);
    Keeper& getRecords();
    const Keeper& getRecords() const;
    void print(std::ostream& out, int filter = 0) const;
    void save(const std::string& path) const;
    void load(const std::string& path);
};
