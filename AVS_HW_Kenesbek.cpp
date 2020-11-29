#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <omp.h>
#include<algorithm>

using namespace std;


/// <summary>
/// Метод для перевода числа в Вектор интов
/// </summary>
/// <param число="number"></param>
/// <returns></returns>
static vector<int> toListInt(long number)
{
	bool check = false;
	vector<int> el;
	el.resize(1);
	el.at(0) = number % 10;
	int	count = 0;
	while (number > 0)
	{
		for (size_t i = 0; i < el.size(); i++)
		{
			if (number % 10 != el[i])
				check = true;
		}
		if (check == true)
		{
			el.resize(el.size() + 1);
			el.at(el.size()-1) = number % 10;
			check = false;
		}
		number /= 10;
	}
	return el;
}
/// <summary>
/// Метод для сравнивания начального числа с числом * n
/// </summary>
/// <param вектор первого числа="as"></param>
/// <param вектор первого числа * на n="newas"></param>
/// <returns></returns>
static bool Res(vector <int> as, vector<int> newas)
{
	bool check = false;
	for (size_t i = 0; i < as.size(); i++)
	{
		for (size_t j = 0; j < newas.size(); j++)
		{
			if (as[i] == newas[j])
			{
				check = true;
				break;
			}
		}
		if (check == false)
		{
			return false;
		}
		if (i != as.size() - 1) {
			check = false;
		}
	}
	return true;
}
/// <summary>
/// Метод, который возращает подходящий ответ в виде вектора числа
/// </summary>
/// <param число вводимое пользователем="n"></param>
/// <param результат, который выводится по ссылке="res"></param>
static void MainMethod(int n, vector<int>* res)
{
#pragma omp parallel
	{
#pragma omp for
		for (int i = 1000; i < 1000000000; i++)//вы можете изменить верхнюю границу здесь для быстрой провеки
		{
#pragma omp critical
			{
				//cout << "Thread #" << omp_get_thread_num() << endl;
				if (Res(toListInt(i), toListInt(i * n)))
				{
					res->resize(res->size() + 1);
					res->at(res->size()-1) = i;
				}
			}
		}
	}
}
int main()
{
	try
	{

		int n, numthreads;
		do
		{
			cout << "Enter the number of threads" << endl;
			cin >> numthreads;
		} while (numthreads < 1);
		do
		{
			cout << "Enter a number from 1 to 9" << endl;
			cin >> n;
		} while (n < 1 || n > 9);
		cout << "The program is running. Please wait..." << endl;
		vector<int> result;
		omp_set_num_threads(numthreads);
		MainMethod(n, &result);

		system("Color A");
		sort(result.begin(), result.end());
		for (size_t i = 0; i < result.size(); i++)
		{
			
			cout << result[i] << "   ";
		}
		cout << endl << "Program ended seccessufully!";
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
}
