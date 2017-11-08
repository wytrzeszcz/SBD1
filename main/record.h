
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


	bool operator>(const record& lhs,const record& rhs)
	{
		if(lhs.get_size()>rhs.get_size()) return true;
		if (lhs.get_size()==rhs.get_size())
		{
			vector<char> left=lhs;
			vector<char> right=rhs;
			sort(left.begin(),left.end(),greater());
			sort(right.begin(),right.end(),greater());
			if(left>right) return true;
		}
		return false;
	}
	bool operator==(const record& lhs,const record& rhs)
	{
		
		// sort(numbers.begin(), numbers.end(), greater());
		if (lhs.get_size()==rhs.get_size())
		{
			vector<char> left=lhs;
			vector<char> right=rhs;
			sort(left.begin(),left.end(),greater());
			sort(right.begin(),right.end(),greater());
			if(left==right) return true;
		}
		return false;
	}


	bool operator>=(const record& lhs,const record& rhs)
	{
		return lhs>rhs || lhs==rhs;
	}	


	bool operator<(const record& lhs,const record& rhs)
	{
		return !(lhs>rhs || lhs==rhs);
	}

	bool operator<=(const record& lhs,const record& rhs)
	{
		return !(lhs>rhs);
	}
	private:
	vector<char>  data;
}
