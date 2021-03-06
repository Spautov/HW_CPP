#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <vector>
#include <algorithm>

class Student
{
private:
	std::string name_;
	std::string surname_;
	int age_;
	std::string to_upper_(const std::string &str)
	{
		std::string tmp("");
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			tmp += toupper(*it);
		}
		return tmp;
	}

public:
	const std::string &get_name() const
	{
		return name_;
	}
	void set_name(const std::string name)
	{
		name_ = to_upper_(name);
	}
	//---
	const std::string &get_surname() const
	{
		return surname_;
	}
	void set_surname(const std::string surname)
	{
		surname_ = to_upper_(surname);
	}
	//---
	int get_age() const
	{
		return age_;
	}
	void set_age(int age)
	{
		age_ = age;
	}
	Student(const Student &s)
	{
		name_ = s.name_;
		surname_ = s.surname_;
		age_ = s.age_;
	}

	Student(std::string name, std::string surname, int age) : name_(to_upper_(name)), 
												surname_(to_upper_(surname)),age_(age)
	{	}

	Student() : name_(""), surname_(""), age_(0)
	{	}

	Student &operator=(const Student &s)
	{
		if (this != &s)
		{
			name_ = s.name_;
			surname_ = s.surname_;
			age_ = s.age_;
		}
		return *this;
	}

	friend std::ostream& operator <<(std::ostream& os, const Student& stud);
};



class Group 
{
	std::vector<Student> member_;
	
	struct sort_class_name
	{
		bool operator() (Student stud1, Student stud2)
		{
			return (stud1.get_name() < stud2.get_name());
		}
	} sort_object_name;

	struct sort_class_surname
	{
		bool operator() (Student stud1, Student stud2)
		{
			return (stud1.get_surname() < stud2.get_surname());
		}
	} sort_object_surname;

	struct sort_class_age
	{
		bool operator() (Student stud1, Student stud2)
		{
			return (stud1.get_age() < stud2.get_age());
		}
	} sort_object_age;

	std::string to_upper_(const std::string &str)
	{
		std::string tmp("");
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			tmp += toupper(*it);
		}
		return tmp;
	}

public:
	Group() = default;
	Group(Student st)
	{
		member_.push_back(st);
	}
	Group(std::vector<Student> member)
	{
		member_.swap(member);
	}
	~Group() = default;
	bool empty() const
	{
		return member_.empty();
	}
	int size()
	{
		return member_.size();
	}
	void push(Student &stud)
	{
		member_.push_back(stud);
	}
	void push(std::string name, std::string surname, int age)
	{
		member_.push_back(Student(name, surname, age));
	}
	Student &at(int num)
	{
		return member_.at(num);
	}
	
	void erase(int num)
	{
		member_.erase(member_.begin()+num);
	}

	void sort_name()
	{
		if (!member_.empty())
		{
			std::sort(member_.begin(), member_.end(), sort_object_name);
		}
	}
	
	void sort_surname()
	{
		if (!member_.empty())
		{
			std::sort(member_.begin(), member_.end(), sort_object_surname);
		}
	}
	
	void sort_age()
	{
		if (!member_.empty())
		{
			std::sort(member_.begin(), member_.end(), sort_object_age);
		}
	}

	int find_name(const std::string &name)
	{
		std::string tmp;
		tmp = to_upper_(name);
		for (auto it = member_.begin(); it != member_.end(); ++it)
		{
			if (it->get_name() == tmp)
			{
				return it - member_.begin();
			}
		}
		return -1;
	}

	int find_surname(const std::string &surname)
	{
		std::string tmp;
		tmp = to_upper_(surname);
		for (auto it = member_.begin(); it != member_.end(); ++it)
		{
			if (it->get_surname() == tmp)
			{
				return it - member_.begin();
			}
		}
		return -1;
	}

	int find_age(int age)
	{
		for (auto it = member_.begin(); it != member_.end(); ++it)
		{
			if (it->get_age() == age)
			{
				return it - member_.begin();
			}
		}
		return -1;
	}

	friend std::ostream& operator <<(std::ostream& os, const Group& grup);

};

int main()
{
	Group my_group;
	Student ivsn("Ivan", "Petrov", 19);
	my_group.push(ivsn);
	my_group.push("Katja", "Ivanova", 18);
	my_group.push("Artem", "Krivoy", 17);
	std::cout << "Creation of group:" << std::endl;
	std::cout << my_group << std::endl;
	std::cout << "sorting according to a name:" << std::endl;
	my_group.sort_name();
	std::cout << my_group << std::endl;
	std::cout << "sorting according to a surname:" << std::endl;
	my_group.sort_surname();
	std::cout << my_group << std::endl;
	std::cout << "sorting according to a age:" << std::endl;
	my_group.sort_age();
	std::cout << my_group << std::endl;

	std::cout << "search in a name:" << std::endl;
	std::cout << "member # "<< my_group.find_name(std::string("Katja"))<< " has name \"Katja\"" << std::endl;
	std::cout << "search in a surname:" << std::endl;
	std::cout << "member # " << my_group.find_surname(std::string("Krivoy")) << " has surname \"Krivoy\"" << std::endl;
	std::cout << "search in a age:" << std::endl;
	std::cout << "member # " << my_group.find_age(19) << " is 19 ears old " << std::endl;

    return 0;
}

std::ostream & operator<<(std::ostream & os, const Student & stud)
{
	os << stud.get_name() << " " << stud.get_surname() << " : " << stud.get_age();
	return os;
}

std::ostream & operator<<(std::ostream & os, const Group & grup)
{
	if (!grup.empty())
	{
		for (auto it = grup.member_.begin(); it != grup.member_.end(); ++it)
		{
			os << "# " << it - grup.member_.begin() <<" : " << *it << std::endl;
		}
	}
	return os;
}
