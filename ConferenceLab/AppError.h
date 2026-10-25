#pragma once
#include <stdexcept>
#include <string>

class AppError : public std::runtime_error {
public:
    AppError();
    explicit AppError(const std::string& message);
    AppError(const AppError& other);
    ~AppError() noexcept override;
};
