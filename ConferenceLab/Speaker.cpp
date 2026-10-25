#include "Speaker.h"
#include "Input.h"
#include <iostream>

Speaker::Speaker()
    : organization("Не задано"), report("Не задано"), annotation("Не задано") {
    std::cout << "[Speaker] конструктор без параметров\n";
}
Speaker::Speaker(
    const std::string& name,
    const std::string& organization,
    const std::string& report,
    const std::string& annotation)
    : Base(name) {
    setOrganization(organization);
    setReport(report);
    setAnnotation(annotation);
    std::cout << "[Speaker] конструктор с параметрами: "
        << getName() << '\n';
}
Speaker::Speaker(const Speaker& other)
    : Base(other), organization(other.organization),
      report(other.report),
      annotation(other.annotation) {
    std::cout << "[Speaker] конструктор копирования: "
        << getName() << '\n';
}
Speaker::~Speaker() {
    std::cout << "[Speaker] деструктор: " << getName() << '\n';
}
const std::string& Speaker::getOrganization() const {
    return organization;
}
void Speaker::setOrganization(const std::string& value) {
    Input::checkText(value);
    organization = value;
}
const std::string& Speaker::getReport() const {
    return report;
}
void Speaker::setReport(const std::string& value) {
    Input::checkText(value);
    report = value;
}
const std::string& Speaker::getAnnotation() const {
    return annotation;
}
void Speaker::setAnnotation(const std::string& value) {
    Input::checkText(value);
    annotation = value;
}
const char* Speaker::type() const { return "Speaker"; }
Base* Speaker::clone() const { return new Speaker(*this); }
void Speaker::input(std::istream& in, std::ostream& out) {
    std::string newName = Input::text(in, out, "ФИО: ");
    std::string neworganization = Input::text(in, out,
        "Организация или ВУЗ: ");
    std::string newreport = Input::text(in, out,
        "Тема доклада: ");
    std::string newannotation = Input::text(in, out,
        "Аннотация: ");
    // Применяем изменения после проверки всех полей.
    setName(newName);
    setOrganization(neworganization);
    setReport(newreport);
    setAnnotation(newannotation);
}
void Speaker::print(std::ostream& out) const {
    out << "Выступающий\nФИО: " << getName()
        << "\nОрганизация или ВУЗ: " << organization
        << "\nТема доклада: " << report
        << "\nАннотация: " << annotation << '\n';
}
