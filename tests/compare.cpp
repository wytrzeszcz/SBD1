
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include "../main/record.h"
using namespace std;

char cases[9][32]={
		{0},  /*0*/
		{0},  /* 1 */
		{1,1},/* 2 */
		{1,2},/* 3 */
		{1,3},/* 4 */
		{1,1},/* 5 */
		{2,1,1},/* 6 */
		{2,1,2},/* 7 */
		{2,2,1}/* 8 */
	};


int main()
{
	vector<record> r;
	for (int i=0;i<9;i++)r.push_back(record(cases[i]));
	cout << "compare test"<<endl;
	for (int o=0;o<6;o++)
	{
		for(int x=0;x<9;x++)
		{
			for (int y=0;y<9;y++)
			{
				switch(o)
				{
					case 0:
					(r[x]==r[y])? cout<<"OK "<<r[x]<<"=="<<r[y]<<endl : cout<<"Nope "<<r[x]<<"=="<<y<<endl;
					break;
					
					case 1:
					(r[x]>=r[y])? cout<<"OK "<<r[x]<<">="<<r[y]<<endl : cout<<"Nope "<<r[x]<<">="<<r[y]<<endl;
					break;
					
					case 2:
					(r[x]<=r[y])? cout<<"OK "<<r[x]<<"<="<<r[y]<<endl : cout<<"Nope "<<r[x]<<"<="<<r[y]<<endl;
					break;
					
					case 3:
					(r[x]<r[y])? cout<<"OK "<<r[x]<<"<"<<r[y]<<endl : cout<<"Nope "<<r[x]<<"<"<<r[y]<<endl;
					break;
					
					case 4:
					(r[x]>r[y])? cout<<"OK "<<r[x]<<">"<<r[y]<<endl : cout<<"Nope "<<r[x]<<">"<<r[y]<<endl;
					break;
					
					case 5:
					(r[x]!=r[y])? cout<<"OK "<<r[x]<<"!="<<r[y]<<endl : cout<<"Nope "<<r[x]<<"!="<<r[y]<<endl;
					break;
				}
			}
		}
	}
}
