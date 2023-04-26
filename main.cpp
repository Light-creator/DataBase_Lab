#include <iostream>
#include <string>

#include "structures.hpp"

using namespace std;

int splitBySeps(string *strArr, string strCmd, string seps, int l)
{
    for (int i = 0; i < l; i++)
        strArr[i].clear();
    int count, idxArr, i, strLen, sepLen;
    count = idxArr = i = 0;
    strLen = strCmd.length();
    sepLen = seps.length();
    while (i < strLen)
    {
        int flag = 1;
        for (int j = 0; j < sepLen; j++)
        {
            if (seps[j] == strCmd[i])
            {
                if (strArr[idxArr] != "")
                    idxArr++;
                flag = 0;
            }
        }
        if (flag)
        {
            strArr[idxArr] += strCmd[i];
        }
        i++;
    }
    if (strArr[idxArr] == "")
        return idxArr;
    return idxArr + 1;
}

Set *createDevices(string devices)
{
    Set *set = new Set(6);
    string *strArr = new string[9];
    int count = splitBySeps(strArr, devices, "[];", 9);
    for (int i = 0; i < count; i++)
    {
        set->insertVal(strArr[i]);
    }
    delete[] strArr;
    return set;
}

Car *createCar(string *strArr)
{

    string car_vendor, car_model, car_id;
    int year, carrying, axles;
    Set *devices;

    for (int i = 0; i < 14; i += 2)
    {
        if (strArr[i] == "car_vendor")
        {
            car_vendor = strArr[i + 1];
        }
        else if (strArr[i] == "car_model")
        {
            car_model = strArr[i + 1];
        }
        else if (strArr[i] == "car_id")
        {
            car_id = strArr[i + 1];
        }
        else if (strArr[i] == "year")
        {
            year = stoi(strArr[i + 1]);
        }
        else if (strArr[i] == "carrying")
        {
            carrying = stoi(strArr[i + 1]);
        }
        else if (strArr[i] == "axles")
        {
            axles = stoi(strArr[i + 1]);
        }
        else if (strArr[i] == "devices")
        {
            devices = createDevices(strArr[i + 1]);
        }
        else
        {
            return NULL;
        }
    }

    Car *car = new Car(car_vendor, car_model, car_id, year, carrying, axles, devices);
    return car;
}

Condition *parseCond(string strCond)
{
    Condition *cond = new Condition;

    string key = "";
    string val = "";
    int strLen, flag, i;
    strLen = strCond.length();
    flag = i = 0;
    while (i < strLen)
    {
        if (strCond[i] == '/' && strCond[i + 8] == '/')
        {
            cond->operand = _INCLUDE;
            i += 9;
            flag = 1;
        }
        else if (strCond[i] == '/' && strCond[i + 3] == '/')
        {
            cond->operand = _IN;
            i += 4;
            flag = 1;
        }
        else if (strCond[i] == '=' && strCond[i + 1] == '=')
        {
            cond->operand = _EQ;
            i += 2;
            flag = 1;
        }
        else if (strCond[i] == '!' && strCond[i + 1] == '=')
        {
            cond->operand = _NOT_EQ;
            i += 2;
            flag = 1;
        }
        else if (strCond[i] == '>' && strCond[i + 1] == '=')
        {
            cond->operand = _MORE_EQ;
            i += 2;
            flag = 1;
        }
        else if (strCond[i] == '<' && strCond[i + 1] == '=')
        {
            cond->operand = _LESS_EQ;
            i += 2;
            flag = 1;
        }
        else if (strCond[i] == '<' && strCond[i + 1] != '=')
        {
            cond->operand = _LESS;
            i += 2;
            flag = 1;
        }
        else if (strCond[i] == '>' && strCond[i + 1] != '=')
        {
            cond->operand = _MORE;
            i += 2;
            flag = 1;
        }
        else
        {
            if (flag)
                val += strCond[i];
            else
                key += strCond[i];
            i++;
        }
    }

    if (key == "car_vendor")
        cond->key = _VENDOR;
    else if (key == "car_model")
        cond->key = _MODEL;
    else if (key == "car_id")
        cond->key = _ID;
    else if (key == "year")
        cond->key = _YEAR;
    else if (key == "carrying")
        cond->key = _CARR;
    else if (key == "axles")
        cond->key = _AXLES;
    else if (key == "devices")
        cond->key = _DEVICES;

    cond->val = val;

    return cond;
}

void fillFields(string *strFields, vars *fieldArr, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (strFields[i] == "car_vendor")
            fieldArr[i] = _VENDOR;
        else if (strFields[i] == "car_model")
            fieldArr[i] = _MODEL;
        else if (strFields[i] == "car_id")
            fieldArr[i] = _ID;
        else if (strFields[i] == "year")
            fieldArr[i] = _YEAR;
        else if (strFields[i] == "carrying")
            fieldArr[i] = _CARR;
        else if (strFields[i] == "axles")
            fieldArr[i] = _AXLES;
        else if (strFields[i] == "devices")
            fieldArr[i] = _DEVICES;
    }
}

bool checkStrCond(string val, Condition *cond)
{
    // _IN, _INCLUDE, _EQ, _NOT_EQ
    string *strArr = new string[10];
    int count;
    switch (cond->operand)
    {
    case _INCLUDE:
        count = splitBySeps(strArr, cond->val, "[],'", 10);
        for (int i = 0; i < count; i++)
        {
            if (val != strArr[i])
                return false;
        }
        return true;
    case _IN:
        count = splitBySeps(strArr, cond->val, "[],'", 10);
        for (int i = 0; i < count; i++)
        {
            if (val == strArr[i])
                return true;
        }
        return false;
    case _EQ:
        if (val == cond->val)
            return true;
        return false;
    case _NOT_EQ:
        if (val == cond->val)
            return false;
        return true;
    default:
        return false;
    }
    delete[] strArr;
}

bool checkIntCond(int val, Condition *cond)
{
    //_IN, _INCLUDE, _EQ, _NOT_EQ, _LESS, _MORE, _LESS_EQ, _MORE_EQ,
    string *strArr = new string[10];
    int count;
    switch (cond->operand)
    {
    case _INCLUDE:
        count = splitBySeps(strArr, cond->val, "[],'", 10);
        for (int i = 0; i < count; i++)
        {
            if (val != stoi(strArr[i]))
                return false;
        }
        return true;
    case _IN:
        count = splitBySeps(strArr, cond->val, "[],'", 10);
        for (int i = 0; i < count; i++)
        {
            if (val == stoi(strArr[i]))
                return true;
        }
        return false;
    case _EQ:
        if (val == stoi(cond->val))
            return true;
        return false;
    case _NOT_EQ:
        if (val == stoi(cond->val))
            return false;
        return true;
    case _LESS:
        if (val < stoi(cond->val))
            return true;
        return false;
    case _MORE:
        if (val > stoi(cond->val))
            return true;
        return false;
    case _LESS_EQ:
        if (val <= stoi(cond->val))
            return true;
        return false;
    case _MORE_EQ:
        if (val >= stoi(cond->val))
            return true;
        return false;
    default:
        return false;
    }
    delete[] strArr;
}

bool checkSetCond(Set *val, Condition *cond)
{

    string *strArr = new string[10];
    int count = splitBySeps(strArr, cond->val, "[],'", 10);
    switch (cond->operand)
    {
    case _INCLUDE:
        for (int i = 0; i < count; i++)
        {
            if (!val->inSet(strArr[i]))
                return false;
        }
        return true;
    case _IN:
        for (int i = 0; i < count; i++)
        {
            if (val->inSet(strArr[i]))
                return true;
        }
        return false;
    case _EQ:
        if (!val->checkSize(count + 1))
            return false;
        for (int i = 0; i < count; i++)
        {
            if (!val->inSet(strArr[i]))
                return false;
        }
        return true;
    case _NOT_EQ:
        if (!val->checkSize(count + 1))
            return true;
        for (int i = 0; i < count; i++)
        {
            if (!val->inSet(strArr[i]))
                return true;
        }
        return false;
    default:
        return false;
    }
    delete[] strArr;
}

bool checkCond(Node *node, Condition **conds, int c)
{
    // _VENDOR, _MODEL, _ID, _CARR, _YEAR, _DEVICES, _AXLES,
    bool f = true;
    for (int i = 0; i < c; i++)
    {
        if (conds[i]->key == _VENDOR)
            f = checkStrCond(node->car->car_vendor, conds[i]);
        else if (conds[i]->key == _MODEL)
            f = checkStrCond(node->car->car_model, conds[i]);
        else if (conds[i]->key == _ID)
            f = checkStrCond(node->car->car_id, conds[i]);
        else if (conds[i]->key == _YEAR)
            f = checkIntCond(node->car->year, conds[i]);
        else if (conds[i]->key == _AXLES)
            f = checkIntCond(node->car->axles, conds[i]);
        else if (conds[i]->key == _CARR)
            f = checkIntCond(node->car->carrying, conds[i]);
        else
            f = checkSetCond(node->car->devices, conds[i]);

        if (!f)
            break;
    }

    return f;
}

void printNodeWhere(vars *fields, Condition **conds, List *list, int c, int fc)
{
    // _VENDOR, _MODEL, _ID, _CARR, _YEAR, _DEVICES, _AXLES,
    cout << endl;
    Node *ptr = list->header;
    int idx = 1;
    while (ptr != nullptr)
    {
        bool f = checkCond(ptr, conds, c);
        if (f)
        {
            cout << idx << ")" << endl;
            for (int i = 0; i < fc; i++)
            {
                switch (fields[i])
                {
                case _VENDOR:
                    cout << "car_vendor: " << ptr->car->car_vendor << endl;
                    break;
                case _MODEL:
                    cout << "car_model: " << ptr->car->car_model << endl;
                    break;
                case _ID:
                    cout << "car_id: " << ptr->car->car_id << endl;
                    break;
                case _YEAR:
                    cout << "year: " << ptr->car->year << endl;
                    break;
                case _CARR:
                    cout << "carrying: " << ptr->car->carrying << endl;
                    break;
                case _AXLES:
                    cout << "axles: " << ptr->car->axles << endl;
                    break;
                case _DEVICES:
                    cout << "devices: ";
                    ptr->car->devices->printSet();
                    cout << endl;
                    break;
                default:
                    break;
                }
            }
            cout << endl;
            idx++;
        }

        ptr = ptr->next;
    }
    if(idx == 1) cout << "Select 0 elements..." << endl;
    cout << "---------------------" << endl;
}

int updateWhere(fieldsUpdate **fields, Condition **conds, List *list, int c)
{
    Node *ptr = list->header;
    Set *set;
    int kU = 0;
    while (ptr != nullptr)
    {
        bool f = checkCond(ptr, conds, c);
        if (f)
        {
            kU++;
            for (int i = 0; i < sizeof(fields) / sizeof(fieldsUpdate *) + 1; i++)
            {
                switch (fields[i]->key)
                {
                case _VENDOR:
                    ptr->car->car_vendor = fields[i]->val;
                    break;
                case _MODEL:
                    ptr->car->car_model = fields[i]->val;
                    break;
                case _ID:
                    ptr->car->car_id = fields[i]->val;
                    break;
                case _YEAR:
                    ptr->car->year = stoi(fields[i]->val);
                    break;
                case _CARR:
                    ptr->car->carrying = stoi(fields[i]->val);
                    break;
                case _AXLES:
                    ptr->car->axles = stoi(fields[i]->val);
                    break;
                case _DEVICES:
                    set = createDevices(fields[i]->val);
                    ptr->car->devices = set;
                    break;
                default:
                    break;
                }
            }
        }

        ptr = ptr->next;
    }
    return kU;
}

fieldsUpdate **fillStructField(string *fieldArr, int count)
{
    fieldsUpdate **fields = new fieldsUpdate *[count / 2 + 1];
    int k = 0;
    for (int i = 0; i < count; i += 2, k++)
    {
        fields[k] = new fieldsUpdate;

        if (fieldArr[i] == "car_vendor")
        {
            fields[k]->key = _VENDOR;
            fields[k]->val = fieldArr[i + 1];
        }
        else if (fieldArr[i] == "car_model")
        {
            fields[k]->key = _MODEL;
            fields[k]->val = fieldArr[i + 1];
        }
        else if (fieldArr[i] == "car_id")
        {
            fields[k]->key = _ID;
            fields[k]->val = fieldArr[i + 1];
        }
        else if (fieldArr[i] == "year")
        {
            fields[k]->key = _YEAR;
            fields[k]->val = fieldArr[i + 1];
        }
        else if (fieldArr[i] == "carrying")
        {
            fields[k]->key = _CARR;
            fields[k]->val = fieldArr[i + 1];
        }
        else if (fieldArr[i] == "axles")
        {
            fields[k]->key = _AXLES;
            fields[k]->val = fieldArr[i + 1];
        }
        else if (fieldArr[i] == "devices")
        {
            fields[k]->key = _DEVICES;
            fields[k]->val = fieldArr[i + 1];
        }
    }

    return fields;
}

int deleteWhere(Condition **conds, List *list, int c)
{
    Node *ptr = list->header;
    Node *predPtr = list->header;
    Set *set;
    int idx = 0;
    int kD = 0;
    while (ptr != nullptr)
    {
        bool f = checkCond(ptr, conds, c);
        if (f)
        {
            kD++;
            if (idx == 0)
            {
                if (ptr->next == nullptr)
                {
                    list->header = nullptr;
                    break;
                }
                else
                {
                    list->header = ptr->next;
                }
            }
            else if (ptr->next == nullptr)
            {
                predPtr->next = nullptr;
                break;
            }
            else
            {
                predPtr->next = ptr->next;
            }
            delete ptr;
        }

        predPtr = ptr;
        ptr = ptr->next;
        idx++;
    }
    return kD;
}

bool cmpStrFields(string val1, string val2)
{
    if (val1 == val2)
        return true;
    return false;
}

bool cmpIntFields(int val1, int val2)
{
    if (val1 == val2)
        return true;
    return false;
}

bool cmpSetFields(Set *set1, Set *set2)
{
    if (!set1->checkSize(set2->size))
        return false;
    for (int i = 0; i < set2->size; i++)
    {
        if (!set1->inSet(set2->vals[i]))
            return false;
    }
    return true;
}

bool cmpNodes(Node *ptr, Node *lastPtr, vars *fields, int fc)
{
    bool f = false;
    for (int i = 0; i < fc; i++)
    {
        switch (fields[i])
        {
        case _VENDOR:
            f = cmpStrFields(ptr->car->car_vendor, lastPtr->car->car_vendor);
            break;
        case _MODEL:
            f = cmpStrFields(ptr->car->car_model, lastPtr->car->car_model);
            break;
        case _ID:
            f = cmpStrFields(ptr->car->car_id, lastPtr->car->car_id);
            break;
        case _YEAR:
            f = cmpIntFields(ptr->car->year, lastPtr->car->year);
            break;
        case _CARR:
            f = cmpIntFields(ptr->car->carrying, lastPtr->car->carrying);
            break;
        case _AXLES:
            f = cmpIntFields(ptr->car->axles, lastPtr->car->axles);
            break;
        case _DEVICES:
            f = cmpSetFields(ptr->car->devices, lastPtr->car->devices);
            break;
        default:
            break;
        }
        if(f) return true;
    }

    return f;
}

int uniq(vars *fields, List *list, int fc)
{
    Node *ptr = list->header;
    Node *predPtr = list->header;
    Node *tmp;

    if (list->header->next == nullptr)
        return 0;
    Node *lastPtr = list->header->next;

    int idx = 0;
    int kU = 0;
    bool f;
    while (ptr != nullptr)
    {
        f = 0;
        lastPtr = ptr->next;
        while (lastPtr != nullptr)
        {
            f = cmpNodes(ptr, lastPtr, fields, fc);
            if (f)
            {
                kU++;
                tmp = ptr;
                if (idx == 0)
                {
                    if (ptr->next == nullptr){
                        list->header = nullptr;
                        predPtr = ptr->next;
                        ptr = ptr->next;
                    }
                    else
                    {
                        list->header = ptr->next;
                        predPtr = ptr->next;
                        ptr = ptr->next;
                    }
                    idx--;
                } 
                else 
                {
                    ptr = ptr->next;
                    predPtr->next = ptr;
                }
                delete tmp;
                break;
            }
            lastPtr = lastPtr->next;
        }
        if(!f){
            predPtr = ptr;
            ptr = ptr->next;    
        }
        idx++;
    }

    return kU;
}

int main()
{

    Set *set = new Set(6);
    set->insertVal("radio");
    set->insertVal("belts");

    Set *set2 = new Set(6);
    set2->insertVal("seats");
    set2->insertVal("windows");

    Car *car = new Car("Kia", "Sorento", "fgdffg", 1232, 213, 34, set);
    Car *car2 = new Car("BMW", "Focus", "43gdsd5", 1532, 13, 14, set2);
    Car *car3 = new Car("Kia", "Rio", "43gdsd5", 1532, 13, 14, set2);
    Car *car4 = new Car("Ford", "Transit", "43gdsd5", 1532, 13, 14, set);
    Car *car5 = new Car("Kia", "Optima", "43gdsd5", 1532, 13, 14, set);

    List *list = new List;
    list->push(car);
    list->push(car2);
    list->push(car3);
    list->push(car4);
    list->push(car5);

    string strCmd;
    string *strArr = new string[20];

    int sizeArr = 0;
    int choice;

    while (1)
    {
        cout << "1 - Enter the command" << endl;
        cout << "2 - Exit" << endl;

        cin >> choice;
        getchar();
        if (choice == 2)
            break;
        else if (choice == 1)
        {
            cout << "Enter the command: ";
            getline(cin, strCmd);
            int count = splitBySeps(strArr, strCmd, " ", 20);

            if (strArr[0] == "insert")
            {
                count = splitBySeps(strArr, strArr[1], ",=", 20);

                if (count < 14)
                {
                    cout << "Incorrect data..." << endl;
                    continue;
                }

                Car *car = createCar(strArr);
                list->push(car);
                // insert car_vendor=Tayota,car_model=Rav4,car_id=12sad,year=1111,carrying=4,axles=2,devices=['belts';'display']
            }
            else if (strArr[0] == "select")
            {
                string *fieldArr = new string[10];
                int fieldCount = splitBySeps(fieldArr, strArr[1], ",", 10);
                vars *fields = new vars[fieldCount];
                fillFields(fieldArr, fields, fieldCount);

                // select car_vendor,car_id,year devices/include/['radio'] car_model==Kia
                Condition **conds = new Condition *[count - 2];
                int k = 0;
                for (int i = 2; i < count; i++)
                {
                    conds[k] = parseCond(strArr[i]);
                    k++;
                }

                printNodeWhere(fields, conds, list, count - 2, fieldCount);

                // Free memory
                for (int i = 0; i < count - 2; i++)
                    delete conds[i];

                delete[] conds;
                delete[] fields;
                delete[] fieldArr;
            }
            else if (strArr[0] == "update")
            {
                string *fieldArr = new string[20];
                int fieldCount = splitBySeps(fieldArr, strArr[1], ",=", 20);
                fieldsUpdate **fields = fillStructField(fieldArr, fieldCount);

                Condition **conds = new Condition *[count - 2];
                int k = 0;
                for (int i = 2; i < count; i++)
                {
                    conds[k] = parseCond(strArr[i]);
                    k++;
                }

                int kU = updateWhere(fields, conds, list, count - 2);
                cout << "update:" << kU << endl;

                // Free memory
                for (int i = 0; i < count - 2; i++)
                    delete conds[i];

                for (int i = 0; i < fieldCount / 2; i++)
                    delete fields[i];

                delete[] fieldArr;
                delete[] fields;
                delete[] conds;
            }
            else if (strArr[0] == "delete")
            {
                Condition **conds = new Condition *[count - 2];
                int k = 0;
                for (int i = 1; i < count; i++)
                {
                    conds[k] = parseCond(strArr[i]);
                    k++;
                }

                int kD = deleteWhere(conds, list, count - 1);
                cout << "delete:" << kD << endl;

                // Free memory
                for (int i = 0; i < count - 2; i++)
                    delete conds[i];
                delete[] conds;
            }
            else if (strArr[0] == "uniq")
            {
                string *fieldArr = new string[10];
                int fieldCount = splitBySeps(fieldArr, strArr[1], ",", 10);
                vars *fields = new vars[fieldCount];
                fillFields(fieldArr, fields, fieldCount);

                int kU = uniq(fields, list, fieldCount);
                cout << "uniq:" << kU << endl;

                list->printList();

                // Free memory
                delete[] fieldArr;
                delete[] fields;
            }
        }
        else
        {
            cout << "Incorrect data..." << endl;
        }
    }

    delete list;
    delete[] strArr;
    return 0;
}