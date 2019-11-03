#include <math.h>
#include <ios>
#include "TCALC.h"

// OPerations
#define OP_PLUS          0
#define OP_MINUS         1
#define OP_MULTIPLY      2
#define OP_DIVIDE        3
#define OP_PERCENT       4
#define OP_POWER         5
#define OP_UMINUS        6
#define OP_SIN           7
#define OP_COS           8
#define OP_TG            9
#define OP_CTG           10
#define OP_ARCSIN        11
#define OP_ARCCOS        12
#define OP_ARCTG         13
#define OP_ARCCTG        14
#define OP_SH            15
#define OP_CH            16
#define OP_TH            17
#define OP_CTH           18
#define OP_EXP           19
#define OP_LG            20
#define OP_LN            21
#define OP_SQRT          22
#define OP_IN            23
#define OP_X             24

// Определени математических констант

#define M_PI             3.1415926535897932384626433832795
#define F_G              9.81
#define M_E              2.71828182845904523536
#define H_LEET           1337

TCALCNode *TCALC::CreateNode(double _value, TCALCNode *_left, TCALCNode *_right)
{
	TCALCNode *pNode = new TCALCNode(_value, _left, _right);
	return pNode;
}

void TCALC::SendError(int errNum) //Обработчик ошибок
{
	static char *errs[10] = 
	{ NULL,
	  NULL,
		"Внезапный конец выражения",
		"Конец выражения ожидается",
		"Пропущеннаи открывающая скобка",
		"Пропущенна закрывающая скобка",
		NULL
	};
	static char buffer[80];

	int len = strlen(curToken);



	if(*curToken=='\0')
		strcpy(curToken, "Пустое выражение");

	switch(errNum)
		{
			case 0:
				sprintf(buffer, "Что за хрень: '%s'", curToken);
				errs[0] = buffer;
				break;

			case 1:
				sprintf(buffer, "Что за хрень: '%s'", curToken);
				errs[1] = buffer;
				break;

			case 6:
				sprintf(buffer, "Что за хрень: '%s'", curToken);
				errs[6] = buffer;
				break;
		}

	TError error(errs[errNum], pos-len);

	root = NULL;

	throw error;

	return;
}

bool TCALC::GetToken(void)
{
	*curToken = '\0';

	while(expr[pos]==' ') pos++;

		if(expr[pos]=='\0')
		{
			curToken[0] = '\0';
			typToken = CALC_END;
			return true;
		}
	else
			if(IsDelim())
				{
					curToken[0] = expr[pos++];
					curToken[1] = '\0';
						switch(*curToken)
							{
								case '+':
									typToken = CALC_PLUS;
									return true;

								case '-':
									typToken = CALC_MINUS;
									return true;

								case '*':
									typToken = CALC_MULTIPLY;
									return true;

								case '/':
									typToken = CALC_DIVIDE;
									return true;

								case '%':
									typToken = CALC_PERCENT;
									return true;
								case '[': 
								case '(':
									typToken = CALC_L_BRACKET;
									return true;

								case ']': 

								case ')':
									typToken = CALC_R_BRACKET;
									return true;
							}
				}
	else if(IsLetter())
	{
		int i=0;
		while(IsLetter()) curToken[i++] = expr[pos++];
		curToken[i] = '\0';

		int len = strlen(curToken);
		for(i=0; i<len; i++)
			if(curToken[i]>='A' && curToken[i]<='Z')
				curToken[i] += 'a' - 'A';

		if(!strcmp(curToken, "x"))

			{
				typToken = CALC_X;
				return true;
			}

		else if(!strcmp(curToken, "leet"))

			{
				typToken = CALC_LEET;
				return true;
			}

		else if(!strcmp(curToken, "g")) 

			{
				typToken = CALC_G;
				return true;
			}




		else if(!strcmp(curToken, "pi"))
			
			{
				typToken = CALC_PI;
				return true;
			}

		else if(!strcmp(curToken, "sin"))
			{
				typToken = CALC_SIN;
				return true;
			}

		else if(!strcmp(curToken, "cos"))
		
			{
				typToken = CALC_COS;
				return true;
			}

		else if(!strcmp(curToken, "tg"))
			
			{
				typToken = CALC_TG;
				return true;
			}

		else if(!strcmp(curToken, "ctg"))
			
			{
				typToken = CALC_CTG;
				return true;
			}

		else if(!strcmp(curToken, "arcsin"))
			
			{
				typToken = CALC_ARCSIN;
				return true;
			}

		else if(!strcmp(curToken, "arccos"))
			
			{
				typToken = CALC_ARCCOS;
				return true;
			}


		else if(!strcmp(curToken, "arcctg"))
				
			{
				typToken = CALC_ARCCTG;
				return true;
			}



		else if(!strcmp(curToken, "sh"))
			
			{
				typToken = CALC_SH;
				return true;
			}

		else if(!strcmp(curToken, "ch"))

			{
				typToken = CALC_CH;
				return true;
			}

		else if(!strcmp(curToken, "th"))
			
			{	
				typToken = CALC_TH;
				return true;
			}

		else if(!strcmp(curToken, "cth"))
			
			{
				typToken = CALC_CTH;
				return true;
			}

		else if(!strcmp(curToken, "exp"))
			
			{
				typToken = CALC_EXP;
				return true;
			}

		else if(!strcmp(curToken, "lg"))
			
			{
				typToken = CALC_LG;
				return true;
			}

		else if(!strcmp(curToken, "ln"))
			
			{
				typToken = CALC_LN;
				return true;
			}

		else if(!strcmp(curToken, "sqrt"))
		
			{
				typToken = CALC_SQRT;
				return true;
			}

		else SendError(0);
	}






	else if(IsDigit() || IsPoint())
	{
		int i=0;
		while(IsDigit()) curToken[i++] = expr[pos++];
		if(IsPoint())
			{
				curToken[i++] = expr[pos++];
				while(IsDigit()) curToken[i++] = expr[pos++];
			}
		curToken[i] = '\0';
		typToken = CALC_NUMBER;
		return true;
	}

	else
	{
		curToken[0] = expr[pos++];
		curToken[1] = '\0';
		SendError(1);
	}

	return false;
}      

bool TCALC::Compile(char *_expr)
{

	pos = 0;
	expr = _expr;
	*curToken = '\0';
	if(root!=NULL)
		{
			DelTree(root);
			root = NULL;
		}

	GetToken();
	if(typToken==CALC_END) SendError(2);

	root = Expr();
	if(typToken!=CALC_END) SendError(3);
	return true;
}

TCALCNode *TCALC::Expr(void)
{
	TCALCNode *temp = Expr1();

	while(1)
	{
		if(typToken == CALC_PLUS)
			{
				GetToken();
				temp = CreateNode(OP_PLUS, temp, Expr1());
			}

		else if(typToken==CALC_MINUS)
			{
				GetToken();
				temp = CreateNode(OP_MINUS, temp, Expr1());
			}
		else break;
	}


	return temp;
}



TCALCNode *TCALC::Expr1(void)
{
	TCALCNode *temp = Expr2();

	while(1)
	{
		if(typToken==CALC_MULTIPLY)
			{
				GetToken();
				temp = CreateNode(OP_MULTIPLY, temp, Expr2());
			}

		else if(typToken==CALC_DIVIDE)
			{
				GetToken();
				temp = CreateNode(OP_DIVIDE, temp, Expr2());
			}

		else if(typToken==CALC_PERCENT)
			{
				GetToken();
				temp = CreateNode(OP_PERCENT, temp, Expr2());
			}
		else break;
	}

	return temp;
}

TCALCNode *TCALC::Expr2(void)
{
    TCALCNode *temp = Expr3();
    return temp;
}

TCALCNode *TCALC::Expr3(void)
{
	TCALCNode *temp;

	if(typToken==CALC_PLUS)
	{
		GetToken();
		temp = Expr4();
	}


	else if(typToken==CALC_MINUS)
	{
		GetToken();
		temp = CreateNode(OP_UMINUS, Expr4());
	}

	else
		temp = Expr4();

	return temp;      
}

TCALCNode *TCALC::Expr4(void)
{
	TCALCNode *temp;

	if(typToken >= CALC_SIN && typToken<=CALC_X)
		{
			temp = CreateNode(OP_SIN-CALC_SIN+typToken);
			GetToken();

			if(typToken!=CALC_L_BRACKET)
				SendError(4);
				GetToken();

			temp->left = Expr();

			if(typToken!=CALC_R_BRACKET)
				SendError(5);
				GetToken();
		}

	else
		temp = Expr5();

	return temp;
}

TCALCNode *TCALC::Expr5(void)
{
	TCALCNode *temp;

	switch(typToken)
		{
			case CALC_NUMBER:
				temp = CreateNode((double)atof(curToken));
				GetToken();
                break;
			case CALC_PI:
				temp = CreateNode((double)M_PI);
				GetToken();
				break;
			case CALC_G:
				temp =CreateNode((double)F_G);
				GetToken();
				break;
			case CALC_L_BRACKET:
				GetToken();
				temp = Expr();
				if(typToken!=CALC_R_BRACKET) SendError(5);
				GetToken();
				break;
			case CALC_LEET:
				temp = CreateNode((double) H_LEET);
				GetToken();
				break;
			default:
				SendError(6);
	}

	return temp;         
}

double TCALC::Evaluate(void)
{
	result = CalcTree(root);
	return result;
}

double TCALC::CalcTree(TCALCNode *tree) // Обработчик действий
{

	static double temp;

	if(tree->left==NULL && tree->right==NULL)
		return tree->value;  
	
	else
		switch((int)tree->value)
	{
		case OP_PLUS:
			return CalcTree(tree->left)+CalcTree(tree->right);
			// "(tree->left)+(tree->right)"

		case OP_MINUS:
			return CalcTree(tree->left)-CalcTree(tree->right);
			// "(tree->left)-(tree->right)"

		case OP_MULTIPLY:
			return CalcTree(tree->left)*CalcTree(tree->right);
			// "(tree->left)*(tree->right)"

		case OP_DIVIDE:
			return CalcTree(tree->left)/CalcTree(tree->right);	
			// "(tree->left)/(tree->right)"

		case OP_PERCENT:
			return (int)CalcTree(tree->left)%(int)CalcTree(tree->right);	
			// "(tree->left)%(tree->right)"

		case OP_POWER:
			return (double)pow(CalcTree(tree->left),CalcTree(tree->right));
			// "(tree->left)^(tree->right)"

		case OP_UMINUS:
			return -CalcTree(tree->left);
			// "-(tree->left)"

		case OP_SIN:
			return sin(CalcTree(tree->left));
			// "sin(tree->left"

		case OP_COS:
			return cos(CalcTree(tree->left));
			// "cos(tree->left)"

		case OP_TG:
			return tan(CalcTree(tree->left));
			// "tan(tree->left)"

		case OP_CTG:
			return 1.0/tan(CalcTree(tree->left));
			// "ctg(tree->left)"

		case OP_ARCSIN:
			return asin(CalcTree(tree->left));
			// "arcsin(tree->left)"

		case OP_ARCCOS:
			return acos(CalcTree(tree->left));
			// "arccos(tree->left)"

		case OP_ARCTG:
			return atan(CalcTree(tree->left));
			// "atctg(tree->left)"

		case OP_ARCCTG:
			return M_PI/2.0-atan(CalcTree(tree->left));
			// "arcctg(tree->left)"

		case OP_SH:
			temp = CalcTree(tree->left);
			return (exp(temp)-exp(-temp))/2.0;	
			// "sh(tree->left)"

		case OP_CH:
			temp = CalcTree(tree->left);
			return (exp(temp)+exp(-temp))/2.0;
			// "ch(tree->left)"

		case OP_TH:
			temp = CalcTree(tree->left);
			return (exp(temp)-exp(-temp))/(exp(temp)+exp(-temp));
			// "th(tree->left)"

		case OP_CTH:
			temp = CalcTree(tree->left);
			return (exp(temp)+exp(-temp))/(exp(temp)-exp(-temp));
			// "cth(tree->left)"

		case OP_EXP:
			return exp(CalcTree(tree->left));
			// "e^(tree->left)"

		case OP_LG:
			return log10(CalcTree(tree->left));
			// "log10(tree->left)"

		case OP_LN:
			return log(CalcTree(tree->left));
			// "loge(tree->left)"

		case OP_SQRT:
			return sqrt(CalcTree(tree->left));
			// "(tree->left)^(1/2)"

		case OP_X:	
			return x[int(CalcTree(tree->left))];

		case OP_IN:
			return 1;

	}

	return 0;
}

void TCALC::DelTree(TCALCNode *tree)
{
	if(tree==NULL) return;

	DelTree(tree->left);
	DelTree(tree->right);

	delete tree;

	return;
}
