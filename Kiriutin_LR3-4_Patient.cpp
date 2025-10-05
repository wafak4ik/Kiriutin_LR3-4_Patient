#include "Kiriutin_LR3-4_Patient.h"
#include <algorithm>
#include <numeric>
#include <sstream>

// Конструктор по умолчанию
Patient::Patient() : name("Unknown"), age(0) {}

// Параметризованный конструктор
Patient::Patient(string patientName, unsigned patientAge) 
    : name(patientName), age(patientAge) {}

// Параметризованный конструктор с делегированием
Patient::Patient(string patientName, unsigned patientAge, 
                 vector<string> diags, vector<int> scores)
    : Patient(patientName, patientAge)
{
    diagnoses = diags;
    conditionScores = scores;
}

// Конструктор копирования
Patient::Patient(const Patient& other)
    : name(other.name), age(other.age), 
      diagnoses(other.diagnoses), 
      conditionScores(other.conditionScores) {}

// Конструктор преобразования
Patient::Patient(const string& str) {
    stringstream ss(str);
    getline(ss, name, ',');
    ss >> age;
}

// Вычисление среднего состояния
double Patient::calculateAverageCondition() const {
    if (conditionScores.empty()) return 0.0;
    double sum = accumulate(conditionScores.begin(), conditionScores.end(), 0.0);
    return sum / conditionScores.size();
}

// Перегрузка оператора сложения
Patient Patient::operator+(const Patient& other) const {
    Patient result = *this;
    
    // Добавляем уникальные диагнозы
    for (const auto& diagnosis : other.diagnoses) {
        if (find(result.diagnoses.begin(), result.diagnoses.end(), diagnosis) == result.diagnoses.end()) {
            result.diagnoses.push_back(diagnosis);
        }
    }
    
    // Объединяем оценки состояния
    result.conditionScores.insert(result.conditionScores.end(),
                                 other.conditionScores.begin(),
                                 other.conditionScores.end());
    
    return result;
}

// Префиксный инкремент (увеличивает возраст)
Patient& Patient::operator++() {
    ++age;
    return *this;
}

// Постфиксный инкремент
Patient Patient::operator++(int) {
    Patient temp = *this;
    ++age;
    return temp;
}

// Сравнение по возрасту
bool Patient::operator==(const Patient& other) const {
    return age == other.age;
}

// Оператор присваивания
const Patient& Patient::operator=(const Patient& other) {
    if (this != &other) {
        name = other.name;
        age = other.age;
        diagnoses = other.diagnoses;
        conditionScores = other.conditionScores;
    }
    return *this;
}

// Оператор вывода
ostream& operator<<(ostream& mystream, const Patient& obj) {
    mystream << "Имя: " << obj.name << ", Возраст: " << obj.age 
             << ", Среднее состояние: " << obj.calculateAverageCondition();
    mystream << "\nДиагнозы: ";
    for (const auto& diagnosis : obj.diagnoses) {
        mystream << diagnosis << "; ";
    }
    mystream << "\nОценки состояния: ";
    for (const auto& score : obj.conditionScores) {
        mystream << score << " ";
    }
    return mystream;
}

// Оператор ввода
istream& operator>>(istream& mystream, Patient& obj) {
    cout << "Введите имя пациента: ";
    mystream >> obj.name;
    cout << "Введите возраст: ";
    mystream >> obj.age;
    
    obj.diagnoses.clear();
    obj.conditionScores.clear();
    
    int numDiagnoses;
    cout << "Введите количество диагнозов: ";
    mystream >> numDiagnoses;
    
    for (int i = 0; i < numDiagnoses; ++i) {
        string diagnosis;
        cout << "Диагноз " << i + 1 << ": ";
        mystream >> diagnosis;
        obj.diagnoses.push_back(diagnosis);
    }
    
    int numScores;
    cout << "Введите количество оценок состояния: ";
    mystream >> numScores;
    
    for (int i = 0; i < numScores; ++i) {
        int score;
        cout << "Оценка " << i + 1 << " (1-10): ";
        mystream >> score;
        obj.conditionScores.push_back(score);
    }
    
    return mystream;
}