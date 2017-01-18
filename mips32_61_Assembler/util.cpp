#include "mips32New.h"
#include "mips32New.tab.h"
#include <fstream>
#include <stdarg.h>

#include <iostream> 
#include <sstream> 
#include <fstream> 
#include <string> 
#include <vector>
#include <string.h> 
using namespace std;
vector<string> vtext,vdata;
//32位机器指令
InsNode *g_curMacIns;
//输入文件与输出文件;
FILE *IFile;


InsNode*g_macLinkTab;
int numOfOder = 0;
void setParameter()
{
	yylineno = 1;
	g_curMacIns = new InsNode();
}

//将当前指令机器码，写入机器码链表中;
bool ConstructMacLinkTab( int curComNo )
{
	numOfOder++;
	InsNode * temp = g_macLinkTab;
	g_curMacIns->insAddr = curComNo ;
	if( g_macLinkTab == NULL )
	{
		g_macLinkTab = g_curMacIns;
		g_macLinkTab->next = NULL;
		g_curMacIns = new  InsNode();
		if( g_curMacIns == NULL )
			cout<<"Memery error,new InsNode failed!";
		return true;
	}
	while( temp->next != NULL)
		temp = temp->next;

	temp->next = g_curMacIns;

	g_curMacIns = new  InsNode();
	if( g_curMacIns == NULL )
		cout<<"dddddddddddddddddddddddddddddddddddddddd";
	return true;
}


int cmpsymbol( const void *a, const void *b )
{
	return (((symbol*)a)->addr  -  ((symbol*)b)->addr) ;
}


void ComHex(char *com,int size,char* dest)
{
	memset(dest,0,10);
	int temp = 0;
	int base = 1;
	for( int i = 0 ; i < size / 4 ; i++)
	{
		temp = 0;
		base = 1;
		for( int j = 0; j<4; j++)
		{
			if( com[ j + i * 4 ] & 1 )
			{
				temp +=  base;
			}
			base *= 2 ;
		}
		dest[i] = ( (temp > 9) ? temp-10+'A' : temp + '0' ) ;
	}
}

bool intToHexstr(int src, char* dest )
{
	int b = 0;
	for( int i = 7; i >= 0; i -- ){
		b = src % 16;
		src /= 16 ;
		dest[i] =  ( (b > 9) ? b-10+'A' : b + '0' ) ;
	}
	dest[8] = 0;
	return true;
}

bool writeProgCoe()	
{
	const char *outFile[] = { "memblk0.coe","memblk1.coe","memblk2.coe","memblk3.coe"};
	FILE*	 progCoeFile[4] ;
	ofstream progBinFile("progbin",ios::out | ios::binary );
	 progCoeFile[0] = fopen("memblk0.coe","w");
	 progCoeFile[1] = fopen("memblk1.coe","w");
	 progCoeFile[2] = fopen("memblk2.coe","w");
	 progCoeFile[3] = fopen("memblk3.coe","w");
	 for( int i = 0; i < 4; i++ ){
	 	fprintf(progCoeFile[i],"MEMORY_INITIALIZATION_RADIX=16;\n");
	 	fprintf(progCoeFile[i],"MEMORY_INITIALIZATION_VECTOR=\n" );
	 }
	// backFillSeg();

	int curAddr = 0;
	char tempHex[10];
	InsNode *curIns = g_macLinkTab;
	
#ifdef DEBUG
	for( int i = 0; i < 4; i++)	fprintf(progCoeFile[i],"%d:",curAddr );
#endif
	//在程序地址0写入跳转指令，跳转至地址为4K处
	fprintf(progCoeFile[0],"00,\n");fprintf(progCoeFile[1],"04,\n");fprintf(progCoeFile[2],"00,\n");fprintf(progCoeFile[3],"08,\n");
	unsigned int bincom = 0x08000400;
	progBinFile.write( (char*)&bincom,4);
	curAddr +=4;

	//写数据段；
	qsort( symtab, curSymNum,sizeof( symbol ), cmpsymbol );
	while( curAddr < beginOfData )
	{
	#ifdef DEBUG
		for( int i = 0; i < 4; i++)	fprintf(progCoeFile[i],"%d:",curAddr );
	#endif
		for( int i = 0; i < 4; i++)	fprintf(progCoeFile[i],"00,\n" );
		bincom = 0;
		progBinFile.write( (char*)&bincom,4);
		curAddr+=4;
	}
	//遍历变量表
 	for( int j = 0; j < curSymNum; j++)
	{
		if( symtab[j] .flag == 1)
			continue;

 		while( curAddr < symtab[j].addr   )
 		{
 #ifdef DEBUG
 			for( int i = 0; i < 4; i++)	fprintf(progCoeFile[i],"%d:",curAddr );
 #endif
 			for( int i = 0; i < 4; i++)	fprintf(progCoeFile[i],"00,\n" );
 			bincom = 0;
 			progBinFile.write( (char*)&bincom,4);
 			curAddr+=4;
 		}
 		char t_str[9];
 		intToHexstr( symtab[j].Val[0] , t_str);
 #ifdef DEBUG
 		for( int i = 0; i < 4; i++)	fprintf(progCoeFile[i],"%d:",curAddr );
 #endif
 		for( int i = 0; i < 4; i++ )
 		{
 			fprintf( progCoeFile[3-i],"%c%c",t_str[i *2 ],t_str[i *2 +1] );
 			fprintf( progCoeFile[3-i], ",\n");
 		}
 		progBinFile.write((char*)&(symtab[j].Val[0]),4);
 		curAddr+=4;
 	}
	//填充数据段空白；
 	while( curAddr < beginOfCode  )
 	{
 #ifdef DEBUG
 		for( int i = 0; i < 4; i++)	fprintf(progCoeFile[i],"%d:",curAddr );
 #endif
 		for( int i = 0; i < 4; i++)	{fprintf(progCoeFile[i],"00,\n" ); fflush(progCoeFile[i]);}
 		bincom = 0;
 		progBinFile.write( (char*)&bincom,4);
 		curAddr+=4;
 	}
	
 	/************************************************************************/
 	/* 以上部分写到4K位置，以下开始写代码段；                                                   */
 	/************************************************************************/
	int k = 0;
 	while ( k++, curIns != NULL)
 	{
 		ComHex ( curIns->Com,32,tempHex );
		//填充多个代码段之间空间
 		while( curAddr <curIns->insAddr )
 		{
 #ifdef DEBUG
 			for( int i = 0; i < 4; i++)	fprintf(progCoeFile[i],"%d:",curAddr );
 #endif
 			for( int i = 0; i < 4; i++)	fprintf(progCoeFile[i],"00,\n" );
 			bincom = 0;
 			progBinFile.write( (char*)&bincom,4);
 			curAddr += 4;
 		}
 #ifdef DEBUG
 		for( int i = 0; i < 4; i++)	fprintf(progCoeFile[i],"%d:",curAddr );
 #endif
 		for( int i = 0; i < 4; i++ )
 		{
 			fprintf( progCoeFile[i],"%c%c",tempHex[i *2 +1],tempHex[i *2 ] );
 			unsigned char c = (( tempHex[i *2 +1] < 'A' )? tempHex[i *2 +1] - '0' : tempHex[i *2 +1] -'A' +10);
 			c = c<<4;
 			c = c  | ( (tempHex[i *2 ] < 'A' )? tempHex[i *2] - '0' : tempHex[i *2 ] -'A'+10 );
 			progBinFile.write( (char*)(&c) ,1);
 			if( curIns->next != NULL )
 				fprintf( progCoeFile[i], ",\n");
 			else
 				fprintf(progCoeFile[i], ";\n");
 			//fflush(progCoeFile[3-i]);
 		}
 		curIns = curIns->next;
 		curAddr +=4;
 	}
 	for( int i = 0; i < 4; i++ )
 	{
 		fflush(progCoeFile[i]);
 		fclose(progCoeFile[i]);
 	}
 	progBinFile.close();
	return true;
}

bool writeProgCoe1()	
{
// 	FILE*	 ProgFile = fopen("prog.coe", "w" ) ;
// 	fprintf(ProgFile,"MEMORY_INITIALIZATION_RADIX=16;\n");
// 	fprintf(ProgFile,"MEMORY_INITIALIZATION_VECTOR=\n");

// 	backFillSeg();
// 	char tempHex[10];
// 	InsNode *curIns = g_macLinkTab;
// 	while ( curIns != NULL)
// 	{
// 		ComHex ( curIns->Com,32,tempHex );
// #ifdef DEBUG
// 		fprintf( ProgFile, "%d: %d,",curIns->insAddr + 0x1000,curIns->insAddr /4 +1);
// #endif
// 		for( int i = 7; i >= 0; i-- ){
// 			fprintf(ProgFile,"%c",tempHex[i]);
// 		}
// 		if( curIns->next != NULL )
// 			fprintf( ProgFile, ",\n");
// 		else
// 			fprintf(ProgFile, ";\n");
// 		curIns = curIns->next;
// 	}
// 	fflush(ProgFile);
// 	fclose(ProgFile);
	return true;
}

bool writeDataCoe(){
	// FILE* DataFile = fopen("dmem32.coe","w");

	// fprintf(DataFile,"MEMORY_INITIALIZATION_RADIX=16;\n");
	// fprintf(DataFile,"MEMORY_INITIALIZATION_VECTOR=\n");

	// char tempHex[10];
	// qsort( symtab, curSymNum,sizeof( symbol* ), cmpsymbol );
	// int t_curaddr = 0;
	// for( int i = 0; i < curSymNum; i++){
	// 	while( t_curaddr < symtab[i] ->varAddr )
	// 	{
	// 		fprintf(DataFile,"00000000,\n");
	// 		t_curaddr+=4;
	// 	}
	// 	char t_str[9];
	// 	intToHexstr( symtab[i] ->varVal ,t_str);
	// 	if( i == curSymNum - 1)
	// 		fprintf(DataFile,"%s;\n",t_str );
	// 	else
	// 		fprintf(DataFile,"%s,\n",t_str );
	// 	t_curaddr+=4;
	// }

	// fflush(DataFile);
	// fclose(DataFile);	
	return true;
}

int getNextToken()
{
	// int resState = 0;
	// while( ( resState = yylex() ) != T_ERR && resState )
	// {
	// 	cout<<"("<<resState<<")";
	// 	return resState;
	// }
	// if (  resState == T_ERR )
	// 	return 0;
	// printf("lexical anylyze complete.\n" );
	return 0;
}
void testlex()
{
	// while( getNextToken() )
	// {
	// 	cout<<yylineno<<" "
	// 		<<yytext<<" "
	// 		<<curSymNum<<" "
	// 		<<curSymNum<<" "
	// 		<<"curComNo:"<<curComNo<<" "
	// 		<<tokenNumVal<<" "<<endl;
	// }
	// for( int i = 0; i< curSymNum; i++)
	// {
	// 	cout<<symtab[i]->name<<endl;
	// }
	// for( int i = 0; i< curSymNum; i++)
	// {
	// 	cout<<symtab[i]->name<<endl;
	// }

}


// bool backFillSeg()
// {
// 	for( int i = 0; i< curSymNum; i++)
// 	{
// 		ref* temp = symtab[i]->refList;
// 		while( temp != NULL )
// 		{
// 			if( temp->comType == 0)
// 			{
// 				int val = (symtab[i]->segComAddr - temp->ins->insAddr -4) >>2;
// 				for( int i = 0; i <= 15 ; i++){
// 					temp->ins->Com[i] = 1 & (val);
// 					val = val>>1;
// 				}
// 			}else if( temp->comType == 1)
// 			{
// 				int val = (symtab[i]->segComAddr ) >>2;
// 				for( int i = 0; i <= 25 ; i++){
// 					temp->ins->Com[i] = 1 & (val);
// 					val = val>>1;
// 				}
// 			}
// 			temp = temp->next;
// 		}

// 	}
// 	return true;
// }
int HEXNUM1ToInt(const char * strHex)
{
	int beginPos = ((strHex[0] == '-') ? 1 : 0) ;
	int len = strlen(strHex);

	char * strCpy = (char*)malloc(sizeof(char) * len + 1);
	strcpy(strCpy,strHex);
	int res = 0;
	int base = 1;
	for( int i = len-2; i >= beginPos; i-- ){
		strCpy[i] = tolower( strCpy[i]);
		res += base * ( (strCpy[i] <='9' && strCpy[i] >= '0') ? strCpy[i] - '0' : strCpy[i] - 'a' + 10) ;
		base *= 16;
	}
	//free(strCpy);
	return ((strHex[0] == '-') ? -res : res) ;
}
int HEXNUM2ToInt(const char * strHex)
{
	int beginPos = ((strHex[0] == '-') ? 3 : 2) ;
	int len = strlen(strHex);

	char * strCpy = (char*)malloc(sizeof(char) * len + 1);
	strcpy(strCpy,strHex);
	int res = 0;
	int base = 1;
	for( int i = len-1; i >= beginPos; i-- ){
		strCpy[i] = tolower( strCpy[i]);
		res += base * ( (strCpy[i] <='9' && strCpy[i] >= '0') ? strCpy[i] - '0' : strCpy[i] - 'a' + 10) ;
		base *= 16;
	}
	//free(strCpy);
	return ((strHex[0] == '-') ? -res : res) ;
}

struct symbol* lookupSym( char* symName , int type)
{
	for( int i = 0; i< curSymNum ; i++)
	{
		if( strcmp( symName,symtab[i].name ) == 0) 
		{
			if( symtab[i].refHead == NULL )
				return &symtab[i];
			else
			{
				ref *newref = new ref();
				newref->ins = g_curMacIns;
				newref->comType = type;
				newref->next = symtab[i].refHead;
				symtab[i].refHead = newref;
				return NULL;
			}
		}
	}
	symtab[ curSymNum ] . name = new char[ strlen(symName ) + 1];
	strcpy( symtab[ curSymNum ] . name, symName );
	ref *newref = new ref();
	newref->ins = g_curMacIns;
	newref->comType = type;
	newref->next = symtab[curSymNum].refHead;
	symtab[curSymNum++].refHead = newref;
	return NULL ;
}
struct symbol* lookUpVar( char* varName )
{
	for( int i = 0; i< curSymNum ; i++)
		if( strcmp( varName,symtab[i].name ) == 0) 
			return &symtab[i];
	return NULL;
}
struct symbol* lookUpSeg( char* varName ,int comType)
{
	// for( int i = 0; i< curSymNum ; i++)
	// 	if( strcmp( varName , symtab[ i]->name ) == 0) 
	// 	{
	// 		if( symtab[i]->segComAddr == -1 )
	// 		{
	// 			ref *newref = new ref();
	// 			newref->ins = g_curMacIns;
	// 			newref->comNo = curComNo ;
	// 			newref->comType = comType;
	// 			newref->next = symtab[i]->refList;
	// 			symtab[i]->refList = newref;
	// 		}
	// 		else 
	// 			return symtab[i];
	// 	}
	// 	symbol * newseg = new symbol();
	// 	newseg->name  = new char[strlen(varName)];
	// 	strcpy(newseg->name ,varName );
	// 	symtab[curSymNum] = newseg; 
	// 	ref *newref = new ref();
	// 	newref->ins = g_curMacIns;
	// 	newref->comNo = curComNo ;
	// 	newref->comType = comType ;
	// 	newref->next = symtab[curSymNum]->refList ;
	// 	symtab[curSymNum++]->refList = newref ;
		return NULL;
}

int addsymbol( char* name, int curAddr, int f ,int varVal,int vartype)
{
	//是否越界
	if( curSymNum >= NHASH )
		return 0;
	//符号是否重复
	for( int i = 0; i < curSymNum; i++){
		if( strcmp( name, symtab[i].name ) == 0){
			//标号重复,是否进行回填
			if( symtab[i].addr != -1 )
			{
				cerr<<"symbol repeat! lineno:"<<yylineno<<endl;
				return -1;
			}
			else
			{
				symtab[i].addr = curAddr;
				symtab[i].flag = f;
				if( f == 0 )
				{
					symtab[i].Val = new int[10];
					symtab[i].Val[0] = varVal;
					symtab[i].numOfVal = 1;
				}
				ref * curref = symtab[i].refHead;
				while( curref != NULL )
				{
					int t_val = 0;
					switch(curref->comType )
					{
						case T_ICOM:
							t_val = symtab[i].addr - curref->ins->insAddr - 1 ;
							t_val = t_val>>2;
							for( int j = 0; j <= 15; j++)
							{
								(*(curref->ins))[j] = 1 & (t_val);
								t_val = t_val>>1;
							}
						break;
						case T_LWICOM:
							t_val = symtab[i].addr  ;
							for( int j = 0; j <= 15; j++)
							{
								(*(curref->ins))[j] = 1 & (t_val);
								t_val = t_val>>1;
							}
						break;
						case T_BICOM:
							t_val = symtab[i].addr >> 2 ;
							for( int j = 0; j <= 15; j++)
							{
								(*(curref->ins))[j] = 1 & (t_val);
								t_val = t_val>>1;
							}
						break;
						case T_JCOM:
							t_val = symtab[i].addr >> 2 ;
							for( int j = 0; j < 26; j++)
							{
								(*(curref->ins))[j] = 1 & (t_val);
								t_val = t_val>>1;
							}
						break;
						default:
						;
					}
					curref = curref->next;
				}
				//清空引用链表
				symtab[i].refHead = NULL;
				return 0;
			}
		}
	}
	//新建符号
	symbol* newseg = new symbol();
	newseg->flag = f;
	newseg->name = new char[strlen(name)+1];strcpy( newseg->name , name);
	newseg->addr = curAddr;
	//判断是否为变量
	if( f == 0 )
	{
		newseg->Val = new int[10];
		newseg->Val[0] = varVal;
		newseg->numOfVal = 1;
		newseg->vartype = vartype;
	}
	symtab[curSymNum++] = *newseg;
	return 0;
}   

int prefunc(const char* inf , const  char *outf) 
{ 
	ifstream fin(inf, ios::in); 
	ofstream fout(outf, ios::out); 
	char line[1024]={0}; 
	int flag=0;
	int i = 0;
	while(fin.getline(line, sizeof(line))) 
	{ 
		i = 0;
		while( line[i] == ' ' || line [i] == '\t' )
			i++;
		if (strncmp(line+i,".text",5)==0 || strncmp(line+i,".TEXT",5) ==0  )
			flag=1;
		if (strncmp(line+i,".data",5)==0 || strncmp(line+i,".DATA",5)==0)
			flag=2;
		string temp=line;
		if (flag==1)
			vtext.push_back(temp);
		if (flag==2)
			vdata.push_back(temp);
	} 
	for (vector<string>::iterator it=vdata.begin();it!=vdata.end();it++)
		fout<<*it<<"\n";
	for (vector<string>::iterator it=vtext.begin();it!=vtext.end();it++)
		fout<<*it<<"\n";
	fin.clear(); 
	fin.close(); 
	fout.clear();
	fout.close();
	return 0;
} 
int checkresult()
{
	qsort( symtab, curSymNum,sizeof( symbol ), cmpsymbol );
	if( symtab[0].addr == -1 )
		return -1;
	return 0;
}
void yyerror(const char *s, ...)
{
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "%d: error: ", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
  syntaxOK = 0;
}
