from tcalc import TCalc, TCalcException

print("Курсовая работа Ананьева Романа КМБ-1-11 (python порт от @tripolskypetr)")
print("Была допилена Трипольским Петром, пока что из ПИ19-1")
print("( чистка кода на C++, порт под python )")
print("Введите выражение: ")

calc = TCalc()


while True:
    try:
        print("Ответ:    ", calc.evalute(str(input(">> "))))
    except TCalcException as ex:
        print(ex)
