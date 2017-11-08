
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class record
{
	public:
	record(char* rawData)
	{
		cerr<<"Creating record!"<<endl;
		for (int i=1;i<=rawData[0];i++)
		{
			this->data.push_back(rawData[i]);
		}
	}
	record(char* rawData, int* ptr)
	{
		(*ptr)++;
		cerr<<"Creating record!!"<<endl;
		for (int i=1;i<=rawData[0];i++)
		{
			this->data.push_back(rawData[i]);
			(*ptr)++;
		}
	}
	~record()
	{
		cerr<<"deleting record!"<<endl;
		this->data.clear();
	};
	int get_size() const
	{
		return this->data.size();
	}
	
	
	int get_num(int i) const
	{
		return this->data[i];
	}
	
	void  operator=(const record& rhs)
	{
		data=rhs.data;
	}
		
	bool operator>(const record& rhs) const
	{
		if(data.size() >rhs.get_size()) return true;
		if (data.size()==rhs.get_size())
		{
			vector<char> left=data;
			vector<char> right=rhs.data;
			sort(left.begin(),left.end());
			sort(right.begin(),right.end());
			reverse(left.begin(),left.end());
			reverse(right.begin(),right.end());


			if(left>right) return true;
		}
		return false;
	}
	bool operator==(const record& rhs)
	{
		
		// sort(numbers.begin(), numbers.end(), greater());
		if (data.size()==rhs.get_size())
		{
			vector<char> left=data;
			vector<char> right=rhs.data;
			sort(left.begin(),left.end());
			sort(right.begin(),right.end());
			reverse(left.begin(),left.end());
			reverse(right.begin(),right.end());

			if(left==right) return true;
		}
		return false;
	}


	bool operator>=(const record& rhs)
	{
		return *this>rhs || *this==rhs;
	}	


	bool operator<(const record& rhs)
	{
		return !(*this>rhs || *this==rhs);
	}

	bool operator<=(const record& rhs)
	{
		return !(*this>rhs);
	}
	bool operator!=(const record& rhs)
	{
		return !(*this==rhs);
	}
	
	friend ostream &operator<<(std::ostream &os, const record  &r) 
	{ 
		os<<r.get_size()<<"{";
		for (int i=0;i<r.get_size();i++)
		{
			os<<r.get_num(i);
			if(i+1<r.get_size()) os<<",";
		}
		return os<<"}";
	}	
	
	private:
	vector<char>  data;
};
