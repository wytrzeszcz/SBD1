
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
friend ostream&;
class record
{
	public:
	record(char* rawData)
	{
		for (int i=1;i<=rawData[0];i++)
		{
			this.data.pushback(rawData[i]);
		}
	}
	~record();
	int get_size()
	{
		return this.data.size;
	}
	string to_text()
	{

	}

	bool operator==(const record& lhs,const record& rhs)
	{
		if (lhs.get_size()==rhs.get_size())
		{
			
		}
		else return false;
	}
	

	private:
	vector<char>  data;
}
