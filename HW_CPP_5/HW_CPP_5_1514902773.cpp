#include <iostream>
#include <vector>
#include <iterator>
#include <cstddef>


template<typename T>
class RingBuffer
{
private:
	int _max_size;
	int _size;
	std::vector<T> _buffer;
	int it_write;
	int it_begin;
public:
	RingBuffer() : _max_size(10), _size(0)
	{
		_buffer.resize(_max_size);
		it_write = 0;
		it_begin = -1;
	};

	RingBuffer(int count) : _max_size(count), _size(0)
	{
		_buffer.resize(_max_size);
		it_write = 0;
		it_begin = -1;
	};

	~RingBuffer() = default;


	void push(T const &var)
	{
		_buffer.at(it_write) = var;
		if (it_write == it_begin && _size != 0)
		{
			if (it_begin == _max_size - 1)
			{
				it_begin = 0;
			}
			else
			{
				++it_begin;
			}
		}
		if (_size == 0)
		{
			it_begin = 0;
		}
		if (_size < _max_size)
		{
			++_size;
		}
		
		if (it_write == _max_size - 1)
		{
			it_write = 0;
		}
		else
		{
			++it_write;
		}
	}

	T& at(int num)
	{
		int temp;
		temp = (it_begin + num)% _max_size;
		return _buffer.at(temp);
	}

	T pop()
	{
		T temp = 0;

		if (_size > 0)
		{
			temp = _buffer.at(it_begin);
			++it_begin;
			--_size;
			if (it_begin == _max_size && _size != 0)
			{
				it_begin = 0;
			}
			if (_size == 0)
			{
				it_begin = -1;
				it_write = 0;
			}
		};
		return temp;
	} 

	int size() const
	{
		return _size;
	}

	int max_size() const
	{
		return _max_size;
	}

	void resize(int count)
	{
		std::vector<T> temp_buff(count);
		int start = it_begin;
		int end = it_write;
		int it_old;
		int it_new = 0;
		
		if (start >= 0)
		{
			if (end <= start)
			{
				end += _max_size;
			};

			for (int i = start; i < end; ++i)
			{
				it_old = i % _max_size;
				if (it_new < count)
				{
					temp_buff.at(it_new) = _buffer.at(it_old);
				}
				else
				{
					break;
				}
				++it_new;
			}
			it_begin = 0;
			if (_size > count)
			{
				_size = count;
			}
			_max_size = count;
			it_write = it_new;
			if (it_write == _max_size)
			{
				it_write = 0;
			}
			_buffer = temp_buff;
		}
	}

	 template<typename T1>
	 friend std::ostream& operator << (std::ostream &s, const  RingBuffer<T1> &rb);
};

template<typename T1>
std::ostream& operator << (std::ostream &s, const  RingBuffer<T1> &rb)
{
	int start = rb.it_begin;
	int end = rb.it_write;
	int temp;
	if (start >= 0)
	{
		if (end <= start)
		{
			end += rb._max_size;
		};
		for (int i = start; i <end; ++i)
		{
			temp = i % rb._max_size;
			s << rb._buffer.at(temp) << "\n";
		}
	}
	return s;
}


int main()
{
	//TEST: RingBuffer()
	RingBuffer<int> first_ring;
	std::cout << "TEST: RingBuffer() - ";
	if (first_ring.max_size() == 10)
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	};
	
	//TEST: RingBuffer(int count)
	RingBuffer<float> second_ring(37);
	std::cout << "TEST: RingBuffer(int count) - ";
	if (second_ring.max_size() == 37)
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	};

	//TEST: push()
	std::cout << "TEST: push() - ";
	first_ring.push(15);
	first_ring.push(16);
	first_ring.push(17);
	if ((first_ring.size() == 3) && (first_ring.at(1) == 16))
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	};

	//TEST: ring write 
	std::cout << "TEST: ring write -  ";
	first_ring.push(18);
	first_ring.push(19);
	first_ring.push(20);
	first_ring.push(21);
	first_ring.push(22);
	first_ring.push(23);
	first_ring.push(24);
	first_ring.push(25);
	first_ring.push(26);
	if ((first_ring.size() == 10) && (first_ring.at(0) == 17))
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	};
	
	//TEST: pop()
	std::cout << "TEST: pop() - ";
	int help_var = first_ring.pop();
	if ((first_ring.size() == 9) && help_var == 17 && (first_ring.at(0) == 18))
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	};

	//TEST: size()
	std::cout << "TEST: size() - ";
	first_ring.pop();
	first_ring.pop();
	first_ring.push(27);
	if (first_ring.size() == 8)
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	};
	//TEST: max_size()
	std::cout << "TEST: max_size() - ";
	help_var = first_ring.max_size();
	first_ring.pop();
	first_ring.pop();
	first_ring.push(29);
	first_ring.push(30);
	first_ring.push(31);
	first_ring.push(32);
	first_ring.push(33);
	first_ring.push(34);
	if (first_ring.max_size() == help_var && first_ring.max_size() == 10)
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	};
	//TEST: resize() #1
	std::cout << "TEST: resize()  #1 - ";
	first_ring.resize(15);
	first_ring.push(35);
	first_ring.push(35);
	first_ring.push(36);
	first_ring.push(38);
	first_ring.push(39);
	if (first_ring.max_size() == 15 && first_ring.size() == 15 && first_ring.at(14) == 39)
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	};

	//TEST: resize() #2
	std::cout << "TEST: resize()  #2 - ";
	first_ring.resize(8);
	
	if (first_ring.max_size() == 8 && first_ring.size() == 8 && first_ring.at(7) == 32)
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	};

	return 0;
}
