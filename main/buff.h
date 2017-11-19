#include "./record.h"
#include <cstdio>
#include <list>
enum  direction
{
	read=0,
	write=1
};

class buff
{
	/*
	 * 1. pobranie bloku z pamieci  zewnetrznej read_block();
	 * 2. zapisanie bloku do pamięci zewnętrzej store_block();
	 * 3. Oddanie rekordu pop_record()
	 * 4. przyjecie rekodrdu push_record();
	 * 5. Flaga konca serii !!!
	 * 6. zmien plik
	 * 7. posortuj
	 * 8. ustaw rozmiar
	 * 9.
	 * 
	 * 
	 * algorytm nad
	 * 1.dla wszystkich serii  co nie maja flagi
	 * 2.weź rekord
	 * 3. wybierz
	 */
	
	
	
	public:
	
	buff()	{			}
	buff( int size,int tapenr, int seriesnr, direction d, int nin,bool in_place,bool autosort=false)
	{
		sorting=autosort;
		bufsize=size;
		tmp_buff=new char[size+33](); // magic number 33 is one byte more than one record
		dir=d;
		series=seriesnr;
		char name[50];
		tmp_buff_ptr=0;
		read_counter=0;
		write_counter=0;
		n=nin;
		save_id=0;
		eof=false;
		offset=0;
		inplace=in_place;
		if(dir==read)
		{
			if(inplace)snprintf(name, sizeof(name), "%d_%d.tape", series%2,tapenr);
			else snprintf(name, sizeof(name), "%d_%d.tape", series,tapenr);
			tape=fopen(name,"rb");
		}	
		else
		{
			if(inplace)snprintf(name, sizeof(name), "%d_%d.tape", (series+1)%2,tapenr);
			else snprintf(name, sizeof(name), "%d_%d.tape", series+1,tapenr);
			tape=fopen(name,"w+b");
		}
		if(tape==NULL)cout<<"no to sie wysypie bo nie mam tasmy"<<endl;
		
	} 

	buff(int size,char* name)
	{
		sorting=false;
		bufsize=size;
		tmp_buff=new char[size+33](); // magic number 33 is one byte more than one record
		dir=read;
		tmp_buff_ptr=0;
		read_counter=0;
		write_counter=0;
		save_id=0;
		eof=false;
		offset=0;
		tape=fopen(name,"rb");

	}


	void sort(){data.sort();}

	record top()
	{
		if(dir==read)
		{
			if (data.empty() && !eof)
			{
				 if(read_next_block())	 return data.front();
				 else return record();
			}
			return data.front();
		}
		return record();
	}
	record pop()
	{
		eos=false;
		record ret(0);
		if (data.empty() && !eof)
		{ 
			if(sorting)
			{
				for(int i=0;i<n;i++) read_next_block();
				data.sort();
			}
			else read_next_block();
		}
		ret=data.front();
		data.pop_front();
		if (data.empty() && !eof)
		{ 
			if(sorting)
			{
				for(int i=0;i<n;i++) read_next_block();
				data.sort();
			}
			else read_next_block();
		}
		if(data.front().broken()) eos=true;
		if(data.front()<ret) eos=true;
		return ret;
	}
	
	
	bool next_series()
	{
				cerr<<"          NEXT "<<endl;

		eos=false;
		if(dir==read) 
		{
			//cout<<"next series"<<endl;
			eos=false;
			//if(data.empty())read_next_block();
			return eos;
		}
		if(dir==write)
		{
			//cout<<"next write file: ";
			flush();
			fclose(tape);
			char name[50];
			if(inplace)snprintf(name, sizeof(name), "%d_%d.tape", (series+1)%2,(save_id)%(n-1));
			else snprintf(name, sizeof(name), "%d_%d.tape", series+1,(save_id)%(n-1));
			//cout<<name<<endl;
			save_id++;
			tape=fopen(name,"ab");
			if(tape==NULL) cout<<"syplo sie"<<endl;
			return true;
		}
	}
	void push(record rec)
	{
		if(last_rec>rec){next_series();}
		tmp_buff_ptr+=(int)rec.to_bin((char*)(tmp_buff+tmp_buff_ptr));
		if(tmp_buff_ptr>=bufsize)   save();
		last_rec=rec;
	}

	void save()
	{
		cerr<< "                                  SAVING "<<write_counter<<endl;

		fwrite(tmp_buff,1,bufsize,tape);
		int j=0;
		for(int i=bufsize; i<tmp_buff_ptr ; i++) 
		{
			j++;
			tmp_buff[i-bufsize]=tmp_buff[i];
		}
		tmp_buff_ptr=j;
		//cout<< tmp_buff_ptr<<"tmpbufptr"<<endl;
		write_counter++;
	}
	
	void flush()
	{
		if(tmp_buff_ptr>0)
		{
			fwrite(tmp_buff,1,tmp_buff_ptr,tape);
			tmp_buff_ptr=0;
			write_counter++;
			
		}
	}
	void clear_files(int runds,int tapes)
	{
		char name[50];
		for(int i=0;i<tapes;i++)
		{
			snprintf(name, sizeof(name), "%d_%d.tape", (runds+1)%2,i);
			remove(name);
			//tape=fopen(name,"w");
			//fclose(tape);
			
		}
	}
		
	int tapes_used(){return min(save_id,n-1);}
	int reads(){return read_counter;}
	int writes(){return write_counter;}
	bool series_end(){return eos||empty();}
	bool empty(){return eof && data.empty();	}
	
	private:
	list<record> data;
	FILE *tape;
	direction dir;
	bool eof; //end of file
	bool eos; //end of series
	int bufsize;
	int tmp_buff_ptr;
	char *tmp_buff;
	int tmp_buff_size;
	int offset;
	int write_counter;
	int read_counter;
	record last_rec;
	int save_id;
	int series;
	int n;//number of buffers
	bool sorting;
	bool inplace;
		
	bool valid_record(char* rawData, int i ,int buff_size)	{return ((int)rawData[i]+i+1<=buff_size) ;}
	
	
	bool read_next_block()
	{
		cerr<<"READING "<<read_counter<<endl;
		//data.push_back(record());
		bool ret=false;
		int i=0;
		if(eof) return ret;
		int read_bytes=fread(tmp_buff+offset,1,bufsize,tape);
		read_counter++;
		if(read_bytes<1) 
		{
			eof=true;
			data.push_back(record(0));
			return ret;
		}
		
		while(true)
		{
		
			if(valid_record(tmp_buff,i,read_bytes+offset))
			{
				data.push_back(record(tmp_buff+i,&i));
				ret=true;
			}
			else
			{
				int tmpoffset=offset;	
				for (i,offset=0;i<read_bytes+tmpoffset;i++,offset++)
				{
					tmp_buff[offset]=tmp_buff[i];
				}
				
				break;
			}
		}
		if(feof(tape)) eof=true;
		if(sorting) sort();
		
		return ret;
	}
		
};
