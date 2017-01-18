#include "mips32New.h"
#include "mips32New.tab.h"
int main( int argc, char** argv )
{
	freopen( "outlog.txt","w",stdout);
	//freopen( "errlog.txt","w",stderr);
	FILE *f ;
	if( argc == 1 )
	{
		prefunc( "testcpu.asm", "ifile.asm");
		f = fopen("ifile.asm" , "r");
	}else
	{
		prefunc( argv[1], "ifile.asm");
		f = fopen("ifile.asm" , "r");
	}
	if( f == NULL)
		cerr<<"Can not open file!\n";
	yyrestart(f);

	cerr<<"Parse begin!"<<endl;
	setParameter();
	while( yylex() );
	//yyparse();
	if( checkresult() != 0 ) 
	{
		syntaxOK = 0;
		cerr<<"some symbol no be declare£¡"<<endl;
	}
	if(syntaxOK)
	{
		cerr<<"\nSyntax analysis success!\n";
		writeProgCoe();
	}
	else
		cerr<<"\nSyntax analysis failed!\n";
	return 0;
}