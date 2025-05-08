#include <iostream>
#include <memory>
#include <vector>
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
    SurveillanceArray(const SurveillanceArray& other) {
        for (const auto& obj : other.objects) {
            objects.push_back(std::unique_ptr<DetectedObject>(obj->clone()));
        }
    }

    SurveillanceArray& operator=(const SurveillanceArray& other) {
        if (this != &other) {
            objects.clear();
            for (const auto& obj : other.objects) {
                objects.push_back(std::unique_ptr<DetectedObject>(obj->clone()));
            }
        }
        return *this;
    }

    SurveillanceArray(SurveillanceArray&& other) noexcept = default;
    SurveillanceArray& operator=(SurveillanceArray&& other) noexcept = default;

    ~SurveillanceArray() = default;

    // Добавление объекта (используем фабричные методы)
    void addPerson(int x1, int y1, int x2, int y2, Gender g, TernaryStatus child,
        TernaryStatus glasses, TernaryStatus beard) {
        objects.push_back(std::make_unique<Person>(x1, y1, x2, y2, g, child, glasses, beard));
    }

    void addCyclist(int x1, int y1, int x2, int y2, Gender g, TernaryStatus child,
        TernaryStatus glasses, TernaryStatus beard) {
        objects.push_back(std::make_unique<Cyclist>(x1, y1, x2, y2, g, child, glasses, beard));
    }

    void addMotorcycle(int x1, int y1, int x2, int y2, const unsigned char color[3], const char* plate) {
        objects.push_back(std::make_unique<Motorcycle>(x1, y1, x2, y2, color, plate));
    }

    void addCar(int x1, int y1, int x2, int y2, const unsigned char color[3],
        const char* plate, bool isTaxi) {
        objects.push_back(std::make_unique<Car>(x1, y1, x2, y2, color, plate, isTaxi));
    }

    void addBag(int x1, int y1, int x2, int y2, unsigned int seenTime) {
        objects.push_back(std::make_unique<UnattendedBag>(x1, y1, x2, y2, seenTime));
    }

    // Удаление объекта по индексу
    void remove(size_t index) {
        if (index < objects.size()) {
            objects.erase(objects.begin() + index);
        }
    }

    // Вывод всех объектов
    void printAll() const {
        std::cout << "=== Surveillance Objects ===\n";
        for (const auto& obj : objects) {
            obj->Print(std::cout);
            std::cout << "-------------------------\n";
        }
    }

    // Получение размера массива
    size_t size() const {
        return objects.size();
    }

    // Очистка массива
    void clear() {
        objects.clear();
    }
};

// Тестирование
int main() {
    try {
        SurveillanceArray array;

        // Добавляем объекты разных типов
        array.addPerson(10, 20, 50, 100, Gender::MALE,
            TernaryStatus::NO, TernaryStatus::YES, TernaryStatus::NO);

        array.addCyclist(30, 40, 80, 120, Gender::FEMALE,
            TernaryStatus::UNKNOWN, TernaryStatus::NO, TernaryStatus::UNKNOWN);

        unsigned char red[3] = { 255, 0, 0 };
        array.addMotorcycle(100, 100, 200, 180, red, "1234 AB-1");

        unsigned char blue[3] = { 0, 0, 255 };
        array.addCar(150, 80, 300, 200, blue, "5678 CD-2", true);

        array.addBag(200, 200, 220, 230, 36000); // 10:00:00

        // Выводим все объекты
        array.printAll();

        // Тестируем удаление
        std::cout << "\nRemoving first object...\n";
        array.remove(0);
        array.printAll();

        // Тестируем копирование
        std::cout << "\nTesting copy...\n";
        SurveillanceArray array2 = array;
        array2.printAll();

        // Тестируем перемещение
        std::cout << "\nTesting move...\n";
        SurveillanceArray array3 = std::move(array2);
        array3.printAll();
        std::cout << "Original array size after move: " << array2.size() << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

