#pragma once
#include "Base.h"

class Administrator : public Base {
private:
    std::string position;
    std::string responsibility;
public:
    Administrator();
    Administrator(
        const std::string& name,
        const std::string& position,
        const std::string& responsibility);
    Administrator(const Administrator& other);
    ~Administrator() override;
    const std::string& getPosition() const;
    void setPosition(const std::string& value);
    const std::string& getResponsibility() const;
    void setResponsibility(const std::string& value);
    const char* type() const override;
    Base* clone() const override;
    void input(std::istream& in, std::ostream& out) override;
    void print(std::ostream& out) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};
