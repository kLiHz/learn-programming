#include <iostream>
#include "myint.h"

void factorial()
{
    h_int result, a = 1;
    for (int i = 1; i <= 20; i++)
    {
        a *= i;
        std::cout << i << "! = " << a << std::endl;
        result += a;
    }
    std::cout << "Their sum is " << result;
}

void sum()
{
    std::cout << "A + B Problem: ";
    h_int A, B;
    std::cout << "A: "; std::cin >> A;
    std::cout << "B: "; std::cin >> B;
    std::cout << A << " + " << B << " = " << A.add(B) << std::endl;
}

int main()
{
    factorial();
    sum();
    return 0;
}
