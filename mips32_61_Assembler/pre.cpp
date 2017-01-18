#include <iostream> 
#include <sstream> 
#include <fstream> 
#include <string> 
#include <vector>
#include <string.h> 
using namespace std;
vector<string> vtext,vdata;
int prefunc(int args, char **argv) 
{ 
	ifstream fin("alarmm.s", ios::in); 
	ofstream fout("temp.s", ios::out); 
	char line[1024]={0}; 
	char text[]="	.text";
	char data[]=".data";
	int flag=0;
	while(fin.getline(line, sizeof(line))) 
	{ 
		if (strcmp(line,text)==0)
			flag=1;
		if (strcmp(line,data)==0)
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