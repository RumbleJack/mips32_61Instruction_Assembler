mipsnew:
	bison -d mips32New.y
	flex mips32New.l
	g++ -o mipsnew mips32New.tab.c lex.yy.c util.cpp subRoutine.cpp main.cpp
clean:
	rm mips32New.tab.c mips32New.tab.h lex.yy.c mipsnew memblk0.coe memblk1.coe memblk2.coe memblk3.coe \
	progbin
