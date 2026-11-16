#include <iostream>
#include <algorithm>
#include "Vector_T.h"

// Печать вектора через итераторы
void print(const Vector<int>& v) {
    std::cout << "[ ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "]  size = " << v.size() << ", capacity = " << v.capacity() << "\n";
}

// Функция печатает число, умноженное на 10
void printTimesTen(int x) {
    std::cout << x * 10 << " ";
}

int main() {
    // Создание вектора и добавление элементов
    std::cout << "1. push_back\n";
    Vector<int> v;
    if (v.empty()) {
        std::cout << "vector is empty\n";
    }
    v.push_back(40);
    v.push_back(10);
    v.push_back(30);
    v.push_back(20);
    v.push_back(50);
    print(v);

    // Доступ к элементам
    std::cout << "\n2. access\n";
    std::cout << "front = " << v.front() << "\n";
    std::cout << "back = " << v.back() << "\n";
    std::cout << "v[1] = " << v[1] << "\n";
    std::cout << "v.at(2) = " << v.at(2) << "\n";

    try {
        v.at(100);
    } 
    catch (const std::out_of_range& e) {
        std::cout << "v.at(100) -> error: " << e.what() << "\n";
    }

    // Удаление последнего элемента
    std::cout << "\n3. pop_back\n";
    int removed = v.pop_back();
    std::cout << "removed " << removed << "\n";
    print(v);

    // Копирование
    std::cout << "\n4. copy\n";
    Vector<int> copy = v;
    copy[0] = 999;
    std::cout << "original: ";
    print(v);
    std::cout << "copy:     ";
    print(copy);

    // Перемещение
    std::cout << "\n5. move\n";
    Vector<int> moved = std::move(copy);
    std::cout << "moved: ";
    print(moved);
    std::cout << "copy after move: ";
    print(copy);

    // Присваивание
    std::cout << "\n6. assignment\n";
    Vector<int> a;
    a.push_back(1);
    a = v;
    std::cout << "a = v: ";
    print(a);

    Vector<int> b;
    b = std::move(a);
    std::cout << "b = move(a): ";
    print(b);
    std::cout << "a after move: ";
    print(a);

    // reserve и resize
    std::cout << "\n7. reserve / resize\n";
    v.reserve(20);
    std::cout << "reserve(20): ";
    print(v);
    v.resize(6);
    std::cout << "resize(6):   ";
    print(v);
    v.resize(3);
    std::cout << "resize(3):   ";
    print(v);

    // Алгоритмы стандартной библиотеки
    std::cout << "\n8. STL algorithms\n";
    v.push_back(5);
    v.push_back(25);
    std::cout << "before sort: ";
    print(v);

    std::sort(v.begin(), v.end());
    std::cout << "after sort:  ";
    print(v);

    auto found = std::find(v.begin(), v.end(), 25);
    if (found != v.end()) {
        std::cout << "std::find(25): found at index " << (found - v.begin()) << "\n";
    } else {
        std::cout << "std::find(25): not found\n";
    }

    std::cout << "std::for_each (x * 10): ";
    std::for_each(v.begin(), v.end(), printTimesTen);
    std::cout << "\n";

    // Очистка
    std::cout << "\n9. clear\n";
    v.clear();
    print(v);

    // Концепт Numeric
    // Vector<bool> vb;
    // Vector<char> vc;
    // Vector<std::string> vs;

    return 0;
}