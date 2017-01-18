#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <iostream>
using namespace std;
//********************
//#define DEBUG
//#define YY_NO_UNISTD_H
#define LINUX

#define StackSize 100				//堆栈大小
#define CountOfVN 30			   //终结符数      
#define CountOfVT 40				//非终结符? 
#define NumOfRule 32				//语法规则条数?1?位置0为空
#define DepthOfRule 10			//规则深度
#define BeginOfVN 40			
struct InsNode;
struct symbol;

extern int tokenNumVal;
extern int curComNo ;   //scanner当前扫描位置,当前代码段的指令序号
extern int curDataPos ;	//scanner当前扫描位置的數據地址
extern int curDataAddr ;
extern int curCodeAddr ;
extern int beginOfData ;
extern int beginOfCode;

/* simple symtab of fixed size */
#define NHASH 9997
extern int curSymNum;
extern struct symbol symtab[NHASH];


struct symbol{ 
	int  flag; // 0 reprensent varible
	char *name;
	int  addr;
	
	int numOfVal;
	int *Val;
	int vartype;//0-2分别表示byte,half,word

	struct ref* refHead;
	InsNode* ins;

	int comType;  // 0 : beq,bne 1: j jal

	symbol(int f = 0){
		flag = f;
		name = NULL;
		addr = -1;
		
		ins = NULL;
		refHead = NULL;
		if(f == 0 ){
			Val = new int[10];
			numOfVal = 0;
		}
	}
	bool add(int val){
		if( numOfVal < 10 ){
			Val[numOfVal++] = val;
			return true;
		}
		return false;
	}

};
struct InsNode 
{
	//指令地址
	int insAddr; 
	//二进制码指令;
	char Com[35];
	int instype; 
	InsNode *next;

	InsNode()
	{
		instype = -1;
		insAddr = 0;
		next = NULL; 
	}
	char& operator[](int i )
	{
		return Com[i];
	}
};

struct ref{
	struct ref* next;
	InsNode* ins;
	int comType;  // 0 : beq,bne 1: j jal//用于回填时判断回填类?直接使用终结符枚举类?
	ref(){
		ins = NULL;
		next = NULL;
		comType = -1;
	}
};
//用于支持支持hilo指令
struct hilo
{
	int ishi;	 //1: hi, 0: lo
	char* name;
};
struct symbol* lookupSym( char* symName , int type);
int cmpSymbol( const void *a, const void *b );
bool backFillSeg( ) ;
int addsymbol ( char* name, int curAddr, int f, int varVal,int vartype = 2 );
int HEXNUM1ToInt(const char *);
int HEXNUM2ToInt(const char *);
int yylex();
void yyrestart  (FILE * input_file );
extern int yylineno;
void yyerror(const char *s, ...);
extern char* yytext;
extern bool syntaxOK ;
////////////////////////////////////////////////////////////////////////////////////////一些全局变量的定?


extern int curNumOfVar;
extern int curNumOfSeg;
//输入文件
extern FILE *IFile;
//32位机器指?
extern InsNode* g_curMacIns;
extern InsNode*g_macLinkTab;
////////////////////////////////////////////////////////////////////////////////////////一些函数的定义;
void setParameter();													//设置预测分析表和语法分析?
bool ConstructMacLinkTab(int No_Com);				//添加机器指令到链?
bool writeProgCoe();														//写程序coe
bool writeDataCoe();														//写数据coe
int  DEDUCTION(int NumOfVN);								//产生式入?
int  SyntacticAnalysis();			//语法分析程序
void ComHex(char *com,int size,char* dest);					//指令转为16进制
int getNextToken();													//词法分析，取得下一个TOKEN
bool intToHexstr(int src, char* dest );
void testlex();
int prefunc(const char* inf , const  char *outf) ;
//用于调试;
extern int numOfOder;
bool writeProgCoe1();

struct ast {
  int nodetype;   
  struct ast *l;
  struct ast *r;
};

struct idnum
{
	int nodetype;  //nodeType = A 
	int flag;      // 0 : val  1: str  2: hl
	int val;
	char* str;
	hilo* hl;
};

int constructNop(  int fn );
int constructR_1( int fn, int rd, int rs, int rt );
int constructR_2( int fn, int rd, int rt,int sval );
int constructR_3( int fn, int rs, int rt );
int constructR_4( int fn ,int reg);
int constructR_5( int fn );
int constructI_1(int fn, int rt, int rs , ast* node );
int constructI_2(int fn, int rt,  ast* node ,int rs  );
int constructI_3(int fn, int rs , ast* node );
int constructI_4(int fn, int rt , ast* node );
int constructJ_1(int fn, ast* node );
ast* newinn(int n );
ast* newini(char* id );
ast* newinhl(hilo* hl );
int checkresult();