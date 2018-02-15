#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <string.h>


class decart
{
	const float PI = 3.14159265358979f;
public:
	float x = 0.0;
	float y = 0.0;

	decart() = default;
	decart(float xin, float yin) : x(xin), y(yin)
	{	}

	decart(const decart &dec)
	{
		x = dec.x;
		y = dec.y;
	}

	decart& operator = (const decart &dec)
	{
		if (this != &dec)
		{
			x = dec.x;
			y = dec.y;
		}
		return *this;
	}


	const bool operator== (const decart &top)
	{
		if ((x == top.x) && (y == top.y))
		{
			return true;
		}
		return false;
	}

	const bool operator!= (const decart &top)
	{
		if ((x != top.x) || (y != top.y))
		{
			return true;
		}
		return false;
	}

	float line(const decart &d);
	float angle(decart &d_prev, const decart &d_foll);


};

class polygon
{
private:
	std::vector<decart> corner;
	void turn();
	bool cmp(polygon &obj);
public:
	polygon()
	{
		corner.push_back(decart(0.0, 0.0));
		corner.push_back(decart(0.5, 0.87));
		corner.push_back(decart(1.0, 0.0));
	};
	void add(int pos, const float &xin, const float &yin)
	{
		if (pos >= 0 && pos<corner.size())
		{
			corner.insert(corner.begin() + pos, decart(xin, yin));
		}
		else if (pos == corner.size())
		{
			corner.insert(corner.end(), decart(xin, yin));
		}
	};

	void del(int pos)
	{
		if (pos >= 0 && pos<corner.size())
		{
			corner.erase(corner.begin() + pos);
		}
	}

	int get_size()
	{
		return corner.size();
	}
	friend const bool operator==(polygon &pol1, polygon pol2);
	friend const bool operator!=(polygon &pol1, const polygon &pol2);
	operator bool();
	void move(const int &dx, const int &dy);
	float perimeter();
	float aver_leng();
	bool is_right();
};

std::ostream& operator << (std::ostream &s, const decart &d);
std::ostream &operator<<(std::ostream &s, polygon &pol);

int main()
{

	decart d1(0.8, 3.6);
	std::cout << "Test operator \"<<\" for decert: " << d1 << std::endl;

	decart d2 = d1;
	std::cout << "Test operators \"=\" and \"==\" for decert: ";
	if (d1 == d2)
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	}
	decart d3(1.0, 0.0);

	std::cout << "Test operator \"!=\" for decert: ";
	if (d1 != d3)
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	}

	polygon figure1;
	polygon figyre2;

	figyre2.add(figyre2.get_size(), 1.0, 0.0);
	figyre2.add(figyre2.get_size(), 0.5, 0.87);
	figyre2.add(figyre2.get_size(), 0.0, 0.0);
	figyre2.del(0);
	figyre2.del(0);
	figyre2.del(0);
	std::cout << "Test operators \"==\" for polygon: ";
	if (figure1 == figyre2)
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	}

	figyre2.add(figyre2.get_size(), 7.0, 12.0);

	std::cout << "Test operators \"!=\" for polygon: ";
	if (figure1 != figyre2)
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	}

	std::cout << "Test method  \"perimetr\" for polygon: ";
	if (abs(figure1.perimeter() - 3.006) < 0.001)
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	}

	std::cout << "Test method  \"aver_len\" for polygon: ";
	if (abs(figure1.aver_leng() - 1.002) < 0.001)
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	}
	
	std::cout << "Test operators \"bool()\" for polygon: ";
	if (bool( figyre2))
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	}

	
	figyre2.del(0);
	figyre2.del(0);
	figyre2.del(0);
	figyre2.del(0);
	figyre2.add(figyre2.get_size(), 0.0, 0.0);
	figyre2.add(figyre2.get_size(), 1.0, 0.0);
	figyre2.add(figyre2.get_size(), 1.0, 1.0);
	figyre2.add(figyre2.get_size(), 0.0, 1.0);

	std::cout << "Test method  \"is_right\" for polygon: ";
	if (figyre2.is_right())
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	}
	
	std::cout << "Test operator \"<<\": " << figure1 << std::endl;
	std::cout << "Test operator \"<<\": " << figyre2 << std::endl;

	return 0;
}

float decart::line(const decart &d)
{
	float deltaX = d.x - x;
	float deltaY = d.y - y;
	float l = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	return l;
}

float decart::angle(decart & d_prev, const decart & d_foll)
{
	float side1 = line(d_prev);
	float side2 = line(d_foll);
	float side3 = d_prev.line(d_foll);
	float cos_angle = (pow(side1, 2) + pow(side2, 2) - pow(side3, 2)) / (2 * side1*side2);
	float angl = acos(cos_angle)*180/PI;
	return angl;
}

void polygon::turn()
{
	if (corner.size() >= 3)
	{
		decart tmp;
		tmp = corner.at(0);
		int lim = corner.size() - 1;
		for (int i = 0; i < lim; ++i)
		{
			corner.at(i) = corner.at(i + 1);
		}
		corner.at(lim) = tmp;
	}
}

bool polygon::cmp(polygon & obj)
{
	if (corner.size() != obj.corner.size())
	{
		return false;
	}
	int lim = corner.size()-1;
	float line_in;
	float line_out;
	float angle_in;
	float angle_out;
	bool cmp_line;
	bool cmp_angle;

	for (int i = 1; i < lim; ++i)
	{
		line_in = corner.at(i).line(corner.at(i + 1));
		angle_in = corner.at(i).angle(corner.at(i - 1), corner.at(i + 1));
		line_out = obj.corner.at(i).line(obj.corner.at(i + 1));
		angle_out = obj.corner.at(i).angle(obj.corner.at(i - 1), obj.corner.at(i + 1));
		cmp_line = abs(line_in - line_out) > 0.00001;
		cmp_angle = abs(angle_in - angle_out) > 0.00001;
		if (cmp_line || cmp_angle)
		{
			return false;
		}
	}

	line_in = corner.at(0).line(corner.at(1));
	angle_in = corner.at(0).angle(corner.at(lim), corner.at(1));
	line_out = obj.corner.at(0).line(obj.corner.at(1));
	angle_out = obj.corner.at(0).angle(obj.corner.at(lim), obj.corner.at(1));
	cmp_line = abs(line_in - line_out) > 0.00001;
	cmp_angle = abs(angle_in - angle_out) > 0.00001;
	if (cmp_line || cmp_angle)
	{
		return false;
	}
	line_in = corner.at(lim).line(corner.at(0));
	angle_in = corner.at(lim).angle(corner.at(lim - 1), corner.at(0));
	line_out = obj.corner.at(lim).line(obj.corner.at(0));
	angle_out = obj.corner.at(lim).angle(obj.corner.at(lim - 1), obj.corner.at(0));
	cmp_line = abs(line_in - line_out) > 0.00001;
	cmp_angle = abs(angle_in - angle_out) > 0.00001;
	if (cmp_line || cmp_angle)
	{
		return false;
	}
	return true;
}

polygon::operator bool()
{
	if (this->corner.size() > 0)
	{
		return true;
	}
	return false;
}


void polygon::move(const int &dx, const int &dy)
{
	int lim = corner.size();
	for (int i = 0; i < lim; ++i)
	{
		corner.at(i).x += dx;
		corner.at(i).y += dy;
	}
}

float polygon::perimeter()
{
	int lim = corner.size() - 1;
	float lenght = 0.0f;
	for (int i = 0; i < lim; ++i)
	{
		lenght += corner.at(i).line(corner.at(i + 1));
	}
	lenght += corner.at(lim).line(corner.at(0));

	return lenght;
}

float polygon::aver_leng()
{
	float lenght = (perimeter() / corner.size());
	return lenght;
}

bool polygon::is_right()
{
	float examole = 180 - (360 / float(corner.size()));
	int lim = corner.size() - 1;
	float angle = 0.0f;
	for (int i = 1; i < lim; ++i)
	{
		angle = corner.at(i).angle(corner.at(i - 1), corner.at(i + 1));
		
		if (abs(angle - examole) > 0.001)
		{ 
			return false;
		}
	}
	angle = corner.at(0).angle(corner.at(lim), corner.at(1));
	if (abs(angle - examole) > 0.001)
	{
		return false;
	}

	angle = corner.at(lim).angle(corner.at(lim - 1), corner.at(0));

	if (abs(angle - examole) > 0.001)
	{
		return false;
	}
	return true;
}

const bool operator==(polygon & pol1, polygon pol2)
{
	int lim = pol1.corner.size();
	bool tmp = false;
	for (int i = 0; i < lim; ++i)
	{
		tmp = pol1.cmp(pol2);
		if (tmp) 
		{
			return tmp;
		}
		pol2.turn();
	}
	return tmp;
}

const bool operator!=(polygon &pol1, const polygon &pol2)
{
	return !(pol1 == pol2);
}

std::ostream& operator<<(std::ostream &s, const decart &d)
{
	s << "X:" << d.x << " " << "Y:" << d.y;
	return s;
}


std::ostream &operator<<(std::ostream &s, polygon &pol)
{
	if (pol.is_right())
		{
		s << "angle: "  << pol.get_size() << ", perimeter: " << pol.perimeter()
			<< ", average length side: " << pol.aver_leng()
			<< ", the polygon is regular";
	}
	else
	{
		s << "angle: " << pol.get_size()
			<< ", perimeter: " << pol.perimeter()
			<< ", average length side: " << pol.aver_leng()
			<< ", the polygon is not regular";
	}

	return s;
}
 
