// desp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// table 3.10 f-function final permutation
int p[] = { 
    16,  7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26,  5, 18, 31, 10,
     2,  8, 24, 14, 32, 27,  3,  9,
    19, 13, 30,  6, 22, 11,  4, 25
};

int main(int argc, char *argv[])
{
    char input[32];
    char output[32];
    memset(output, 0, 32);

    std::cout << "Hello DES P Mapper!\n";

    if (argc < 2)
    {
        std::cout << "provide the input bits" << std::endl;
    }
    
    // copy the argv
    // MSB=0... LSB=31
    for (int i = 0; i <32; i++)
    {
        input[i] = argv[1][i];
    }

   
    // do the mapping
    // input bit of the table is mapped to output bit of table index
    // output[table index] = input[ table[table index] ]
    for (int i = 0; i < 32; i++)
    {
        int pIndex = p[i] - 1;
        output[i] = input[pIndex];
    }
    
    // print the input MSB...LSB
    printf(" input: ");
    for (int i = 0; i < 32; i++)
    {
        printf("%c", input[i]);
    }
    printf("\n");

    // print the output MSB...LSB
    printf("output: ");
    for (int i = 0; i < 32; i++)
    {
        printf("%c", output[i]);
    }
    printf("\n");
}

