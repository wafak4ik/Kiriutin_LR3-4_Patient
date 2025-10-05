#ifndef _METHODS_H
#define _METHODS_H

#include "Kiriutin_LR3-4_Patient.h"
#include <vector>
#include <algorithm>

using namespace std;

// Глобальный вектор объектов
vector<Patient> allPatients;

// Функции проверки корректности данных
bool isValidAge(unsigned age) {
    return age <= 150;
}

bool isValidConditionScore(int score) {
    return score >= 1 && score <= 10;
}

bool isValidName(const string& name) {
    return !name.empty() && name.length() <= 50;
}

// Функции ввода с контролем корректности
unsigned inputAge() {
    unsigned age;
    while (true) {
        cout << "Введите возраст (0-150): ";
        cin >> age;
        if (isValidAge(age)) break;
        cout << "Ошибка! Возраст должен быть от 0 до 150 лет.\n";
    }
    return age;
}

string inputName() {
    string name;
    while (true) {
        cout << "Введите имя: ";
        cin >> name;
        if (isValidName(name)) break;
        cout << "Ошибка! Имя не может быть пустым или длиннее 50 символов.\n";
    }
    return name;
}

int inputConditionScore() {
    int score;
    while (true) {
        cout << "Введите оценку состояния (1-10): ";
        cin >> score;
        if (isValidConditionScore(score)) break;
        cout << "Ошибка! Оценка должна быть от 1 до 10.\n";
    }
    return score;
}

// Метод отображения всех объектов
void showAllPatients() {
    if (allPatients.empty()) {
        cout << "Список пациентов пуст.\n";
        return;
    }
    
    cout << "=== ВСЕ ПАЦИЕНТЫ ===\n";
    for (size_t i = 0; i < allPatients.size(); ++i) {
        cout << "Пациент " << i + 1 << ":\n";
        cout << allPatients[i] << "\n\n";
    }
}

// Демонстрация конструкторов
void demonstrateDefaultConstructor() {
    Patient patient;
    allPatients.push_back(patient);
    cout << "Создан пациент конструктором по умолчанию:\n";
    cout << patient << "\n";
}

void demonstrateParameterizedConstructor() {
    string name = inputName();
    unsigned age = inputAge();
    
    Patient patient(name, age);
    allPatients.push_back(patient);
    cout << "Создан пациент параметризованным конструктором:\n";
    cout << patient << "\n";
}

void demonstrateFullParameterizedConstructor() {
    string name = inputName();
    unsigned age = inputAge();
    
    vector<string> diagnoses;
    vector<int> scores;
    
    int numDiagnoses;
    cout << "Введите количество диагнозов: ";
    cin >> numDiagnoses;
    
    for (int i = 0; i < numDiagnoses; ++i) {
        string diagnosis;
        cout << "Диагноз " << i + 1 << ": ";
        cin >> diagnosis;
        diagnoses.push_back(diagnosis);
    }
    
    int numScores;
    cout << "Введите количество оценок состояния: ";
    cin >> numScores;
    
    for (int i = 0; i < numScores; ++i) {
        int score = inputConditionScore();
        scores.push_back(score);
    }
    
    Patient patient(name, age, diagnoses, scores);
    allPatients.push_back(patient);
    cout << "Создан пациент полным параметризованным конструктором:\n";
    cout << patient << "\n";
}

void demonstrateCopyConstructor() {
    if (allPatients.empty()) {
        cout << "Сначала создайте хотя бы одного пациента!\n";
        return;
    }
    
    cout << "Исходный пациент:\n";
    cout << allPatients.back() << "\n";
    
    Patient copiedPatient(allPatients.back());
    allPatients.push_back(copiedPatient);
    cout << "Скопированный пациент:\n";
    cout << copiedPatient << "\n";
}

void demonstrateConversionConstructor() {
    string data;
    cout << "Введите данные в формате 'Имя,возраст': ";
    cin.ignore();
    getline(cin, data);
    
    Patient patient(data);
    allPatients.push_back(patient);
    cout << "Создан пациент конструктором преобразования:\n";
    cout << patient << "\n";
}

// Демонстрация методов объектов
void demonstrateCalculateAverage() {
    if (allPatients.empty()) {
        cout << "Сначала создайте пациента!\n";
        return;
    }
    
    cout << "Выберите пациента (1-" << allPatients.size() << "): ";
    size_t index;
    cin >> index;
    
    if (index < 1 || index > allPatients.size()) {
        cout << "Неверный индекс!\n";
        return;
    }
    
    double average = allPatients[index - 1].calculateAverageCondition();
    cout << "Среднее состояние пациента: " << average << "\n";
}

// Демонстрация операций
void demonstrateOperatorPlus() {
    if (allPatients.size() < 2) {
        cout << "Нужно как минимум 2 пациента!\n";
        return;
    }
    
    Patient result = allPatients[0] + allPatients[1];
    allPatients.push_back(result);
    cout << "Результат сложения пациентов:\n";
    cout << "Пациент 1: " << allPatients[0] << "\n";
    cout << "Пациент 2: " << allPatients[1] << "\n";
    cout << "Результат: " << result << "\n";
}

void demonstrateOperatorIncrement() {
    if (allPatients.empty()) {
        cout << "Сначала создайте пациента!\n";
        return;
    }
    
    cout << "Исходный пациент:\n";
    cout << allPatients.back() << "\n";
    
    // Префиксный инкремент
    ++allPatients.back();
    cout << "После префиксного инкремента:\n";
    cout << allPatients.back() << "\n";
    
    // Постфиксный инкремент
    Patient temp = allPatients.back()++;
    cout << "Возвращенное значение постфиксного инкремента:\n";
    cout << temp << "\n";
    cout << "После постфиксного инкремента:\n";
    cout << allPatients.back() << "\n";
}

void demonstrateOperatorComparison() {
    if (allPatients.size() < 2) {
        cout << "Нужно как минимум 2 пациента!\n";
        return;
    }
    
    bool areEqual = (allPatients[0] == allPatients[1]);
    cout << "Пациент 1 (возраст " << allPatients[0].getAge() << ")\n";
    cout << "Пациент 2 (возраст " << allPatients[1].getAge() << ")\n";
    cout << "Возраст одинаковый: " << (areEqual ? "Да" : "Нет") << "\n";
}

void demonstrateOperatorInput() {
    Patient patient;
    cin >> patient;
    allPatients.push_back(patient);
    cout << "Создан пациент через оператор ввода:\n";
    cout << patient << "\n";
}

// Функция для сортировки пациентов по возрасту
void sortPatientsByAge() {
    sort(allPatients.begin(), allPatients.end(),
         [](const Patient& a, const Patient& b) {
             return a.getAge() < b.getAge();
         });
    cout << "Пациенты отсортированы по возрасту.\n";
    showAllPatients();
}

#endif // _METHODS_H