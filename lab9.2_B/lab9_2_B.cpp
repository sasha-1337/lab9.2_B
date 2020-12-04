#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>

using namespace std;

enum Speciality { PROGRAMMER, ENGINEER, ELECTRICIAN };
string specStr[] = { "���������", "�������", "��������" };
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
	cout << "������ ������� ��������: "; cin >> N;
	Student* p = new Student[N];

	int ispec;
	Speciality spec;
	string prizv;
	int found;

	int MenuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ���� ������� ������ '�����' � ������� �������� " << endl;
		cout << " [4] - ������� ������������� �����" << endl;
		cout << " [5] - ������� ����� ���������� �� ������� �� ��������" << endl;
		cout << " [6] - �������� ������������� �� ���� �����"
			<< endl << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> MenuItem;
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
			cout << "������ ����� ������:" << endl;
			cout << " ������������ (0 - ���������, 1 - �������, 2 - ��������): ";
			cin >> ispec;
			spec = (Speciality)ispec;
			cin.get();
			cin.sync();
			cout << " �������: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, spec)) != -1)
				cout << "�������� �������� � ������� " << found + 1 << endl;
			else
				cout << "�������� �������� �� ��������" << endl;
			break;
		case 6:
			PrintIndexSorted(p, IndexSort(p, N), N);
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;

		}
	} while (MenuItem != 0);
	return 0;
}

void Create(Student* p, const int N)
{
	int spec, midMARK;
	for (int i = 0; i < N; i++)
	{
		cout << " ������� � " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " �������: "; getline(cin, p[i].prizv);
		cout << " ����: "; cin >> p[i].kurs;
		cout << " C����������� (0 - ���������, 1 - �������, 2 - ��������): "; cin >> spec;
		p[i].spec = (Speciality)spec;
		switch (p[i].spec)
		{
		case PROGRAMMER:
			cout << " Գ���� "; cin >> p[i].phisic;
			cout << " ���������� "; cin >> p[i].math;
			cout << " ����������� "; cin >> p[i].inform;
			break;
		case ENGINEER:
			cout << " Գ���� "; cin >> p[i].phisic;
			cout << " ���������� "; cin >> p[i].math;
			cout << " ������� ������ "; cin >> p[i].NumMeth;
			break;
		case ELECTRICIAN:
			cout << " Գ���� "; cin >> p[i].phisic;
			cout << " ���������� "; cin >> p[i].math;
			cout << " ��������� "; cin >> p[i].pedagogy;
			break;
		}
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "================================================================================================================"
		<< endl;
	cout << "| � | ������� | ���� | ������������ | Գ���� | ���������� | ����������� | ������� ������ | ��������� | �/� |"
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

	cout << " �������: ������� ������ '�����' � ������� ��������." << endl;
	cout << "=======================" << endl;
	cout << "|      Գ����     | " << count_Phisic << " |" << endl;
	cout << "-----------------------" << endl;
	cout << "|    ����������   | " << count_Math << " |" << endl;
	cout << "-----------------------" << endl;
	cout << "|   �����������   | " << count_IT << " |" << endl;
	cout << "-----------------------" << endl;
	cout << "| ������� ������ | " << count_NumMeth << " |" << endl;
	cout << "-----------------------" << endl;
	cout << "|    ���������   | " << count_Pedagogy << " |" << endl;
	cout << "=======================" << endl;
}

int goodMARK(const int N, int mark) {// �������� ������ ������
	int count = 0;
	(mark == 4 || mark == 5) ? count++ : count = 0;
	return count;
}

float midMark(const int N, int mark_1, int mark_2, int mark_3) {
	float midMARK = 0;
	for (int i = 0; i < N; i++)
		midMARK = (mark_1 + mark_2 + mark_3) / 3.; // ���������� ���������� ����
	return midMARK;
}

int BinSearch(Student* p, const int N, const string prizv, const Speciality spec)
{ // ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
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
	for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
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
	int* I = new int[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		I[i] = i; // ��������� ���� ����������� ������
	int i, j, value; // �������� ��������� ����� �������
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1; j >= 0 && ((p[I[j]].spec > p[value].spec) || // � ����� �����
			(p[I[j]].spec == p[value].spec) || // � ����� �����
			(p[I[j]].spec == p[value].spec && p[I[j]].prizv == p[value].prizv)); j--) // � ������� �����
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
	cout << "| � | ������� | ���� | ������������ | Գ���� | ���������� | ����������� | ������� ������ | ��������� | �/� |"
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