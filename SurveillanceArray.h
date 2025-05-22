#pragma once
#include <vector>
#include <memory>

#include "C:\Users\Huawei\source\repos\6.1б\6.1б\person.h"
#include "C:\Users\Huawei\source\repos\6.1б\6.1б\cyclist.h"
#include "C:\Users\Huawei\source\repos\6.1б\6.1б\motorcycle.h"
#include "C:\Users\Huawei\source\repos\6.1б\6.1б\car.h"
#include "C:\Users\Huawei\source\repos\6.1б\6.1б\unattended_bag.h"

class SurveillanceArray {
private:
    std::vector<std::unique_ptr<DetectedObject>> objects;

public:
    // Конструкторы
    SurveillanceArray() = default;

    // Правило пяти
    SurveillanceArray(const SurveillanceArray& other);

    SurveillanceArray& operator=(const SurveillanceArray& other);

    SurveillanceArray(SurveillanceArray&& other) noexcept = default;
    SurveillanceArray& operator=(SurveillanceArray&& othr) noexcept = default;

    ~SurveillanceArray() = default;

    // Добавление объекта (используем фабричные методы)
    void addPerson(int x1, int y1, int x2, int y2, Gender g, TernaryStatus child,
        TernaryStatus glasses, TernaryStatus beard);

    void addCyclist(int x1, int y1, int x2, int y2, Gender g, TernaryStatus child,
        TernaryStatus glasses, TernaryStatus beard);

    void addMotorcycle(int x1, int y1, int x2, int y2, const unsigned char color[3], const char* plate);

    void addCar(int x1, int y1, int x2, int y2, const unsigned char color[3],
        const char* plate, bool isTaxi);

    void addBag(int x1, int y1, int x2, int y2, unsigned int seenTime);

    // Удаление объекта по индексу
    void remove(size_t index);

    // Вывод всех объектов
    void printAll() const; 

    // Получение размера массива
    size_t size() const; 

    // Очистка массива
    void clear();
};
