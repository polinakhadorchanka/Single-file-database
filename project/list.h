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
	string name; // Наименование товара
	string type; // Тип товара
	string country; // Страна-производитель
	string material; // Материал
	string description; // Описание товара
	double price; // Цена товара
	int count; // Кол-во поставляемого товара
	DELIVERYDATE date; // Дата поставки
	string store; // Наименование/номер магазина
	string provider; // Поставщик
};

static list<DOORFURNITURE> lst; // Список товаров

string DateToString(DELIVERYDATE date); // Возвращает дату в виде строки