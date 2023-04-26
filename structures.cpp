#include <iostream>
#include <string>

#include "structures.hpp"

using namespace std;


Set::Set(int _cap)
{
    size = 0;
    cap = _cap;
    vals = new string[_cap];
}

Set::~Set()
{
    delete[] vals;
}

bool Set::insertVal(string value)
{
    if (size == cap)
    {
        cout << "Error: Too many args..." << endl;
        return false;
    }

    if (inSet(value))
    {
        cout << "Error: This item already exists..." << endl;
        return false;
    }

    vals[size] = value;
    size++;
    return true;
}

bool Set::checkSize(int val) {
    if(val == size) return true;
    return false;
}

bool Set::inSet(string value)
{
    for (int i = 0; i < size; i++)
    {
        if (vals[i] == value)
            return true;
    }
    return false;
}

void Set::printSet()
{
    cout << "{ ";
    for (int i = 0; i < size; i++)
    {
        cout << vals[i] << " ";
    }
    cout << "}" << endl;
}

Car::Car(string _car_vendor, string _car_model, string _car_id, int _year, int _carrying, int _axles, Set *_devices)
{
    car_vendor = _car_vendor;
    car_model = _car_model;
    car_id = _car_id;

    year = _year;
    carrying = _carrying;
    axles = _axles;
    devices = _devices;
}
Car::~Car()
{
    delete devices;
}

void Car::printCar()
{
    cout << "car vendor: " << car_vendor << " car model: " << car_model << endl;
    cout << "car id: " << car_id << " year: " << year << endl;
    cout << "carrying: " << carrying << " axles: " << axles << endl;
    cout << "devices: ";
    devices->printSet();
    cout << endl
         << "-------------------------------" << endl;
}

List::List()
{
    header = nullptr;
}

List::~List()
{
    Node *tmp = header;
    while (header != nullptr)
    {
        tmp = header->next;
        delete header->car;
        delete header;
        header = tmp;
    }
}

void List::push(Car *car)
{
    if (header == nullptr)
    {
        header = new Node(car);
        return;
    }

    Node *tmp = header;
    while (tmp->next != nullptr)
    {
        tmp = tmp->next;
    }

    tmp->next = new Node(car);
}

void List::pop()
{
}

void List::printList()
{
    cout << "[" << endl;
    Node *tmp = header;
    int i = 0;
    while (tmp != nullptr)
    {
        cout << i + 1 << ") " << endl;
        tmp->car->printCar();
        tmp = tmp->next;
        i++;
    }
    cout << "]" << endl;
}
