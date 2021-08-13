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
		return Proxy(str,index);
	}
	
	struct Proxy
	{
		size_t start;
		char* r_str;
		Proxy(char* str,size_t start) :start(start), r_str(str){}
		String operator[](size_t index) const
		{
			String answer = String();
			const size_t length = index - start;
			if ( length > 0)	
			{
				char* out_str = new char[length+1]();
				for (size_t i = 0; i < length; i++) {
					out_str[i] = r_str[i+start];
				}				
				answer = String(out_str);
				delete[] out_str;
			}
			return  answer;
		}
	};

};


TEST(ThemeFive, TestFiveTwo) {
	String const hello("hello");
	String const hell = hello[0][4]; // теперь в hell хранится подстрока "hell"
	String const ell = hello[1][4]; // теперь в ell хранится подстрока "ell"
	String const zero = hello[3][3];
	EXPECT_STREQ(hell.str, "hell");
	EXPECT_STREQ(ell.str, "ell");
	EXPECT_STREQ(zero.str, "");
    EXPECT_TRUE(true);
}