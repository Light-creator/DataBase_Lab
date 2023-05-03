#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

using namespace std;

#include <iostream>
#include <string>

enum conditions_type {
    _IN, _INCLUDE, _EQ, _NOT_EQ, _LESS, _MORE, _LESS_EQ, _MORE_EQ,
};

enum vars {
    _VENDOR, _MODEL, _ID, _CARR, _YEAR, _DEVICES, _AXLES,
};

struct Condition {
    vars key;
    string val;
    conditions_type operand;
};

struct fieldsUpdate {
    vars key;
    string val;
};

class Set {
public:
    int cap;
    string *vals;

public:
    int size;
    Set(int _cap);
    ~Set();

    bool insertVal(string value);
    bool inSet(string value);
    bool checkSize(int val);
    void printSet();

};

class Car {
public:
    Car(string _car_vendor, string _car_model, string _car_id, int year, int _carrying, int _axles, Set *_devices);
    ~Car();
    void printCar();

    string car_vendor;
    string car_model;
    string car_id;

    int year;
    int carrying;
    int axles;

    Set *devices;
};

struct Node {
    Car *car;
    struct Node *next;

    Node(Car *_car) {
        car = _car;
        next = nullptr;
    }
};

class List {

public:
    Node *header;
    List();
    ~List();

    void push(Car *car);
    void printList();
};

#endif // STRUCTURES_H_INCLUDED