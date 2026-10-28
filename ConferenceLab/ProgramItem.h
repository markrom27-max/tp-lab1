#pragma once
#include "Base.h"

class ProgramItem : public Base {
private:
    std::string day;
    std::string time;
public:
    ProgramItem();
    ProgramItem(
        const std::string& name,
        const std::string& day,
        const std::string& time);
    ProgramItem(const ProgramItem& other);
    ~ProgramItem() override;
    const std::string& getDay() const;
    void setDay(const std::string& value);
    const std::string& getTime() const;
    void setTime(const std::string& value);
    const char* type() const override;
    Base* clone() const override;
    void input(std::istream& in, std::ostream& out) override;
    void print(std::ostream& out) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};
