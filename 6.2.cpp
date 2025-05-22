#include <iostream>
#include "SurveillanceArray.h"

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

        std::cout << "\n\n\n";
        SurveillanceArray arr4 = array3;
        arr4.printAll();


    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

