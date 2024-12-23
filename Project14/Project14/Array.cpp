#include <iostream>

template <typename T>
class Array {
private:
    T* data;
    size_t size;

public:
    // Конструктор за замовчуванням
    Array(size_t size = 0) : size(size) {
        data = new T[size];
    }

    // Конструктор копіювання
    Array(const Array& other) : size(other.size) {
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Конструктор переносу
    Array(Array&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;  // Очищаємо ресурс у іншому об'єкті
        other.size = 0;
    }

    // Оператор = (глибоке копіювання)
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Оператор = (перенос)
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;  // Видаляємо поточний ресурс
            data = other.data;  // Переносимо ресурс
            size = other.size;
            other.data = nullptr;  // Очищаємо ресурс у іншому об'єкті
            other.size = 0;
        }
        return *this;
    }

    // Оператор [] (доступ до елементу по індексу)
    T& operator[](size_t index) {
        return data[index];
    }

    // Оператор << (виведення масиву в консоль)
    friend std::ostream& operator<<(std::ostream& os, const Array& arr) {
        for (size_t i = 0; i < arr.size; ++i) {
            os << arr.data[i] << " ";
        }
        return os;
    }

    // Деструктор
    ~Array() {
        delete[] data;
    }
};

int main() {
    Array<int> arr1(5);
    for (int i = 0; i < 5; ++i) arr1[i] = i + 1;

    // Тестування конструктора переносу
    Array<int> arr2 = std::move(arr1);  // перенесення
    std::cout << arr2 << std::endl;  // Виведемо перенесений масив

    // Тестування оператора переносу
    Array<int> arr3(3);
    arr3 = std::move(arr2);  // перенесення
    std::cout << arr3 << std::endl;

    return 0;
}
