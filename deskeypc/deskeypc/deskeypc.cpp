// desp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#define SIZE_MAX_BUFFER                                 80
#define SIZE_FFUNC_PERMUTATAION_INPUT                   32
#define SIZE_FFUNC_PERMUTATAION_OUTPUT                  32
#define SIZE_KEYSCHED_PERMUTED_CHOICE_1_INPUT           56
#define SIZE_KEYSCHED_PERMUTED_CHOICE_1_OUTPUT          56
#define SIZE_KEYSCHED_PERMUTED_CHOICE_2_INPUT           56
#define SIZE_KEYSCHED_PERMUTED_CHOICE_2_OUTPUT          48

#define MAX_ARGS         4
#define ARG_PERMUTATION  1
#define ARG_INPUT_TYPE   2
#define ARG_INPUT_VALUE  3

// table 3.10 f-function final permutation
// 32 bit to 32 bit
int p[] = {
    16,  7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26,  5, 18, 31, 10,
     2,  8, 24, 14, 32, 27,  3,  9,
    19, 13, 30,  6, 22, 11,  4, 25
    };

// table 3.11 Key Schedule PC-1
// 56 to 56 bit
int pc1[] = {
    57, 49, 41, 33, 25, 17,  9,  1,
    58, 50, 42, 34, 26, 18, 10,  2,
    59, 51, 43, 35, 27, 19, 11,  3,
    60, 52, 44, 36, 63, 55, 47, 39,
    31, 23, 15,  7, 62, 54, 46, 38,
    30, 22, 14,  6, 61, 53, 45, 37,
    29, 21, 13,  5, 28, 20, 12,  4
    };

// table 3.12 Key Schedule PC-2, 
// 56 to 48 bit
int pc2[] = {
    14, 17, 11, 24,  1,  5,  3, 28,
    15,  6, 21, 10, 23, 19, 12,  4,
    26,  8, 16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
    };

void dumpArray(std::vector<char> charArray);
std::vector<char> asciiHexToasciiBinary(std::vector<char> charArray);
std::vector<char> asciiBinToasciiHex(std::vector<char> charArray);

int main(int argc, char* argv[])
{
    int* pTable;
    int pTableSize;
    int inputSize;
    bool isBinaryInput = true;
    std::vector<char> input;
    std::vector<char> output;
    
    std::cout << "Hello DES P, PC-1, PC-2 Table Mapper!" << std::endl;

    if (argc < MAX_ARGS)
    {
        std::cout << "not enough arguments" << std::endl;
        return 1;
    }

    if (strcmp(argv[ARG_PERMUTATION], "p") == 0)
    {
        pTable = p;
        pTableSize = SIZE_FFUNC_PERMUTATAION_OUTPUT;
        inputSize = SIZE_FFUNC_PERMUTATAION_INPUT;
        std::cout << "using f function final P" << std::endl;
    }
    else if (strcmp(argv[ARG_PERMUTATION], "pc1") == 0)
    {
        pTable = pc1;
        pTableSize = SIZE_KEYSCHED_PERMUTED_CHOICE_1_OUTPUT;
        inputSize = SIZE_KEYSCHED_PERMUTED_CHOICE_1_INPUT;
        std::cout << "using key schedule PC-1" << std::endl;
    }
    else if (strcmp(argv[ARG_PERMUTATION], "pc2") == 0)
    {
        pTable = pc2;
        pTableSize = SIZE_KEYSCHED_PERMUTED_CHOICE_2_OUTPUT;
        inputSize = SIZE_KEYSCHED_PERMUTED_CHOICE_2_INPUT;
        std::cout << "using key schedule PC-2" << std::endl;
    }
    else
    {
        std::cout << "unrecognized key type" << std::endl;
        return 1;
    }

    if (strcmp(argv[ARG_INPUT_TYPE], "bin") == 0)
    {
        isBinaryInput = true;
    }
    else if (strcmp(argv[ARG_INPUT_TYPE], "hex") == 0)
    {
        isBinaryInput = false;
    }
    else
    {
        std::cout << "unrecognized input type" << std::endl;
        return 1;
    }

    // validate input size
    if (isBinaryInput)
    {
        if (strlen(argv[ARG_INPUT_VALUE]) != inputSize)
        {
            std::cout << "bin input length mismatch" << std::endl;
            return 1;
        }
    }
    else
    {
        if (strlen(argv[ARG_INPUT_VALUE]) != (inputSize/4))
        {
            std::cout << "hex input length mismatch" << std::endl;
            return 1;
        }
    }

    // vectorize the argv, NOTE: MSB=0... LSB=31
    for (int i = 0; i < (int)strlen(argv[ARG_INPUT_VALUE]); i++)
    {
        input.push_back(argv[ARG_INPUT_VALUE][i]);
    }

    if (!isBinaryInput)
    {
        // overwrite input
        input = asciiHexToasciiBinary(input);
    }

    // add parity bits if pc1
    // this step takes the 56 bit key and adds parity bits at
    // ever 7th bit; 8 bits total, so the final size is 64 bits
    std::vector<char> expansion;
    if (pTable == pc1)
    {
        for (int i = 0; i < (int)input.size(); i++)
        {
            expansion.push_back(input[i]);

            if ( ((i + 1) % 7) == 0 )
            {
                // add parity bits
                expansion.push_back('0');
            }
        }

        // pre-expansion
        std::cout << "input " << input.size() << "-bits:" << std::endl;
        dumpArray(input);
        std::cout << " (0x";
        dumpArray(asciiBinToasciiHex(input));
        std::cout << ")";
        std::cout << std::endl;

        std::cout << "expanded key, parity bits added to input" << std::endl;

        // use expansion now
        input = expansion;
    }

    // hex or binary?

    // do the mapping
    // input bit of the table is mapped to output bit of table index
    // output[table index] = input[ table[table index] ]
    for (int i = 0; i < pTableSize; i++)
    {
        int pIndex = pTable[i] - 1;
        output.push_back(input.at(pIndex));
    }

    // print the input MSB...LSB
    std::cout << "input " << input.size() << "-bits:" << std::endl;
    dumpArray(input);
    std::cout << " (0x";
    dumpArray(asciiBinToasciiHex(input));
    std::cout << ")";
    std::cout << std::endl;

    // print the output MSB...LSB
    std::cout << "output " << output.size() << "-bits:" << std::endl;
    dumpArray(output);
    std::cout << " (0x";
    dumpArray(asciiBinToasciiHex(output));
    std::cout << ")";
    std::cout << std::endl;
}


void dumpArray(std::vector<char> charArray)
{
    for (char c : charArray)
    {
        std::cout << c;
    }
}

std::vector<char> asciiBinToasciiHex(std::vector<char> charArray)
{
    int a, b, c, d = 0;
    std::vector<char> hexArray;

    for (int i = 0; i < (int)charArray.size(); i+=4)
    {
        if (charArray[i + 0] == '1') a = 1; else a = 0;
        if (charArray[i + 1] == '1') b = 1; else b = 0;
        if (charArray[i + 2] == '1') c = 1; else c = 0;
        if (charArray[i + 3] == '1') d = 1; else d = 0;

        int abcd = (a << 3) | (b << 2) | (c << 1) | (d << 0);

        switch (abcd)
        {
        case 0:
            hexArray.push_back('0');
            break;
        case 1:
            hexArray.push_back('1');
            break;
        case 2:
            hexArray.push_back('2');
            break;
        case 3:
            hexArray.push_back('3');
            break;
        case 4:
            hexArray.push_back('4');
            break;
        case 5:
            hexArray.push_back('5');
            break;
        case 6:
            hexArray.push_back('6');
            break;
        case 7:
            hexArray.push_back('7');
            break;
        case 8:
            hexArray.push_back('8');
            break;
        case 9:
            hexArray.push_back('9');
            break;
        case 10:
            hexArray.push_back('a');
            break;
        case 11:
            hexArray.push_back('b');
            break;
        case 12:
            hexArray.push_back('c');
            break;
        case 13:
            hexArray.push_back('d');
            break;
        case 14:
            hexArray.push_back('e');
            break;
        case 15:
            hexArray.push_back('f');
            break;
        default:
            break;
        }

    }


    return hexArray;
}

std::vector<char> asciiHexToasciiBinary(std::vector<char> charArray)
{
    std::vector<char> binaryArray;

    for (char c : charArray)
    {
        switch (c)
        {
        case '0':
            binaryArray.push_back('0');
            binaryArray.push_back('0');
            binaryArray.push_back('0');
            binaryArray.push_back('0');
            break;
        case '1':
            binaryArray.push_back('0');
            binaryArray.push_back('0');
            binaryArray.push_back('0');
            binaryArray.push_back('1');
            break;
        case '2':
            binaryArray.push_back('0');
            binaryArray.push_back('0');
            binaryArray.push_back('1');
            binaryArray.push_back('0');
            break;
        case '3':
            binaryArray.push_back('0');
            binaryArray.push_back('0');
            binaryArray.push_back('1');
            binaryArray.push_back('1');
            break;
        case '4':
            binaryArray.push_back('0');
            binaryArray.push_back('1');
            binaryArray.push_back('0');
            binaryArray.push_back('0');
            break;
        case '5':
            binaryArray.push_back('0');
            binaryArray.push_back('1');
            binaryArray.push_back('0');
            binaryArray.push_back('1');
            break;
        case '6':
            binaryArray.push_back('0');
            binaryArray.push_back('1');
            binaryArray.push_back('1');
            binaryArray.push_back('0');
            break;
        case '7':
            binaryArray.push_back('0');
            binaryArray.push_back('1');
            binaryArray.push_back('1');
            binaryArray.push_back('1');
            break;
        case '8':
            binaryArray.push_back('1');
            binaryArray.push_back('0');
            binaryArray.push_back('0');
            binaryArray.push_back('0');
            break;
        case '9':
            binaryArray.push_back('1');
            binaryArray.push_back('0');
            binaryArray.push_back('0');
            binaryArray.push_back('1');
            break;
        case 'a':
            binaryArray.push_back('1');
            binaryArray.push_back('0');
            binaryArray.push_back('1');
            binaryArray.push_back('0');
            break;
        case 'b':
            binaryArray.push_back('1');
            binaryArray.push_back('0');
            binaryArray.push_back('1');
            binaryArray.push_back('1');
            break;
        case 'c':
            binaryArray.push_back('1');
            binaryArray.push_back('1');
            binaryArray.push_back('0');
            binaryArray.push_back('0');
            break;
        case 'd':
            binaryArray.push_back('1');
            binaryArray.push_back('1');
            binaryArray.push_back('0');
            binaryArray.push_back('1');
            break;
        case 'e':
            binaryArray.push_back('1');
            binaryArray.push_back('1');
            binaryArray.push_back('1');
            binaryArray.push_back('0');
            break;
        case 'f':
            binaryArray.push_back('1');
            binaryArray.push_back('1');
            binaryArray.push_back('1');
            binaryArray.push_back('1');
            break;
        default:
            break;
        }
    }

    return binaryArray;
}