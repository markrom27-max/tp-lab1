#include "Factory.h"
#include "Speaker.h"
#include "Administrator.h"
#include "ProgramItem.h"
#include "AppError.h"

Base* createObject(int type) {
    switch (type) {
    case 1: return new Speaker;
    case 2: return new Administrator;
    case 3: return new ProgramItem;
    default: throw AppError("Неизвестный тип объекта.");
    }
}

Base* createObject(const std::string& type) {
    if (type == "Speaker") return createObject(1);
    if (type == "Administrator") return createObject(2);
    if (type == "ProgramItem") return createObject(3);
    throw AppError("Неизвестный тип записи в файле: " + type);
}
