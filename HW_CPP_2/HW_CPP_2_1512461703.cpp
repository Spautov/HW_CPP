#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

class Time
{
private:
	int seconds_ = 0;
public:
	explicit Time() = default;
	explicit Time(int seconds) : seconds_(seconds) { }
	Time(int seconds, int minuts, int hours)
	{
		seconds_ = 3600 * hours + 60 * minuts + seconds;
	}
	Time(const Time &t) : seconds_(t.seconds_) { }
	Time(Time &&t)
	{
		seconds_ = t.seconds_;
		t.seconds_ = 0;
	}
	~Time() = default;

	int get_seconds() const
	{
		return seconds_ % 60;
	}

	int get_minuts() const
	{
		return (seconds_ % 3600) / 60;
	}
	int get_hours() const
	{
		return (seconds_ / 3600) %24;
	}

	void set_time(int hour, int minu = 0, int sec = 0)
	{
		seconds_ = sec + (60 * minu) + (3600 * hour);
	}

	void set_time(int hour, int minu, int sec, std::string st)
	{
	    transform(st.begin(), st.end(), st.begin(), toupper);
	    if (st == "AM")
        {
            seconds_ = sec + (60 * minu) + (3600 * hour);
        }
        else if (st == "PM")
        {
            seconds_ = sec + (60 * minu) + (3600 * (hour+12));
        }
	}

	Time& operator=(const Time &t)
	{
		this->seconds_ = t.seconds_;
	}

	Time& operator++()
	{
		seconds_++;
		return *this;
	}

	Time operator++(int)
	{
		Time t(*this);
		seconds_++;
		return t;
	}

	Time& operator--()
	{
		seconds_--;
		return *this;
	}

	Time operator--(int)
	{
		Time t(*this);
		seconds_--;
		return t;
	}
	friend Time operator+(Time t1, const Time &t2);
	friend Time operator-(Time t1, const Time &t2);
	friend Time operator+=(Time &t1, const Time &t2);
	friend Time operator-=(Time &t1, const Time &t2);


};


Time operator+(Time t1, const Time &t2)
{
	t1.seconds_ += t2.seconds_;
	return t1;
}

Time operator-(Time t1, const Time &t2)
{
	t1.seconds_ -= t2.seconds_;
	return t1;
}

Time operator+=(Time &t1, const Time &t2)
{
	t1.seconds_ += t2.seconds_;
	return t1;
}

Time operator-=(Time &t1, const Time &t2)
{
	t1.seconds_ -= t2.seconds_;
	return t1;
}


std::ostream& operator<<(std::ostream &s, const Time& t)
{
	if (t.get_hours() <= 12)
	{
		s << t.get_hours() << ":" << t.get_minuts() << ":" << t.get_seconds() << " AM";
		return s;
	}
	else
	{
		s << t.get_hours()%12 << ":" << t.get_minuts() << ":" << t.get_seconds() << " PM";
		return s;
	}
}

std::istream& operator>> ( std::istream& is, Time& t )
{
    int h;
    int m;
    int s;
    std::string st;
   is >> h >> m >> s >> st;
   t.set_time(h, m, s, st);
   return is;
}



int main()
{
	Time U1(417);
    Time U2(516);
    Time U3;

    std::cout << "Test operator + :";
    U3 = U1 + U2;
    if (U3.get_seconds() == 33 && U3.get_minuts() == 15 && U3.get_hours() == 0)
    {
        std::cout << " OK" <<std::endl;
    }
    else
    {
        std::cout << " ERROR" <<std::endl;
    }

	std::cout << "Test operator - :";
	U3 = U2 - U1;
    if (U3.get_seconds() == 39 && U3.get_minuts() == 1 && U3.get_hours() == 0)
    {
        std::cout << " OK" <<std::endl;
    }
    else
    {
        std::cout << " ERROR" <<std::endl;
    }

    std::cout << "Test operator ++ pref :";
    U3 = U1 + U2;
    ++U3;
    if (U3.get_seconds() == 34 && U3.get_minuts() == 15 && U3.get_hours() == 0)
    {
        std::cout << " OK" <<std::endl;
    }
    else
    {
        std::cout << " ERROR" <<std::endl;
    }

    std::cout << "Test operator ++ post :";
    U3 = U1++ + U2;

    if (U3.get_seconds() == 33 && U3.get_minuts() == 15 && U3.get_hours() == 0 && U1.get_seconds() == 58 &&
        U1.get_minuts() == 6 && U1.get_hours() == 0)
    {
        std::cout << " OK" <<std::endl;
    }
    else
    {
        std::cout << " ERROR" <<std::endl;
    }

    U1.set_time(0,0,270);
    U2.set_time(0,0,34);

    std::cout << "Test operator -- pref :";
    U3 = U1 + U2;
    --U3;
    if (U3.get_seconds() == 3 && U3.get_minuts() == 5 && U3.get_hours() == 0)
    {
        std::cout << " OK" <<std::endl;
    }
    else
    {
        std::cout << " ERROR" <<std::endl;
    }

    std::cout << "Test operator -- post :";
    U1.set_time(1,16,27);
    U2.set_time(3,29,34);

    U3 = U1-- + U2;
    U3;
    if (U3.get_seconds() == 1 && U3.get_minuts() == 46 && U3.get_hours() == 4 && U1.get_seconds() == 26 &&
        U1.get_minuts() == 16 && U1.get_hours() == 1)
    {
        std::cout << " OK" <<std::endl;
    }
    else
    {
        std::cout << " ERROR" <<std::endl;
    }

    std::cout << "Test operator = :";
    U1.set_time(6,0,54);
    U3 = U1;
    if (U1.get_seconds() == U3.get_seconds() && U1.get_minuts() == U3.get_minuts() && U1.get_hours() == U3.get_hours())
    {
        std::cout << " OK" <<std::endl;
    }
    else
    {
        std::cout << " ERROR" <<std::endl;
    }

    std::cout << "Test operator += :";
    U1.set_time(0,4,54);
    U2.set_time(2,38,48);
    U1 += U2;

    if (U1.get_seconds() == 42 && U1.get_minuts() == 43 && U1.get_hours() == 2)
    {
        std::cout << " OK" <<std::endl;
    }
    else
    {
        std::cout << " ERROR" <<std::endl;
    }

    std::cout << "Test operator -= :";
    U1.set_time(2,29,54);
    U2.set_time(1,15,43);
    U1 -= U2;

    if (U1.get_seconds() == 11 && U1.get_minuts() == 14 && U1.get_hours() == 1)
    {
        std::cout << " OK" <<std::endl;
    }
    else
    {
        std::cout << " ERROR" <<std::endl;
    }

    std::cout << "Test operator << :";
    std::cout << U1 << std::endl;
    std::cout << "Test operator >> :";
    std::cin >> U1 ;
    std::cout << U1 << std::endl;

	return 0;
}
