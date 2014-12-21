#include <cstring>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mmsystem.h>
#include <conio.h>
#include "Ant1Freeze.h"
#include <ios>

using namespace std;

int main(void)
{

	setlocale (LC_ALL, "Russian");
	TCALC CALC;
	char expr[255];
	static double x[10];

	HANDLE Ant1Freeze = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Ant1Freeze, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	
	cout << "Курсовая работа Ананьева Романа КМБ-1-11" << endl;
	cout << "Введите выражение" << endl;
	cout << "" << endl;


	CALC.SetX((double *)&x);

	while(1)
	{
		//Ввод выражения в окно
		cout << ">>  ";
		cin.getline(expr, 255); 

		// если "bb" то закрыться//////////////
		if(!strcmp(expr, "bb")) break;//ВЫХОД//
		///////////////////////////////////////

		try
			{
				CALC.Compile(expr);
				CALC.Evaluate();
				cout << "Ответ:    " << CALC.GetResult() << endl << endl; 					//Вывод ответа на экран
				cout << "" <<endl; 
			}
		catch(TError error)
			{
				
				cerr << error.error << " на "<< error.pos << " месте " << endl 				<< endl; // Печать ошибки
				continue;
			}
	}

	return 0;
}
