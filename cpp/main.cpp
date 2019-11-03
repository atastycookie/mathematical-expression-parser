#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ios>

#include "TCALC.h"

int main() {
    TCALC CALC;
    char expr[255];
    cout << "Курсовая работа Ананьева Романа КМБ-1-11" << endl;
    cout << "Введите выражение" << endl;
    cout << "" << endl;
    while (1) {
        cout << ">>  ";
        cin.getline(expr, 255);
        try {
            CALC.Compile(expr);
            CALC.Evaluate();
            cout << "Ответ:    " << CALC.GetResult() << endl << endl;
            cout << "" <<endl;
        } catch(const char* msg) {
            cerr << msg << endl;
            continue;
        }
    }
}
