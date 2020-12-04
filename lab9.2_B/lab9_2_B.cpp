#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>

using namespace std;

enum Speciality { PROGRAMMER, ENGINEER, ELECTRICIAN };
string specStr[] = { "програміст", "інженер", "електрик" };
struct Student
{
	string prizv;
	unsigned kurs;
	Speciality spec;
	int phisic;
	int math;
	int inform;
	int pedagogy;
	int NumMeth;
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
int goodMARK(const int N, int mark);
float midMark(const int N, int mark_1, int mark_2, int mark_3);
int BinSearch(Student* p, const int N, const string prizv, const Speciality spec);
void Print_Mark(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "Введіть кількість студентів: "; cin >> N;
	Student* p = new Student[N];

	int ispec;
	Speciality spec;
	string prizv;
	int found;

	int MenuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід кількості оцінок 'добре' з кожного предмету " << endl;
		cout << " [4] - фізичне впорядкування даних" << endl;
		cout << " [5] - бінарний пошук працівника за посадою та прізвищем" << endl;
		cout << " [6] - індексне впорядкування та вивід даних"
			<< endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> MenuItem;
		cout << endl << endl << endl;

		switch (MenuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Print_Mark(p, N);
			break;
		case 4:
			Sort(p, N);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " спеціальність (0 - програміст, 1 - інженер, 2 - електрик): ";
			cin >> ispec;
			spec = (Speciality)ispec;
			cin.get();
			cin.sync();
			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, spec)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 6:
			PrintIndexSorted(p, IndexSort(p, N), N);
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;

		}
	} while (MenuItem != 0);
	return 0;
}

void Create(Student* p, const int N)
{
	int spec, midMARK;
	for (int i = 0; i < N; i++)
	{
		cout << " Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " Прізвище: "; getline(cin, p[i].prizv);
		cout << " Курс: "; cin >> p[i].kurs;
		cout << " Cпеціальність (0 - програміст, 1 - інженер, 2 - електрик): "; cin >> spec;
		p[i].spec = (Speciality)spec;
		switch (p[i].spec)
		{
		case PROGRAMMER:
			cout << " Фізика "; cin >> p[i].phisic;
			cout << " Математика "; cin >> p[i].math;
			cout << " інформатика "; cin >> p[i].inform;
			break;
		case ENGINEER:
			cout << " Фізика "; cin >> p[i].phisic;
			cout << " Математика "; cin >> p[i].math;
			cout << " Чисельні методи "; cin >> p[i].NumMeth;
			break;
		case ELECTRICIAN:
			cout << " Фізика "; cin >> p[i].phisic;
			cout << " Математика "; cin >> p[i].math;
			cout << " Педагогіка "; cin >> p[i].pedagogy;
			break;
		}
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "================================================================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Інформатика | Чисельні методи | Педагогіка | С/б |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].kurs << " "
			<< "| " << setw(14) << left << specStr[p[i].spec];
		switch (p[i].spec)
		{
		case PROGRAMMER:
			cout << "|" << setw(8) << setprecision(2) << fixed << p[i].phisic << "|" << p[i].math << setw(12) << right
				<< "|" << p[i].inform << setw(13) << "|" << setw(18) << "|" << setw(13) << "|"
				<< setprecision(2) << midMark(N, p[i].phisic, p[i].math, p[i].inform) << " |" << endl;
			break;
		case ENGINEER:
			cout << "|" << setw(8) << setprecision(2) << fixed << p[i].phisic << "|" << p[i].math << setw(12) << right << "|"
				<< setw(14) << "|" << p[i].NumMeth << setw(17) << "|" << setw(13) << "|"
				<< setprecision(2) << midMark(N, p[i].phisic, p[i].math, p[i].NumMeth) << " |" << endl;
			break;
		case ELECTRICIAN:
			cout << "|" << setw(8) << setprecision(2) << fixed << p[i].phisic << "|" << p[i].math << setw(12) << right << "|"
				<< setw(14) << "|" << setw(18) << "|" << p[i].pedagogy << setw(12) << "|"
				<< setprecision(2) << midMark(N, p[i].phisic, p[i].math, p[i].pedagogy) << " |" << endl;
			break;
		}
	}
	cout << "================================================================================================================" << endl;
	cout << endl;
}

void Print_Mark(Student* p, const int N)
{
	int count_Phisic = 0, count_Math = 0, count_IT = 0, count_NumMeth = 0, count_Pedagogy = 0;
	for (int i = 0; i < N; i++)
	{
		count_Phisic += goodMARK(N, p[i].phisic);
		count_Math += goodMARK(N, p[i].math);
		count_IT += goodMARK(N, p[i].inform);
		count_NumMeth += goodMARK(N, p[i].NumMeth);
		count_Pedagogy += goodMARK(N, p[i].pedagogy);
	}

	cout << " Таблиця: кількість оцінок 'добре' з кожного предмету." << endl;
	cout << "=======================" << endl;
	cout << "|      Фізика     | " << count_Phisic << " |" << endl;
	cout << "-----------------------" << endl;
	cout << "|    Математика   | " << count_Math << " |" << endl;
	cout << "-----------------------" << endl;
	cout << "|   Інформатика   | " << count_IT << " |" << endl;
	cout << "-----------------------" << endl;
	cout << "| Чисельні методи | " << count_NumMeth << " |" << endl;
	cout << "-----------------------" << endl;
	cout << "|    Педагогіка   | " << count_Pedagogy << " |" << endl;
	cout << "=======================" << endl;
}

int goodMARK(const int N, int mark) {// лічильник гарних оцінок
	int count = 0;
	(mark == 4 || mark == 5) ? count++ : count = 0;
	return count;
}

float midMark(const int N, int mark_1, int mark_2, int mark_3) {
	float midMARK = 0;
	for (int i = 0; i < N; i++)
		midMARK = (mark_1 + mark_2 + mark_3) / 3.; // розрахунок середнього балу
	return midMARK;
}

int BinSearch(Student* p, const int N, const string prizv, const Speciality spec)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].spec == spec)
			return m;
		if ((p[m].spec < spec) ||
			(p[m].spec == spec && p[m].prizv < prizv)) {
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}

void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].spec > p[i1 + 1].spec) ||
				(p[i1].spec == p[i1 + 1].spec && p[i1].prizv < p[i1 + 1].prizv) ||
				(p[i1].spec == p[i1 + 1].spec && p[i1].prizv == p[i1 + 1].prizv && p[i1].kurs > p[i1 + 1].kurs))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}

int* IndexSort(Student* p, const int N)
{
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1; j >= 0 && ((p[I[j]].spec > p[value].spec) || // в першу чергу
			(p[I[j]].spec == p[value].spec) || // в другу чергу
			(p[I[j]].spec == p[value].spec && p[I[j]].prizv == p[value].prizv)); j--) // в останню чергу
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "================================================================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Інформатика | Чисельні методи | Педагогіка | С/б |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].kurs << " "
			<< "| " << setw(14) << left << specStr[p[I[i]].spec];
		switch (p[i].spec)
		{
		case PROGRAMMER:
			cout << "|" << setw(8) << setprecision(2) << fixed << p[I[i]].phisic << "|" << p[I[i]].math << setw(12) << right
				<< "|" << p[I[i]].inform << setw(13) << "|" << setw(18) << "|" << setw(13) << "|"
				<< setprecision(2) << midMark(N, p[I[i]].phisic, p[i].math, p[I[i]].inform) << " |" << endl;
			break;
		case ENGINEER:
			cout << "|" << setw(8) << setprecision(2) << fixed << p[I[i]].phisic << "|" << p[I[i]].math << setw(12) << right << "|"
				<< setw(14) << "|" << p[I[i]].NumMeth << setw(17) << "|" << setw(13) << "|"
				<< setprecision(2) << midMark(N, p[I[i]].phisic, p[I[i]].math, p[I[i]].NumMeth) << " |" << endl;
			break;
		case ELECTRICIAN:
			cout << "|" << setw(8) << setprecision(2) << fixed << p[I[i]].phisic << "|" << p[I[i]].math << setw(12) << right << "|"
				<< setw(14) << "|" << setw(18) << "|" << p[I[i]].pedagogy << setw(12) << "|"
				<< setprecision(2) << midMark(N, p[I[i]].phisic, p[I[i]].math, p[I[i]].pedagogy) << " |" << endl;
			break;
		}
	}
	cout << "================================================================================================================" << endl;
	cout << endl;
}