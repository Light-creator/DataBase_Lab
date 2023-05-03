#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

using namespace std;

#include <iostream>
#include <string>

#include "structures.hpp"

int splitBySeps(string *strArr, string strCmd, string seps, int l);
bool checkStrCond(string val, Condition *cond);
bool checkIntCond(int val, Condition *cond);
bool checkSetCond(Set *val, Condition *cond);
bool checkCond(Node *node, Condition **conds, int c);
bool cmpStrFields(string val1, string val2);
bool cmpIntFields(int val1, int val2);
bool cmpSetFields(Set *set1, Set *set2);
bool cmpNodes(Node *ptr, Node *lastPtr, vars *fields, int fc);

int updateWhere(fieldsUpdate **fields, Condition **conds, List *list, int c);
void printNodeWhere(vars *fields, Condition **conds, List *list, int c, int fc);
int deleteWhere(Condition **conds, List *list, int c);
int uniq(vars *fields, List *list, int fc);

Set *createDevices(string devices);
Car *createCar(string *strArr);

Condition *parseCond(string strCond);
fieldsUpdate **fillStructField(string *fieldArr, int count);

void fillFields(string *strFields, vars *fieldArr, int count);

#endif