#include "Conference.h"
#include "Factory.h"
#include "Input.h"
#include "AppError.h"
#include <iostream>
#include <memory>
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    try {
        Conference conference(Input::text(std::cin, std::cout,
            "Название конференции: "));
        while (std::cin) {
            std::cout << "\n1 Добавить  2 Просмотр  3 Изменить\n"
                << "4 Удалить   5 Копировать запись\n"
                << "6 Переименовать  7 Копия конференции\n"
                        << "0 Выход\n";
            try {
                int command = Input::number(std::cin, std::cout,
                    "Действие: ", 0, 7);
                if (command == 0) break;
                Keeper& keeper = conference.getRecords();
                if (command == 1) {
                    int type = Input::number(std::cin, std::cout,
                        "1 Выступающий  2 Администрация  3 Программа: ",
                        1, 3);
                    std::unique_ptr<Base> item(createObject(type));
                    item->input(std::cin, std::cout);
                    keeper.add(item.get());
                    item.release();
                    std::cout << "Запись добавлена.\n";
                } else if (command == 2) {
                    int filter = Input::number(std::cin, std::cout,
                        "0 Все  1 Выступающие  2 Администрация  3 Программа: ",
                        0, 3);
                    conference.print(std::cout, filter);
                } else if (command >= 3 && command <= 5) {
                    if (keeper.getCount() == 0)
                        throw AppError("Контейнер пуст.");
                    int index = Input::number(std::cin, std::cout,
                        "Номер записи: ", 1, keeper.getCount()) - 1;
                    if (command == 3) {
                        keeper[index].input(std::cin, std::cout);
                        std::cout << "Запись изменена.\n";
                    } else if (command == 4) {
                        keeper.remove(index);
                        std::cout << "Запись удалена.\n";
                    } else {
                        std::unique_ptr<Base> copy(keeper[index].clone());
                        keeper.add(copy.get());
                        copy.release();
                        std::cout << "Копия добавлена.\n";
                    }
                } else if (command == 6) {
                    conference.setName(Input::text(std::cin, std::cout,
                        "Новое название: "));
                } else if (command == 7) {
                    Conference copy(conference);
                    copy.print(std::cout);
                    std::cout << "Копия создана и будет уничтожена.\n";
                }
            } catch (const std::exception& error) {
                std::cout << "Ошибка: " << error.what() << '\n';
            }
        }
    } catch (const std::exception& error) {
        std::cout << "Ошибка: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
