const M_PI = 3.1415926535897932384626433832795;
const F_G = 9.81;
const H_LEET = 1337;

const MAX_EXPR_LEN = 255;
const MAX_TOKEN_LEN = 80;

const CALC_END = -1;
const CALC_L_BRACKET = -2;
const CALC_R_BRACKET = -3;
const CALC_NUMBER = -4;

const OP_PLUS = 0;
const OP_MINUS = 1;
const OP_MULTIPLY = 2;
const OP_DIVIDE = 3;
const OP_PERCENT = 4;
const OP_POWER = 5;
const OP_UMINUS = 6;

const OP_SIN = 7;
const OP_COS = 8;
const OP_TG = 9;
const OP_CTG = 10;
const OP_ARCSIN = 11;
const OP_ARCCOS = 12;
const OP_ARCTG = 13;
const OP_ARCCTG = 14;
const OP_SH = 15;
const OP_CH = 16;
const OP_TH = 17;
const OP_CTH = 18;
const OP_EXP = 19;
const OP_LG = 20;
const OP_LN = 21;
const OP_SQRT = 22;
const OP_IN = 23;
const CALC_PI = 24;
const CALC_G = 25;
const CALC_LEET = 26;

const TERMINATOR = "\x00";

function strlen(list1) {
  let i = 0;
  while (list1[i] !== TERMINATOR) {
    i++;
  }
  return i;
}

function strcmp(list1, list2) {
  const total = Math.min(list1.length, list2.length);
  for (let i = 0; i < total; i++) {
    if (i > list1.length - 1) return false;
    if (i > list2.length - 1) return false;
    if (list1[i] !== list2[i]) return false;
  }
  return true;
}

function atof(text) {
  const str = text.slice(0, strlen(text)).join("");
  const integer = parseInt(str);
  const double = parseFloat(str);
  return integer === double ? integer : double;
}

class TCALCNode {
  constructor(_value = 0, _left = null, _right = null) {
    this.value = _value;
    this.left = _left;
    this.right = _right;
  }
}

class TCALC {
  constructor() {
    this.root = null;
    this.expr = Array(MAX_EXPR_LEN).fill(TERMINATOR);
    this.curToken = Array(MAX_TOKEN_LEN).fill(TERMINATOR);
    this.typToken = 0;
    this.pos = 0;
    this.result = 0;
  }

  static IsDelim(self) {
    for (const char of "+-*/%^()[]") {
      if (self.expr[self.pos] === char) {
        return true;
      }
    }
    return false;
  }

  static IsLetter(self) {
    const char = self.expr[self.pos];
    return (char >= "a" && char <= "z") || (char >= "A" && char <= "Z");
  }

  static IsDigit(self) {
    const char = self.expr[self.pos];
    return char >= "0" && char <= "9";
  }

  static IsPoint(self) {
    return self.expr[self.pos] === ".";
  }

  GetToken() {
    this.curToken[0] = TERMINATOR;
    while (this.expr[this.pos] === " ") {
      this.pos++;
    }
    if (this.expr[this.pos] === TERMINATOR) {
      this.curToken[0] = TERMINATOR;
      this.typToken = CALC_END;
      return true;
    } else if (TCALC.IsDelim(this)) {
      this.curToken[0] = this.expr[this.pos];
      this.pos++;
      this.curToken[1] = TERMINATOR;
      const tmp = this.curToken.slice(0, strlen(this.curToken)).join("");
      switch (tmp) {
        case "+":
          this.typToken = OP_PLUS;
          break;
        case "-":
          this.typToken = OP_MINUS;
          break;
        case "*":
          this.typToken = OP_MULTIPLY;
          break;
        case "/":
          this.typToken = OP_DIVIDE;
          break;
        case "%":
          this.typToken = OP_PERCENT;
          break;
        case "[":
        case "(":
          this.typToken = CALC_L_BRACKET;
          break;
        case "]":
        case ")":
          this.typToken = CALC_R_BRACKET;
          break;
      }
      return true;
    } else if (TCALC.IsLetter(this)) {
      let i = 0;
      while (TCALC.IsLetter(this)) {
        this.curToken[i] = this.expr[this.pos];
        this.pos++;
        i++;
      }
      this.curToken[i] = TERMINATOR;
      const len = strlen(this.curToken);
      for (let i = 0; i < len; i++) {
        if (this.curToken[i] >= "A" && this.curToken[i] <= "Z") {
          this.curToken[i] = String.fromCharCode(
            this.curToken[i].charCodeAt(0) +
              "a".charCodeAt(0) -
              "A".charCodeAt(0),
          );
        }
      }
      if (!strcmp(this.curToken, "leet".split(""))) {
        this.typToken = CALC_LEET;
      } else if (!strcmp(this.curToken, "g".split(""))) {
        this.typToken = CALC_G;
      } else if (!strcmp(this.curToken, "pi".split(""))) {
        this.typToken = CALC_PI;
      } else if (!strcmp(this.curToken, "sin".split(""))) {
        this.typToken = OP_SIN;
      } else if (!strcmp(this.curToken, "cos".split(""))) {
        this.typToken = OP_COS;
      } else if (!strcmp(this.curToken, "tg".split(""))) {
        this.typToken = OP_TG;
      } else if (!strcmp(this.curToken, "ctg".split(""))) {
        this.typToken = OP_CTG;
      } else if (!strcmp(this.curToken, "arcsin".split(""))) {
        this.typToken = OP_ARCSIN;
      } else if (!strcmp(this.curToken, "arccos".split(""))) {
        this.typToken = OP_ARCCOS;
      } else if (!strcmp(this.curToken, "sh".split(""))) {
        this.typToken = OP_SH;
      } else if (!strcmp(this.curToken, "ch".split(""))) {
        this.typToken = OP_CH;
      } else if (!strcmp(this.curToken, "th".split(""))) {
        this.typToken = OP_TH;
      } else if (!strcmp(this.curToken, "cth".split(""))) {
        this.typToken = OP_CTH;
      } else if (!strcmp(this.curToken, "exp".split(""))) {
        this.typToken = OP_EXP;
      } else if (!strcmp(this.curToken, "lg".split(""))) {
        this.typToken = OP_LG;
      } else if (!strcmp(this.curToken, "ln".split(""))) {
        this.typToken = OP_LN;
      } else if (!strcmp(this.curToken, "sqrt".split(""))) {
        this.typToken = OP_SQRT;
      } else {
        this.SendError(0);
      }
    } else if (TCALC.IsDigit(this) || TCALC.IsPoint(this)) {
      let i = 0;
      while (TCALC.IsDigit(this)) {
        this.curToken[i] = this.expr[this.pos];
        this.pos++;
        i++;
      }
      if (TCALC.IsPoint(this)) {
        this.curToken[i] = this.expr[this.pos];
        this.pos++;
        i++;
        while (TCALC.IsDigit(this)) {
          this.curToken[i] = this.expr[this.pos];
          this.pos++;
          i++;
        }
      }
      this.curToken[i] = TERMINATOR;
      this.typToken = CALC_NUMBER;
      return true;
    } else {
      this.curToken[0] = this.expr[this.pos];
      this.pos++;
      this.curToken[1] = TERMINATOR;
      this.SendError(1);
    }
    return false;
  }

  CreateNode(_value, _left, _right) {
    return new TCALCNode(_value, _left, _right);
  }

  Expr() {
    let temp = this.Expr1();
    while (true) {
      if (this.typToken === OP_PLUS) {
        this.GetToken();
        temp = this.CreateNode(OP_PLUS, temp, this.Expr1());
      } else if (this.typToken === OP_MINUS) {
        this.GetToken();
        temp = this.CreateNode(OP_MINUS, temp, this.Expr1());
      } else {
        break;
      }
    }
    return temp;
  }

  Expr1() {
    let temp = this.Expr2();
    while (true) {
      if (this.typToken === OP_MULTIPLY) {
        this.GetToken();
        temp = this.CreateNode(OP_MULTIPLY, temp, this.Expr2());
      } else if (this.typToken === OP_DIVIDE) {
        this.GetToken();
        temp = this.CreateNode(OP_DIVIDE, temp, this.Expr2());
      } else if (this.typToken === OP_PERCENT) {
        this.GetToken();
        temp = this.CreateNode(OP_PERCENT, temp, this.Expr2());
      } else {
        break;
      }
    }
    return temp;
  }

  Expr2() {
    let temp = null;
    if (this.typToken === OP_PLUS) {
      this.GetToken();
      temp = this.Expr3();
    } else if (this.typToken === OP_MINUS) {
      this.GetToken();
      temp = this.CreateNode(OP_UMINUS, this.Expr3(), null);
    } else {
      temp = this.Expr3();
    }
    return temp;
  }

  Expr3() {
    let temp = null;
    if (this.typToken >= OP_SIN && this.typToken <= OP_SQRT + 1) {
      temp = this.CreateNode(OP_SIN - OP_SIN + this.typToken, null, null);
      this.GetToken();
      if (this.typToken !== CALC_L_BRACKET) {
        this.SendError(4);
      }
      this.GetToken();
      temp.left = this.Expr();
      if (this.typToken !== CALC_R_BRACKET) {
        this.SendError(5);
      }
      this.GetToken();
    } else {
      temp = this.Expr4();
    }
    return temp;
  }

  Expr4() {
    let temp = null;
    if (this.typToken === CALC_NUMBER) {
      temp = this.CreateNode(atof(this.curToken), null, null);
      this.GetToken();
    } else if (this.typToken === CALC_PI) {
      temp = this.CreateNode(M_PI, null, null);
      this.GetToken();
    } else if (this.typToken === CALC_G) {
      temp = this.CreateNode(F_G, null, null);
      this.GetToken();
    } else if (this.typToken === CALC_L_BRACKET) {
      this.GetToken();
      temp = this.Expr();
      if (this.typToken !== CALC_R_BRACKET) {
        this.SendError(5);
      }
      this.GetToken();
    } else if (this.typToken === CALC_LEET) {
      temp = this.CreateNode(H_LEET, null, null);
      this.GetToken();
    } else {
      this.SendError(5);
    }
    return temp;
  }

  SendError(errNum) {
    if (this.curToken === TERMINATOR) {
      console.log("Пустое выражение");
    } else if (errNum === 2) {
      console.log("Внезапный конец выражения");
    } else if (errNum === 3) {
      console.log("Конец выражения ожидается");
    } else if (errNum === 4) {
      console.log("Пропущеннаи открывающая скобка");
    } else if (errNum === 5) {
      console.log("Пропущенна закрывающая скобка");
    } else {
      console.log("Неизвестная ошибка");
    }
    throw new Error("");
  }

  Compile(_expr) {
    this.pos = 0;
    this.expr = _expr.concat([TERMINATOR]);
    if (this.root !== null) {
      this.root = null;
    }
    this.GetToken();
    if (this.typToken === CALC_END) {
      this.SendError(2);
    }
    this.root = this.Expr();
    if (this.typToken !== CALC_END) {
      this.SendError(3);
    }
    return true;
  }

  GetResult() {
    return this.result;
  }

  Evaluate() {
    this.result = this.CalcTree(this.root);
  }

  CalcTree(tree) {
    if (tree.left === null && tree.right === null) {
      return tree.value;
    } else {
      const op = tree.value;
      switch (op) {
        case OP_PLUS:
          return this.CalcTree(tree.left) + this.CalcTree(tree.right);
        case OP_MINUS:
          return this.CalcTree(tree.left) - this.CalcTree(tree.right);
        case OP_MULTIPLY:
          return this.CalcTree(tree.left) * this.CalcTree(tree.right);
        case OP_DIVIDE:
          return this.CalcTree(tree.left) / this.CalcTree(tree.right);
        case OP_PERCENT:
          return this.CalcTree(tree.left) % this.CalcTree(tree.right);
        case OP_POWER:
          return Math.pow(this.CalcTree(tree.left), this.CalcTree(tree.right));
        case OP_UMINUS:
          return -this.CalcTree(tree.left);
        case OP_SIN:
          return Math.sin(this.CalcTree(tree.left));
        case OP_COS:
          return Math.cos(this.CalcTree(tree.left));
        case OP_TG:
          return Math.tan(this.CalcTree(tree.left));
        case OP_CTG:
          return 1.0 / Math.tan(this.CalcTree(tree.left));
        case OP_ARCSIN:
          return Math.asin(this.CalcTree(tree.left));
        case OP_ARCCOS:
          return Math.acos(this.CalcTree(tree.left));
        case OP_ARCTG:
          return Math.atan(this.CalcTree(tree.left));
        case OP_ARCCTG:
          return M_PI / 2.0 - Math.atan(this.CalcTree(tree.left));
        case OP_SH:
          const temp1 = this.CalcTree(tree.left);
          return (Math.exp(temp1) - Math.exp(-temp1)) / 2.0;
        case OP_CH:
          const temp2 = this.CalcTree(tree.left);
          return (Math.exp(temp2) + Math.exp(-temp2)) / 2.0;
        case OP_TH:
          const temp3 = this.CalcTree(tree.left);
          return (
            (Math.exp(temp3) - Math.exp(-temp3)) /
            (Math.exp(temp3) + Math.exp(-temp3))
          );
        case OP_CTH:
          const temp4 = this.CalcTree(tree.left);
          return (
            (Math.exp(temp4) + Math.exp(-temp4)) /
            (Math.exp(temp4) - Math.exp(-temp4))
          );
        case OP_EXP:
          return Math.exp(this.CalcTree(tree.left));
        case OP_LG:
          return Math.log10(this.CalcTree(tree.left));
        case OP_LN:
          return Math.log(this.CalcTree(tree.left));
        case OP_SQRT:
          return Math.sqrt(this.CalcTree(tree.left));
        case OP_IN:
          return 1;
      }
    }
    return 0;
  }
}

const CALC = new TCALC();

console.log(
  "Курсовая работа Ананьева Романа КМБ-1-11 (python порт от @tripolskypetr)",
);
console.log("Была допилена Трипольским Петром, пока что из ПИ19-1");
console.log("( чистка кода на C++, порт под nodejs )");
console.log("Введите выражение: ");

const readline = require("readline").createInterface({
  input: process.stdin,
  output: process.stdout,
});

function prompt() {
  readline.question(">> ", (input) => {
    try {
      CALC.Compile(Array.from(input));
      CALC.Evaluate();
      console.log("Ответ:    ", CALC.GetResult());
      console.log("");
    } catch (e) {
      readline.close();
    }
    prompt();
  });
}

prompt();
