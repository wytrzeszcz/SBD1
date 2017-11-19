#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <cstdio>
#include <vector>
//#include "../main/record.h"
#include "../main/buff.h"
using namespace std;
int main(int argc, char* argv[])
{
	if(argc<2)
	{
		cout<<"No file name!"<<endl;
		return -1;
	}
	
	int buffsize=1024;
	buff* input  = new buff(buffsize,argv[1]);
	while(!(input->empty()))
	{
	  cout<<input->pop()<<endl;
	}
	
	
	return 0;
}
