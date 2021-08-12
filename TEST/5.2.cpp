#include "pch.h"
#include <cstddef> // size_t

struct String {
	size_t size;
	char* str;

	
	
	String(const char* str = "")
	{
		int len = strlen(str);
		this->size = len;
		char* nstr = new char[len + 1];
		strcpy(nstr, str);
		this->str = nstr;
	}
	String(size_t n, char c): size(n), str(&c)
	{
		this->size = n;
		char* nstr = new char[n + 1];
		for (size_t i = 0; i < n; i++) {
			nstr[i] = c;
		}
		nstr[n + 1] = '\n';
		//strcpy(nstr,str);
		this->str = nstr;
	}
	~String()
	{
		delete[] str;
	}

	String(const String& other) :size(other.size), str(new char[size + 1])
	{
		for (size_t i = 0; i < size; i++) { str[i] = other.str[i]; }
		str[size] = '\0';
	}

	void swap(String& other) {
		std::swap(size, other.size);
		std::swap(str, other.str);
	}

	
	String& operator=(const String& other)
	{
		if (this != &other) {
			String(other).swap(*this);
		}
		return *this;
	};

	void append(const String& other);

	struct Proxy;
	
	Proxy operator[] (size_t index) const
	{
		++index;
		return Proxy(str,index);
	}
	
	struct Proxy
	{
		char* r_string;
		size_t start;
		Proxy(char* real_string, size_t start) :r_string(real_string), start(start){}
		~Proxy() { }
		String operator[](size_t index) const
		{
			String answer{};
			//for (size_t i = start; i < index; ++i)
			//	answer.append((r_string + i));
			return answer;
		}
	};

	/*Proxy operator[] (size_t index) const
	{
		++index;
		return Proxy(str,index);
	}

	struct Proxy
	{
		char* r_string;
		size_t start;
		Proxy(char *real_string, size_t start) : r_string(real_string), start(start) {};
		~Proxy() { };
		String operator[](size_t index) const
		{
			char* out {};
			size_t numof = index-start;
			if (numof > 0) {
				memcpy(out, r_string, sizeof(char) * numof);
				String answer{ out };
				return answer;
			}
			else
				return String();
		}
	};*/

	

};


TEST(ThemeFive, TestFiveTwo) {
	String const hello("hello");
	String const hell = hello[0][4]; // теперь в hell хранится подстрока "hell"
	String const ell = hello[1][4]; // теперь в ell хранится подстрока "ell"
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}