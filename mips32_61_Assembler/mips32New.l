/*  mips32_61 assembler lex.l
    author:JackRen
*/

%option noyywrap nodefault yylineno case-insensitive

%x COMMENT
%{
	
	# include "mips32New.tab.h"
	# include "mips32New.h"
  #include "stdio.h"
  #include "stdlib.h"
  #include "ctype.h"
  #ifndef LINUX
    #include "io.h"
  #endif
  int curSymNum = 0;
	int curComNo = -1;
	int curDataPos = -1;

	int beginOfData = 0x0400;//1k
	int beginOfCode = 0x1000;//1k
	int curDataAddr = 0;//1k
	int curCodeAddr = 0;//4k

	int curNumOfVar = 0;
	int curNumOfSeg = 0;

	struct symbol symtab[NHASH];
	int alphaToRegNum(char * text);
	//|$at|$v[0-1{1}]|$a[0-4]{1}|$t[0-9]{1} |$s[0-7]{1}|$k[0-1]{1}|$gp|$sp|$s8|$fp|$ra
%}

HEXNUM1  [-+]?[0-9A-Fa-f]*H{1} 
HEXNUM2  [-+]?0x[0-9A-Fa-f]*
INTEGER  [-+]?[1-9][0-9]* 
ID [$]?[a-zA-Z][a-zA-Z0-9_]*
SPACE [ \t\r]
ALPHAREG   ($zero|$at|$v[0-1{1}]|$a[0-3]{1}|$t[0-9]{1}|$s[0-7]{1}|$k[0-1]{1}|$gp|$sp|$s8|$fp|$ra)


%%
"."DATA      { curDataPos = 0; curComNo == -1 ; printf( ".DATA ");    return T_DATA; }
"."TEXT      { curComNo = 0;   printf( ".CODE ");    return T_CODE; }
"."WORD |
"."4byte     { printf( ".WORD ");  return T_WORD; }
"."byte     { printf( ".byte ");  return T_BYTE; }
"."half     { printf( ".half ");  return T_HALF; }
\n           { printf( "\nlineno:%d",yylineno);  return EOL; }

{HEXNUM1}   { yylval.d = HEXNUM1ToInt(yytext); printf( "NUM(%d) ",yylval.d ); return T_NUM;}
{HEXNUM2}   { yylval.d = HEXNUM2ToInt(yytext); printf( "NUM(%d) ",yylval.d ); return T_NUM;}
{INTEGER} |
(0)+        { yylval.d = atoi( yytext ); printf( "NUM(%d) ",yylval.d ); return T_NUM;}
           
":"       { printf( ": "); return ':'; }
","       { printf( ", "); return ','; }


(";"|"#")   { /*注释处理*/BEGIN(COMMENT); }
<COMMENT>\n { BEGIN(INITIAL); yyless(0); /*printf( "T_COMMENT ");*/}
<COMMENT>.
<COMMENT><<EOF>>  { printf("%d: Unterminated comment\n",yylineno); 
                    cerr<<yylineno<<":Unterminated comment\n";return T_ERR;
                  /*(";"|"#")(.*)/\n  { printf( "T_COMMENT ");} */
                  }

{ALPHAREG}          { yylval.d = alphaToRegNum(yytext); printf( "T_REG "); return T_REG; }
$[0-9][0-9]?        { yylval.d = atoi(yytext+1); printf( "T_REG ");return T_REG; }
"("{ALPHAREG}")"    { yytext[strlen(yytext)-1] = 0; yylval.d = alphaToRegNum(yytext + 1 ); printf( "T_BREG ");return T_BREG; }
"("$[0-9][0-9]?")"  { yytext[strlen(yytext)-1] = 0; yylval.d = atoi(yytext+2); printf( "T_BREG ");return T_BREG; }

NOP                 { curComNo++; yylval.fn = 0; printf( "T_NOP "); return T_NOP; }

ADD                 { curComNo++; yylval.fn = 0; printf( "T_RCOM ");return T_RCOM; }
ADDU                { curComNo++; yylval.fn = 1; printf( "T_RCOM ");return T_RCOM; }
SUB                 { curComNo++; yylval.fn = 2; printf( "T_RCOM ");return T_RCOM; } 
SUBU                { curComNo++; yylval.fn = 3; printf( "T_RCOM ");return T_RCOM; } 
AND                 { curComNo++; yylval.fn = 4; printf( "T_RCOM ");return T_RCOM; }
OR                  { curComNo++; yylval.fn = 5; printf( "T_RCOM ");return T_RCOM; }
XOR                 { curComNo++; yylval.fn = 6; printf( "T_RCOM ");return T_RCOM; } 
NOR                 { curComNo++; yylval.fn = 7; printf( "T_RCOM ");return T_RCOM; }
SLT                 { curComNo++; yylval.fn = 8; printf( "T_RCOM ");return T_RCOM; }
SLTU                { curComNo++; yylval.fn = 9; printf( "T_RCOM ");return T_RCOM; }
SLLV                { curComNo++; yylval.fn = 10;printf( "T_RCOM ");return T_RCOM; }
SRAV                { curComNo++; yylval.fn = 11;printf( "T_RCOM ");return T_RCOM; }
SRLV                { curComNo++; yylval.fn = 12;printf( "T_RCOM ");return T_RCOM; }



SLL                 { curComNo++; yylval.fn = 0;printf( "T_RSCOM ");return T_RSCOM; }
SRA                 { curComNo++; yylval.fn = 1;printf( "T_RSCOM ");return T_RSCOM; }
SRL                 { curComNo++; yylval.fn = 2;printf( "T_RSCOM ");return T_RSCOM; }
MFC0                { curComNo++; yylval.fn = 3;printf( "T_RSCOM ");return T_RSCOM; } 
MTC0                { curComNo++; yylval.fn = 4;printf( "T_RSCOM ");return T_RSCOM; }

MULT                { curComNo++; yylval.fn = 0;printf( "T_RMDCOM ");return T_RMDCOM; } 
MULTU               { curComNo++; yylval.fn = 1;printf( "T_RMDCOM ");return T_RMDCOM; }  
DIV                 { curComNo++; yylval.fn = 2;printf( "T_RMDCOM ");return T_RMDCOM; } 
DIVU                { curComNo++; yylval.fn = 3;printf( "T_RMDCOM ");return T_RMDCOM; } 
JALR                { curComNo++; yylval.fn = 4;printf( "T_RMDCOM ");return T_RMDCOM; }


MFHI                { curComNo++; yylval.fn = 0;printf( "T_RMJCOM ");return T_RMJCOM; } 
MFLO                { curComNo++; yylval.fn = 1;printf( "T_RMJCOM ");return T_RMJCOM; }  
MTHI                { curComNo++; yylval.fn = 2;printf( "T_RMJCOM ");return T_RMJCOM; }  
MTLO                { curComNo++; yylval.fn = 3;printf( "T_RMJCOM ");return T_RMJCOM; }  
JR                  { curComNo++; yylval.fn = 4;printf( "T_RMJCOM ");return T_RMJCOM; }

BREAK                { curComNo++; yylval.fn = 0; printf( "T_RRCOM ");return T_RRCOM;} 
SYSCALL              { curComNo++; yylval.fn = 1; printf( "T_RRCOM ");return T_RRCOM;} 
ERET                 { curComNo++; yylval.fn = 2; printf( "T_RRCOM ");return T_RRCOM;} 
TLBP                 { curComNo++; yylval.fn = 3; printf( "T_RRCOM ");return T_RRCOM;} 
TLBR                 { curComNo++; yylval.fn = 4; printf( "T_RRCOM ");return T_RRCOM;} 
TLBWI                { curComNo++; yylval.fn = 5; printf( "T_RRCOM ");return T_RRCOM;} 
TLBWR                { curComNo++; yylval.fn = 6; printf( "T_RRCOM ");return T_RRCOM;}

ADDI                { curComNo++; yylval.fn = 0; printf( "T_ICOM ");return T_ICOM;}
ADDIU               { curComNo++; yylval.fn = 1; printf( "T_ICOM ");return T_ICOM;} 
ANDI                { curComNo++; yylval.fn = 2; printf( "T_ICOM ");return T_ICOM;}
ORI                 { curComNo++; yylval.fn = 3; printf( "T_ICOM ");return T_ICOM;} 
XORI                { curComNo++; yylval.fn = 4; printf( "T_ICOM ");return T_ICOM;}
SLTI                { curComNo++; yylval.fn = 5; printf( "T_ICOM ");return T_ICOM;}
SLTIU               { curComNo++; yylval.fn = 6; printf( "T_ICOM ");return T_ICOM;} 
BEQ                 { curComNo++; yylval.fn = 7; printf( "T_ICOM ");return T_ICOM;} 
BNE                 { curComNo++; yylval.fn = 8; printf( "T_ICOM ");return T_ICOM;} 

LW                  { curComNo++; yylval.fn = 0;printf( "T_LWICOM ");return T_LWICOM;} 
SW                  { curComNo++; yylval.fn = 1;printf( "T_LWICOM ");return T_LWICOM;}
LB                  { curComNo++; yylval.fn = 2;printf( "T_LWICOM ");return T_LWICOM;}
LBU                 { curComNo++; yylval.fn = 3;printf( "T_LWICOM ");return T_LWICOM;}
LH                  { curComNo++; yylval.fn = 4;printf( "T_LWICOM ");return T_LWICOM;}
LHU                 { curComNo++; yylval.fn = 5;printf( "T_LWICOM ");return T_LWICOM;}
SB                  { curComNo++; yylval.fn = 6;printf( "T_LWICOM ");return T_LWICOM;}
SH                  { curComNo++; yylval.fn = 7;printf( "T_LWICOM ");return T_LWICOM;}

BGEZ            { curComNo++; yylval.fn = 0;printf( "T_BICOM ");return T_BICOM;}
BGTZ            { curComNo++; yylval.fn = 1;printf( "T_BICOM ");return T_BICOM;}
BLEZ            { curComNo++; yylval.fn = 2;printf( "T_BICOM ");return T_BICOM;}
BLTZ            { curComNo++; yylval.fn = 3;printf( "T_BICOM ");return T_BICOM;}
BGEZAL          { curComNo++; yylval.fn = 4;printf( "T_BICOM ");return T_BICOM;}
BLTZAL          { curComNo++; yylval.fn = 5;printf( "T_BICOM ");return T_BICOM;}

LUI             { curComNo++; yylval.fn = 0;printf( "T_SICOM ");return T_SICOM;}
J               { curComNo++; yylval.fn = 0;printf( "T_JCOM ");return T_JCOM;}
JAL             { curComNo++; yylval.fn = 1;printf( "T_JCOM ");return T_JCOM;}


%hi"("{ID}")"          { 
                        yylval.hl = new hilo();
                        yylval.hl->name = new char[strlen(yytext)+1];
                        yytext[strlen(yytext)-1] = 0;
                        strcpy( yylval.hl->name, yytext+4 );
                        yylval.hl->ishi = 1;
                         printf( "lable(hi:%s) ",yylval.hl->name);  return T_HILO; 
                       }
%lo"("{ID}")"         { 
                        yylval.hl = new hilo();
                        yylval.hl->name = new char[strlen(yytext)+1];
                        yytext[strlen(yytext)-1] = 0;
                        strcpy( yylval.hl->name, yytext+4 );
                        yylval.hl->ishi = 1;
                         printf( "lable(lo:%s) ",yylval.hl->name);  return T_HILO; 
                       }
{ID}/{SPACE}*":"  { 
                        yylval.str = new char[strlen(yytext) + 1];
                        strcpy( yylval.str , yytext );
                        //cerr<<"There is a Lexical error,lineNo: "<<yylineno <<" errToken: "<<yytext<<endl;
                        printf( "lable(%s) ",yylval.str);  
                        return T_IDNAME;
                      }
{ID}              { 
                    yylval.str = new char[strlen(yytext) + 1];
                    strcpy( yylval.str, yytext );
                    printf( "IDNAME(%s) ",yytext); 
                    return T_IDNAME;
                  }
{SPACE}         { printf( " ");/*什么也不做,滤掉白字符和\t*/}
.               { cerr<<"There is a Lexical error,lineNo: "<<yylineno<<" errToken: "<<yytext<<endl;/*return T_ERR;*/ }
%%


int alphaToRegNum(char * text)
{
  if( text[1] == 'z'){
    return 0;
  }else if(text[2] == 't'){
    return 1;
  }else if(text[1] == 'v'){
    return 2 + text[2] - '0';
  }else if(text[1] == 'a'){
    return 4 + text[2] - '0';
  }else if(text[1] == 't' && text[2] <= '7'){
    return 8 + text[2] - '0';
  }else if(text[1] == 's' && text[2] <= '7' && text[2] >= '0'){
    return 16 + text[2] - '0';
  }else if(text[1] == 't' && text[2] >= '8'){
    return 24 + text[2] - '8';
  }else if(text[1] == 'k' ){
    return 26 + text[2] - '0';
  }else if(text[1] == 'g' ){
    return 28;
  }else if(text[1] == 's' && text[2] == 'p' ){
    return 29;
  }else if((text[1] == 's' && text[2] == '8' )|| text[1] == 'f'){
    return 30;
  }else if(text[1] == 'r' && text[2] == 'a' ){
    return 31;
  }
  return -1;
}