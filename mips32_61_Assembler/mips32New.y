%{
#  include <stdio.h>
#  include <stdlib.h>
#  include "mips32New.h"

bool syntaxOK = 1;
%}

%union {
  struct ast *a;
  
  struct symbol *s;		/* which symbol */
  struct idnum  *in ;
  //symlist *sl;
  char *str;
  struct hilo* hl;   /*支持hilo伪指令*/
  int d;
  int fn;			  /* which INS*/
  char* kw;     /*KeyWord*/
};

/* declare tokens */

%token <kw> T_DATA T_CODE T_WORD T_BYTE T_HALF
%token <d> T_NUM T_REG T_BREG
%token <str> T_IDNAME 
%token <hl> T_HILO 
%token <fn> T_NOP T_RCOM T_RSCOM T_RMDCOM T_RMJCOM T_RRCOM T_ICOM T_LWICOM T_BICOM T_SICOM T_JCOM
%token EOL ':' ',' T_ERR

//%right %nonassoc 
%left T_DATA T_CODE EOL error
%type <str> N_VARID 
%type <a>  N_DATASEG N_CODESEG N_DATAHEAD N_CODEHEAD N_NUM_ID N_COM N_ORDER N_ORDERS N_SUBSEGID  N_EOLS N_VARS N_VAR     

%start N_PRO
%%

N_PRO: /* nothing */          { ; }
     |  N_PRO N_CODESEG       { printf("\nSyntax anylysis CodeSegment successful! \n\n");  }
     |  N_PRO N_DATASEG       { printf("\nSyntax anylysis DataSegment successful! \n\n");  }
     |  N_PRO error EOL       { yyerrok; syntaxOK = 0; cerr<<"\nSyntex error,lineNo: "<<yylineno<<endl; }
     ;
N_DATASEG:  N_DATAHEAD N_VARS  { $$ = NULL; printf("\n/*****Databody Found!*****/\n");}
    ;
N_DATAHEAD: T_DATA T_NUM EOL   { $$ = NULL; curDataAddr = $2; 
                                printf("\n/*****Datahead Found!*****/%d\n ",curDataAddr);}
    | T_DATA  EOL              { $$ = NULL; curDataAddr = 0;  
                                  printf("\n/*****Datahead Found!*****/%d\n ",curDataAddr);}
    ;
N_VARS:/* nothing */             { $$ = NULL; }
    |  N_VAR N_VARS               { $$ = NULL; }
    ;
N_VAR: N_VARID N_EOLS T_WORD T_NUM EOL { 
                                   $$ = NULL; 
                                   addsymbol($1, curDataPos + beginOfData + curDataAddr ,0,$4,2);
                                   curDataPos += 4 ;
                                 }
    | N_VARID N_EOLS T_BYTE T_NUM EOL { 
                                   $$ = NULL; 
                                   addsymbol($1, curDataPos + beginOfData + curDataAddr , 0 ,$4,0 );
                                   curDataPos += 1 ;
                                 }
     | N_VARID N_EOLS T_HALF T_NUM EOL { 
                                   $$ = NULL; 
                                   addsymbol($1, curDataPos + beginOfData + curDataAddr ,0,$4,1 );
                                   curDataPos += 2 ;
                                 }                             
    | EOL                          { $$ = NULL; }
N_EOLS:                          { $$ = NULL; }
    | N_EOLS EOL                   { $$ = NULL; }
    ;
N_VARID: T_IDNAME                  { $$ = $1; }
    | T_IDNAME ':'                 { $$ = $1; }

N_CODESEG: N_CODEHEAD N_ORDERS     { $$ = NULL; printf("\n/*****Codebody Found!*****/\n");}
    ;
N_CODEHEAD:  T_CODE T_NUM EOL      { $$ = NULL; curCodeAddr = $2; 
                                      printf("\n/*****Codehead Found!*****/\n ");}
    | T_CODE EOL                   { $$ = NULL; curCodeAddr = 0; 
                                      printf("\n/*****Codehead Found!*****/\n ");}
    ;
N_ORDERS:                          { $$ = NULL; }
    | N_ORDER N_ORDERS             { $$ = NULL; }
    | N_SUBSEGID N_ORDER N_ORDERS  { $$ = NULL; }
    ;
N_SUBSEGID: T_IDNAME ':'           { addsymbol($1, curComNo*4 + beginOfCode + curCodeAddr , 1 , 0 ); }
    ;
N_ORDER: N_COM EOL                 { $$ = NULL; }
   | EOL                           { $$ = NULL; }
   | N_COM error EOL               { yyerrok; syntaxOK = 0; cerr<<"\nSyntax  error,lineNo: "<<yylineno<<endl; }
    ;
N_COM: T_NOP                              { $$ = NULL; constructNop ( $1 ); }
    | T_RCOM T_REG ',' T_REG ',' T_REG    { $$ = NULL; constructR_1 ( $1,$2,$4,$6 );}
    | T_RSCOM T_REG ',' T_REG ',' T_NUM   { $$ = NULL; constructR_2 ( $1,$2,$4,$6 );}
    | T_RMDCOM T_REG ',' T_REG            { $$ = NULL; constructR_3 ( $1,$2,$4 );}
    | T_RMJCOM T_REG                      { $$ = NULL; constructR_4 ( $1,$2 ); }
    | T_RRCOM                             { $$ = NULL; constructR_5 ( $1 );}
    | T_ICOM T_REG ',' T_REG ','  N_NUM_ID{ $$ = NULL; constructI_1 ( $1,$2,$4,$6 );}
    | T_LWICOM T_REG ','N_NUM_ID T_BREG   { $$ = NULL; constructI_2 ( $1,$2,$4,$5 );}
    | T_BICOM T_REG ',' N_NUM_ID          { $$ = NULL; constructI_3 ( $1,$2,$4 );}
    | T_SICOM T_REG ',' N_NUM_ID          { $$ = NULL; constructI_4 ( $1,$2,$4 );}
    | T_JCOM  N_NUM_ID                    { $$ = NULL; constructJ_1 ( $1,$2 ); }
    ;
N_NUM_ID: T_NUM                           { $$ = newinn($1); }
        | T_IDNAME                        { $$ = newini($1); }
        | T_HILO                          { $$ = newinhl($1); }
%%

/* 
  T_RCOM,   //R格式指令助记符    ADD ADDU SUB SUBU  AND NOR OR XOR  SLT SLTU SRAV SLLV SRLV
  T_RSCOM,  //SLL |SRA |SRL | MFC0 | MTC0
  T_RMDCOM,  // MULT | MULTU | DIV | DIVU | JALR  { return T_RMDCOM; }
  T_RMJCOM , //MFHI | MFLO | MTHI | MTLO | JR
  T_RRCOM,  // BREAK | SYSCALL | ERET | TLBP | TLBR | TLBWI | TLBWR

  T_ICOM,   //addi ADDIU ANDI BEQ BNE  ORI SLTI SLTIU XORI
  T_LWICOM, //LW SW
  T_BICOM,  //BICOM(bgez|bgtz|blez|bltz|bgezal|bltzal)
  T_SICOM,  //LUI
  T_JCOM,   //J jal 

  T_ERR,//error token,failed;
  stmt: IF exp THEN list           { $$ = newflow('I', $2, $4, NULL); }
    | IF exp THEN list ELSE list  { $$ = newflow('I', $2, $4, $6); }
    | WHILE exp DO list           { $$ = newflow('W', $2, $4, NULL); }
    | exp
    ;
*/

