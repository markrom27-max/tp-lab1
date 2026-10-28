#pragma once
#include <string>
class Base;
Base* createObject(int type);
Base* createObject(const std::string& type);
