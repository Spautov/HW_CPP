#include <iostream>
#include <string.h>

class person
{
private:
	char *name;
	const int MAX_LEN = 80;
public:
	person()
	{
		name = new char[MAX_LEN];
		strncpy(name, "", MAX_LEN - 1);
	}

	person(char *my_name)
	{
		name = new char[MAX_LEN];
		strncpy(name, my_name, MAX_LEN - 1);
	}

	person(const person &obj)
	{
		name = new char[MAX_LEN];
		strncpy(name, obj.name, MAX_LEN - 1);
	}

	~person()
	{
		delete[] name;
	}

	void set_name(const char *new_name)
	{
		strncpy(name, new_name, MAX_LEN - 1);
	}
	char* get_name() const
	{
		return name;
	}
};

class flat
{
private:
	int Count = 0;
public:
	person *resident;
	flat(): Count(1)
	{
		resident = new person[Count];
	}

	flat(int num) : Count(num)
	{
		resident = new person[Count];
	}

	flat(const flat  &obj)
	{
		resident = new person[obj.Count];
		Count = obj.Count;
		for (int i = 0; i < obj.Count; ++i)
		{
			resident[i].set_name(obj.resident[i].get_name());
		}
	}

	flat & operator= (const flat &obj)
	{
		if (this != &obj)
		{
			delete[] resident;
			Count = obj.Count;
			resident = new person[Count];
			for (int i = 0; i < Count; ++i)
			{
				resident[i].set_name(obj.resident[i].get_name());
			}
		}
		return *this;
	}

	~flat()
	{
		delete[] resident;
	}

	void add_person(char *name)
	{
		int new_Count = Count + 1;
		person *tmp = new person[new_Count];
		for (int i = 0; i<Count; ++i)
		{
			tmp[i].set_name(resident[i].get_name());
		}
		tmp[new_Count - 1].set_name(name);
		Count = new_Count;
		resident = tmp;
	}
	int get_count()
	{
		return Count;
	}
};

class home
{
private:
	int Count = 1;
public:
	flat *number;
	home() : Count(1)
	{
		number = new flat[Count];
	}
	home(int num) : Count(num)
	{
		number = new flat[Count];
	}
	~home()
	{
		delete[] number;
	}

	void add_flat(int num)
	{
		int new_Count = Count + 1;
		flat *tmp = new flat[new_Count];
		for (int i = 0; i<Count; ++i) 
		{
			tmp[i] = flat(number[i].get_count());
			for (int j = 0; j < tmp[i].get_count(); ++j)
			{
				tmp[i].resident[j].set_name(number[i].resident[j].get_name());
			}
		}
		tmp[new_Count - 1] = flat(num);
		Count = new_Count;
		number = tmp;
	}    

	
	int get_count()
	{
		return Count;
	}
};


int main()
{
	
	home mosherova(3);
	mosherova.number[0].resident[0].set_name("Kolja");
	mosherova.number[1].resident[0].set_name("Tolja");
	mosherova.number[2].resident[0].set_name("Youra");
	mosherova.add_flat(3);
	std::cout << mosherova.number[0].get_count() << std::endl;
	std::cout << mosherova.get_count() << std::endl;
	std::cout << mosherova.number[1].resident[0].get_name() << std::endl;
	return 0;
}
