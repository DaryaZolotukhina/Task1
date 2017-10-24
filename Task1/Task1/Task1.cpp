
/*������� ������������ ����� ������ ��� ��� ����� ���� ������� ����� ������� ����������� �� ����. 
H������ ����� �����, ����� ��������� �� �������� �� ��������� ������� ����������.*/
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <io.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

const int maxPath = 100000;

bool CheckTop(int **Matr, int Num, int n, int & sum) {
	//���������� ��������� ��������
	/*�������� ������� �������� �����*/
	int *ShortPath = new int[n];
	/*�������� ������� ���������� �������*/
	bool *Visited = new bool[n];
	//��������� ������� ���������� ������� � �������� �����
	int i;
	sum = 0;
	for (i = 0; i < n; i++) {
		ShortPath[i] = maxPath;
		Visited[i] = false; //0 - �� �������, 1 - �������
	}
	ShortPath[Num] = 0; //�������� ���� �� ��������� ������ - 0

	int top = Num; //top - ������� �����

	do
	{
		i = 0;
		for (; i < n; i++) {//���� ����� ����� �� ������� � �� ��� ������� � ���������� �� ���� �� ��������� ������, ��� ����
			if (i != top && !Visited[i] && ShortPath[top] + Matr[i][top] < ShortPath[i]) {
				ShortPath[i] = ShortPath[top] + Matr[i][top];//��������� ����� ���� � ������ i
			}
		}
		Visited[top] = true; //������� ����� ��������

		int min = maxPath;//��������� �����
		top = -1; //�����, ������� ����� ������ ������� ��� ���������� ����
		for (i = 0; i < n; i++) { //���� ������������� ����� � ����� �������� �����
			if (!Visited[i] && ShortPath[i] < min) {
				min = ShortPath[i];
				top = i;
			}
		}

	} while (top != -1); //��� ������ ���������



	i = 0;
	while (i < n && ShortPath[i] < maxPath) {
		sum += ShortPath[i];
		i++;
	}

	/*�������� ������� �����*/
	delete[] ShortPath;
	delete[] Visited;

	if (i == n) return true;
	//else
	return false;


}

int **CreateGraf(int n) {
	int **Graf = new int*[n];
	for (int i = 0; i < n; i++) {
		Graf[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		Graf[i][i] = 0;

	}
	return Graf;
}
bool AddElem(int **Matr, int a, int i, int j) {
	if (a < 0) return false;
	Matr[i][j] = a;
	Matr[j][i] = a;
	return true;
}


int main() {

	setlocale(LC_ALL, "Russian");
	/*�������� ������������ �������*/
	int **Graf;
	int n;


	cout << "��� �� ������ ������ ���������� � �������? 1 - � ����������, 2 - ��������" << endl;
	int ans;
	cin >> ans;
	if (ans == 1) {

		cout << "������� ���������� �������" << endl;
		cin >> n;

		Graf = CreateGraf(n);
		/*���� ����� � �������*/
		cout << "������� ���������� ����� ��������:" << endl;
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				int a;
				cout << i + 1 << " � " << j + 1 <<  endl;
				do {
					cin >> a;
				} while (!AddElem(Graf, a, i, j));

			}
		}
	}
	else
	{
		cout << "������� ���������� �������" << endl;
		cin >> n;

		Graf = CreateGraf(n);
		/*�������������� ������������*/
		srand(time(0));
		/*���� ����� � �������*/
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				int a;
				do {
					/*����������� ��������*/
					a=rand() % 20 + 1;
				} while (!AddElem(Graf, a, i, j));

			}
		}
	}

	//����� ������� 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(4) << Graf[i][j] << " ";
		}
		cout << endl;
	}

	//��������� ������ ����� � ���������� ����� ����� � ���������, ��������� �����
	int sum = 0, minsum = maxPath;
	int SearchTop = -1;
	for (int i = 0; i < n; i++) {
		if (CheckTop(Graf, i, n, sum) && (sum < minsum)) {
			SearchTop = i;
			minsum = sum;
		}
	}

	if (SearchTop == -1) {
		cout << "������ ������ ���" << endl;
	}
	else
		cout << "������� ����� - ����� ����� " << SearchTop + 1 << ", ����� - " << minsum << endl;
	
	getchar();
	getchar();

	/*�������� ������� �� ������*/
	for (int i = 0; i < n; i++) {
		delete[] Graf[i];
	}

	return 0;
}