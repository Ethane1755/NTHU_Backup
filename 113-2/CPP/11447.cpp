#include<cassert>
#include<iostream>
#include<map>
#include<ostream>
#include<string>
#include"11447.h"

namespace oj
{
	String::String(const std::string &str_)
		:str(str_){}

	String::String(const String &rhs)
		:str(rhs.str){}

	String& String::operator=(const String &rhs)
	{
		str=rhs.str;
		return *this;
	}

	std::ostream& operator<<(std::ostream &os,const String &str)
	{
		return os<<str.str;
	}
	void insert(std::map<int, String> &ma, int key, const std::string &str) {
        auto it = ma.find(key);
        if (it != ma.end()) it->second.str = str + it->second.str;
        else ma.insert({key, String(str)});
    }

    void output(const std::map<int, String> &ma, int begin, int end) {
        for (auto it = ma.lower_bound(begin); it != ma.end() && it->first <= end; ++it) {
            std::cout << it->second << " ";
        }
    }

    void erase(std::map<int, String> &ma, int begin, int end) {
        auto it = ma.lower_bound(begin);
        while (it != ma.end() && it->first <= end) {
            it = ma.erase(it); 
        }
    }

    std::ostream &operator<<(std::ostream &os, const std::map<int, String> &ma) {
        for (const auto &pair : ma) {
            os << pair.second << " ";
        }
        return os;
    }
}

int main()
{
	using namespace std;
	using namespace oj;
	map<int,String> ma;
	for(string cmd;cin>>cmd;)
	{
		if(cmd=="insert")
		{
			int key;
			cin>>key>>cmd;
			insert(ma,key,cmd);
		}
		else
			if(cmd=="range")
			{
				int begin,end;
				cin>>cmd>>begin>>end;
				if(cmd=="output")
					output(ma,begin,end);
				else
					if(cmd=="erase")
						erase(ma,begin,end);
					else
						assert(false);
			}
			else
				assert(false);
		cout<<ma<<endl;
	}
}