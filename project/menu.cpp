#include "menu.h"

using namespace std;

// Функция для включения/отключения отображения курсора. Взята из интернета
bool ShowConsoleCursor(bool bShow)
{
	CONSOLE_CURSOR_INFO cci;
	HANDLE hStdOut;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
		return FALSE;
	if (!GetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	cci.bVisible = bShow;
	if (!SetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	return TRUE;
}

/* Функция отображения главного меню
	activeItem - номер активной строки
	submenu - true, если необходимо открыть подменю
	activeSubItem - номер активной строки подменю
*/
void getMainMenu(list<DOORFURNITURE> lst, int activeItem = 0, bool submenu = false, int activeSubItem = 0) {
	char key = 0;		

	cout << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  +-----------------------------------------------------+" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  -                                                     -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  -                     База данных                     -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  -              Магазин дверной фурнитуры              -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  -                       м е н ю                       -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  -                                                     -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  +-----------------------------------------------------+" << endl;
	cout << "\t\t\t\t\t\t\t\t" << (activeItem == 0 ? "\x1b[32m>>>\x1b[0m" : "  -") << " открыть базу данных                                 -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  +-----------------------------------------------------+" << endl;
	cout << "\t\t\t\t\t\t\t\t" << (activeItem == 1 ? "\x1b[32m>>>\x1b[0m" : "  -") << " загрузить базу данных из файла                      -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  +-----------------------------------------------------+" << endl;
	cout << "\t\t\t\t\t\t\t\t" << (activeItem == 2 ? "\x1b[32m>>>\x1b[0m" : "  -") << " добавление                                          -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  +-----------------------------------------------------+" << endl;
	cout << "\t\t\t\t\t\t\t\t" << (activeItem == 3 ? "\x1b[32m>>>\x1b[0m" : "  -") << " удаление                                            -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  +-----------------------------------------------------+" << endl;
	cout << "\t\t\t\t\t\t\t\t" << (activeItem == 4 ? "\x1b[32m>>>\x1b[0m" : "  -") << " редактирование                                      -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  +-----------------------------------------------------+" << endl;
	cout << "\t\t\t\t\t\t\t\t" << (activeItem == 5 ? "\x1b[32m>>>\x1b[0m" : "  -") << " сортировка                                          -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  +-----------------------------------------------------+" << endl;
	cout << "\t\t\t\t\t\t\t\t" << (activeItem == 6 ? "\x1b[32m>>>\x1b[0m" : "  -") << " поиск                                               -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  +-----------------------------------------------------+" << endl;
	cout << "\t\t\t\t\t\t\t\t" << (activeItem == 7 ? "\x1b[32m>>>\x1b[0m" : "  -") << " сформировать отчет                                  -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  +-----------------------------------------------------+" << endl;
	cout << "\t\t\t\t\t\t\t\t" << (activeItem == 8 ? "\x1b[32m>>>\x1b[0m" : "  -") << " выход                                               -" << endl;
	cout << "\t\t\t\t\t\t\t\t" << "  +-----------------------------------------------------+" << endl;

	string tmp = "";
	if (!submenu) { // Если подменю не отображается
		while (key != 80 && key != 72 && key != 13)
		{
			key = _getch();

			switch (key) {
			case 80: // При нажатии стрелки вниз
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); // Перемещение курсора в начальную позицию
				if (activeItem == 8) getMainMenu(lst, 0); // Если указатель был на последней строке, то перенести курсор на 1ую строку
				else getMainMenu(lst, ++activeItem); // Иначе перенести курсор на строку ниже
				break;

			case 72: // При нажтиии стрелки вверх (по аналогии с кодом выше)
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
				if (activeItem == 0) getMainMenu(lst, 8);
				else getMainMenu(lst, --activeItem);
				break;
			case 13: // При нажатии кнопку Enter
				switch (activeItem) {
				case 0:
					printList(lst, 0, 1, true);
					break;
				case 1:
					if (loadFromFile(lst)) {
						printWarning("Данные успешно загружены!");
					}
					else {
						printWarning("При чтении данных возникла ошибка!");
					}
					system("cls");
					getMainMenu(lst, 0);
					break;
				case 2:
					addNewElement(lst, true);
					break;
				case 3:
					getMenu3(lst, activeItem, activeSubItem);
					break;
				case 4:
					printListEdit(lst, 0, 1, true);
					break;
				case 5:
					getMenu5(lst, activeItem, activeSubItem);
					break;
				case 6:
					tmp = printDialog("Введите строку для поиска (поиск производится по всем полям): ");
					printSearchList(lst, tmp, 0, 1, true);
					getMainMenu(lst, 0);
					break;
				case 7:
					getMenu7(lst, activeItem, activeSubItem);
					break;
				case 8:
					getMenu8(lst, activeItem, activeSubItem);
					break;
				}
				break;
			}
		}
	}
	else { // Иначе
		switch (activeItem) {
		case 3:
			getMenu3(lst, activeItem, activeSubItem);
			break;
		case 5:
			getMenu5(lst, activeItem, activeSubItem);
			break;
		case 7:
			getMenu7(lst, activeItem, activeSubItem);
			break;
		case 8:
			getMenu8(lst, activeItem, activeSubItem);
			break;
		}
	}
}

/* Подменю Удаление
	activeItem - номер активной строки в главном меню
	activeSubItem - номер активной строки в подменю
*/
void getMenu3(list<DOORFURNITURE> lst, int activeItem, int activeSubItem) {
	char key = 0;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,20 }); // Перемещаем курсор в нужную позицию
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,21 });
	cout << (activeSubItem == 0 ? "\x1b[32m>>>\x1b[0m" : "  -") << " удалить запись                         -" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,22 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,23 });
	cout << (activeSubItem == 1 ? "\x1b[32m>>>\x1b[0m" : "  -") << " удалить все записи                     -" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,24 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,25 });
	cout << (activeSubItem == 2 ? "\x1b[32m>>>\x1b[0m" : "  -") << " назад                                  -" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,26 });
	cout << "  +----------------------------------------+" << endl;

	while (key != 80 && key != 72 && key != 13)
	{
		key = _getch();

		switch (key) { // Все по аналогии с главным меню
		case 80:
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
			if (activeSubItem == 2) getMainMenu(lst, activeItem, true, 0);
			else getMainMenu(lst, activeItem, true, ++activeSubItem);
			break;

		case 72:
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
			if (activeSubItem == 0) getMainMenu(lst, activeItem, true, 2);
			else getMainMenu(lst, activeItem, true, --activeSubItem);
			break;
		case 13:
			cout << activeSubItem << endl;
			switch (activeSubItem) {
			case 0: // Если удалить одну запись, то просто вызываем функцию отображения всего списка, т.к. она включает в себя и возможность удаления записи
				printList(lst, 0, 1, true);
				break;
			case 1: // Если удалить все записи, то очищаем список и выводим сообщение
				lst.clear();
				printWarning("Список товаров был успешно удален!");
				system("cls");
				getMainMenu(lst, 0);
				break;
			case 2:
				system("cls");
				getMainMenu(lst, activeItem, false, 0);
				break;
			}
			break;
		}
	}
}

/* Подменю Сортировка */
void getMenu5(list<DOORFURNITURE> lst, int activeItem, int activeSubItem) {
	char key = 0;

	// Вставила сортировки по своему усмотрению, считаю, что сортировки по всем полям во всех направлениях не нужны (работаю они все равно однотипно)
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,24 }); // Перемещаем курсор в нужную позицию
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,25 });
	wcout << (activeSubItem == 0 ? "\x1b[32m>>>\x1b[0m" : "  -") << L" по наименованию товара (↑)             -" << endl; // Используем wcout и L"" (юникод) для отображения стрелок в консоли

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,26 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,27 });
	wcout << (activeSubItem == 1 ? "\x1b[32m>>>\x1b[0m" : "  -") << L" по количеству (↑)                      -" << endl;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,28 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,29 });
	wcout << (activeSubItem == 2 ? "\x1b[32m>>>\x1b[0m" : "  -") << L" по количеству (↓)                      -" << endl;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,30 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,31 });
	wcout << (activeSubItem == 3 ? "\x1b[32m>>>\x1b[0m" : "  -") << L" по дате поставки (↑)                   -" << endl;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,32 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,33 });
	wcout << (activeSubItem == 4 ? "\x1b[32m>>>\x1b[0m" : "  -") << L" по дате поставки (↓)                   -" << endl;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,34 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,35 });
	wcout << (activeSubItem == 5 ? "\x1b[32m>>>\x1b[0m" : "  -") << L" по магазину (↑)                        -" << endl;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,36 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,37 });
	wcout << (activeSubItem == 6 ? "\x1b[32m>>>\x1b[0m" : "  -") << L" по поставщику (↑)                      -" << endl;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,38 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,39 });
	cout << (activeSubItem == 7 ? "\x1b[32m>>>\x1b[0m" : "  -") << " назад                                  -" << endl;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,40 });
	cout << "  +----------------------------------------+" << endl;

	while (key != 80 && key != 72 && key != 13)
	{
		key = _getch();

		switch (key) { // Все по аналогии с главным меню
		case 80:
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
			if (activeSubItem == 7) getMainMenu(lst, activeItem, true, 0);
			else getMainMenu(lst, activeItem, true, ++activeSubItem);
			break;

		case 72:
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
			if (activeSubItem == 0) getMainMenu(lst, activeItem, true, 7);
			else getMainMenu(lst, activeItem, true, --activeSubItem);
			break;
		case 13:
			cout << activeSubItem << endl;
			switch (activeSubItem) {
			case 0:
				sortList(lst, 1);
				break;
			case 1:
				sortList(lst, 2);
				break;
			case 2:
				sortList(lst, 3);
				break;
			case 3:
				sortList(lst, 4);
				break;
			case 4:
				sortList(lst, 5);
				break;
			case 5:
				sortList(lst, 6);
				break;
			case 6:
				sortList(lst, 7);
				break;
			case 7:
				system("cls");
				getMainMenu(lst, activeItem, false, 0);
				break;
			}
			printList(lst, 0, 1, true);
			break;
		}
	}
}

/* Подменю Отчеты */
void getMenu7(list<DOORFURNITURE> lst, int activeItem, int activeSubItem) {
	char key = 0;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,28 }); // Перемещаем курсор в нужную позицию
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,29 });
	cout << (activeSubItem == 0 ? "\x1b[32m>>>\x1b[0m" : "  -") << " отчет №1                               -" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,30 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,31 });
	cout << (activeSubItem == 1 ? "\x1b[32m>>>\x1b[0m" : "  -") << " отчет №2                               -" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,32 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,33 });
	cout << (activeSubItem == 2 ? "\x1b[32m>>>\x1b[0m" : "  -") << " отчет №3                               -" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,34 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,35 });
	cout << (activeSubItem == 3 ? "\x1b[32m>>>\x1b[0m" : "  -") << " назад                                  -" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,36 });
	cout << "  +----------------------------------------+" << endl;

	list<DOORFURNITURE> newLst;
	DOORFURNITURE df;
	string filename = "";
	const time_t tm = time(nullptr);
	char buf[64], buf2[64];
	double tmp = 0; int tmp2 = 0;

	strftime(buf, size(buf), "%m", localtime(&tm)); // Получаем текущий месяц
	strftime(buf2, size(buf), "%Y", localtime(&tm)); // Получаем текущий год

	while (key != 80 && key != 72 && key != 13)
	{
		key = _getch();

		switch (key) { // Все по аналогии с главным меню
		case 80:
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
			if (activeSubItem == 3) getMainMenu(lst, activeItem, true, 0);
			else getMainMenu(lst, activeItem, true, ++activeSubItem);
			break;

		case 72:
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
			if (activeSubItem == 0) getMainMenu(lst, activeItem, true, 3);
			else getMainMenu(lst, activeItem, true, --activeSubItem);
			break;
		case 13:
			switch (activeSubItem) {
			case 0: // Получить список товаров, поступивших за текущий месяц
				for (auto element : lst) {
					if (element.date.month == atoi(buf) && element.date.year == atoi(buf2)) newLst.push_front(element);
				}

				if (saveToFileReport(newLst, "Товары, поступившие за текущий месяц", filename)) 
					system(("notepad " + filename).c_str());
				break;
			case 1: // Получить список товаров, цена которых выше средней цены по всем товарам
				// Рассчитаем среднюю стоимость
				for (auto element : lst) {
					tmp += element.price;
				}
				tmp = tmp / lst.size();

				for (auto element : lst) {
					if (element.price > tmp) newLst.push_front(element);
				}

				if (saveToFileReport(newLst, "Товары, цена которых выше средней цены всех товаров", filename))
					system(("notepad " + filename).c_str());
				break;
			case 2: // Получить список товаров и их суммарную стоимость за текущий год
				for (auto element : lst) { // Отбираем товары за текущий год
					if (element.date.year == atoi(buf2)) newLst.push_front(element);
				}

				// Теперь считаем общую стоимость
				for (auto element : newLst) { // Отбираем товары за текущий год
					tmp += element.price * element.count;
					tmp2 += element.count;
				}

				df = { "ИТОГО: ", "", "", "", "", tmp, tmp2, {0,0,0}, "", "" };
				newLst.push_back(df);

				if (saveToFileReport(newLst, "Товары, поступившие за текущий год с указанием общей стоимости", filename))
					system(("notepad " + filename).c_str());
				break;
			case 3:
				break;
			}
			system("cls");
			getMainMenu(lst, activeItem, false, 0);
			break;
		}
	}
}

/* Подменю Выход */
void getMenu8(list<DOORFURNITURE> lst, int activeItem, int activeSubItem) {
	char key = 0;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,30 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,31 });
	cout << (activeSubItem == 0 ? "\x1b[32m>>>\x1b[0m" : "  -") << " сохранить и выйти                      -" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,32 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,33 });
	cout << (activeSubItem == 1 ? "\x1b[32m>>>\x1b[0m" : "  -") << " выйти                                  -" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,34 });
	cout << "  +----------------------------------------+" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,35 });
	cout << (activeSubItem == 2 ? "\x1b[32m>>>\x1b[0m" : "  -") << " назад                                  -" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 122,36 });
	cout << "  +----------------------------------------+" << endl;

	while (key != 80 && key != 72 && key != 13)
	{
		key = _getch();

		switch (key) {
		case 80:
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
			if (activeSubItem == 2) getMainMenu(lst, activeItem, true, 0);
			else getMainMenu(lst, activeItem, true, ++activeSubItem);
			break;

		case 72:
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
			if (activeSubItem == 0) getMainMenu(lst, activeItem, true, 2);
			else getMainMenu(lst, activeItem, true, --activeSubItem);
			break;
		case 13:
			cout << activeSubItem << endl;
			switch (activeSubItem) {
			case 0:
				if (saveToFile(lst))
					printWarning("Данные успешно сохранены!");
				else
					printWarning("При записи данных возникла ошибка!");
				break;
			case 1:
				exit(0);
				break;
			case 2:
				system("cls");
				getMainMenu(lst, activeItem, false, 0);
				break;
			}
			break;
		}
	}
}

/* Вывод списка товаров */
void printList(list<DOORFURNITURE> lst, int activeItem = 0, int site = 1, bool clear = false) { 
	if (lst.empty()) { // Если список пуст
		printWarning("Список товаров пуст!"); // Выводим предукпреждение
		system("cls");
		getMainMenu(lst, 0);
	}
	else { // Иначе
		if (clear) { // Если нужно очистить экран (передается как параметр функции)
			system("cls"); // Очищаем его
			system("MODE CON: COLS=253 LINES=42"); // Меняем размер окна
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { 250, 9999 }); // Полосы прокрутки
		}

		string line(180, '-'), line2(155, ' '), line3(50, '-'), line4(50, ' '); // Задаем несколько статичных строк из одинаковых символов для отображения интерфейса

		cout << "   \x1b[7m +" << line << "+ \x1b[0m   " << endl; // Задание цвета https://habr.com/ru/post/94647/
		cout  << "   \x1b[7m " << setw(6) << left << "| №" << setw(66) << left << " | Наименование товара" << setw(19) << left << " | Количество (шт)" << setw(20) << left << " | Дата поставки" << setw(35) << left << " | Магазин" << 
			setw(35) << left << " | Поставщик" << "| \x1b[0m" << endl;
		cout << "   \x1b[7m +" << line << "+ \x1b[0m   " << endl;

		// Выводим 18 записей списка в зависимости от страницы
		int i = 0;
		int index = 18 * (site - 1);
		for (DOORFURNITURE el : lst) {
			if (i >= index && i < index + 18) {
				cout << "    +" << line << "+    " << endl;
				printElement(i + 1, el, activeItem == i%18);
			}
			i++;
		}
		cout << "    +" << line << "+    " << endl;

		cout << "    <<< предыдущая" << line2 << "следующая >>>    " << endl;


		//-------------------------------------------------------------
		//-------------------------------------------------------------
		// Выводим подсказку для удаления (справа в нижнем углу)
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 40 });
		cout << "\x1b[32m" << "    Backspace - удалить запись. Отменить невозможно! " << "\x1b[0m" << endl;

		//-------------------------------------------------------------
		//-------------------------------------------------------------
		// Определяем номер элемента выделенной на текущей момент записи в исходном списке, выводим полные данные по этому элементу в правой части экрана
		int activeItemInList = (18 * site) - (18 - activeItem);
		
		// Шапка
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 0 });
		cout << "   \x1b[7m +" << line3 << "+ \x1b[0m   " << endl;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 1 });
		cout << "   \x1b[7m |" << "                 Доп. информация                  " << "| \x1b[0m   " << endl;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 2 });
		cout << "   \x1b[7m +" << line3 << "+ \x1b[0m   " << endl;

		// Предварительно стираем предыдущий текст, который был в правой части, т.к. мы не очищаем весь экран, а перерисовываем поверх (чтобы было меньше раздражающих миганий, очистка консоли очень заметна)
		short pos = 4;
		i = 0;
		for (int i = 0; i < 20; i++) {
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, ++pos }); // Перемещаем курсор в нужную позицию
			cout << "    " + line4 << endl;
		}

		// Подробные данные об элементе
		i = 0;
		pos = 8;
		for (DOORFURNITURE el : lst) {
			if (i == activeItemInList) {
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 4 });
				cout << "\x1b[32m" << "    Тип товара: " << "\x1b[0m" << el.type << endl;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 5 });
				cout << "\x1b[32m" << "    Страна-производитель: " << "\x1b[0m" << el.country << endl;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 6 });
				cout << "\x1b[32m" << "    Материал: " << "\x1b[0m" << el.material << endl;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 7 });
				cout << "\x1b[32m" << "    Рекомендуемая стоимость: " << "\x1b[0m" << el.price << " р." << endl;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 8 });
				cout << "\x1b[32m" << "    Описание: " << "\x1b[0m" << endl;

				// Разделяем описание на подстроки на случай, если текст большой, и выводим каждую подстроку отдельно
				int descriptionLine = el.description.size()/ 50 + 1;
				for (int i = 0; i < descriptionLine; i++) {
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, ++pos }); // Перемещаем курсор в нужную позицию
					cout << "    " + el.description.substr(i * 50, 50) << endl;
				}
			}
			i++;
		}

		// Обработка нажатий клавиш на клавиатуре
		char key = 0;
		list<DOORFURNITURE>::iterator itr; // Объявляем итератор
		while (key != 80 && key != 72 && key != 27 && key != 75 && key != 77 && key != 8)
		{
			key = _getch();

			switch (key) {
			case 80: // При нажатии стрелки вниз
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); // Перемещение курсора в начальную позицию
				if ((lst.size()/site > 18 && activeItem == 17) || (lst.size() / site <= 18 && activeItem == lst.size()%18-1)) 
					printList(lst, 0, site); // Если указатель был на последней строке, то перенести курсор на 1ую строку
				else 
					printList(lst, ++activeItem, site); // Иначе перенести курсор на строку ниже
				break;

			case 72: // При нажтиии стрелки вверх (по аналогии с кодом выше)
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
				if (activeItem == 0) printList(lst, lst.size() / site > 18 ? 17 : lst.size() % 18 - 1, site);
				else printList(lst, --activeItem, site);
				break;
			case 75: // При нажатии стрелки влево
				if (site > 1) {
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); // Перемещение курсора в начальную позицию
					printList(lst, 0, --site, true);
				}
				else printList(lst, activeItem, site, true);
				break;
			case 77: // При нажтиии стрелки вправо (по аналогии с кодом выше)
				if (site < lst.size() / 18 + 1) {
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
					printList(lst, 0, ++site, true);
				}
				else printList(lst, activeItem, site, true);
				break;
			case 8: // При нажтиии DEL
				// Ранее в коде мы уже определили позицию выделенного элемента в списке, просто удаляем его и выводим сообщение
				itr = lst.begin(); // Ссылаемся на первый элемент списка
				advance(itr, activeItemInList); // Перемещаем итератор на нужную позицию
				lst.erase(itr); // И удаляем элемент

				printWarning("Элемент был успешно удален!");
				printList(lst, 0, site, true);
				break;
			case 27: // При нажатии кнопку Esc
				system("MODE CON: COLS=190 LINES=42");
				system("cls");
				getMainMenu(lst, 0);
				break;
			}

		}
	}
}

/* Вывод элемента списка товаров */
void printElement(int num, DOORFURNITURE element, bool active = false) {
	cout << (active ? "\x1b[32m >> " : "    ") <<
		setw(6) << left << "| " + to_string(num) << setw(66) << left << " | " + element.name << setw(19) << left << " | " + to_string(element.count) <<
		setw(20) << left << " | " + DateToString(element.date) << setw(35) << left << " | " + element.store <<
		setw(35) << left << " | " + element.provider << "| \x1b[0m" << "\x1b[0m" << endl;
}

/* Вывод предупреждения */
void printWarning(string msg) {
	int messLine = msg.size() / 69 + 1;
	string line(71, '-');
	short pos = 18;
	char key = 0;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56,17 }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;41m +" << line << "+ \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56,18 }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;41m |" << "                                                                       " << "| \x1b[0m" << endl;

	for (int i = 0; i < messLine; i++) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
		cout << "\x1b[0;37;41m | " << setw(69) << left << msg.substr(i*69, 69) << " | \x1b[0m" << endl;
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;41m |" << "                                                                       " << "| \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;41m |" << "                                                         \x1b[7m +--------+ \x1b[0;37;41m  " << "| \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;41m |" << "                                                         \x1b[7m |   ОК   | \x1b[0;37;41m  " << "| \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;41m |" << "                                                         \x1b[7m +--------+ \x1b[0;37;41m  " << "| \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;41m |" << "                                                                       " << "| \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;41m +" << line << "+ \x1b[0m" << endl;

	while (key != 13)
	{
		key = _getch();
	}
}

/* Удаление предупреждения с консоли */
void clearWarning() {
	string line(100, ' ');
	short pos = 17;

	for (int i = 0; i < 10; i++) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, pos++ });
		cout << line;
	}
}

/* Добавление нового элемента */
void addNewElement(list<DOORFURNITURE> lst, bool clear = false) {
	if (clear) { // Если нужно очистить экран (передается как параметр функции)
		system("cls"); // Очищаем его
	}

	char key = 0;
	string tempValue;
	DOORFURNITURE newEl;

	string line(180, '-'), line2(80, ' '), line3(115, ' '), line4(150, ' ');

	cout << "   \x1b[7m +" << line << "+ \x1b[0m   " << endl; 
	cout << "   \x1b[7m " << "|" << line2 << "Добавление элемента" << line2 << " | \x1b[0m" << endl;
	cout << "   \x1b[7m +" << line << "+ \x1b[0m   " << endl;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 4 });
	cout << "\x1b[32m" << "    Наименование товара: " << "\x1b[0m" << endl;
	cout << "\x1b[32m" << "    Тип товара: " << "\x1b[0m" << endl;
	cout << "\x1b[32m" << "    Страна-производитель: " << "\x1b[0m" << endl;
	cout << "\x1b[32m" << "    Материал: " << "\x1b[0m" << endl;
	cout << "\x1b[32m" << "    Описание товара: " << "\x1b[0m" << endl << endl << endl;
	cout << "\x1b[32m" << "    Рекомендуемая цена за ед. товара (р.): " << "\x1b[0m" << endl; // Валюту потом поменяешь, кали захочешь)
	cout << "\x1b[32m" << "    Кол-во поставляемого товара (шт.): " << "\x1b[0m" << endl;
	cout << "\x1b[32m" << "    Дата поставки: " << "\x1b[0m" << endl;
	cout << "\x1b[32m" << "    Наименование магазина: " << "\x1b[0m" << endl;
	cout << "\x1b[32m" << "    Поставщик: " << "\x1b[0m" << endl;

	while (true) {
		ShowConsoleCursor(true); // Включаем отображение курсора
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 4 });
		getline(cin, tempValue);
		if (!isEmpty(tempValue)) {
			newEl.name = tempValue;
			break;
		}
		else {
			ShowConsoleCursor(false); // Включаем отображение курсора
			printWarning("Данное поле не может быть пустым!"); // Выводим сообщение
			clearWarning(); // Удаляет отображение предупреждения
		}
	}

	while (true) {
		ShowConsoleCursor(true); // Включаем отображение курсора
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 5 });
		getline(cin, tempValue);
		if (!isEmpty(tempValue)) {
			newEl.type = tempValue;
			break;
		}
		else {
			ShowConsoleCursor(false); // Включаем отображение курсора
			printWarning("Данное поле не может быть пустым!"); // Выводим сообщение
			clearWarning(); // Удаляет отображение предупреждения
		}
	}

	while (true) {
		ShowConsoleCursor(true); // Включаем отображение курсора
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 6 });
		getline(cin, tempValue);
		if (!isEmpty(tempValue) && onlyLetters(tempValue)) {
			newEl.country = tempValue;
			break;
		}
		else {
			ShowConsoleCursor(false); // Включаем отображение курсора
			printWarning("Данное поле не может быть пустым! Поле может содержать только буквы латиноского алфавита"); // Выводим сообщение
			clearWarning(); // Удаляет отображение предупреждения
			// Очистка уже написанного текста в данном поле
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 6 });
			cout << line3;
		}
	}

	while (true) {
		ShowConsoleCursor(true); // Включаем отображение курсора
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 7 });
		getline(cin, tempValue);
		newEl.material = tempValue;
		break;
	}

	while (true) {
		ShowConsoleCursor(true); // Включаем отображение курсора
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 8 });
		getline(cin, tempValue);
		newEl.description = tempValue;
		break;
	}

	while (true) {
		ShowConsoleCursor(true); // Включаем отображение курсора
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 11 });
		getline(cin, tempValue);
		if (!isEmpty(tempValue) && atof(tempValue.c_str())) {
			newEl.price = atof(tempValue.c_str());
			break;
		}
		else {
			ShowConsoleCursor(false); // Включаем отображение курсора
			printWarning("Данное поле не может быть пустым! Поле может содержать значения типа double!"); // Выводим сообщение
			clearWarning(); // Удаляет отображение предупреждения
			// Очистка уже написанного текста в данном поле
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 11 });
			cout << line3;
		}
	}

	while (true) {
		ShowConsoleCursor(true); // Включаем отображение курсора
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 12 });
		getline(cin, tempValue);
		if (!isEmpty(tempValue) && atoi(tempValue.c_str())) {
			newEl.count = atoi(tempValue.c_str());
			break;
		}
		else {
			ShowConsoleCursor(false); // Включаем отображение курсора
			printWarning("Данное поле не может быть пустым! Поле может содержать значения типа int!"); // Выводим сообщение
			clearWarning(); // Удаляет отображение предупреждения
			// Очистка уже написанного текста в данном поле
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 12 });
			cout << line3;
		}
	}

	while (true) {
		ShowConsoleCursor(true); // Включаем отображение курсора
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 13 });
		getline(cin, tempValue);
		if (!isEmpty(tempValue) && isDate(tempValue)) {
			newEl.date = { atoi(tempValue.substr(0,2).c_str()), atoi(tempValue.substr(3,2).c_str()), atoi(tempValue.substr(6,4).c_str()) };
			break;
		}
		else {
			ShowConsoleCursor(false); // Включаем отображение курсора
			printWarning("Данное поле не может быть пустым! Дата должна быть в формате дд.мм.гггг!"); // Выводим сообщение
			clearWarning(); // Удаляет отображение предупреждения
			// Очистка уже написанного текста в данном поле
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 13 });
			cout << line3;
		}
	}

	while (true) {
		ShowConsoleCursor(true); // Включаем отображение курсора
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 14 });
		getline(cin, tempValue);
		if (!isEmpty(tempValue)) {
			newEl.store = tempValue;
			break;
		}
		else {
			ShowConsoleCursor(false); // Включаем отображение курсора
			printWarning("Данное поле не может быть пустым!"); // Выводим сообщение
			clearWarning(); // Удаляет отображение предупреждения
		}
	}

	while (true) {
		ShowConsoleCursor(true); // Включаем отображение курсора
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 15 });
		getline(cin, tempValue);
		if (!isEmpty(tempValue)) {
			newEl.provider = tempValue;
			break;
		}
		else {
			ShowConsoleCursor(false); // Включаем отображение курсора
			printWarning("Данное поле не может быть пустым!"); // Выводим сообщение
			clearWarning(); // Удаляет отображение предупреждения
		}
	}

	ShowConsoleCursor(false);
	lst.push_front(newEl);
	printWarning("Запись успешно добавлена!");
	system("cls");
	getMainMenu(lst, 0);
}

/* Проверка строки на пустоту */
bool isEmpty(string str) {
	if (str.size() == 0) return true;
	else return false;
}

/* Проверка строки на содержание в ней только кирилицы */
bool onlyLetters(string str) {
	for (char el : str) {
		if (el >= -64 && el <= -1 || el == ' ') {}
		else return false;
	}

	return true;
}

/* Проверка даты */
bool isDate(string str) { // На високосный год проверки в данной функции нет, т.е. в феврале всегда допускается 29 дней
	if (str.size() != 10) return false;
	if (str[2] != '.' || str[5] != '.') return false;
	else if (atoi(str.substr(0, 2).c_str()) && atoi(str.substr(3, 2).c_str()) && atoi(str.substr(6, 4).c_str())) {
		int day = atoi(str.substr(0, 2).c_str()),
			month = atoi(str.substr(3, 2).c_str()),
			year = atoi(str.substr(6, 4).c_str());

		if (year < 2000) return false;
		if (month < 1 || month > 12) return false;
		if (day < 1 || (day > 29 && month == 2) ||
			(day > 30 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) ||
			(day > 31 && (month == 4 || month == 6 || month == 9 || month == 11))) return false;
	}
	else return true;
}

/* Вывод списка для редактирования */
void printListEdit(list<DOORFURNITURE> lst, int activeItem = 0, int site = 1, bool clear = false) {
	if (lst.empty()) { // Если список пуст
		printWarning("Список товаров пуст!"); // Выводим предукпреждение
		system("cls");
		getMainMenu(lst, 0);
	}
	else { // Иначе
		if (clear) { // Если нужно очистить экран (передается как параметр функции)
			system("cls"); // Очищаем его
			system("MODE CON: COLS=253 LINES=63"); // Меняем размер окна
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { 250, 9999 }); // Полосы прокрутки
		}

		string line(180, '-'), line2(155, ' '), line3(50, '-'), line4(50, ' '); // Задаем несколько статичных строк из одинаковых символов для отображения интерфейса

		cout << "   \x1b[7m +" << line << "+ \x1b[0m   " << endl; // Задание цвета https://habr.com/ru/post/94647/
		cout << "   \x1b[7m " << setw(6) << left << "| №" << setw(66) << left << " | Наименование товара" << setw(19) << left << " | Количество (шт)" << setw(20) << left << " | Дата поставки" << setw(35) << left << " | Магазин" <<
			setw(35) << left << " | Поставщик" << "| \x1b[0m" << endl;
		cout << "   \x1b[7m +" << line << "+ \x1b[0m   " << endl;

		// Выводим 18 записей списка в зависимости от страницы
		int i = 0;
		int index = 18 * (site - 1);
		for (DOORFURNITURE el : lst) {
			if (i >= index && i < index + 18) {
				cout << "    +" << line << "+    " << endl;
				printElement(i + 1, el, activeItem == i % 18);
			}
			i++;
		}
		cout << "    +" << line << "+    " << endl;

		cout << "    <<< предыдущая" << line2 << "следующая >>>    " << endl;

		//-------------------------------------------------------------
		//-------------------------------------------------------------
		// Выводим подсказку  (справа в нижнем углу)
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 61 });
		cout << "\x1b[32m" << "    Enter - выбрать для редактирования " << "\x1b[0m" << endl;

		//-------------------------------------------------------------
		//-------------------------------------------------------------
		// Определяем номер элемента выделенной на текущей момент записи в исходном списке, выводим полные данные по этому элементу в правой части экрана
		int activeItemInList = (18 * site) - (18 - activeItem);

		// Шапка
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 0 });
		cout << "   \x1b[7m +" << line3 << "+ \x1b[0m   " << endl;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 1 });
		cout << "   \x1b[7m |" << "                 Доп. информация                  " << "| \x1b[0m   " << endl;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 2 });
		cout << "   \x1b[7m +" << line3 << "+ \x1b[0m   " << endl;

		// Предварительно стираем предыдущий текст, который был в правой части, т.к. мы не очищаем весь экран, а перерисовываем поверх (чтобы было меньше раздражающих миганий, очистка консоли очень заметна)
		short pos = 4;
		i = 0;
		for (int i = 0; i < 20; i++) {
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, ++pos }); // Перемещаем курсор в нужную позицию
			cout << "    " + line4 << endl;
		}

		// Подробные данные об элементе
		i = 0;
		pos = 8;
		for (DOORFURNITURE el : lst) {
			if (i == activeItemInList) {
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 4 });
				cout << "\x1b[32m" << "    Тип товара: " << "\x1b[0m" << el.type << endl;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 5 });
				cout << "\x1b[32m" << "    Страна-производитель: " << "\x1b[0m" << el.country << endl;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 6 });
				cout << "\x1b[32m" << "    Материал: " << "\x1b[0m" << el.material << endl;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 7 });
				cout << "\x1b[32m" << "    Рекомендуемая стоимость: " << "\x1b[0m" << el.price << " р." << endl;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 8 });
				cout << "\x1b[32m" << "    Описание: " << "\x1b[0m" << endl;

				// Разделяем описание на подстроки на случай, если текст большой, и выводим каждую подстроку отдельно
				int descriptionLine = el.description.size() / 50 + 1;
				for (int i = 0; i < descriptionLine; i++) {
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, ++pos }); // Перемещаем курсор в нужную позицию
					cout << "    " + el.description.substr(i * 50, 50) << endl;
				}
			}
			i++;
		}

		// Обработка нажатий клавиш на клавиатуре
		char key = 0;
		string tempValue;
		DOORFURNITURE newEl;
		string line5(180, '-'), line6(80, ' '), line7(115, ' '), line8(150, ' ');

		while (key != 80 && key != 72 && key != 27 && key != 75 && key != 77 && key != 13)
		{
			key = _getch();

			switch (key) {
			case 80: // При нажатии стрелки вниз
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); // Перемещение курсора в начальную позицию
				if ((lst.size() / site > 18 && activeItem == 17) || (lst.size() / site <= 18 && activeItem == lst.size() % 18 - 1))
					printListEdit(lst, 0, site); // Если указатель был на последней строке, то перенести курсор на 1ую строку
				else
					printListEdit(lst, ++activeItem, site); // Иначе перенести курсор на строку ниже
				break;

			case 72: // При нажтиии стрелки вверх (по аналогии с кодом выше)
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
				if (activeItem == 0) printListEdit(lst, lst.size() / site > 18 ? 17 : lst.size() % 18 - 1, site);
				else printListEdit(lst, --activeItem, site);
				break;
			case 75: // При нажатии стрелки влево
				if (site > 1) {
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); // Перемещение курсора в начальную позицию
					printListEdit(lst, 0, --site, true);
				}
				else printListEdit(lst, activeItem, site, true);
				break;
			case 77: // При нажтиии стрелки вправо (по аналогии с кодом выше)
				if (site < lst.size() / 18 + 1) {
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
					printListEdit(lst, 0, ++site, true);
				}
				else printListEdit(lst, activeItem, site, true);
				break;
			case 13: // При нажтиии enter
					 
				/*// Ранее в коде мы уже определили позицию выделенного элемента в списке, просто удаляем его и выводим сообщение
				itr = lst.begin(); // Ссылаемся на первый элемент списка
				advance(itr, activeItemInList); // Перемещаем итератор на нужную позицию
				lst.erase(itr); // И удаляем элемент*/

				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 45 });

				cout << "   \x1b[7m +" << line5 << "+ \x1b[0m   " << endl;
				cout << "   \x1b[7m " << "|" << line6 << "Изменение элемента " << line6 << " | \x1b[0m" << endl;
				cout << "   \x1b[7m +" << line5 << "+ \x1b[0m   " << endl;

				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 49 });
				cout << "\x1b[32m" << "    Наименование товара: " << "\x1b[0m" << endl;
				cout << "\x1b[32m" << "    Тип товара: " << "\x1b[0m" << endl;
				cout << "\x1b[32m" << "    Страна-производитель: " << "\x1b[0m" << endl;
				cout << "\x1b[32m" << "    Материал: " << "\x1b[0m" << endl;
				cout << "\x1b[32m" << "    Описание товара: " << "\x1b[0m" << endl << endl << endl;
				cout << "\x1b[32m" << "    Рекомендуемая цена за ед. товара (р.): " << "\x1b[0m" << endl; // Валюту потом поменяешь, кали захочешь)
				cout << "\x1b[32m" << "    Кол-во поставляемого товара (шт.): " << "\x1b[0m" << endl;
				cout << "\x1b[32m" << "    Дата поставки: " << "\x1b[0m" << endl;
				cout << "\x1b[32m" << "    Наименование магазина: " << "\x1b[0m" << endl;
				cout << "\x1b[32m" << "    Поставщик: " << "\x1b[0m" << endl;

				while (true) {
					ShowConsoleCursor(true); // Включаем отображение курсора
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 49 });
					getline(cin, tempValue);
					if (!isEmpty(tempValue)) {
						newEl.name = tempValue;
						break;
					}
					else {
						ShowConsoleCursor(false); // Включаем отображение курсора
						printWarning("Данное поле не может быть пустым!"); // Выводим сообщение
						clearWarning(); // Удаляет отображение предупреждения
					}
				}

				while (true) {
					ShowConsoleCursor(true); // Включаем отображение курсора
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 50 });
					getline(cin, tempValue);
					if (!isEmpty(tempValue)) {
						newEl.type = tempValue;
						break;
					}
					else {
						ShowConsoleCursor(false); // Включаем отображение курсора
						printWarning("Данное поле не может быть пустым!"); // Выводим сообщение
						clearWarning(); // Удаляет отображение предупреждения
					}
				}

				while (true) {
					ShowConsoleCursor(true); // Включаем отображение курсора
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 51 });
					getline(cin, tempValue);
					if (!isEmpty(tempValue) && onlyLetters(tempValue)) {
						newEl.country = tempValue;
						break;
					}
					else {
						ShowConsoleCursor(false); // Включаем отображение курсора
						printWarning("Данное поле не может быть пустым! Поле может содержать только буквы латиноского алфавита"); // Выводим сообщение
						clearWarning(); // Удаляет отображение предупреждения
						// Очистка уже написанного текста в данном поле
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 51 });
						cout << line7;
					}
				}

				while (true) {
					ShowConsoleCursor(true); // Включаем отображение курсора
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 52 });
					getline(cin, tempValue);
					newEl.material = tempValue;
					break;
				}

				while (true) {
					ShowConsoleCursor(true); // Включаем отображение курсора
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 53 });
					getline(cin, tempValue);
					newEl.description = tempValue;
					break;
				}

				while (true) {
					ShowConsoleCursor(true); // Включаем отображение курсора
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 56 });
					getline(cin, tempValue);
					if (!isEmpty(tempValue) && atof(tempValue.c_str())) {
						newEl.price = atof(tempValue.c_str());
						break;
					}
					else {
						ShowConsoleCursor(false); // Включаем отображение курсора
						printWarning("Данное поле не может быть пустым! Поле может содержать значения типа double!"); // Выводим сообщение
						clearWarning(); // Удаляет отображение предупреждения
						// Очистка уже написанного текста в данном поле
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 56 });
						cout << line7;
					}
				}

				while (true) {
					ShowConsoleCursor(true); // Включаем отображение курсора
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 57 });
					getline(cin, tempValue);
					if (!isEmpty(tempValue) && atoi(tempValue.c_str())) {
						newEl.count = atoi(tempValue.c_str());
						break;
					}
					else {
						ShowConsoleCursor(false); // Включаем отображение курсора
						printWarning("Данное поле не может быть пустым! Поле может содержать значения типа int!"); // Выводим сообщение
						clearWarning(); // Удаляет отображение предупреждения
						// Очистка уже написанного текста в данном поле
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 57 });
						cout << line7;
					}
				}

				while (true) {
					ShowConsoleCursor(true); // Включаем отображение курсора
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 58 });
					getline(cin, tempValue);
					if (!isEmpty(tempValue) && isDate(tempValue)) {
						newEl.date = { atoi(tempValue.substr(0,2).c_str()), atoi(tempValue.substr(3,2).c_str()), atoi(tempValue.substr(6,4).c_str()) };
						break;
					}
					else {
						ShowConsoleCursor(false); // Включаем отображение курсора
						printWarning("Данное поле не может быть пустым! Дата должна быть в формате дд.мм.гггг!"); // Выводим сообщение
						clearWarning(); // Удаляет отображение предупреждения
						// Очистка уже написанного текста в данном поле
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 58 });
						cout << line7;
					}
				}

				while (true) {
					ShowConsoleCursor(true); // Включаем отображение курсора
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 59 });
					getline(cin, tempValue);
					if (!isEmpty(tempValue)) {
						newEl.store = tempValue;
						break;
					}
					else {
						ShowConsoleCursor(false); // Включаем отображение курсора
						printWarning("Данное поле не может быть пустым!"); // Выводим сообщение
						clearWarning(); // Удаляет отображение предупреждения
					}
				}

				while (true) {
					ShowConsoleCursor(true); // Включаем отображение курсора
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 60 });
					getline(cin, tempValue);
					if (!isEmpty(tempValue)) {
						newEl.provider = tempValue;
						break;
					}
					else {
						ShowConsoleCursor(false); // Включаем отображение курсора
						printWarning("Данное поле не может быть пустым!"); // Выводим сообщение
						clearWarning(); // Удаляет отображение предупреждения
					}
				}

				ShowConsoleCursor(false);

				i = 0;
				for (DOORFURNITURE& el : lst) {
					if (i == activeItemInList) {
						el = newEl;
						break;
					}						
					i++;
				}

				printWarning("Элемент был успешно изменен!");
				printListEdit(lst, activeItem, site, true);
				break;
			case 27: // При нажатии кнопку Esc
				system("MODE CON: COLS=190 LINES=42");
				system("cls");
				getMainMenu(lst, 0);
				break;
			}

		}
	}
}

/* Сохранение в файл */
bool saveToFile(list<DOORFURNITURE> lst) {
	string filename = printDialog("Введите имя файла:");
	ofstream out;
	out.open(filename); // окрываем файл для записи
	if (out.is_open())
	{
		out << lst.size() << endl;
		for (auto el : lst) {
			out << el.name << endl << el.type << endl << el.country << endl << el.material << endl << el.description << endl <<
				el.price << endl << el.count << endl << el.date.day << endl << el.date.month << endl << el.date.year << endl << el.store << endl << el.provider << endl;
		}
	}
	else return false;

	out.close();
	return true;
}

/* Загрузка из файла */
bool loadFromFile(list<DOORFURNITURE>& lst) {
	lst.clear();
	string filename = printDialog("Введите имя файла:");

	ifstream in(filename); // окрываем файл для чтения
	try {
		if (in.is_open())
		{
			string tmp;
			int count;

			getline(in, tmp);
			count = atoi(tmp.c_str());

			for (int i = 0; i < count; i++) {
				DOORFURNITURE newEl;
				getline(in, tmp);
				newEl.name = tmp;

				getline(in, tmp);
				newEl.type = tmp;

				getline(in, tmp);
				newEl.country = tmp;

				getline(in, tmp);
				newEl.material = tmp;

				getline(in, tmp);
				newEl.description = tmp;

				getline(in, tmp);
				newEl.price = atof(tmp.c_str());

				getline(in, tmp);
				newEl.count = atoi(tmp.c_str());

				getline(in, tmp);
				newEl.date.day = atoi(tmp.c_str());

				getline(in, tmp);
				newEl.date.month = atoi(tmp.c_str());

				getline(in, tmp);
				newEl.date.year = atoi(tmp.c_str());

				getline(in, tmp);
				newEl.store = tmp;

				getline(in, tmp);
				newEl.provider = tmp;

				lst.push_front(newEl);
			}
		}
		else return false;
		in.close();
	}
	catch (int ex) {
		return false;
	}

	return true;
}

/* Сортировки */
void sortList(list<DOORFURNITURE>& lst, int type) {
	switch (type) {
	case 1: // по наименованию товара (↑) 
		lst.sort(listPred1);
		break;
	case 2: // по количеству (↑) 
		lst.sort(listPred2);
		break;
	case 3: // по количеству (↓) 
		lst.sort(listPred3);
		break;
	case 4: // по дате поставки (↑)
		lst.sort(listPred4);
		break;
	case 5: // по дате поставки (↓)  
		lst.sort(listPred5);
		break;
	case 6: // по магазину (↑)  
		lst.sort(listPred6);
		break;
	case 7: // по поставщику (↑)
		lst.sort(listPred7);
		break;
	}
}

// Предикаты для сортировок
bool listPred1(DOORFURNITURE n1, DOORFURNITURE n2) {
	return n1.name < n2.name;
}

bool listPred2(DOORFURNITURE n1, DOORFURNITURE n2) {
	return n1.count < n2.count;
}

bool listPred3(DOORFURNITURE n1, DOORFURNITURE n2) {
	return n1.count > n2.count;
}

bool listPred4(DOORFURNITURE n1, DOORFURNITURE n2) {
	if (n1.date.year < n2.date.year) return true;
	else if (n1.date.year > n2.date.year) return false;
	else if (n1.date.month < n2.date.month) return true;
	else if (n1.date.month > n2.date.month) return false;
	else if (n1.date.day < n2.date.day) return true;
	else return false;
}

bool listPred5(DOORFURNITURE n1, DOORFURNITURE n2) {
	if (n1.date.year > n2.date.year) return true;
	else if (n1.date.year < n2.date.year) return false;
	else if (n1.date.month > n2.date.month) return true;
	else if (n1.date.month < n2.date.month) return false;
	else if (n1.date.day > n2.date.day) return true;
	else return false;
}

bool listPred6(DOORFURNITURE n1, DOORFURNITURE n2) {
	return n1.store < n2.store;
}

bool listPred7(DOORFURNITURE n1, DOORFURNITURE n2) {
	return n1.provider < n2.provider;
}

/* Диалоговое окно для запроса параметров */
string printDialog(string msg) {
	int messLine = msg.size() / 69 + 1;
	string line(71, '-');
	short pos = 18;
	char key = 0;
	string res;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56,17 }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;40m +" << line << "+ \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56,18 }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;40m |" << "                                                                       " << "| \x1b[0m" << endl;

	for (int i = 0; i < messLine; i++) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
		cout << "\x1b[0;37;40m | " << setw(69) << left << msg.substr(i * 69, 69) << " | \x1b[0m" << endl;
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;40m |" << "                                                                       " << "| \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;40m |" << "                                                                       " << "| \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;40m |" << "                                                                       " << "| \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;40m |" << "                                                         \x1b[7m +--------+ \x1b[0;37;40m  " << "| \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;40m |" << "                                                         \x1b[7m |   ОК   | \x1b[0;37;40m  " << "| \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;40m |" << "                                                         \x1b[7m +--------+ \x1b[0;37;40m  " << "| \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;40m |" << "                                                                       " << "| \x1b[0m" << endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 56, ++pos }); // Перемещаем курсор в нужную позицию
	cout << "\x1b[0;37;40m +" << line << "+ \x1b[0m" << endl;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 61, pos-6 });
	ShowConsoleCursor(true);
	getline(cin, res);
	ShowConsoleCursor(false);
	return res;
}

/* Сохранение отчета в файл */
bool saveToFileReport(list<DOORFURNITURE> lst, string reportName, string &filename) {
	filename = printDialog("Введите имя файла, в котором будет сохранен отчет:");
	ofstream out;
	out.open(filename); // окрываем файл для записи
	if (out.is_open())
	{
		string line(301, '-');

		out << reportName << endl << endl;

		out << "    +" << line << "+    " << endl;
		out << "    " << setw(6) << left << "| №" << setw(66) << left << " | Наименование товара"  << setw(20) << left << " | Дата поставки" << setw(35) << left << " | Магазин" <<
			setw(35) << left << " | Поставщик" << 
			setw(35) << left << " | Тип товара" << 
			setw(35) << left << " | Страна-изготовитель" << 
			setw(35) << left << " | Количество" << 
			setw(35) << left << " | Цена" << "| " << endl;
		out << "    +" << line << "+    " << endl;

		int num = 1;
		for (auto element : lst) {
			out << "    +" << line << "+    " << endl;
			out  << "    " << setw(6) << left << "| " + to_string(num) << setw(66) << left << " | " + element.name << setw(19) <<
				setw(20) << left << " | " + DateToString(element.date) << setw(35) << left << " | " + element.store <<
				setw(35) << left << " | " + element.provider << 
				setw(35) << left << " | " + element.type <<  
				setw(35) << left << " | " + element.country <<  
				setw(35) << left << " | " + to_string(element.count) << 
				setw(35) << left << " | " + to_string(element.price) << "| " << endl;
			num++;
		}
		out << "    +" << line << "+    " << endl;
	}
	else return false;

	out.close();
	return true;
}

/* Вывод списка по искомому значению */
// Реализация пропущена (похожа на PrintList)
void printSearchList(list<DOORFURNITURE> lst, string searchStr, int activeItem = 0, int site = 1, bool clear = false) {
	list<DOORFURNITURE> newLst;
	for (auto element : lst) {
		string fullStr = element.name + element.type + element.country + element.material + element.description + to_string(element.count) + to_string(element.price) + DateToString(element.date) + element.store + element.provider;
		if (fullStr.find(searchStr) != std::string::npos) newLst.push_front(element);
	}

	if (lst.empty()) { // Если список пуст
		printWarning("Список товаров пуст!"); // Выводим предукпреждение
		system("cls");
		getMainMenu(lst, 0);
	}
	else { // Иначе
		if (clear) { // Если нужно очистить экран (передается как параметр функции)
			system("cls"); // Очищаем его
			system("MODE CON: COLS=253 LINES=42"); // Меняем размер окна
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { 250, 9999 }); // Полосы прокрутки
		}

		string line(180, '-'), line2(155, ' '), line3(50, '-'), line4(50, ' '); // Задаем несколько статичных строк из одинаковых символов для отображения интерфейса

		cout << "   \x1b[7m +" << line << "+ \x1b[0m   " << endl; // Задание цвета https://habr.com/ru/post/94647/
		cout << "   \x1b[7m " << setw(6) << left << "| №" << setw(66) << left << " | Наименование товара" << setw(19) << left << " | Количество (шт)" << setw(20) << left << " | Дата поставки" << setw(35) << left << " | Магазин" <<
			setw(35) << left << " | Поставщик" << "| \x1b[0m" << endl;
		cout << "   \x1b[7m +" << line << "+ \x1b[0m   " << endl;

		// Выводим 18 записей списка в зависимости от страницы
		int i = 0;
		int index = 18 * (site - 1);
		for (DOORFURNITURE el : newLst) {
			if (i >= index && i < index + 18) {
				cout << "    +" << line << "+    " << endl;
				printElement(i + 1, el, activeItem == i % 18);
			}
			i++;
		}
		cout << "    +" << line << "+    " << endl;

		cout << "    <<< предыдущая" << line2 << "следующая >>>    " << endl;

		//-------------------------------------------------------------
		//-------------------------------------------------------------
		// Определяем номер элемента выделенной на текущей момент записи в исходном списке, выводим полные данные по этому элементу в правой части экрана
		int activeItemInList = (18 * site) - (18 - activeItem);

		// Шапка
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 0 });
		cout << "   \x1b[7m +" << line3 << "+ \x1b[0m   " << endl;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 1 });
		cout << "   \x1b[7m |" << "                 Доп. информация                  " << "| \x1b[0m   " << endl;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 2 });
		cout << "   \x1b[7m +" << line3 << "+ \x1b[0m   " << endl;

		// Предварительно стираем предыдущий текст, который был в правой части, т.к. мы не очищаем весь экран, а перерисовываем поверх (чтобы было меньше раздражающих миганий, очистка консоли очень заметна)
		short pos = 4;
		i = 0;
		for (int i = 0; i < 20; i++) {
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, ++pos }); // Перемещаем курсор в нужную позицию
			cout << "    " + line4 << endl;
		}

		// Подробные данные об элементе
		i = 0;
		pos = 8;
		for (DOORFURNITURE el : newLst) {
			if (i == activeItemInList) {
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 4 });
				cout << "\x1b[32m" << "    Тип товара: " << "\x1b[0m" << el.type << endl;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 5 });
				cout << "\x1b[32m" << "    Страна-производитель: " << "\x1b[0m" << el.country << endl;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 6 });
				cout << "\x1b[32m" << "    Материал: " << "\x1b[0m" << el.material << endl;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 7 });
				cout << "\x1b[32m" << "    Рекомендуемая стоимость: " << "\x1b[0m" << el.price << " р." << endl;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, 8 });
				cout << "\x1b[32m" << "    Описание: " << "\x1b[0m" << endl;

				// Разделяем описание на подстроки на случай, если текст большой, и выводим каждую подстроку отдельно
				int descriptionLine = el.description.size() / 50 + 1;
				for (int i = 0; i < descriptionLine; i++) {
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 190, ++pos }); // Перемещаем курсор в нужную позицию
					cout << "    " + el.description.substr(i * 50, 50) << endl;
				}
			}
			i++;
		}

		// Обработка нажатий клавиш на клавиатуре
		char key = 0;
		list<DOORFURNITURE>::iterator itr; // Объявляем итератор
		while (key != 80 && key != 72 && key != 27 && key != 75 && key != 77 && key != 8)
		{
			key = _getch();

			switch (key) {
			case 80: // При нажатии стрелки вниз
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); // Перемещение курсора в начальную позицию
				if ((newLst.size() / site > 18 && activeItem == 17) || (newLst.size() / site <= 18 && activeItem == newLst.size() % 18 - 1))
					printSearchList(lst, searchStr, 0, site); // Если указатель был на последней строке, то перенести курсор на 1ую строку
				else
					printSearchList(lst, searchStr, ++activeItem, site); // Иначе перенести курсор на строку ниже
				break;

			case 72: // При нажтиии стрелки вверх (по аналогии с кодом выше)
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
				if (activeItem == 0) printSearchList(lst, searchStr, newLst.size() / site > 18 ? 17 : newLst.size() % 18 - 1, site);
				else printSearchList(lst, searchStr, --activeItem, site);
				break;
			case 75: // При нажатии стрелки влево
				if (site > 1) {
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); // Перемещение курсора в начальную позицию
					printSearchList(lst, searchStr, 0, --site, true);
				}
				else printSearchList(lst, searchStr, activeItem, site, true);
				break;
			case 77: // При нажтиии стрелки вправо (по аналогии с кодом выше)
				if (site < lst.size() / 18 + 1) {
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
					printSearchList(lst, searchStr, 0, ++site, true);
				}
				else printSearchList(lst, searchStr, activeItem, site, true);
				break;
			case 27: // При нажатии кнопку Esc
				system("MODE CON: COLS=190 LINES=42");
				system("cls");
				break;
			}

		}
	}
}