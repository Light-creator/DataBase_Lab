#include <iostream>
#include <string>

#include "structures.hpp"
#include "utils.hpp"

using namespace std;

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