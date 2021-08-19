#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include<fstream>
#include <time.h>
#include "list.h"


bool ShowConsoleCursor(bool bShow); // ������� ���������/���������� ��������� ������� (����� �� ��������� ���������)

void getMainMenu(list<DOORFURNITURE> lst, int activeItem, bool submenu, int activeSubItem); // ������� ����������� �������� ����
void getMenu3(list<DOORFURNITURE> lst, int activeItem, int activeSubItem); // ������� ��� ��������
void getMenu5(list<DOORFURNITURE> lst, int activeItem, int activeSubItem); // ������� ��� ����������
void getMenu7(list<DOORFURNITURE> lst, int activeItem, int activeSubItem); // ������� ��� �������
void getMenu8(list<DOORFURNITURE> lst, int activeItem, int activeSubItem); // ������� ��� ������

void printList(list<DOORFURNITURE> lst, int activeItem, int site, bool clear); // ����� ������ �������
void printSearchList(list<DOORFURNITURE> lst, string searchStr, int activeItem, int site, bool clear); // ����� ������ ������� �� ��������� ��������
void printElement(int num, DOORFURNITURE element, bool active); // ����� �������� ������ �������

void printWarning(string msg); // ����� ��������������
void clearWarning(); // ������� ��������������

void addNewElement(list<DOORFURNITURE> lst, bool clear); // ���������� ������ ��������

bool isEmpty(string str); // true - ���� ������ ������
bool onlyLetters(string str); // true - ���� � ������ ������ ����� (��������)
bool isDate(string str); // true - ���� ������� ���������� ����

void printListEdit(list<DOORFURNITURE> lst, int activeItem, int site, bool clear); // ����� ������ ������� ��� ��������������

bool saveToFile(list<DOORFURNITURE> lst); // ���������� ������ � ����
bool loadFromFile(list<DOORFURNITURE>& lst); // �������� ������ �� �����
bool saveToFileReport(list<DOORFURNITURE> lst, string reportName, string& filename); // ���������� ������ � ����

void sortList(list<DOORFURNITURE>& lst, int type); // ���������� (����������� �������� ������)
bool listPred1(DOORFURNITURE n1, DOORFURNITURE n2);
bool listPred2(DOORFURNITURE n1, DOORFURNITURE n2);
bool listPred3(DOORFURNITURE n1, DOORFURNITURE n2);
bool listPred4(DOORFURNITURE n1, DOORFURNITURE n2);
bool listPred5(DOORFURNITURE n1, DOORFURNITURE n2);
bool listPred6(DOORFURNITURE n1, DOORFURNITURE n2);
bool listPred7(DOORFURNITURE n1, DOORFURNITURE n2);

string printDialog(string msg); // ���������� ���� ��� ������� ����������