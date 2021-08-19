#include "menu.h"
#include "list.h"

using namespace std;

extern list<DOORFURNITURE> lst; // Список товаров

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	system("MODE CON: COLS=190 LINES=42"); // Задаем размер окна (после запуска менять размер консоли не рекомендуется)
	ShowConsoleCursor(false); // Скрываем отображение курсора


	getMainMenu(lst, 0, false, 0); // Вызываем главное меню
}
