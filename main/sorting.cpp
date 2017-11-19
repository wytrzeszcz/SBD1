#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <cstdio>
#include <vector>
//#include "../main/record.h"
#include "../main/buff.h"
using namespace std;
bool all_series_end(vector<buff> &inputs)
{
	for (int i=0;i<inputs.size();i++) 
	{
		if(!(inputs[i].series_end())) return false;
	}
	return true;
}

bool all_files_end(vector<buff> &inputs)
{
	for (int i=0;i<inputs.size();i++) 
	{
		if(!inputs[i].empty()) return false;
	}
	return true;
}

void all_series_reset(vector<buff> &inputs)
{
	for (int i=0;i<inputs.size();i++) inputs[i].next_series();
	
}

int min_tape(vector<buff> &inputs)
{
	//cout<<"min"<<endl;
	int ret=-1;
	record tmp;
	for (int i=0;i<inputs.size();i++) 
	{
		if(!(inputs[i].series_end())) 
			if( tmp>inputs[i].top()) 
			{
				ret=i;
				tmp=inputs[i].top();
			}
	}
	
	
	return ret;
}

int main(int argc, char* argv[])
{
	
	if(argc<2)
	{ 
		cout<<"tapes size"<<endl;
		return 0;
	}
	int writes=0;
	int reads=0;
	direction r=read;
	direction w=write;
	int tapes=atoi(argv[1]);
	int buffsize=atoi(argv[2]);
	rename("input.tape","0_0.tape");
	bool inplace=false;
	if(argc>3) inplace=true;
	//inplace=true;
	int rounds=0;
	buff* input  = new buff(buffsize,0,rounds,r,tapes,inplace,true);
	buff* output = new buff(buffsize,0,rounds,w,tapes,inplace);
	while(!(input->empty()))output->push(input->pop());
	output->flush();
	rounds++;
	writes+=output->writes();
	reads+=input->reads();
	int used_tapes=output->tapes_used();
	if(!(used_tapes<2))
	{
		delete input;
		delete output;
		vector<buff> inputs;
		do{
			
			for(int i=0;i<used_tapes;i++) inputs.push_back(buff(buffsize,i,rounds,r,tapes,inplace));
			if(inplace)
			{
				output->clear_files(rounds,tapes);
			}
			output=new buff(buffsize,0,rounds,w,tapes,inplace);
			while(!all_files_end(inputs))
			{

				while(!all_series_end(inputs))
				{
					int t=min_tape(inputs);
					record tmp=inputs[t].pop();
					if(!tmp.broken()) 
					{
						output->push(tmp);
					}
				}

				all_series_reset(inputs);


			}
			
			for (int i=0;i<inputs.size();i++){reads+=inputs[i].reads();}
			inputs.clear();
			output->flush();
			writes+=output->writes();
			used_tapes=output->tapes_used();
			delete output;
			rounds++;
			
			
		}while(used_tapes>1);
	}	
	
			char name[16];
			if(inplace)snprintf(name, sizeof(name), "%d_%d.tape", (rounds)%2,0);
			else snprintf(name, sizeof(name), "%d_%d.tape", rounds,0);
			rename(name,"output.tape");
	
	cout<<"R:"<<reads<<"\tW:"<<writes<<"\tS:"<<rounds<<endl;
	
	return 0;
}
