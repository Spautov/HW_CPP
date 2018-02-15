#include <iostream>
#include <string>
#include <iomanip>

class Student
{
private:
    std::string name_;
    int age_;

public:
    const std::string &get_name() const
    {
        return name_;
    }
    void set_name(const std::string name)
    {
        name_ = name;
    }
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
        age_ = s.age_;
    }

    Student(std::string name, int age) : name_(name), age_(age)
    {	}

    Student() : name_("None"), age_(0)
    {	}

    Student &operator=(const Student &s)
    {
        if (this != &s)
        {
            name_ = s.name_;
            age_ = s.age_;
        }
        return *this;
    }

};

class Group
{
private:
    Student *member_;
    int coun_;

public:
    Group()
    {
        member_ = nullptr;
        coun_ = 0;
    }

    Group(int num)
    {
        member_ = new Student[num];
        coun_ = num;
    }

    Group(const Group &g)
    {
        if (g.coun_>0)
        {
            delete[] member_;
            coun_ = g.coun_;
            member_ = new Student[coun_];
            for (int i = 0; i<coun_; ++i)
            {
                member_[i] = g.member_[i];
            }
        }
        else
        {
            delete[] member_;
            member_ = nullptr;
            coun_ = 0;
        }
    }

    Group &operator=(const Group &g)
    {
        if (this != &g)
        {
            if (g.coun_>0)
            {
                delete[] member_;
                coun_ = g.coun_;
                member_ = new Student[coun_];
                for (int i = 0; i<coun_; ++i)
                {
                    member_[i] = g.member_[i];
                }
            }
            else
            {
                delete[] member_;
                member_ = nullptr;
                coun_ = 0;
            }
        }
        return *this;
    }

    ~Group()
    {
        delete[] member_;
    }

    void push(const Student &s)
    {
        if (coun_ > 0)
        {
            Student *tmp = new Student[coun_ + 1];
            for (int i = 0; i < coun_; ++i)
            {
                tmp[i] = member_[i];
            }
            tmp[coun_] = s;
            delete[] member_;
            member_ = tmp;
        }
        else
        {
            member_ = new Student[coun_ + 1];
            member_[coun_] = s;
        }
        ++coun_;
    }

    Student pop()
    {
        int temp_count = coun_;
        Student tmp;
        if (coun_ > 1)
        {
            Student *temp = new Student[coun_ - 1];
            for (int i = 0; i < (coun_ - 1); ++i)
            {
                temp[i] = member_[i];
            }
            tmp = member_[coun_ - 1];
            delete[] member_;
            member_ = temp;
            --temp_count;
        }
        else if (coun_ == 1)
        {
            tmp = member_[coun_ - 1];
            delete[] member_;
            member_ = nullptr;
            --temp_count;
        }
        coun_ = temp_count;
        return tmp;
    }

    int get_count()const
    {
        return coun_;
    }

    Student get_member(const int num) const
    {
        if (num >= 0 && num < coun_)
        {
            return member_[num];
        }
        return Student();
    }

    void set_member(const int num, const std::string name, const int age)
    {
        if (num >= 0 && num < coun_)
        {
            member_[num].set_name(name);
            member_[num].set_age(age);
        }
    }

    void set_member(const int num, const Student &s)
    {
        if (num >= 0 && num < coun_)
        {
            member_[num] = s;
        }
    }

    void show() const
    {
        if (coun_>0)
        {
            std::cout<<std::setw(4)<< "#"<<std::setw(15)<< "NAME" << std::setw(6)<< "AGE"<< std::endl;
            for (int i = 0; i<coun_; ++i)
            {
                std::cout<<std::setw(4)<< i <<std::setw(15)
                << member_[i].get_name() << std::setw(6)<< member_[i].get_age() << std::endl;
            }
        }
        else
        {
            std::cout<<"The group has no members" << std::endl;
        }
        std::cout<< std::endl<< std::endl;
    }

    void sorting_name()
    {
        Student tmp;
        bool k;
        for (int i = 0; i<=(coun_ - 2); ++i)
        {
            for (int j = 0; j<=(coun_ - 2)-i; ++j)
            {
                k = (member_[j].get_name() > member_[j+1].get_name());
                if (k)
                {
                    tmp = member_[j];
                    member_[j] = member_[j+1];
                    member_[j+1]= tmp;
                }
            }
        }
    }
};



int main()
{
    Group group1(3);
    Group group2;
    group1.set_member(0, "Dasha", 14);
    group1.set_member(1, "Kolja", 13);
    group1.set_member(2, "Stas", 14);
    group1.show();
    group2.push(Student("Vitaliy", 17));
    group2.push(Student("Andrey", 16));
    group2.push(Student("Dmitriy", 17));
    group2.push(Student("Zoja", 17));
    group2.show();
    group2.sorting_name();
    group2.show();
    group1.sorting_name();
    group1.show();
    group1.pop();
    group1.show();
    return 0;
}
