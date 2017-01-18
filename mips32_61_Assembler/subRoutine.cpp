#include "mips32New.h"
#include "mips32New.tab.h"

int constructNop(  int fn )
{
	memset((g_curMacIns)->Com  ,0,33);
	switch( fn ){
		case 0 :
		if ( !ConstructMacLinkTab( (curComNo-1) * 4 + curCodeAddr + beginOfCode ) )
			return -1;
		break;
		default: 
		return -1;
	}
	return 0;
}
int constructR_1( int fn, int rd, int rs, int rt )
{
	memset((g_curMacIns)->Com  ,0,33);
	switch( fn ){
		case 0:
		(*g_curMacIns)[5] = 1;
		break;
		case 1:
		(*g_curMacIns)[5] = 1;
		(*g_curMacIns)[0] = 1;
		break;
		case 2:
		(*g_curMacIns)[5] = 1;
		(*g_curMacIns)[1] = 1;
		break;
		case 3:
		(*g_curMacIns)[5] = 1;
		(*g_curMacIns)[1] = 1;
		(*g_curMacIns)[0] = 1;
		break;
		case 4:
		(*g_curMacIns)[5] = 1;
		(*g_curMacIns)[2] = 1;
		break;
		case 5:
		(*g_curMacIns)[5] = 1;
		(*g_curMacIns)[2] = 1;
		(*g_curMacIns)[0] = 1;
		break;
		case 6:
		(*g_curMacIns)[5] = 1;
		(*g_curMacIns)[2] = 1;
		(*g_curMacIns)[1] = 1;
		break;
		case 7:
		(*g_curMacIns)[5] = 1;
		(*g_curMacIns)[2] = 1;
		(*g_curMacIns)[1] = 1;
		(*g_curMacIns)[0] = 1;
		break;
		case 8:
		(*g_curMacIns)[5] = 1;
		(*g_curMacIns)[3] = 1;
		(*g_curMacIns)[1] = 1;
		break;
		case 9:
		(*g_curMacIns)[5] = 1;
		(*g_curMacIns)[3] = 1;
		(*g_curMacIns)[1] = 1;
		(*g_curMacIns)[0] = 1;
		break;
		case 10:
		(*g_curMacIns)[2] = 1;
		break;
		case 11:
		(*g_curMacIns)[2] = 1;
		(*g_curMacIns)[1] = 1;
		break;
		case 12:
		(*g_curMacIns)[2] = 1;
		(*g_curMacIns)[1] = 1;
		(*g_curMacIns)[0] = 1;
		break;
		default:
			return -1;
	}
	int base = 11;
	int t_val = 0;
	for( int j = 0; j < 3 ; j++,base += 5)
	{
		switch( j ){
			case 0:
				t_val = rd;
				break;
			case 1:
				t_val = rt;
				break;
			case 2:
				t_val = rs;
				break;
		} 
		for( int i = 0; i < 5; i++){
			(*g_curMacIns)[base + i ] = 1 & (t_val);
			t_val = t_val>>1;
		}
	}
	if ( !ConstructMacLinkTab( (curComNo-1) * 4 + curCodeAddr + beginOfCode ) ) 
			return -1;
	return 0;
}
int constructR_2( int fn, int rd, int rt,int sval ){
	memset((g_curMacIns)->Com  ,0,33);
	switch( fn ){
		case 0:
		break;
		case 1:
		(*g_curMacIns)[1] = 1;
		break;
		case 2:
		(*g_curMacIns)[1] = 1;
		(*g_curMacIns)[0] = 1;
		break;
		case 3:
		(*g_curMacIns)[30] = 1;
		break;
		case 4:
		(*g_curMacIns)[30] = 1;
		(*g_curMacIns)[23] = 1;
		break;
		default:
			return -1;
		break;
	}
	//用于区分SLL SRA SRL （0）和 MFC0 MTC0（1）；
	if( fn < 3 )
	{
		for( int i = 6; i <= 10; i++){
			(*g_curMacIns)[i] = 1 & (sval);
			sval = sval>>1;
		}
	}else{
		for( int i = 0; i <= 2; i++){
			(*g_curMacIns)[i] = 1 & (sval);
			sval = sval>>1;
		}
	}

	int base = 11;
	int t_val = 0;
	for( int j = 0; j < 2 ; j++,base += 5)
	{
		switch( j ){
			case 0:
				t_val = rd;
				break;
			case 1:
				t_val = rt;
				break;
		} 
		for( int i = 0; i < 5; i++){
			(*g_curMacIns)[base + i ] = 1 & (t_val);
			t_val = t_val>>1;
		}
	}
	if ( !ConstructMacLinkTab( (curComNo-1) * 4 + curCodeAddr + beginOfCode ) ) 
			return -1;
	return 0;
}
int constructR_3( int fn, int rs, int rt )
{
	memset((g_curMacIns)->Com  ,0,33);
	switch( fn ){
		case 0:
		(*g_curMacIns)[3] = 1;
				(*g_curMacIns)[4] = 1;
		break;
		case 1:
		(*g_curMacIns)[3] = 1;
				(*g_curMacIns)[4] = 1;
				(*g_curMacIns)[0] = 1;
		break;
		case 2:
		(*g_curMacIns)[3] = 1;
				(*g_curMacIns)[4] = 1;
				(*g_curMacIns)[1] = 1;
		break;
		case 3:
		(*g_curMacIns)[3] = 1;
				(*g_curMacIns)[4] = 1;
				(*g_curMacIns)[1] = 1;
				(*g_curMacIns)[0] = 1;
		break;
		case 4:
		(*g_curMacIns)[3] = 1;
				(*g_curMacIns)[0] = 1;
		break;
		default:
			return -1;
		break;
	}
	//用于区分MULT MULTU DIV  DIVU （0）和 JALR（1）；
	if( fn < 4 )
	{
		int base = 16;
		int t_val = 0;
		for( int j = 0; j < 2 ; j++,base += 5)
		{
			switch( j ){
				case 0:
					t_val = rt;
					break;
				case 1:
					t_val = rs;
					break;
			} 
			for( int i = 0; i < 5; i++){
				(*g_curMacIns)[base + i ] = 1 & (t_val);
				t_val = t_val>>1;
			}
		}
	}else
	{
		for( int i = 21; i < 26; i++){
			(*g_curMacIns)[ i ] = 1 & (rt);
			rt = rt>>1;
		}
		for( int i = 11; i < 16; i++){
			(*g_curMacIns)[ i ] = 1 & (rs);
			rs = rs>>1;
		}
	}
	if ( !ConstructMacLinkTab( (curComNo-1) * 4 + curCodeAddr + beginOfCode ) ) 
			return -1;
	return 0;
}
int constructR_4( int fn, int reg )
{
	memset((g_curMacIns)->Com  ,0,33);
	switch( fn ){
		case 0:
		(*g_curMacIns)[4] = 1;
		break;
		case 1:
		(*g_curMacIns)[4] = 1;
				(*g_curMacIns)[1] = 1;
		break;
		case 2:
		(*g_curMacIns)[4] = 1;
				(*g_curMacIns)[0] = 1;
		break;
		case 3:
		(*g_curMacIns)[4] = 1;
				(*g_curMacIns)[0] = 1;
				(*g_curMacIns)[1] = 1;
		break;
		case 4:
		(*g_curMacIns)[3] = 1;
		break;
		default:
			return -1;
		break;
	}
	//用于区分MULT MULTU DIV  DIVU （0）和 JALR（1）；
	if( fn < 2 )
	{
		int base = 11;
		int t_val = reg;
		for( int i = 0; i < 5; i++){
			(*g_curMacIns)[base + i ] = 1 & (t_val);
			t_val = t_val>>1;
		}
	}else
	{
		int base = 21;
		int t_val = reg;
		for( int i = 0; i < 5; i++){
			(*g_curMacIns)[base + i ] = 1 & (t_val);
			t_val = t_val>>1;
		}
	}
	if ( !ConstructMacLinkTab( (curComNo-1) * 4 + curCodeAddr + beginOfCode ) ) 
			return -1;
	return 0;
}
int constructR_5( int fn )
{
	memset((g_curMacIns)->Com  ,0,33);
	switch( fn ){
		case 0:
		(*g_curMacIns)[0] = 1;
				(*g_curMacIns)[2] = 1;
				(*g_curMacIns)[3] = 1;
		break;
		case 1:
		(*g_curMacIns)[2] = 1;
				(*g_curMacIns)[3] = 1;
		break;
		case 2:
		(*g_curMacIns)[4] = 1;
				(*g_curMacIns)[3] = 1;
				(*g_curMacIns)[25] = 1;
				(*g_curMacIns)[30] = 1;
		break;
		case 3:
		(*g_curMacIns)[3] = 1;
				(*g_curMacIns)[25] = 1;
				(*g_curMacIns)[30] = 1;
		break;
		case 4:
		(*g_curMacIns)[0] = 1;
				(*g_curMacIns)[25] = 1;
				(*g_curMacIns)[30] = 1;
		break;
		case 5:
		(*g_curMacIns)[1] = 1;
				(*g_curMacIns)[25] = 1;
				(*g_curMacIns)[30] = 1;
				case 6:
		(*g_curMacIns)[1] = 1;
				(*g_curMacIns)[2] = 1;
				(*g_curMacIns)[25] = 1;
				(*g_curMacIns)[30] = 1;
		break;
		default:
			return -1;
		break;
	}
	if ( !ConstructMacLinkTab( (curComNo-1) * 4 + curCodeAddr + beginOfCode ) )
			return -1;
	return 0;
}


int constructI_1(int fn, int rt, int rs , ast* node  )
{
	memset((g_curMacIns)->Com  ,0,33);
	switch( fn ){
		case 0:
		(*g_curMacIns)[29] = 1;
		break;
		case 1:
		(*g_curMacIns)[29] = 1;
				(*g_curMacIns)[26] = 1;
		break;
		case 2:
		(*g_curMacIns)[29] = 1;
				(*g_curMacIns)[28] = 1;
		break;
		case 3:
		(*g_curMacIns)[29] = 1;
				(*g_curMacIns)[28] = 1;
				(*g_curMacIns)[26] = 1;
		break;
		case 4:
		(*g_curMacIns)[29] = 1;
				(*g_curMacIns)[28] = 1;
				(*g_curMacIns)[27] = 1;
				break;
		case 5:
		(*g_curMacIns)[27] = 1;
				(*g_curMacIns)[29] = 1;
				break;
		case 6:
		(*g_curMacIns)[27] = 1;
				(*g_curMacIns)[29] = 1;
				(*g_curMacIns)[26] = 1;
		break;
		case 7:
		(*g_curMacIns)[28] = 1;
				case 8:
		(*g_curMacIns)[28] = 1;
				(*g_curMacIns)[26] = 1;
		break;
		default:
			return -1;
		break;
	}
	int base = 16;
		int t_val = 0;
		for( int j = 0; j < 2 ; j++,base += 5)
		{
			switch( j ){
				case 0:
					t_val = rt;
					break;
				case 1:
					t_val = rs;
					break;
			} 
			for( int i = 0; i < 5; i++){
				(*g_curMacIns)[base + i ] = 1 & (t_val);
				t_val = t_val>>1;
			}
		}

		if( ((idnum*)node)->flag == 0 )
		{
			t_val = ((idnum*)node)->val;
			for( int i = 0; i <= 15; i++){
				(*g_curMacIns)[i] = 1 & (t_val);
				t_val = t_val>>1;
			}
		}else if(( (idnum*)node)->flag == 1 )
		{
			symbol* cursym = lookupSym( ((idnum*)node)->str, T_ICOM );
			if( cursym != NULL )
			{
				//此处之所看似没有考虑PC= PC + 4, 实际上时因为 curComNo * 4 已经到了下一条指令的地址
				t_val = cursym->addr - ( curComNo * 4 + curCodeAddr +beginOfCode ) ;
				t_val = t_val>>2;
				for( int i = 0; i <= 15; i++)
				{
					(*g_curMacIns)[i] = 1 & (t_val);
					t_val = t_val>>1;
				}
			}
		}else  if(( (idnum*)node)->flag == 2 )
		{
			symbol* cursym = lookupSym( ((idnum*)node)->hl->name, T_LWICOM );
			if( cursym != NULL )
			{
				if( ((idnum*)node)->hl->ishi == 0)
				{
					t_val = cursym->addr  ;
				}else
				{
					t_val = cursym->addr << 16 ;
				}
				for( int i = 0; i <= 15; i++)
				{
					(*g_curMacIns)[i] = 1 & (t_val);
					t_val = t_val>>1;
				}
			}
		}
	if ( !ConstructMacLinkTab( (curComNo-1) * 4 + curCodeAddr + beginOfCode ) )
			return -1;
	return 0;
}
int constructI_2(int fn, int rt,  ast* node ,int rs  )
{
	memset((g_curMacIns)->Com  ,0,33);
	switch( fn ){
		case 0:
		(*g_curMacIns)[26] = 1;
				(*g_curMacIns)[27] = 1;
				(*g_curMacIns)[31] = 1;
		break;
		case 1:
		(*g_curMacIns)[26] = 1;
				(*g_curMacIns)[27] = 1;
				(*g_curMacIns)[29] = 1;
				(*g_curMacIns)[31] = 1;
		break;
		case 2:
		(*g_curMacIns)[31] = 1;
		break;
		case 3:
		(*g_curMacIns)[28] = 1;
				(*g_curMacIns)[31] = 1;
		break;
		case 4:
		(*g_curMacIns)[26] = 1;
				(*g_curMacIns)[31] = 1;
				break;
		case 5:
		(*g_curMacIns)[26] = 1;
				(*g_curMacIns)[28] = 1;
				(*g_curMacIns)[31] = 1;
				break;
		case 6:
		(*g_curMacIns)[29] = 1;
				(*g_curMacIns)[31] = 1;
		break;
		case 7:
		(*g_curMacIns)[26] = 1;
				(*g_curMacIns)[29] = 1;
				(*g_curMacIns)[31] = 1;
		break;
		default:
			return -1;
		break;
	}
	int base = 16;
		int t_val = 0;
		for( int j = 0; j < 2 ; j++,base += 5)
		{
			switch( j ){
				case 0:
					t_val = rt;
					break;
				case 1:
					t_val = rs;
					break;
			} 
			for( int i = 0; i < 5; i++){
				(*g_curMacIns)[base + i ] = 1 & (t_val);
				t_val = t_val>>1;
			}
		}
		if( ((idnum*)node)->flag == 0 )
		{
			t_val = ((idnum*)node)->val;
			for( int i = 0; i <= 15; i++){
				(*g_curMacIns)[i] = 1 & (t_val);
				t_val = t_val>>1;
			}
		}else if ( ((idnum*)node)->flag == 1 )
		{
			symbol* cursym = lookupSym( ((idnum*)node)->str, T_LWICOM );
			if( cursym != NULL )
			{
				t_val = cursym->addr  ;
				for( int i = 0; i <= 15; i++)
				{
					(*g_curMacIns)[i] = 1 & (t_val);
					t_val = t_val>>1;
				}
			}
		}else if ( ((idnum*)node)->flag == 2 )
		{
			symbol* cursym = lookupSym( ((idnum*)node)->hl->name, T_LWICOM );
			if( cursym != NULL )
			{
				if( ((idnum*)node)->hl->ishi == 0)
				{
					t_val = cursym->addr  ;
				}else
				{
					t_val = cursym->addr << 16 ;
				}
				for( int i = 0; i <= 15; i++)
				{
					(*g_curMacIns)[i] = 1 & (t_val);
					t_val = t_val>>1;
				}
			}
		}
	if ( !ConstructMacLinkTab( (curComNo-1) * 4 + curCodeAddr + beginOfCode ) )
			return -1;
	return 0;
}
int constructI_3(int fn, int rs , ast* node )
{
	memset((g_curMacIns)->Com  ,0,33);
	switch( fn ){
		case 0:
		(*g_curMacIns)[26] = 1;
				(*g_curMacIns)[16] = 1;
		break;
		case 1:
		(*g_curMacIns)[28] = 1;
				(*g_curMacIns)[27] = 1;
				(*g_curMacIns)[26] = 1;
		break;
		case 2:
		(*g_curMacIns)[28] = 1;
				(*g_curMacIns)[27] = 1;
		break;
		case 3:
		(*g_curMacIns)[26] = 1;
		break;
		case 4:
		(*g_curMacIns)[26] = 1;
				(*g_curMacIns)[16] = 1;
				(*g_curMacIns)[20] = 1;
				break;
		case 5:
		(*g_curMacIns)[26] = 1;
				(*g_curMacIns)[20] = 1;
				break;
		default:
			return -1;
		break;
	}
	int base = 21;
	int t_val = rs;
	for( int i = 0; i < 5; i++){
		(*g_curMacIns)[base + i ] = 1 & (t_val);
		t_val = t_val>>1;
	}
	if( ((idnum*)node)->flag == 0 )
		{
			t_val = ((idnum*)node)->val;
			for( int i = 0; i <= 15; i++){
				(*g_curMacIns)[i] = 1 & (t_val);
				t_val = t_val>>1;
			}
		}else
		{
			symbol* cursym = lookupSym( ((idnum*)node)->str, T_BICOM );
			if( cursym != NULL )
			{
				t_val = cursym->addr >> 2 ;
				for( int i = 0; i <= 15; i++)
				{
					(*g_curMacIns)[i] = 1 & (t_val);
					t_val = t_val>>1;
				}
			}
		}
	if ( !ConstructMacLinkTab( (curComNo-1) * 4 + curCodeAddr + beginOfCode ) )
			return -1;
	return 0;
}
int constructI_4(int fn, int rt , ast* node  )
{
	memset((g_curMacIns)->Com  ,0,33);
	(*g_curMacIns)[26] = 1;
	(*g_curMacIns)[27] = 1;
	(*g_curMacIns)[28] = 1;
	(*g_curMacIns)[29] = 1;
	int base = 16;
	int t_val = rt;
	for( int i = 0; i < 5; i++){
		(*g_curMacIns)[base + i ] = 1 & (t_val);
		t_val = t_val>>1;
	}
	if( ((idnum*)node)->flag == 0 )
		{
			t_val = ((idnum*)node)->val;
			for( int i = 0; i <= 15; i++){
				(*g_curMacIns)[i] = 1 & (t_val);
				t_val = t_val>>1;
			}
		}else if( ((idnum*)node)->flag == 2 )
		{
			symbol* cursym = lookupSym( ((idnum*)node)->hl->name, T_SICOM );
			if( cursym != NULL )
			{
				if( ((idnum*)node)->hl->ishi == 0)
				{
					t_val = cursym->addr  ;
				}else
				{
					t_val = cursym->addr << 16 ;
				}
				for( int i = 0; i <= 15; i++)
				{
					(*g_curMacIns)[i] = 1 & (t_val);
					t_val = t_val>>1;
				}
			}
		}
	if ( !ConstructMacLinkTab( (curComNo-1) * 4 + curCodeAddr + beginOfCode ) )
		return -1;
	return 0;
}

int constructJ_1(int fn, ast* node )
{
	memset((g_curMacIns)->Com  ,0,33);
	switch( fn ){
		case 0:
		(*g_curMacIns)[27] = 1;
		break;
		case 1:
		(*g_curMacIns)[26] = 1;
				(*g_curMacIns)[27] = 1;
		break;
		default:
			return -1;
		break;
	}
	int base = 21;
	int t_val = 0;
	if( ((idnum*)node)->flag == 0 )
		{
			t_val = ((idnum*)node)->val >> 2;
			for( int i = 0; i < 26; i++){
				(*g_curMacIns)[i] = 1 & (t_val);
				t_val = t_val>>1;
			}
		}else
		{
			symbol* cursym = lookupSym( ((idnum*)node)->str, T_JCOM );
			if( cursym != NULL )
			{
				t_val = cursym->addr >> 2 ;
				for( int i = 0; i < 26; i++)
				{
					(*g_curMacIns)[i] = 1 & (t_val);
					t_val = t_val>>1;
				}
			}
		}
	if ( !ConstructMacLinkTab( (curComNo-1) * 4 + curCodeAddr + beginOfCode ) )
			return -1;
	return 0;
}
ast* newinn(int n )
{
	idnum* in = new idnum();
	in->nodetype = 'A';
	in->flag = 0;
	in->val = n;
	return (ast*)in;
}

ast* newini(char* id )
{
	idnum* in = new idnum();
	in->nodetype = 'A';
	in->flag = 1;
	in->str = new char[strlen(id)+1];
	strcpy( in->str, id );
	return (ast*)in;
}
ast* newinhl(hilo* hl )
{
	idnum* in = new idnum();
	in->nodetype = 'A';
	in->flag = 2;
	in->hl = new hilo();
	in->hl->name = new char[strlen(hl->name)+1];
	strcpy( in->hl->name, hl->name );
	in->hl->ishi = hl->ishi;
	return (ast*)in;
}
