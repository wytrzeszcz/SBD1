
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class record
{
	public:
	record()
	{
		biggest=true;
		broke=false;
	}
	record(int i)
	{
		broke=true;
	}
	record(char* rawData)
	{
		biggest=false;
		broke=false;
		for (int i=1;i<=rawData[0];i++)
		{
			this->data.push_back(rawData[i]);
		}
	}
	record(char* rawData, int* ptr)
	{
		//cout<<"new record"<<endl;
		biggest=false;
		broke=false;

		(*ptr)++;
		for (int i=1;i<=rawData[0];i++)
		{
			if(rawData[i]>9) cout<<"XD "<<i<<endl;
			this->data.push_back(rawData[i]);
			(*ptr)++;
		}
		//cout<<(int)rawData[0]<<"  "<<*this<<endl;
	}
	~record()
	{
		this->data.clear();
	};
	int get_size() const
	{
		return (char)this->data.size();
	}

	int get_num(int i) const
	{
		return this->data[i];
	}
	
	void  operator=(const record& rhs)
	{
		//if(rhs.broken()) cout<<"cos nie tak"<<endl;
		biggest=false;
		broke=rhs.broken();
		data=rhs.data;
	}
	bool broken() const
	{
		return broke;
	}
	bool operator>(const record& rhs) const
	{
		if(biggest) return true;
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
		if(biggest||broke) return false;
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
	
	 int to_bin(char *output) //	WARNIGN OUTPUT IN C STYLE
	{
		if(biggest) return 0;
		//cout<<"to_bin ";
		//cout<<*this<<endl;
		int i=0;
		output[i]=0+get_size();
		for(i=1;i<=get_size();i++)output[i]=0+data[i-1];
		//cout<<i<<endl;
		return i;
	}
	
	
	private:
	vector<char>  data;
	bool biggest;
	bool broke;
};
