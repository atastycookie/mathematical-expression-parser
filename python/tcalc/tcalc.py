import math
from typing import List, Union

# Math consts
M_PI = 3.1415926535897932384626433832795
F_G = 9.81
M_E = 2.71828182845904523536
H_LEET = 1337

# Defines
MAX_EXPR_LEN = 255
MAX_TOKEN_LEN = 80

# Brackets
CALC_END = -1
CALC_L_BRACKET = -2
CALC_R_BRACKET = -3
CALC_NUMBER = -4

# Operations
OP_PLUS = 0
OP_MINUS = 1
OP_MULTIPLY = 2
OP_DIVIDE = 3
OP_PERCENT = 4
OP_POWER = 5
OP_UMINUS = 6

# Math Operations
OP_SIN = 7
OP_COS = 8
OP_TG = 9
OP_CTG = 10
OP_ARCSIN = 11
OP_ARCCOS = 12
OP_ARCTG = 13
OP_ARCCTG = 14
OP_SH = 15
OP_CH = 16
OP_TH = 17
OP_CTH = 18
OP_EXP = 19
OP_LG = 20
OP_LN = 21
OP_SQRT = 22
OP_IN = 23
CALC_PI = 24
CALC_G = 25
CALC_LEET = 26

TERMINATOR = "\x00"


def str_len(list1):
    list1 = list(list1)
    i = 0
    while list1[i] != TERMINATOR:
        i = i + 1
    return i


def strcmp(list1, list2):
    list1 = list(list1)
    list2 = list(list2)
    total = len(list1) if len(list1) < len(list2) else len(list2)
    for i in range(0, total):
        if i > len(list1) - 1:
            return not True
        elif i > len(list2):
            return not True
        elif list1[i] != list2[i]:
            return not False
        else:
            continue


def atof(text: List[str]):
    text = "".join(text[:str_len(text)])
    integer = int(text)
    double = float(text)
    if integer == double:
        return integer
    else:
        return double


class TCalcException(Exception):

    def __init__(self, reason: str):
        self.reason = reason


    def __str__(self):
        return self.reason


class TCalcNode:

    def __init__(self, _value=0, _left=None, _right=None):
        self.left = _left
        self.right = _right
        self.value = _value


class TCalc:
    expr_ = [TERMINATOR for i in range(0, MAX_EXPR_LEN)]
    cur_token = [TERMINATOR for i in range(0, MAX_TOKEN_LEN)]

    def __init__(self):
        self.root = None
        self.typ_token = 0
        self.pos = 0
        self.result = 0

    @classmethod
    def create_node(cls, _value, _left, _right) -> TCalcNode:
        return TCalcNode(_value, _left, _right)

    def is_delim(self):
        for char in list("+-*/%^()[]"):
            if self.expr_[self.pos] == char:
                return True
            else:
                continue
        return False

    def is_letter(self):
        return (
            (ord('a') <= ord(self.expr_[self.pos]) <= ord('z')) or (ord('A') <= ord(self.expr_[self.pos]) <= ord('Z'))
        )

    def is_digit(self):
        return ord('0') <= ord(self.expr_[self.pos]) <= ord('9')

    def is_point(self):
        return self.expr_[self.pos] == "."

    def get_token(self):
        self.cur_token[0] = TERMINATOR
        while self.expr_[self.pos] == " ":
            self.pos = self.pos + 1
        if self.expr_[self.pos] == TERMINATOR:
            self.cur_token[0] = TERMINATOR
            self.typ_token = CALC_END
            return True
        elif self.is_delim():
            self.cur_token[0] = self.expr_[self.pos]
            self.pos = self.pos + 1
            self.cur_token[1] = TERMINATOR
            tmp = "".join(self.cur_token[:str_len(self.cur_token)])
            if tmp == "+":
                self.typ_token = OP_PLUS
                return True
            elif tmp == "-":
                self.typ_token = OP_MINUS
                return True
            elif tmp == "^":
                self.typ_token = OP_POWER
                return True
            elif tmp == "*":
                self.typ_token = OP_MULTIPLY
                return True
            elif tmp == "/":
                self.typ_token = OP_DIVIDE
                return True
            elif tmp == "%":
                self.typ_token = OP_PERCENT
                return True
            elif tmp == "[" or tmp == "(":
                self.typ_token = CALC_L_BRACKET
                return True
            elif tmp == "]" or tmp == ")":
                self.typ_token = CALC_R_BRACKET
                return True
        elif self.is_letter():
            i = 0
            while self.is_letter():
                self.cur_token[i] = self.expr_[self.pos]
                self.pos = self.pos + 1
                i = i + 1
            self.cur_token[i] = TERMINATOR
            _len = str_len(self.cur_token)
            for i in range(0, _len):
                if ord('A') <= ord(self.cur_token[i]) <= ord('Z'):
                    self.cur_token[i] = chr(ord(self.cur_token[i]) + ord('a') - ord('A'))
            if not strcmp(self.cur_token, list("leet")):
                self.typ_token = CALC_LEET
                return True
            elif not strcmp(self.cur_token, list("g")):
                self.typ_token = CALC_G
                return True
            elif not strcmp(self.cur_token, list("pi")):
                self.typ_token = CALC_PI
                return True
            elif not strcmp(self.cur_token, list("sin")):
                self.typ_token = OP_SIN
                return True
            elif not strcmp(self.cur_token, list("cos")):
                self.typ_token = OP_COS
                return True
            elif not strcmp(self.cur_token, list("tg")):
                self.typ_token = OP_TG
                return True
            elif not strcmp(self.cur_token, list("ctg")):
                self.typ_token = OP_CTG
                return True

            elif not strcmp(self.cur_token, list("arcsin")):
                self.typ_token = OP_ARCSIN
                return True
            elif not strcmp(self.cur_token, list("arccos")):
                self.typ_token = OP_ARCCOS
                return True
            elif not strcmp(self.cur_token, list("arctg")):
                self.typ_token = OP_ARCTG
                return True
            elif not strcmp(self.cur_token, list("arcctg")):
                self.typ_token = OP_ARCCTG
                return True
            elif not strcmp(self.cur_token, list("sh")):
                self.typ_token = OP_SH
                return True
            elif not strcmp(self.cur_token, list("ch")):
                self.typ_token = OP_CH
                return True
            elif not strcmp(self.cur_token, list("th")):
                self.typ_token = OP_TH
                return True
            elif not strcmp(self.cur_token, list("cth")):
                self.typ_token = OP_CTH
                return True
            elif not strcmp(self.cur_token, list("exp")):
                self.typ_token = OP_EXP
                return True
            elif not strcmp(self.cur_token, list("lg")):
                self.typ_token = OP_LG
                return True
            elif not strcmp(self.cur_token, list("ln")):
                self.typ_token = OP_LN
                return True
            elif not strcmp(self.cur_token, list("sqrt")):
                self.typ_token = OP_SQRT
                return True
            else:
                self.send_error(0)
        elif self.is_digit() or self.is_point():
            i = 0
            while self.is_digit():
                self.cur_token[i] = self.expr_[self.pos]
                self.pos = self.pos + 1
                i = i + 1
            if self.is_point():
                self.cur_token[i] = self.expr_[self.pos]
                self.pos = self.pos + 1
                i = i + 1
                while self.is_digit():
                    self.cur_token[i] = self.expr_[self.pos]
                    self.pos = self.pos + 1
                    i = i + 1
            self.cur_token[i] = TERMINATOR
            self.typ_token = CALC_NUMBER
            return True
        else:
            self.cur_token[0] = self.expr_[self.pos]
            self.pos = self.pos + 1
            self.cur_token[1] = TERMINATOR
            self.send_error(1)
        return False

    def expr(self):
        temp = self.expr1()
        while True:
            if self.typ_token == OP_PLUS:
                self.get_token()
                temp = self.create_node(OP_PLUS, temp, self.expr1())
            elif self.typ_token == OP_MINUS:
                self.get_token()
                temp = self.create_node(OP_MINUS, temp, self.expr1())
            else:
                break
        return temp

    def expr1(self):
        temp = self.expr2()
        while True:
            if self.typ_token == OP_MULTIPLY:
                self.get_token()
                temp = self.create_node(OP_MULTIPLY, temp, self.expr2())
            elif self.typ_token == OP_DIVIDE:
                self.get_token()
                temp = self.create_node(OP_DIVIDE, temp, self.expr2())
            elif self.typ_token == OP_PERCENT:
                self.get_token()
                temp = self.create_node(OP_PERCENT, temp, self.expr2())
            else:
                break
        return temp

    def expr2(self):
        if self.typ_token == OP_PLUS:
            self.get_token()
            temp = self.expr3()
        elif self.typ_token == OP_MINUS:
            self.get_token()
            temp = self.create_node(OP_UMINUS, self.expr3(), None)
        else:
            temp = self.expr3()
        return temp

    def expr3(self):
        if OP_SIN <= self.typ_token <= OP_SQRT + 1:
            temp = self.create_node(OP_SIN - OP_SIN + self.typ_token, None, None)
            self.get_token()
            if self.typ_token != CALC_L_BRACKET:
                self.send_error(4)
            self.get_token()
            temp.left = self.expr()
            if self.typ_token != CALC_R_BRACKET:
                self.send_error(5)
            self.get_token()
        else:
            temp = self.expr4()
        return temp

    def expr4(self):
        temp = None
        if self.typ_token == CALC_NUMBER:
            temp = self.create_node(atof(self.cur_token), None, None)
            self.get_token()
        elif self.typ_token == CALC_PI:
            temp = self.create_node(M_PI, None, None)
            self.get_token()
        elif self.typ_token == CALC_G:
            temp = self.create_node(F_G, None, None)
            self.get_token()
        elif self.typ_token == CALC_L_BRACKET:
            self.get_token()
            temp = self.expr()
            if self.typ_token != CALC_R_BRACKET:
                self.send_error(5)
            self.get_token()
        elif self.typ_token == CALC_LEET:
            temp = self.create_node(H_LEET, None, None)
            self.get_token()
        else:
            self.send_error(5)
        return temp

    def send_error(self, err_num: int):
        if self.cur_token == TERMINATOR:
            raise TCalcException("Пустое выражение")
        elif err_num == 2:
            raise TCalcException("Внезапный конец выражения")
        elif err_num == 3:
            raise TCalcException("Конец выражения ожидается")
        elif err_num == 4:
            raise TCalcException("Пропущена открывающая скобка")
        elif err_num == 5:
            raise TCalcException("Пропущена закрывающая скобка")
        else:
            raise TCalcException("Неизвестная ошибка")

    def calc_tree(self, tree):
        if tree.left is None and tree.right is None:
            return tree.value
        else:
            op = tree.value
            if op == OP_PLUS:
                return self.calc_tree(tree.left) + self.calc_tree(tree.right)
            elif op == OP_MINUS:
                return self.calc_tree(tree.left) - self.calc_tree(tree.right)
            elif op == OP_MULTIPLY:
                return self.calc_tree(tree.left) * self.calc_tree(tree.right)
            elif op == OP_DIVIDE:
                return self.calc_tree(tree.left) / self.calc_tree(tree.right)
            elif op == OP_PERCENT:
                return self.calc_tree(tree.left) % (self.calc_tree(tree.right))
            elif op == OP_POWER:
                return math.pow(self.calc_tree(tree.left), self.calc_tree(tree.right))
            elif op == OP_UMINUS:
                return -self.calc_tree(tree.left)
            elif op == OP_SIN:
                return math.sin(self.calc_tree(tree.left))
            elif op == OP_COS:
                return math.cos(self.calc_tree(tree.left))
            elif op == OP_TG:
                return math.tan(self.calc_tree(tree.left))
            elif op == OP_CTG:
                return 1.0 / math.tan(self.calc_tree(tree.left))
            elif op == OP_ARCSIN:
                return math.asin(self.calc_tree(tree.left))
            elif op == OP_ARCCOS:
                return math.acos(self.calc_tree(tree.left))
            elif op == OP_ARCTG:
                return math.atan(self.calc_tree(tree.left))
            elif op == OP_ARCCTG:
                return M_PI / 2.0 - math.atan(self.calc_tree(tree.left))
            elif op == OP_SH:
                temp = self.calc_tree(tree.left)
                return (math.exp(temp) - math.exp(-temp)) / 2.0
            elif op == OP_CH:
                temp = self.calc_tree(tree.left)
                return (math.exp(temp) + math.exp(-temp)) / 2.0
            elif op == OP_TH:
                temp = self.calc_tree(tree.left)
                return (math.exp(temp) - math.exp(-temp)) / (math.exp(temp) + math.exp(-temp))
            elif op == OP_CTH:
                temp = self.calc_tree(tree.left)
                return (math.exp(temp) + math.exp(-temp)) / (math.exp(temp) - math.exp(-temp))
            elif op == OP_EXP:
                return math.exp(self.calc_tree(tree.left))
            elif op == OP_LG:
                return math.log10(self.calc_tree(tree.left))
            elif op == OP_LN:
                return math.log(self.calc_tree(tree.left))
            elif op == OP_SQRT:
                return math.sqrt(self.calc_tree(tree.left))
            elif op == OP_IN:
                return 1
        return 0

    def evalute(self, _expr: Union[List[str], str]):
        _expr = list(_expr) if isinstance(_expr, str) else _expr
        self.root = None
        self.typ_token = 0
        self.pos = 0
        self.result = 0

        self.expr_ = _expr + [TERMINATOR]
        self.get_token()
        if self.typ_token == CALC_END:
            self.send_error(2)
        self.root = self.expr()
        if self.typ_token != CALC_END:
            self.send_error(3)

        return self.calc_tree(self.root)
