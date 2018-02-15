#include <iostream>
#include <string>

std::string convers(int number, const int base);
template<typename T>
std::ostream& print_number(std::ostream& s, T number, const int &base);

int main()
{
    int n = 312;
    std::cout << "Number: " << n << " in a coordinate system:" << std::endl;
    std::cout << "2: ";
    print_number(std::cout, n,2);
    std::cout << "3: ";
    print_number(std::cout, n,3);
    std::cout << "4: ";
    print_number(std::cout, n,4);
    std::cout << "5: ";
    print_number(std::cout, n,5);
    std::cout << "6: ";
    print_number(std::cout, n,6);
    std::cout << "7: ";
    print_number(std::cout, n,7);
    std::cout << "8: ";
    print_number(std::cout, n,8);
    std::cout << "9: ";
    print_number(std::cout, n,9);
    std::cout << "10: ";
    print_number(std::cout, n,10);
    std::cout << "11: ";
    print_number(std::cout, n,11);
    std::cout << "12: ";
    print_number(std::cout, n,12);
    std::cout << "13: ";
    print_number(std::cout, n,13);
    std::cout << "14: ";
    print_number(std::cout, n,14);
    std::cout << "15: ";
    print_number(std::cout, n,15);
    std::cout << "16: ";
    print_number(std::cout, n,16);
    std::cout << "17: ";
    print_number(std::cout, n,17);
    std::cout << "18: ";
    print_number(std::cout, n,18);
    std::cout << "19: ";
    print_number(std::cout, n,19);
    std::cout << "20: ";
    print_number(std::cout, n,20);
    std::cout << "21: ";
    print_number(std::cout, n,21);
    std::cout << "22: ";
    print_number(std::cout, n,22);
    std::cout << "23: ";
    print_number(std::cout, n,23);
    std::cout << "24: ";
    print_number(std::cout, n,24);
    std::cout << "25: ";
    print_number(std::cout, n,25);
    std::cout << "26: ";
    print_number(std::cout, n,26);
    std::cout << "27: ";
    print_number(std::cout, n,27);
    std::cout << "28: ";
    print_number(std::cout, n,28);
    std::cout << "29: ";
    print_number(std::cout, n,29);
    std::cout << "30: ";
    print_number(std::cout, n,30);
    std::cout << "31: ";
    print_number(std::cout, n,31);
    std::cout << "32: ";
    print_number(std::cout, n,32);
    return 0;
}

std::string convers(int number, const int base)
{
    std::string out_str;
    if (base<2 || base > 32 )
    {
        return out_str;
    }
    const char liter[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                          'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                          'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                          'U', 'V', 'W'
                         };
    int rest = 0;
    do
    {
        rest = number%base;
        out_str = liter[rest] + out_str;
        number -= rest;
        number /= base;
    }
    while (number/base || number%base  );
    return out_str;
}

template<typename T>
std::ostream& print_number(std::ostream& s, T num, const int &base)
{
    int tmp_num = static_cast<int>(num);
    s << convers(tmp_num, base) << std::endl;
    return s;
}
