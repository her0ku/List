// BBCO-04-19_V2_MALIY_DANIIL.cpp
//

#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;


int fmenu(char**);          // объявление функции меню
// создаем структуру списка
struct Spis
{
	Spis* previous_item; //место для хранения адреса предыдущего элемента
	float d;               // значение элемента
	int id;              // идентификатор элемента списка создается автом начиная с 0
	Spis* next_item;     // место для хранения адреса последующего элемента 
};
// окончание создания структуры списка
//-----------------------------------------------------
// создаем массив меню

char m1[] = { "1.ввод элемента                    :\n" };
char m2[] = { "2.удаление элемента по его id      :\n" };
char m3[] = { "3.печать списка                    :\n" };
char m4[] = { "4.поиск элемента по его значению   :\n" };
char m5[] = { "5.выход                            :\n" };
char* menu[] = { m1,m2,m3,m4,m5 };

//---------------------печать-----------------------------------
Spis* pStart,       // пер-ная. для хра-ния адреса начала списка 
* pEnd,              // пер-ная. для хра-ния адреса последнего эл-та 
* pCurrent,          // пер-ная. для хра-ния адреса текущего эл-та списка
* pTemp,             // пер-ная. для хра-ния промежуточного адреса эл-та списка
* pPrev;             // пер-ная. для хра-ния предыдущего адреса эл-та списка
int count0 = -1;

void input_item();
void del_item(float);
void print_list();
float find_item(float);
void exit_programm() { exit(1); }
char z;

int main()
{

	SetConsoleCP(1251);      // подключаем русский язык 
	SetConsoleOutputCP(1251);// на вывод и ввод
			 // счетчик элементов списка -1 элем-тов нет
	Spis* pStart,            // пер-ная. для хра-ния адреса начала списка 
		* pEnd,              // пер-ная. для хра-ния адреса последнего эл-та 
		* pCurrent,          // пер-ная. для хра-ния адреса текущего эл-та списка
		* pTemp,             // пер-ная. для хра-ния промежуточного адреса эл-та списка
		* pPrev;             // пер-ная. для хра-ния предыдущего адреса эл-та списка
	for (; 1;)
	{
		switch (fmenu(menu))
		{
		case 1:input_item(); break;//вызов функции ввода элемента;
		case 2:float id; cout << "введи id для удаления:"; cin >> id;
			del_item(id); break;
		case 3: print_list(); break;//вызов функции печать списка;
		case 4:int value, id_find; cout << "введи value для поиска:"; cin >> value;
			id_find = find_item(value); cout << id_find << endl; break;
			//вызов функции поиск элемента по его значению;
			// возвращает id найденного элемента
		case 5:exit_programm();//вызов функции выход;
		default: cout << "неверен пункт меню, повторите"; system("pause"); break;
		}
	}
}



void flush_stdin()
{
	cin.clear();
	while (cin.get() != '\n');
}
int fmenu(char* x[])
{
	int q;
	for (int i = 0; i < 5; i++)
		cout << x[i];  // вывод пунктов меню
	cin >> q;

	return q;                  // возвращается пункт меню
}

void input_item()
{
	pCurrent = new Spis;
	cout << endl << "введите значение элемента:";
	cin >> pCurrent->d;
	if (count0 == -1) //не создавали ни одного элемента списка
	{
		count0 += 1;
		pCurrent->id = count0;
		pStart = pCurrent; // запомнили адрес начала списка
		pEnd = pCurrent;   // запомнили адрес последнего элемента списка
		pTemp = pCurrent;                  // запомнили тек. адрес, потребуется при вводе 
											// следующего эл-та		
	}
	else
	{
		count0 += 1;
		pCurrent->id = count0;
		pEnd = pCurrent;       // запомнили адрес последнего элемента списка
		pEnd->previous_item = pCurrent;// запомнили в текущем адрес предыдущего эл-та
		pEnd->next_item = pTemp->next_item;// в поле след. текущего переписали
											   // след. из предыщего

		pStart->previous_item = pEnd;
		pTemp->next_item = pCurrent;
		pCurrent = pTemp;
	}
}

void del_item(float n) {
	int flag = 0;
	pCurrent = pStart;
	for (int i = 0; i <= count0; i++)
	{
		if (pCurrent->d == n)
		{
			flag = 1;
			// берем в найденном элементе адрес предыдущего и в поле следующего
			// предыдущего элемента записываем значение следующего из найденного
			pCurrent->previous_item->next_item = pCurrent->next_item;

			//берем в найденном элементе адрес последующего и в поле предыдущего
			// следущего элемента записываем значение предыдущего из найденного
			pCurrent->next_item->previous_item = pCurrent;
			delete pCurrent;
			count0 -= 1;
			return;
		}
		else
			pCurrent = pCurrent->next_item;
	}
	if (!flag) cout << "элемента с id=" << n << " нет в списке" << endl;

}

void print_list()
{
	if (count0 < 0) {
		cout << "элементов в списке нет" << endl;
		system("pause"); return;
	}
	cout << pStart << endl;
	for (int i = 0; i <= count0; i++)
	{
		cout << pCurrent->previous_item << " : " << pCurrent->id << " : " <<
			pCurrent->d << " : " << pCurrent->next_item << endl;
		//pCurrent = pCurrent->next_item;
	}
}

float find_item(float value)
{
	float d;
	int flag = 0;
	pCurrent = pStart;
	for (int i = 0; i <= count0; i++)
	{
		if (pCurrent->d == value) // совпадают ли значения
		{
			flag = 1;
			cout << pCurrent->previous_item << " : " << pCurrent->id << " : " <<
				pCurrent->d << " : " << pCurrent->next_item << endl;
			cout << "искать далее?(1/0)"; cin >> d;
			if (d == 0) return pCurrent->id;//возвращаем id найденного элемента
			pCurrent = pCurrent->next_item; flag = 0;
		}
		else
			pCurrent = pCurrent->next_item;
	}
	if (!flag) {
		cout << "элемента с зачением=" << value << " нет в списке" << endl;
		return -1;
	}
}