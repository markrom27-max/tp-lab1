#include "Input.h"
#include "AppError.h"
#include <iostream>
#include <sstream>
#include <cctype>

void Input::checkText(const std::string& value) {
    if (value.find_first_not_of(" \t\r\n") == std::string::npos)
        throw AppError("Текстовое поле не может быть пустым.");
    if (value.find_first_of("\r\n") != std::string::npos)
        throw AppError("Поле должно занимать одну строку.");
}

void Input::checkTime(const std::string& value) {
    if (value.size() != 5 || value[2] != ':')
        throw AppError("Время вводится в формате ЧЧ:ММ.");
    for (int i = 0; i < 5; ++i) {
        if (i == 2) continue;
        if (!std::isdigit(static_cast<unsigned char>(value[i])))
            throw AppError("Время должно содержать цифры.");
    }
    int hours = (value[0] - '0') * 10 + value[1] - '0';
    int minutes = (value[3] - '0') * 10 + value[4] - '0';
    if (hours > 23 || minutes > 59)
        throw AppError("Часы: от 00 до 23, минуты: от 00 до 59.");
}

std::string Input::text(std::istream& in, std::ostream& out,
    const std::string& prompt) {
    out << prompt;
    std::string value;
    if (!std::getline(in, value))
        throw AppError("Ввод завершён.");
    checkText(value);
    return value;
}

int Input::number(std::istream& in, std::ostream& out,
    const std::string& prompt, int low, int high) {
    std::string line = text(in, out, prompt);
    std::istringstream stream(line);
    int value;
    char extra;
    if (!(stream >> value) || (stream >> extra)
        || value < low || value > high)
        throw AppError("Введите целое число от "
            + std::to_string(low) + " до " + std::to_string(high));
    return value;
}
