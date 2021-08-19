#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include<fstream>
#include <time.h>
#include "list.h"


bool ShowConsoleCursor(bool bShow); // Функция включения/выключения видимости курсора (взята на просторах интернета)

void getMainMenu(list<DOORFURNITURE> lst, int activeItem, bool submenu, int activeSubItem); // Функция отображения главного меню
void getMenu3(list<DOORFURNITURE> lst, int activeItem, int activeSubItem); // Подменю для удаления
void getMenu5(list<DOORFURNITURE> lst, int activeItem, int activeSubItem); // Подменю для сортировки
void getMenu7(list<DOORFURNITURE> lst, int activeItem, int activeSubItem); // Подменю для отчетов
void getMenu8(list<DOORFURNITURE> lst, int activeItem, int activeSubItem); // Подменю для выхода

void printList(list<DOORFURNITURE> lst, int activeItem, int site, bool clear); // Вывод списка товаров
void printSearchList(list<DOORFURNITURE> lst, string searchStr, int activeItem, int site, bool clear); // Вывод списка товаров по заданному критерию
void printElement(int num, DOORFURNITURE element, bool active); // Вывод элемента списка товаров

void printWarning(string msg); // Вывод предупреждения
void clearWarning(); // Стирает предупрежедние

void addNewElement(list<DOORFURNITURE> lst, bool clear); // Добавление нового элемента

bool isEmpty(string str); // true - если строка пустая
bool onlyLetters(string str); // true - если в строке только буквы (латиница)
bool isDate(string str); // true - если введена корректная дата

void printListEdit(list<DOORFURNITURE> lst, int activeItem, int site, bool clear); // Вывод списка товаров для редактирования

bool saveToFile(list<DOORFURNITURE> lst); // Сохранение данных в файл
bool loadFromFile(list<DOORFURNITURE>& lst); // Загрузка данных из файла
bool saveToFileReport(list<DOORFURNITURE> lst, string reportName, string& filename); // Сохранение отчета в файл

void sortList(list<DOORFURNITURE>& lst, int type); // Сортировка (сортируется исходный список)
bool listPred1(DOORFURNITURE n1, DOORFURNITURE n2);
bool listPred2(DOORFURNITURE n1, DOORFURNITURE n2);
bool listPred3(DOORFURNITURE n1, DOORFURNITURE n2);
bool listPred4(DOORFURNITURE n1, DOORFURNITURE n2);
bool listPred5(DOORFURNITURE n1, DOORFURNITURE n2);
bool listPred6(DOORFURNITURE n1, DOORFURNITURE n2);
bool listPred7(DOORFURNITURE n1, DOORFURNITURE n2);

string printDialog(string msg); // Диалоговое окна для запроса параметров