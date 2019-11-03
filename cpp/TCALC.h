#ifndef TCALC_H
#define TCALC_H

#include <ios>
#include <string>

using namespace std;

// Defines
#define MAX_EXPR_LEN   255
#define MAX_TOKEN_LEN  80

#define CALC_END -1
#define CALC_L_BRACKET -2
#define CALC_R_BRACKET -3
#define CALC_NUMBER -4


// Operations
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
#define CALC_PI          24
#define CALC_G           25
#define CALC_LEET        26

/*****************************************************************************/

struct TCALCNode {
	double value;
	TCALCNode *left;
	TCALCNode *right;
    TCALCNode(
        double _value=0.0,
        TCALCNode *_left=nullptr,
        TCALCNode *_right=nullptr
    ) {
		value = _value;
		left = _left;
		right = _right; 
	}
};

/*****************************************************************************/

class TCALC {
  private:
	TCALCNode *root;
	char *expr;
	char curToken[MAX_TOKEN_LEN];
    /*enum {
        CALC_PLUS, CALC_MINUS, CALC_MULTIPLY, CALC_DIVIDE, CALC_PERCENT, ALC_POWER,
        CALC_SIN, CALC_COS, CALC_TG, CALC_CTG, CALC_ARCSIN, CALC_ARCCOS, ALC_ARCTG,
        CALC_ARCCTG, CALC_SH, CALC_CH, CALC_TH, CALC_CTH, CALC_EXP, CALC_LG,
        CALC_LN, CALC_SQRT, CALC_X, CALC_L_BRACKET, CALC_R_BRACKET, CALC_E,
        CALC_PI, CALC_NUMBER, CALC_END, CALC_G, ALC_EXP1,CALC_LEET
    } typToken; //используемые действия, константы*/
    int typToken;
    int pos;
	double result;
  private:
    TCALCNode *CreateNode(
        double _value=0.0,
        TCALCNode *_left=nullptr,
        TCALCNode *_right=nullptr
    );
	TCALCNode *Expr(void);
    TCALCNode *Expr1(void);
    TCALCNode *Expr2(void);
    TCALCNode *Expr3(void);
    TCALCNode *Expr4(void);
    bool GetToken(void);
    bool IsDelim(void) {
        return (strchr("+-*/%^()[]", expr[pos])!=nullptr);
	}   
    bool IsLetter(void) {
		return ((expr[pos]>='a' && expr[pos]<='z') ||    
		(expr[pos]>='A' && expr[pos]<='Z'));             
	}       
	bool IsDigit(void) {
        return (expr[pos]>='0' && expr[pos]<='9');
	} 
    bool IsPoint(void) {
        return (expr[pos]=='.');
	}                        
	double CalcTree(TCALCNode *tree);
	void  DelTree(TCALCNode *tree);
	void SendError(int errNum);
  public:
	TCALC() { 
        result = 0.0;
        root = nullptr;
	}
	~TCALC() {
		DelTree(root);
        root=nullptr;
	}
	bool Compile(char *expr);
	void Decompile() { 
		DelTree(root);
        root=nullptr;
	}
	double Evaluate();
	double GetResult(void) {
		return result; 
	}
};

/*****************************************************************************/

#endif // TCALC_H
