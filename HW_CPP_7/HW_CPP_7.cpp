#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <fstream>

class Base
{
public:
	virtual void show(std::ofstream &fout) const {};
};

template<typename TBase>
class Storable : public Base
{
	TBase _value;
public:
	Storable() : _value(0) {};
	Storable(TBase begin_value) : _value(begin_value) {};
	virtual void show(std::ofstream &fout) const
	{
		if (fout.is_open() == 0)
		{
			std::cout << "The file was not opened \n";
			return;
		}
		std::cout << typeid(Storable).name() << " : " << _value << std::endl;
		fout << typeid(Storable).name() << " : " << _value << std::endl;
	};
	
	TBase get() const
	{
		return _value;
	}
};


class My_class
{
public:
	int _value = 0;
	My_class() = default;
	My_class(int number) : _value(number) {};
	friend std::ostream& operator << (std::ostream &s, const  My_class &my_obj);
};

std::ostream& operator << (std::ostream &s, const  My_class &my_obj);


class All_objects
{
	std::vector<std::unique_ptr<Base>> _object;
public:
	All_objects() = default;
		
	void push_back(std::unique_ptr<Base> ptr)
	{
		_object.push_back(std::move(ptr));
	}
	void show(std::ofstream &fout) const
	{
		if (_object.empty())
		{
			std::cout << "The object has no members\n";
			return;
		}
		if (fout.is_open() == 0)
		{
			std::cout << "The file was not opened \n";
			return;
		}
		for (auto &ptr : _object)
		{
			ptr->show(fout);
		}

	}
};

int main()
{
	All_objects my_arr;
	my_arr.push_back(std::unique_ptr<Base>(new Storable<int>(50)));
	my_arr.push_back(std::unique_ptr<Base>(new Storable<float>(25.3652f)));
	my_arr.push_back(std::unique_ptr<Base>(new Storable<My_class>(250)));
	std::ofstream f("out_file.txt");
	my_arr.show(f);
	f.close();
	return 0;
}

std::ostream & operator<<(std::ostream & s, const My_class & my_obj)
{
	s << my_obj._value;
	return s;
}