#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ios>

#include "TCALC.h"

int main(int argc, char **argv) {
    (void)(argc);
    (void)(argv);

    TCALC CALC;
    char expr[255];
    static double x[10];

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
