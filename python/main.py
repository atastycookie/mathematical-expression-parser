## -*- coding: utf-8 -*-

from TCALC import TCALC

CALC = TCALC()

print("Курсовая работа Ананьева Романа КМБ-1-11 (python порт от @tripolskypetr)")
print("Была допилена Трипольским Петром, пока что из ПИ19-1")
print("( чистка кода на C++, порт под python )")
print("Введите выражение: ")

while True:
    #try:
    CALC.Compile(list(str(input(">> "))))
    CALC.Evaluate()
    print("Ответ:    ", CALC.GetResult())
    print("")
    #except:
    #    break