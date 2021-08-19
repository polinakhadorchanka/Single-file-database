#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <list>

using namespace std;

struct DELIVERYDATE {
	int day;
	int month;
	int year;
};

struct DOORFURNITURE {
	string name; // ������������ ������
	string type; // ��� ������
	string country; // ������-�������������
	string material; // ��������
	string description; // �������� ������
	double price; // ���� ������
	int count; // ���-�� ������������� ������
	DELIVERYDATE date; // ���� ��������
	string store; // ������������/����� ��������
	string provider; // ���������
};

static list<DOORFURNITURE> lst; // ������ �������

string DateToString(DELIVERYDATE date); // ���������� ���� � ���� ������