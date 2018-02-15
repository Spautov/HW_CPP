#include <stdlib.h>
#include <iostream>
#include <stdarg.h>
#include <cmath>


int count_polinom(int lim, ...)
{
    va_list ap;
    va_start(ap, lim);
    int x = va_arg(ap, int);
    int result = 0;
    for (int i = 0; i<lim-1; ++i)
    {
        int c = va_arg(ap, int);
        result += c*int(pow(x,i));
    }
    va_end(ap);
    return result;
}

int main()
{
    std::cout <<"TEST:  ";
    int res = count_polinom(5, 3, 2, 5, 4, 9);
    if (res == 296)
    {
        std::cout << "OK" << std::endl;
    }
    else
    {
        std::cout << "ERROR" << std::endl;
    }
    return 0;
}
