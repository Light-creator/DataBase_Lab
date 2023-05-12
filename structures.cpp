#include <iostream>
#include <string>
#include <fstream>

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
    ofstream fout("output.txt");
    if (size == cap)
    {
        cout << "Error: Too many args..." << endl;
        fout << "Error: Too many args..." << endl;
        return false;
    }

    if (inSet(value))
    {
        cout << "Error: This item already exists..." << endl;
        fout << "Error: This item already exists..." << endl;
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
    ofstream fout("output.txt");

    cout << "{ ";
    fout << "{ ";
    for (int i = 0; i < size; i++)
    {
        cout << vals[i] << " ";
        fout << vals[i] << " ";
    }
    cout << "}" << endl;
    fout << "}" << endl;
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
    ofstream fout("output.txt");

    cout << "car vendor: " << car_vendor << " car model: " << car_model << endl;
    fout << "car vendor: " << car_vendor << " car model: " << car_model << endl;
    cout << "car id: " << car_id << " year: " << year << endl;
    fout << "car id: " << car_id << " year: " << year << endl;
    cout << "carrying: " << carrying << " axles: " << axles << endl;
    fout << "carrying: " << carrying << " axles: " << axles << endl;
    cout << "devices: ";
    fout << "devices: ";
    devices->printSet();
    cout << endl << "-------------------------------" << endl;
    fout << endl << "-------------------------------" << endl;
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
    ofstream fout("output.txt");

    cout << "[" << endl;
    fout << "[" << endl;
    Node *tmp = header;
    int i = 0;
    while (tmp != nullptr)
    {
        cout << i + 1 << ") " << endl;
        fout << i + 1 << ") " << endl;
        tmp->car->printCar();
        tmp = tmp->next;
        i++;
    }
    cout << "]" << endl;
    fout << "]" << endl;
}
