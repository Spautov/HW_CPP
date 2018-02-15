#include <iostream>
#include <string.h>

class String
{
private:
	int lenght;
	char *content;
public:
	String(int num = 80): lenght(num)
	{
		content = new char[lenght];
		content[0] = '\0';
	}

	String(char *cont, int num = 80) : lenght(num)
	{
		content = new char[lenght];
		strncpy(content, cont, lenght - 1);
	}
	~String()
	{
		delete[] content;
	}

	char *strn()
	{
		return content;
	}

	int len()
	{
		int coun = 0;
		for (int i = 0; i < lenght; ++i)
		{
			if (content[i] == '\0')
			{
				return coun;
			}
			++coun;
		}
		return coun;
	}

	void str_get()
	{
		std::cin >> content;
	}
};

int main()
{
	String y;
	String k("UUUUU", 250);
	std::cout << k.len() << std::endl;
	std::cout << k.strn()<< std::endl;
	y.str_get();
	std::cout << y.strn() << std::endl;
	std::cout << y.len() << std::endl;
	return  0;
}