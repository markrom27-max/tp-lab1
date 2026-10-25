#include "AppError.h"
#include <iostream>

AppError::AppError() : std::runtime_error("Ошибка программы") {
    std::cout << "[AppError] конструктор без параметров\n";
}
AppError::AppError(const std::string& text)
    : std::runtime_error(text) {
    std::cout << "[AppError] конструктор с параметрами\n";
}
AppError::AppError(const AppError& other)
    : std::runtime_error(other) {
    std::cout << "[AppError] конструктор копирования\n";
}
AppError::~AppError() noexcept {
    std::cout << "[AppError] деструктор\n";
}
