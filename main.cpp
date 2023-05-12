#include <iostream>
#include <string>
#include <fstream>

#include "structures.hpp"
#include "utils.hpp"

using namespace std;

void executeCmd(string strCmd, List *list)
{
    ofstream fout("output.txt");

    string *strArr = new string[20];
    int count = splitBySeps(strArr, strCmd, " ", 20);

    if (strArr[0] == "insert")
    {
        count = splitBySeps(strArr, strArr[1], ",=", 20);

        if (count < 14)
        {
            cout << "Incorrect data..." << endl;
            fout << "Incorrect data..." << endl;
            return;
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
        fout << "update:" << kU << endl;

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
        fout << "delete:" << kD << endl;

        // Free memory
        for (int i = 0; i < count - 1; i++)
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
        fout << "uniq:" << kU << endl;

        list->printList();

        // Free memory
        delete[] fieldArr;
        delete[] fields;
    }

    delete[] strArr;
}

int main()
{
    List *list = new List;
    string strCmd;

    int sizeArr = 0;
    int choice;

    ifstream fin("input.txt");

    while (1)
    {
        cout << "1 - Enter the command" << endl;
        cout << "2 - Get commands from the file" << endl;
        cout << "3 - Exit" << endl;

        cin >> choice;
        getchar();
        if (choice == 3)
            break;
        else if (choice == 1)
        {
            cout << "Enter the command: ";
            getline(cin, strCmd);
            executeCmd(strCmd, list);
        } else if(choice == 2) {
            while(getline(fin, strCmd)) {
                executeCmd(strCmd, list);
            }
        }
        else
        {
            cout << "Incorrect data..." << endl;
        }
    }

    list->printList();
    fin.close();
    delete list;
    return 0;
}