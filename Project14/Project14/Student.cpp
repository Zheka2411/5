#include <iostream>

class Student {
private:
    String name;
    String surname;

public:
    // Конструктор за замовчуванням
    Student(const String& name, const String& surname)
        : name(name), surname(surname) {}

    // Конструктор переносу
    Student(Student&& other) noexcept : name(std::move(other.name)), surname(std::move(other.surname)) {}

    // Оператор = (копіювання)
    Student& operator=(const Student& other) {
        if (this != &other) {
            name = other.name;
            surname = other.surname;
        }
        return *this;
    }

    // Оператор = (перенос)
    Student& operator=(Student&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            surname = std::move(other.surname);
        }
        return *this;
    }

    // Доступ до імені та прізвища
    const String& getName() const { return name; }
    const String& getSurname() const { return surname; }
};
