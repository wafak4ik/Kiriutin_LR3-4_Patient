#ifndef _PATIENT_H
#define _PATIENT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Patient
{
    string name;                    // имя пациента
    unsigned age;                   // возраст
    vector<string> diagnoses;       // список диагнозов
    vector<int> conditionScores;    // список оценок общего состояния

public:
    // Конструкторы
    Patient();                                      // по умолчанию
    Patient(string patientName, unsigned patientAge); // параметризованный
    Patient(string patientName, unsigned patientAge, 
            vector<string> diags, vector<int> scores); // параметризованный
    Patient(const Patient& other);                  // копирования
    Patient(const string& str);                     // преобразования

    // Деструктор
    ~Patient() {}

    // Get-методы
    string getName() const { return name; }
    unsigned getAge() const { return age; }
    vector<string> getDiagnoses() const { return diagnoses; }
    vector<int> getConditionScores() const { return conditionScores; }

    // Set-методы
    void setName(string patientName) { name = patientName; }
    void setAge(unsigned patientAge) { age = patientAge; }
    void setDiagnoses(vector<string> diags) { diagnoses = diags; }
    void setConditionScores(vector<int> scores) { conditionScores = scores; }

    // Методы класса
    double calculateAverageCondition() const;

    // Перегруженные операции
    Patient operator+(const Patient& other) const;
    Patient& operator++();       // префиксный инкремент
    Patient operator++(int);     // постфиксный инкремент
    bool operator==(const Patient& other) const;
    const Patient& operator=(const Patient& other);

    // Дружественные функции
    friend ostream& operator<<(ostream& mystream, const Patient& obj);
    friend istream& operator>>(istream& mystream, Patient& obj);
};

#endif // _PATIENT_H