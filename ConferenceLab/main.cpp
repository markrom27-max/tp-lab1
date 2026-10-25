#include "Factory.h"
#include "Base.h"
#include "Input.h"
#include <iostream>
#include <memory>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    try {
        int type = Input::number(std::cin, std::cout,
            "1 Выступающий  2 Администрация  3 Программа: ", 1, 3);
        std::unique_ptr<Base> item(createObject(type));
        item->input(std::cin, std::cout);
        std::cout << *item;
        std::unique_ptr<Base> copy(item->clone());
        std::cout << "Копия объекта:\n" << *copy;
    } catch (const std::exception& error) {
        std::cout << "Ошибка: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
