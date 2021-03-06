/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_MIPS32NEW_TAB_H_INCLUDED
# define YY_YY_MIPS32NEW_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_DATA = 258,
    T_CODE = 259,
    T_WORD = 260,
    T_BYTE = 261,
    T_HALF = 262,
    T_NUM = 263,
    T_REG = 264,
    T_BREG = 265,
    T_IDNAME = 266,
    T_HILO = 267,
    T_NOP = 268,
    T_RCOM = 269,
    T_RSCOM = 270,
    T_RMDCOM = 271,
    T_RMJCOM = 272,
    T_RRCOM = 273,
    T_ICOM = 274,
    T_LWICOM = 275,
    T_BICOM = 276,
    T_SICOM = 277,
    T_JCOM = 278,
    EOL = 279,
    T_ERR = 280
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 9 "mips32New.y" /* yacc.c:1909  */

  struct ast *a;
  
  struct symbol *s;		/* which symbol */
  struct idnum  *in ;
  //symlist *sl;
  char *str;
  struct hilo* hl;   /*支持hilo伪指令*/
  int d;
  int fn;			  /* which INS*/
  char* kw;     /*KeyWord*/

#line 93 "mips32New.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MIPS32NEW_TAB_H_INCLUDED  */
