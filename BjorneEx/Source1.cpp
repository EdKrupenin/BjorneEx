/*#include <cstddef> // size_t

struct String {
	String(const char* str = "");
	String(size_t n, char c);
	~String();

	String(const String& other);
	String& operator=(const String& other);

	void append(const String& other);

	struct Proxy
	{
		Proxy(String* real_string) : real_string(new String(*real_string)) {
		}
		~Proxy() {
			delete real_string;
		};

		void append(const Proxy& other);
		String operator[] (size_t j)
		{
			return String();
		}
		size_t size;
		String* real_string;
	};

	Proxy operator[](size_t index) {
		return Proxy(_arrayofarrays[index],int j);
	}
	
	size_t size;
	char* str;
};*/