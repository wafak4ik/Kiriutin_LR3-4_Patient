#include <iostream>
#include <map>
#include <functional>
#include <limits>
#include <vector>
#include <algorithm>
#include "Kiriutin_LR3-4_Methods.h"

using namespace std;

// Структура для пункта меню
struct MenuItem {
    string title;
    function<void()> action;
};

// Функция для безопасного ввода числа
void EnterNumber(unsigned& choice, const string& prompt) {
    while (true) {
        cout << prompt;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите число.\n";
        } else {
            cin.ignore(); // Очищаем буфер после ввода числа
            break;
        }
    }
}

int main() {
    // Создание меню с использованием std::map
    map<unsigned, MenuItem> menu = {
        {1, {"Создать пациента (конструктор по умолчанию)", demonstrateDefaultConstructor}},
        {2, {"Создать пациента (параметризованный конструктор)", demonstrateParameterizedConstructor}},
        {3, {"Создать пациента (полный параметризованный конструктор)", demonstrateFullParameterizedConstructor}},
        {4, {"Создать пациента (конструктор копирования)", demonstrateCopyConstructor}},
        {5, {"Создать пациента (конструктор преобразования)", demonstrateConversionConstructor}},
        {6, {"Создать пациента (оператор ввода)", demonstrateOperatorInput}},
        {7, {"Показать всех пациентов", showAllPatients}},
        {8, {"Вычислить среднее состояние пациента", demonstrateCalculateAverage}},
        {9, {"Демонстрация оператора сложения", demonstrateOperatorPlus}},
        {10, {"Демонстрация операторов инкремента", demonstrateOperatorIncrement}},
        {11, {"Демонстрация оператора сравнения", demonstrateOperatorComparison}},
        {12, {"Отсортировать пациентов по возрасту", sortPatientsByAge}}
    };

    unsigned choice = 0;

    while (true) {
        cout << "МЕНЮ:\n";
        
        // Вывод всех пунктов меню
        for (const auto& item : menu) {
            cout << item.first << ". " << item.second.title << endl;
        }
        cout << "0. Выход\n";

        EnterNumber(choice, "Введите номер пункта: ");

        if (choice == 0) {
            break;
        }

        cout << endl << "========== ДЕЙСТВИЕ: ==========" << endl;

        // Проверка существования пункта меню
        if (menu.find(choice) != menu.end()) {
            menu[choice].action();
        } else {
            cout << "Некорректный ввод.\n";
        }
        
        cout << endl;
    }

    return 0;
}