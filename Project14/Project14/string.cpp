#include <iostream>
#include <cstring>

class String {
private:
    char* data;
public:
    // Конструктор за замовчуванням
    String(const char* str = "") {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    // Конструктор копіювання
    String(const String& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // Конструктор переносу
    String(String&& other) noexcept : data(other.data) {
        other.data = nullptr; // Після переносу, об'єкт other не має володіти даними
    }

    // Оператор = (глибоке копіювання)
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    // Оператор = (перенос)
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;  // Видаляємо поточний ресурс
            data = other.data;  // Переносимо ресурс
            other.data = nullptr; // Очищаємо ресурс у іншому об'єкті
        }
        return *this;
    }

    // Оператор << (виведення рядка в консоль)
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << str.data;
        return os;
    }

    // Деструктор
    ~String() {
        delete[] data;
    }
};

class Student {
private:
    String name;
    String surname;

public:
    Student(const String& name, const String& surname)
        : name(name), surname(surname) {}

    // Конструктор копіювання
    Student(const Student& other) : name(other.name), surname(other.surname) {}

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


int main() {
    String str1("Hello");
    String str2("World");

    // Тестування конструктора переносу
    String str3 = std::move(str1); // перенесення ресурсу
    std::cout << str3 << std::endl; // Виведемо перенесений рядок

    // Тестування оператора переносу
    str2 = std::move(str3);  // перенесення ресурсу
    std::cout << str2 << std::endl;

    return 0;
}
