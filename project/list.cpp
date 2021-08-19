#include "list.h"

using namespace std;

/* Функция преобразования структуры DELIVERYDATE в строку */
string DateToString(DELIVERYDATE date) {
	return  date.day == 0 ? "" : (date.day < 10 ? "0" : "") + to_string(date.day) + "." + (date.month < 10 ? "0" : "") + to_string(date.month) + "." + to_string(date.year);
}