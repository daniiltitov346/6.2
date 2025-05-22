#pragma once
#include <vector>
#include <memory>

#include "C:\Users\Huawei\source\repos\6.1�\6.1�\person.h"
#include "C:\Users\Huawei\source\repos\6.1�\6.1�\cyclist.h"
#include "C:\Users\Huawei\source\repos\6.1�\6.1�\motorcycle.h"
#include "C:\Users\Huawei\source\repos\6.1�\6.1�\car.h"
#include "C:\Users\Huawei\source\repos\6.1�\6.1�\unattended_bag.h"

class SurveillanceArray {
private:
    std::vector<std::unique_ptr<DetectedObject>> objects;

public:
    // ������������
    SurveillanceArray() = default;

    // ������� ����
    SurveillanceArray(const SurveillanceArray& other);

    SurveillanceArray& operator=(const SurveillanceArray& other);

    SurveillanceArray(SurveillanceArray&& other) noexcept = default;
    SurveillanceArray& operator=(SurveillanceArray&& othr) noexcept = default;

    ~SurveillanceArray() = default;

    // ���������� ������� (���������� ��������� ������)
    void addPerson(int x1, int y1, int x2, int y2, Gender g, TernaryStatus child,
        TernaryStatus glasses, TernaryStatus beard);

    void addCyclist(int x1, int y1, int x2, int y2, Gender g, TernaryStatus child,
        TernaryStatus glasses, TernaryStatus beard);

    void addMotorcycle(int x1, int y1, int x2, int y2, const unsigned char color[3], const char* plate);

    void addCar(int x1, int y1, int x2, int y2, const unsigned char color[3],
        const char* plate, bool isTaxi);

    void addBag(int x1, int y1, int x2, int y2, unsigned int seenTime);

    // �������� ������� �� �������
    void remove(size_t index);

    // ����� ���� ��������
    void printAll() const; 

    // ��������� ������� �������
    size_t size() const; 

    // ������� �������
    void clear();
};
