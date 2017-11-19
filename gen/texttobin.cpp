#include <iostream>
#include <vector>
using namespace std;
int main()
{
	char in;
	bool flag=true;
	vector<char> out;
	while (cin >>noskipws>> in )
	{
		if(in>='0' && in <='9') 
		{
			flag=true;
			out.push_back(in-'0');
		}
		else
		{
			if (flag)
			{
			cout << (char)out.size();
			for (vector<char>::const_iterator i = out.begin(); i != out.end(); ++i)
			cout << *i;
			out.clear();
			flag=false;
			}
			
		}
	}
	//cout<<(char)0;
	return 0;
}
