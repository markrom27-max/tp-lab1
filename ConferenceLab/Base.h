#pragma once
#include <string>
#include <iosfwd>

class Base {
private:
    std::string name;
public:
    Base();
    explicit Base(const std::string& name);
    Base(const Base& other);
    virtual ~Base();
    Base& operator=(const Base& other);
    const std::string& getName() const;
    void setName(const std::string& value);
    virtual const char* type() const = 0;
    virtual Base* clone() const = 0;
    virtual void input(std::istream& in, std::ostream& out) = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;
    friend std::ostream& operator<<(std::ostream& out,
        const Base& object);
};
