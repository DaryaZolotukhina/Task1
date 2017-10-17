
/*Система двусторонних дорог такова что для любой пары городов можно указать соединяющий их путь. 
Hайдите такой город, сумма растояний от которого до остальных городов минимальна.*/
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <io.h>
#include <stdio.h>

using namespace std;

const int maxPath = 100000;


struct TFileInfo { //структура содержит файловую переменную и имя файла
	FILE *f;
	char FileName[20];

};


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
			if (i != top && !Visited[i] && Matr[i][top]>0 && ShortPath[top] + Matr[i][top] < ShortPath[i]) {
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

void ShowMessage(char txt[]) { //вывод сообщения пользователю

	printf_s("%s\n", txt);
	puts("");

}


bool InputQuery(char *txt) { //возвращает ответ пользователя на вопрос в формате yes\no 
	char s[5]; //ответ пользователя
	char ans; //первый символ ответа
	do {
		printf_s("%s\n", txt); //вывод вопроса 
		gets_s(s); //считываем строку
		ans = s[0]; //запомним первый символ ответа
	} while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n'); //пока ответ не подойдет под вариант yes\no 
	return (ans == 'Y' || ans == 'y'); //возвращем true если yes
}



bool CorrectFilename(const char *txt) //проверка на корректность имени файла, boolean //проверяет правильности имени файла
{
	int len; //переменная длины имени
	bool res = true; //переменная результата выполнения функции
	int i = 0; //переменная текущей позиции слова
	int j;
	char cor[8] = "/:?*<>|"; //массив некорректных символов
	len = strlen(txt); //длина имени
	while ((i < len) && (res)) //пока не конец имени и имя верно, выполнять цикл
	{
		j = 0;
		while ((j < 8) && (res)) //пока не проверены все некоррект. символы и имя верно, выполнять цикл
		{
			if (txt[i] != cor[j])
				j++; //если символ корректный, то проверяем следующий некорректный символ
			else
				res = false; //иначе имя некорректно
		}
		i++;//переходим на следующий символ имени
	}
	return res; //возвращаем true - имя корректно, false - имя не корректно
}

void deletestr(char *s, int l, int r) { //удаляет подстроку в строке с позиции l до r
	char s1[30];
	int len = strlen(s); //длина строки
	int i = 0;
	if (l >= 0 && l <= r && r < len) { //если отрезок правильный
		for (; i < l; i++) //копируем строку с 0 до l-1
			s1[i] = s[i];
		for (int j = r + 1; j < len; j++, i++) //копирует с r+1 до len 
			s1[i] = s[j];
		s1[i] = '\0'; //добавляем символ конца
		strcpy_s(s, 30, s1); //сохарняем новую строку в исходную
	}

}


void Trim(char *str) { //удаляет пробелы слева и справа в строке
	int i = 0;
	int len = strlen(str); //длина строки
	int l, r;
	while (i<len && str[i] == ' ') i++; //доходим до символа отличного от пробела
	l = i - 1; //запоминаем позицию 
	i = len - 1;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\n')) i--; //с конца доходим до символа отличного от пробела
	r = i + 1;//запоминаем
	deletestr(str, r, len - 1); 	 //удаляем кусок с пробелами справа
	deletestr(str, 0, l); //удаляем кусок с пробелами слева
}

bool FileExists(char *N)//проверяет существование файла
{
	bool res;


	if (!_access(N, 0)) res = true; //если существует файл с указанным именем, вернет true 
	else res = false;

	return res;
}

bool InputFileName(char *txt, char *FileName, bool MustExist) { //ввод имени файла, MustExist показывает, должен ли существовать файл
	bool check; //результат
	cout << txt << endl; //вывод текста 
	cin >> FileName; //считываем имя
	Trim(FileName); //удалем пробелы слева и справа

	check = true;


	if (strlen(FileName) == 0) { //если пустая строка, выходим из функции с результатом false 
		ShowMessage("Операция отменена");
		check = false;
	}

	else
		if (CorrectFilename(FileName)) { //если имя введено корректно
			if (MustExist) //если должно существовать 
			{

				if (FileExists(FileName)) { //если существует

					check = true; //результат true
				}
				else //не существует
				{

					ShowMessage("Файл не найден"); //вывод сообщения, результат false
					check = false;
				}
			}
			else //если не должен был существовать 
			{
				if (!FileExists(FileName)) { // если не существует 
					check = true;
				}

				else //если существует 
				{
					if (!InputQuery("Такой файл уже существует.Заменить?")) //предлагаем заменить текущий файл новым 
						check = false;
				}
			}
		}
		else {
			ShowMessage("Некорректное имя файла");
		}
		return check; //сохраняем результат
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


	cout << "Как вы хотите ввести информацию о городах? 1 - из файла, 2 - с клавиатуры" << endl;
	int ans;
	cin >> ans;
	if (ans == 2) {

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
		char FileName[20];
		if (InputFileName("Введите имя файла", FileName, true)) {
			ifstream fin(FileName);
			fin >> n;
			//Graf = new int*[n];
			Graf = CreateGraf(n);
			bool ok = true;
			int i = 0, j = 0;
			while (i < n - 1 && !fin.eof() && ok) {
				j = i + 1;
				while (j < n && !fin.eof() && ok) {
					int a;
					fin >> a;
					ok = (AddElem(Graf, a, i, j));
					j++;
				}
				i++;
			}
			if (i < n - 1) {
				cout << "В файле недостаточно данных" << endl;
				ok = false;
			}
			fin.close();
			if (!ok)
				return 0;

		}
		else
			return 0;
	}

	//вывод матрицы 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << Graf[i][j] << " ";
		}
		cout << endl;
	}

	//проверяем каждый город и если от него есть пути во все остальные, сравниваем сумму этих путей с минимумом, запоминая город
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