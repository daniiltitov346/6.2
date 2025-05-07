#include <iostream>
#include <string>

// Базовый класс для всех обнаруженных сущностей
class DetectedEntity {
protected:
    int xmin, ymin, xmax, ymax;

public:
    DetectedEntity(int xMin, int yMin, int xMax, int yMax)
        : xmin(xMin), ymin(yMin), xmax(xMax), ymax(yMax) {}

    virtual ~DetectedEntity() = default;

    virtual void display() const = 0; // Чисто виртуальная функция
    virtual DetectedEntity* clone() const = 0; // Метод клонирования
};

// Пример производного класса
class Human : public DetectedEntity {
private:
    std::string gender;
    bool isChild;
    bool wearingGlasses;
    bool hasBeard;

public:
    Human(int xMin, int yMin, int xMax, int yMax, const std::string& gender, bool isChild,
        bool wearingGlasses, bool hasBeard)
        : DetectedEntity(xMin, yMin, xMax, yMax), gender(gender), isChild(isChild),
        wearingGlasses(wearingGlasses), hasBeard(hasBeard) {}

    void display() const override {
        std::cout << "Human at (" << xmin << ", " << ymin << ") - ("
            << xmax << ", " << ymax << ")\n"
            << "Gender: " << gender << ", Child: " << (isChild ? "Yes" : "No")
            << ", Glasses: " << (wearingGlasses ? "Yes" : "No")
            << ", Beard: " << (hasBeard ? "Yes" : "No") << std::endl;
    }

    DetectedEntity* clone() const override {
        return new Human(*this); // Клонирование объекта
    }
};

// Класс динамического массива
class DynamicArray {
private:
    DetectedEntity** entities; // Массив указателей на сущности
    size_t size; // Текущий размер массива
    size_t capacity; // Вместимость массива

    void resize() {
        capacity *= 2;
        DetectedEntity** newEntities = new DetectedEntity * [capacity];
        for (size_t i = 0; i < size; ++i) {
            newEntities[i] = entities[i];
        }
        delete[] entities; // Освобождение старого массива
        entities = newEntities;
    }

public:
    DynamicArray() : size(0), capacity(2) {
        entities = new DetectedEntity * [capacity];
    }

    // Конструктор копирования
    DynamicArray(const DynamicArray& other) : size(other.size), capacity(other.capacity) {
        entities = new DetectedEntity * [capacity];
        for (size_t i = 0; i < size; ++i) {
            entities[i] = other.entities[i]->clone(); // Клонирование сущностей
        }
    }

    // Оператор копирования
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            for (size_t i = 0; i < size; ++i) {
                delete entities[i]; // Освобождение текущих объектов
            }
            delete[] entities; // Освобождение массива указателей

            size = other.size;
            capacity = other.capacity;
            entities = new DetectedEntity * [capacity];
            for (size_t i = 0; i < size; ++i) {
                entities[i] = other.entities[i]->clone(); // Клонирование
            }
        }
        return *this;
    }

    // Конструктор перемещения
    DynamicArray(DynamicArray&& other) noexcept
        : entities(other.entities), size(other.size), capacity(other.capacity) {
        other.entities = nullptr; // Обнуление указателя
        other.size = 0;
        other.capacity = 0;
    }

    // Оператор перемещения
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < size; ++i) {
                delete entities[i]; // Освобождение текущих объектов
            }
            delete[] entities; // Освобождение массива указателей

            entities = other.entities;
            size = other.size;
            capacity = other.capacity;

            other.entities = nullptr; // Обнуление указателя
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // Метод добавления объекта в массив
    void addEntity(DetectedEntity* entity) {
        if (size >= capacity) {
            resize();
        }
        entities[size++] = entity->clone(); // Клонирование и добавление в массив
    }

    // Метод удаления объекта по индексу
    void removeEntity(size_t index) {
        if (index < size) {
            delete entities[index]; // Освобождение памяти
            for (size_t i = index; i < size - 1; ++i) {
                entities[i] = entities[i + 1]; // Сдвиг элементов
            }
            --size;
        }
    }

    // Метод вывода всех объектов
    void displayEntities() const {
        for (size_t i = 0; i < size; ++i) {
            entities[i]->display(); // Вывод информации о сущности
        }
    }

    // Деструктор
    ~DynamicArray() {
        for (size_t i = 0; i < size; ++i) {
            delete entities[i]; // Освобождение каждого объекта
        }
        delete[] entities; // Освобождение массива указателей
    }
};

// Тестирование динамического массива
void testDynamicArray() {
    DynamicArray array;

    // Добавление объектов в массив (методы шаблоны, не вызываются)
     array.addEntity(new Human(10, 20, 50, 100, "M", true, false, true));
     array.addEntity(new Human(30, 40, 80, 120, "F", false, true, false));

    // Вывод объектов
     array.displayEntities();

     //Удаление объекта
     /*array.removeEntity(0);*/

     //Вывод объектов снова
    /* array.displayEntities();*/
}

int main() {
    testDynamicArray();
    return 0;
}