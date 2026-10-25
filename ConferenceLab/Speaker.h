#pragma once
#include "Base.h"

class Speaker : public Base {
private:
    std::string organization;
    std::string report;
    std::string annotation;
public:
    Speaker();
    Speaker(
        const std::string& name,
        const std::string& organization,
        const std::string& report,
        const std::string& annotation);
    Speaker(const Speaker& other);
    ~Speaker() override;
    const std::string& getOrganization() const;
    void setOrganization(const std::string& value);
    const std::string& getReport() const;
    void setReport(const std::string& value);
    const std::string& getAnnotation() const;
    void setAnnotation(const std::string& value);
    const char* type() const override;
    Base* clone() const override;
    void input(std::istream& in, std::ostream& out) override;
    void print(std::ostream& out) const override;
};
