// et.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Mudit Vats, CSE628 Crypto, M401
// Code to create equivalency classes give a modulus and desired elements
//

#include <iostream>

int main()
{
    std::cout << "Hello Equivalency Class!\n";

    int base;
    int count;

    std::cout << "Enter modulus: ";
    std::cin >> base;

    std::cout << "Enter elements in set: ";
    std::cin >> count;

    for (int j = 0; j < base; j++)
    {

        int start = -(base * count);
        int end = base * count;

        std::cout << "{ ";
        for (int i = start; i < end; i += base)
        {
            printf("%4d, ", i + j);
        }
        std::cout << " }";
        std::cout << std::endl;
    }
}

