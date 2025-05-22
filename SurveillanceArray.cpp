#include "SurveillanceArray.h"
#include <iostream>

// Конструктор копирования
SurveillanceArray::SurveillanceArray(const SurveillanceArray& other) {
    for (const auto& obj : other.objects) {
        objects.push_back(std::unique_ptr<DetectedObject>(obj->clone()));
    }
}

// Оператор присваивания копированием
SurveillanceArray& SurveillanceArray::operator=(const SurveillanceArray& other) {
    if (this != &other) {
        objects.clear();
        for (const auto& obj : other.objects) {
            objects.push_back(std::unique_ptr<DetectedObject>(obj->clone()));
        }
    }
    return *this;
}

// Методы добавления объектов
void SurveillanceArray::addPerson(int x1, int y1, int x2, int y2, Gender g, TernaryStatus child,
    TernaryStatus glasses, TernaryStatus beard) {
    objects.push_back(std::make_unique<Person>(x1, y1, x2, y2, g, child, glasses, beard));
}

void SurveillanceArray::addCyclist(int x1, int y1, int x2, int y2, Gender g, TernaryStatus child,
    TernaryStatus glasses, TernaryStatus beard) {
    objects.push_back(std::make_unique<Cyclist>(x1, y1, x2, y2, g, child, glasses, beard));
}

void SurveillanceArray::addMotorcycle(int x1, int y1, int x2, int y2, const unsigned char color[3], const char* plate) {
    objects.push_back(std::make_unique<Motorcycle>(x1, y1, x2, y2, color, plate));
}

void SurveillanceArray::addCar(int x1, int y1, int x2, int y2, const unsigned char color[3],
    const char* plate, bool isTaxi) {
    objects.push_back(std::make_unique<Car>(x1, y1, x2, y2, color, plate, isTaxi));
}

void SurveillanceArray::addBag(int x1, int y1, int x2, int y2, unsigned int seenTime) {
    objects.push_back(std::make_unique<UnattendedBag>(x1, y1, x2, y2, seenTime));
}

// Удаление объекта по индексу
void SurveillanceArray::remove(size_t index) {
    if (index < objects.size()) {
        objects.erase(objects.begin() + index);
    }
}

// Вывод всех объектов
void SurveillanceArray::printAll() const {
    std::cout << "=== Surveillance Objects ===\n";
    for (const auto& obj : objects) {
        obj->Print(std::cout);
        std::cout << "\n-------------------------\n";
    }
}

// Получение размера массива
size_t SurveillanceArray::size() const {
    return objects.size();
}

// Очистка массива
void SurveillanceArray::clear() {
    objects.clear();
}