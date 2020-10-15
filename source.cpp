#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#define a 12
struct status
{
	int num;
	status* next, * prev;
};

struct Sym
{
	char P;
	Sym* next, * prev;
};

void AddStatus(status*& head, status*& current, int num)
{
	status* NewElem = new status;
	NewElem->num = num;
	NewElem->next = NULL;
	NewElem->prev = NULL;
	if (head == NULL)
		head = NewElem;
	else
	{
		current->next = NewElem;
		NewElem->prev = current;
	}
	current = NewElem;

}

void AddSym(Sym*& head, Sym*& current, char P)
{
	Sym* NewElem = new Sym;
	NewElem->P = P;
	NewElem->next = NULL;
	NewElem->prev = NULL;
	if (head == NULL)
		head = NewElem;
	else
	{
		current->next = NewElem;
		NewElem->prev = current;
	}
	current = NewElem;
}

void Delete(status*& current)
{
	if (current != NULL)
	{
		current = current->prev;
		current->next = NULL;
	}
}

void Delete(Sym*& current)
{
	if (current != NULL)
	{
		current = current->prev;
		if (current != NULL)
			current->next = NULL;
	}
}

void print(int timer, Sym* current_sym, status* current_stat, vector<char> str, int pointer, int command)
{
	Sym* csym = current_sym;
	status* cstat = current_stat;
	int temp_int = 0;
	while (cstat != NULL || temp_int < 2)
	{
		if (temp_int == 0)
			cout << left << " | " << setw(4) << timer << "| ";
		else
			cout << left << " |    " << setfill(' ') << setw(3) << " | ";
		if (csym != NULL)
		{
			cout << setw(5) << " " << setw(8) << csym->P << " | ";
			csym = csym->prev;
		}
		else
			cout << setw(13) << " " << " | ";

		if (cstat != NULL)
		{
			cout << setw(5) << " " << setw(9) << cstat->num << " | ";
			cstat = cstat->prev;
		}
		else
			cout << setw(14) << " " << " | ";

		if (temp_int == 0)
		{
			for (int i = 0; i < str.size(); i++)
				cout << str[i];
			for (int i = 0; i < 16 - str.size(); i++)
				cout << " ";
		}
		else if (temp_int == 1)
		{
			for (int i = 0; i < pointer; i++)
				cout << " ";
			cout << "^";
			for (int i = pointer; i < 15; i++)
				cout << " ";
			cout << " | ";
		}
		else
		{
			for (int i = 0; i < 16; i++)
				cout << " ";
			cout << " | ";
		}
		if (temp_int == 0)
		{
			if (command == 1)
				cout << " | " << setw(18) << "Допуск" << " | ";
			else if (command < 13 && command>0)
				cout << " | " << setw(18) << command << " | ";
			else if (command > 13)
			{
				cout << " | " << "Приведение " << setw(7) << command - 20 << " | ";
			}
			else if (command == -1)
				cout << " | " << setw(18) << "Ошибка" << " | ";
		}
		else
			cout << setw(18) << " " << " | ";
		cout << endl;
		temp_int++;

	}
	cout << " |_____|_______________|________________|__________________|____________________| " << endl;
}

//2x- приведение
void moving(vector<char>& str)
{
	vector<char> LR;
	int LR_s = 0;
	cout << "  ______________________________________________________________________________" << endl;
	cout << " | Шаг | Стек символов | Стек состояний |  Входная строка  | Команда управления |  " << endl;
	cout << " |_____|_______________|________________|__________________|____________________| " << endl;

	int timer = 0, poz_X, command, Tablet[a][a] = {
		//     P, D, L, b, d, c, f, s ,e, #
		/*1*/{ 1,-1,-1, 2,-1,-1,-1,-1,-1,-1 },
		/*2*/{ -1, 3,-1,-1, 7,-1,-1,-1,-1,-1 },
		/*3*/{ -1,-1,-1,-1,-1,-1, 4,-1,-1,-1 },
		/*4*/{ -1, 3, 5,-1, 7,-1,-1,10,-1,-1 },
		/*5*/{ -1,-1,-1,-1,-1,-1,-1,-1, 6,-1 },
		/*6*/{ -1,-1, 5,-1,-1,-1,-1,10,-1,21 },
		/*7*/{ -1,-1,-1,-1,-1, 8,23,-1,-1,23 },
		/*8*/{ -1, 9,-1,-1, 7,-1,-1,-1,-1,-1 },
		/*9*/{ -1,-1,-1,-1,-1,-1,22,-1,-1,22 },
		/*10*/{ -1,-1,-1,-1,-1,11,-1,-1,25,25 },
		/*11*/{ -1,-1,12,-1,-1,-1,-1,10,10,-1 },
		/*12*/{ -1,-1,-1,-1,-1,-1,-1,-1,24,24 },
	};
	status* hstat = NULL;
	status* cstat = NULL;
	Sym* hsym = NULL;
	Sym* csym = NULL;
	bool good = false;
	bool bad = false;
	AddStatus(hstat, cstat, 1);
	int size = str.size();
	int pointer = 0;
	while (good == false && bad == false)
	{
		poz_X = cstat->num - 1;
		switch (str[pointer])
		{
		case 'P':
		{
			command = Tablet[poz_X][0];
			break;
		}
		case 'D':
		{
			command = Tablet[poz_X][1];
			break;
		}
		case 'L':
		{
			command = Tablet[poz_X][2];
			break;
		}
		case 'b':
		{
			command = Tablet[poz_X][3];
			break;
		}
		case 'd':
		{
			command = Tablet[poz_X][4];
			break;
		}
		case 'c':
		{
			command = Tablet[poz_X][5];
			break;
		}
		case 'f':
		{
			command = Tablet[poz_X][6];
			break;
		}
		case 's':
		{
			command = Tablet[poz_X][7];
			break;
		}
		case 'e':
		{
			command = Tablet[poz_X][8];
			break;
		}
		case '#':
		{
			command = Tablet[poz_X][9];
			break;
		}
		}
		print(timer, csym, cstat, str, pointer, command);
		switch (command)
		{
		case 1:
		{
			good = true;
			break;
		}
		case -1:
		{
			bad = true;
			break;
		}
		case 3:
		{
			AddStatus(hstat, cstat, command);
			AddSym(hsym, csym, str[pointer]);
			str.erase(str.begin() + pointer);
			break;
		}
		case 5:
		{
			AddStatus(hstat, cstat, command);
			AddSym(hsym, csym, str[pointer]);
			str.erase(str.begin() + pointer);
			break;
		}
		case 9:
		{
			AddStatus(hstat, cstat, command);
			AddSym(hsym, csym, str[pointer]);
			str.erase(str.begin() + pointer);
			break;
		}
		case 12:
		{
			AddStatus(hstat, cstat, command);
			AddSym(hsym, csym, str[pointer]);
			str.erase(str.begin() + pointer);
			break;
		}
		case 21:
		{
			str.insert(str.begin() + pointer, 'P');
			Delete(cstat);
			Delete(cstat);
			Delete(cstat);
			Delete(cstat);
			Delete(cstat);
			Delete(csym);
			Delete(csym);
			Delete(csym);
			Delete(csym);
			Delete(csym);
			LR.insert(LR.begin() + LR_s, 48 + command - 20);
			LR_s++;
			break;
		}
		case 22:
		{
			str.insert(str.begin() + pointer, 'D');
			Delete(cstat);
			Delete(cstat);
			Delete(cstat);
			Delete(csym);
			Delete(csym);
			Delete(csym);
			LR.insert(LR.begin() + LR_s, 48 + command - 20);
			LR_s++;
			break;
		}
		case 23:
		{
			str.insert(str.begin() + pointer, 'D');
			Delete(cstat);
			Delete(csym);
			LR.insert(LR.begin() + LR_s, 48 + command - 20);
			LR_s++;
			break;
		}
		case 24:
		{
			str.insert(str.begin() + pointer, 'L');
			Delete(cstat);
			Delete(cstat);
			Delete(cstat);
			Delete(csym);
			Delete(csym);
			Delete(csym);
			LR.insert(LR.begin() + LR_s, 48 + command - 20);
			LR_s++;
			break;
		}
		case 25:
		{
			str.insert(str.begin() + pointer, 'L');
			Delete(cstat);
			Delete(csym);
			LR.insert(LR.begin() + LR_s, 48 + command - 20);
			LR_s++;
			break;
		}

		default:
		{
			AddStatus(hstat, cstat, command);
			AddSym(hsym, csym, str[pointer]);
			pointer++;
			break;
		}
		}
		timer++;

	}
	if (good == true)
		cout << "Слово подходит!" << endl;
	else
		cout << "Слово не подходит!" << endl;
	cout << "Последовательность правил грамматики при процессе разбора: ";
	for (int i = LR.size() - 1; i > -1; i--)
		cout << LR[i] << " ";
	cout << endl;
	cout << "Последовательность правил грамматики в нашем входном слове: 12345 ";
}

int main()
{
	setlocale(LC_ALL, "rus");
	int size;
	string temp_str;
	cout << "Введите строку: ";
	cin >> temp_str;
	size = temp_str.length();
	vector<char> str(size);
	for (int i = 0; i < size; i++)
		str[i] = temp_str[i];
	str.insert(str.begin() + size, '#');
	cout << endl;
	moving(str);
	system("pause");
	return 0;
}
