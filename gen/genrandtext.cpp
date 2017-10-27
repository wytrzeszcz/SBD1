#include <iostream> 
#include <cstdlib> //for atoi
#include <cstdint>
#define PROGRAM_NAME random generator
#define PROGRAM_VER v0.1

//#define DEBUG


using namespace std;

int print_help()
{
	cerr << "PROGRAM_NAME  PROGRAM_VER"<<endl;
	cerr << "usage:"<<endl;
	cerr << " PROGRAM_NAME [NUMBER] [-k -m -g -t] [-o] [FILE]"<<endl;
}


int gen(uint64_t base,uint64_t scale)
{
	cout<< "base:"<<base<<endl;
	cout<< "scale:"<<scale<<endl;
	while(scale--)
	{
		while(base--)
		{
			cout<<"rand"<<endl;
		}
	}

	return 0;
}

int main( int argc, char *argv[], char *envp[])
{
	uint64_t base=0;
	uint64_t scale=1;

#ifdef DEBUG	
	cerr << "agrc: "<<argc<<endl;
#endif
	if (argc == 1) 
	{
		print_help();
		return -1;
	}
	if ( atol(argv[1])>0 && argc >=2 )
	{
		base=atol(argv[1]);
	}		
	else
	{
		print_help();
		return -1;
	}
	if(argc >=3 && argv[2][1]=='k') scale=1000;
	if(argc >=3 && argv[2][1]=='m') scale=1000*1000;
	if(argc >=3 && argv[2][1]=='g') scale=1000*1000*1000;
	if(argc >=3 && argv[2][1]=='t') scale=1000*1000*1000*1000;
	gen(base,scale);
	return 0;
}



