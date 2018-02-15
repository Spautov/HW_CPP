#include <iostream>
#include <string.h>

class reservoir
{
private:
	int MAX_LEN = 80;
	char *name;
	float width;
	float lendht;
	float hight;
	float vol;
	float s_mirror;
public:
	reservoir(char* nam = "new", float w = 1, float l = 1, float h = 1) : width(w), lendht(l), hight(h)
	{
		name = new char[MAX_LEN];
		strncpy(name, nam, MAX_LEN - 1);
		s_mirror = width*lendht;
		vol = s_mirror*hight;
	}

	reservoir(const reservoir &obj)  
	{
		name = new char[MAX_LEN];
		strncpy(name, obj.name, MAX_LEN - 1);
		width = obj.width;
		lendht = obj.lendht;
		hight = obj.hight;
		vol = obj.vol;
		s_mirror = obj.s_mirror;
	}  

	reservoir &operator=(const reservoir & obj)
	{
		if (this != &obj)
		{
			strncpy(name, obj.name, MAX_LEN - 1);
			width = obj.width;
			lendht = obj.lendht;
			hight = obj.hight;
			vol = obj.vol;
			s_mirror = obj.s_mirror;
		}
		return *this;
	}


	~reservoir()
	{
		delete[] name;
	}

	float def_vol()
	{
		vol = width*lendht*hight;
		return vol;
	}

	float def_s_mirror()
	{
		s_mirror = width*lendht;
		return s_mirror;
	}

	void set_name(char *nam)
	{
		strncpy(name, nam, MAX_LEN - 1);
	}

	void set_width(float w)
	{
		width = w;
	}
	void set_lendht(float l)
	{
		lendht = l;
	}
	void set_hight(float h)
	{
		hight = h;
	}

	char * get_name()const
	{
		return name;
	}

	float get_width()const
	{
		return width;
	}
	float get_lendht()const
	{
		return lendht;
	}
	float get_hight()const
	{
		return hight;
	}
	
	int cmp(reservoir &obj) const
	{
		if (s_mirror > obj.s_mirror)
		{
			return 1;
		}
		else if (s_mirror < obj.s_mirror)
		{
			return -1;
		}
		return 0;
	}

	
};
//--------------------
void add_iteam(reservoir **arr, int &num)
{
	int siz = num + 1;
	reservoir *tmp = new reservoir[siz];
	for (int i = 0; i < num; ++i)
	{
		tmp[i] = *(*arr + i);
	}
	delete[] * arr;
	*arr = tmp;
	num = siz;
}

reservoir pop_iteam(reservoir **arr, int &num)
{
	reservoir tmp = *(*arr + num);
	int siz = num - 1;
	reservoir *temp = new reservoir[siz];
	for (int i = 0; i < siz; ++i)
	{
		temp[i] = *(*arr + i);
	}
	delete[] * arr;
	*arr = temp;
	num = siz;
	return tmp;
}



int main()
{
	int siz = 15;
	reservoir *narach;
	narach = new reservoir[siz];
	add_iteam(&narach, siz);
	std::cout << narach[1].get_name()<< "--"<< siz << std::endl;
	add_iteam(&narach, siz);
	std::cout << narach[1].get_name() << "--" << siz << std::endl;
	pop_iteam(&narach, siz);
	std::cout << narach[1].get_name() << "--" << siz << std::endl;
	delete[] narach;
	return 0;
}