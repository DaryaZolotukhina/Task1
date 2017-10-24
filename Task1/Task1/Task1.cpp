
/*Система двусторонних дорог такова что для любой пары городов можно указать соединяющий их путь. 
Hайдите такой город, сумма растояний от которого до остальных городов минимальна.*/
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <io.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

const int maxPath = 100000;

bool CheckTop(int **Matr, int Num, int n, int & sum) {
	//реализация алгоритма Дейкстры
	/*Создание матрицы коротких путей*/
	int *ShortPath = new int[n];
	/*Создание матрицы посещенных городов*/
	bool *Visited = new bool[n];
	//заполняем массивы посещенных городов и коротких путей
	int i;
	sum = 0;
	for (i = 0; i < n; i++) {
		ShortPath[i] = maxPath;
		Visited[i] = false; //0 - не посещен, 1 - посещен
	}
	ShortPath[Num] = 0; //короткий путь до исходного города - 0

	int top = Num; //top - текущий город

	do
	{
		i = 0;
		for (; i < n; i++) {//если новый город не текущий и не был посещен и расстояние до него из исходного короче, чем было
			if (i != top && !Visited[i] && ShortPath[top] + Matr[i][top] < ShortPath[i]) {
				ShortPath[i] = ShortPath[top] + Matr[i][top];//обновляем длину пути к городу i
			}
		}
		Visited[top] = true; //текущий город проверен

		int min = maxPath;//ближайший город
		top = -1; //город, который будет выбран текущим для следующего шага
		for (i = 0; i < n; i++) { //ищем непроверенный город с самым коротким путем
			if (!Visited[i] && ShortPath[i] < min) {
				min = ShortPath[i];
				top = i;
			}
		}

	} while (top != -1); //все города проверены



	i = 0;
	while (i < n && ShortPath[i] < maxPath) {
		sum += ShortPath[i];
		i++;
	}

	/*Удаление матрицы путей*/
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
	/*Создание динамической матрицы*/
	int **Graf;
	int n;


	cout << "Как вы хотите ввести информацию о городах? 1 - с клавиатуры, 2 - рандомно" << endl;
	int ans;
	cin >> ans;
	if (ans == 1) {

		cout << "Введите количество городов" << endl;
		cin >> n;

		Graf = CreateGraf(n);
		/*Ввод графа в матрицу*/
		cout << "Введите расстояних между городами:" << endl;
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				int a;
				cout << i + 1 << " и " << j + 1 <<  endl;
				do {
					cin >> a;
				} while (!AddElem(Graf, a, i, j));

			}
		}
	}
	else
	{
		cout << "Введите количество городов" << endl;
		cin >> n;

		Graf = CreateGraf(n);
		/*Автоматическая рандомизация*/
		srand(time(0));
		/*Ввод графа в матрицу*/
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				int a;
				do {
					/*Запаолнение рандомом*/
					a=rand() % 20 + 1;
				} while (!AddElem(Graf, a, i, j));

			}
		}
	}

	//вывод матрицы 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(4) << Graf[i][j] << " ";
		}
		cout << endl;
	}

	//проверяем каждый город и сравниваем сумму путей с минимумом, запоминая город
	int sum = 0, minsum = maxPath;
	int SearchTop = -1;
	for (int i = 0; i < n; i++) {
		if (CheckTop(Graf, i, n, sum) && (sum < minsum)) {
			SearchTop = i;
			minsum = sum;
		}
	}

	if (SearchTop == -1) {
		cout << "Такого города нет" << endl;
	}
	else
		cout << "Искомый город - город номер " << SearchTop + 1 << ", сумма - " << minsum << endl;
	
	getchar();
	getchar();

	/*Удаление матрицы из памяти*/
	for (int i = 0; i < n; i++) {
		delete[] Graf[i];
	}

	return 0;
}