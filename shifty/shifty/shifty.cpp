// shifty.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Mudit Vats, CSE628 Crypto, M401
// Code to brute force decrypt Shift Cipher / Caesar Cipher
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctype.h>
using namespace std;

char key[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

bool skipSpaces = false;

int main(int argc, char *argv[])
{
    std::cout << "Hello Shifty!\n";

    if (argc > 2)
    {
        cout << "skipping spaces" << endl;
        skipSpaces = true;
    }

    cout << "Cipher:" << endl;
    string line;
    ifstream myfile(argv[1]);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line << '\n';
        }
        myfile.close();
    }
    else 
    {
        cout << "Unable to open file";
    }

    // we are going to substitue using the key
    // key[cipher] = plain

    cout << "Decode:" << endl;

    for (int shift = 0; shift < 26; shift++)
    {
        cout << shift << ":";
        string decryptedString = "";
        for (int i = 0; i < line.length(); i++)
        {
            if (skipSpaces && line[i] == 32) continue; // skip space

            char cipherAlpha = tolower(line[i]) - 97; // convert ascii to alpha
            char plainAlpha = ((key[cipherAlpha] - 97) + shift) % 26; // lookup key            
            char plainASCII = plainAlpha + 97; // get lower case back

            // append to final decrypted string
            decryptedString += plainASCII;
        }
        cout << decryptedString << endl;

        // common words check
        if (decryptedString.find("the") != string::npos) cout << "   ^--- found the!" << endl;
        if (decryptedString.find("and") != string::npos) cout << "   ^--- found and!" << endl;
        if (decryptedString.find("of") != string::npos) cout << "   ^--- found of!" << endl;
        if (decryptedString.find("to") != string::npos) cout << "   ^--- found to!" << endl;
        if (decryptedString.find("in") != string::npos) cout << "   ^--- found in!" << endl;
        if (decryptedString.find("is") != string::npos) cout << "   ^--- found is!" << endl;
        if (decryptedString.find("for") != string::npos) cout << "   ^--- found for!" << endl;
        if (decryptedString.find("that") != string::npos) cout << "   ^--- found that!" << endl;
        if (decryptedString.find("was") != string::npos) cout << "   ^--- found was!" << endl;
        if (decryptedString.find("on") != string::npos) cout << "   ^--- found on!" << endl;
        if (decryptedString.find("with") != string::npos) cout << "   ^--- found with!" << endl;
        if (decryptedString.find("he") != string::npos) cout << "   ^--- found he!" << endl;
        if (decryptedString.find("it") != string::npos) cout << "   ^--- found it!" << endl;
        if (decryptedString.find("as") != string::npos) cout << "   ^--- found as!" << endl;
        if (decryptedString.find("at") != string::npos) cout << "   ^--- found at!" << endl;
        if (decryptedString.find("his") != string::npos) cout << "   ^--- found his!" << endl;
        if (decryptedString.find("by") != string::npos) cout << "   ^--- found by!" << endl;
        if (decryptedString.find("be") != string::npos) cout << "   ^--- found be!" << endl;
        if (decryptedString.find("from") != string::npos) cout << "   ^--- found from!" << endl;
        if (decryptedString.find("are") != string::npos) cout << "   ^--- found are!" << endl;
        if (decryptedString.find("this") != string::npos) cout << "   ^--- found this!" << endl;
        if (decryptedString.find("but") != string::npos) cout << "   ^--- found but!" << endl;
        if (decryptedString.find("have") != string::npos) cout << "   ^--- found have!" << endl;
        
        // trigram check
        //if (decryptedString.find("the") != string::npos) cout << "   ^--- found the!" << endl;
        //if (decryptedString.find("and") != string::npos) cout << "   ^--- found and!" << endl;
        if (decryptedString.find("ing") != string::npos) cout << "   ^--- found ing!" << endl;
        if (decryptedString.find("ent") != string::npos) cout << "   ^--- found ent!" << endl;
        if (decryptedString.find("ion") != string::npos) cout << "   ^--- found ion!" << endl;
        if (decryptedString.find("her") != string::npos) cout << "   ^--- found her!" << endl;
        if (decryptedString.find("for") != string::npos) cout << "   ^--- found for!" << endl;
        if (decryptedString.find("tha") != string::npos) cout << "   ^--- found tha!" << endl;
        if (decryptedString.find("nth") != string::npos) cout << "   ^--- found nth!" << endl;
        if (decryptedString.find("int") != string::npos) cout << "   ^--- found int!" << endl;
        if (decryptedString.find("ere") != string::npos) cout << "   ^--- found ere!" << endl;
        if (decryptedString.find("tio") != string::npos) cout << "   ^--- found tio!" << endl;
        if (decryptedString.find("ter") != string::npos) cout << "   ^--- found ter!" << endl;
        if (decryptedString.find("est") != string::npos) cout << "   ^--- found est!" << endl;
        if (decryptedString.find("ers") != string::npos) cout << "   ^--- found ers!" << endl;
        if (decryptedString.find("ati") != string::npos) cout << "   ^--- found ati!" << endl;
        if (decryptedString.find("hat") != string::npos) cout << "   ^--- found hat!" << endl;
        if (decryptedString.find("ate") != string::npos) cout << "   ^--- found ate!" << endl;
        if (decryptedString.find("all") != string::npos) cout << "   ^--- found all!" << endl;
        if (decryptedString.find("eth") != string::npos) cout << "   ^--- found eth!" << endl;
        if (decryptedString.find("hes") != string::npos) cout << "   ^--- found hes!" << endl;
        if (decryptedString.find("ver") != string::npos) cout << "   ^--- found ver!" << endl;
        if (decryptedString.find("his") != string::npos) cout << "   ^--- found his!" << endl;
        if (decryptedString.find("oft") != string::npos) cout << "   ^--- found oft!" << endl;
        if (decryptedString.find("ith") != string::npos) cout << "   ^--- found ith!" << endl;
        if (decryptedString.find("fth") != string::npos) cout << "   ^--- found fth!" << endl;
        if (decryptedString.find("sth") != string::npos) cout << "   ^--- found sth!" << endl;
        if (decryptedString.find("oth") != string::npos) cout << "   ^--- found oth!" << endl;
        if (decryptedString.find("res") != string::npos) cout << "   ^--- found res!" << endl;
        if (decryptedString.find("ont") != string::npos) cout << "   ^--- found ont!" << endl;

        // quadgram check
        if (decryptedString.find("tion") != string::npos) cout << "   ^--- found tion!" << endl;
        if (decryptedString.find("nthe") != string::npos) cout << "   ^--- found nthe!" << endl;
        if (decryptedString.find("ther") != string::npos) cout << "   ^--- found ther!" << endl;
        if (decryptedString.find("that") != string::npos) cout << "   ^--- found that!" << endl;
        if (decryptedString.find("ofth") != string::npos) cout << "   ^--- found ofth!" << endl;
        if (decryptedString.find("fthe") != string::npos) cout << "   ^--- found fthe!" << endl;
        if (decryptedString.find("thes") != string::npos) cout << "   ^--- found thes!" << endl;
        if (decryptedString.find("with") != string::npos) cout << "   ^--- found with!" << endl;
        if (decryptedString.find("inth") != string::npos) cout << "   ^--- found inth!" << endl;
        if (decryptedString.find("atio") != string::npos) cout << "   ^--- found atio!" << endl;

        for (int k = 0; k < 26; k++)
        {
            cout << key[k] << " = " << key[( ((key[k] - 97) + shift) % 26 )] << ", ";
        }
        cout << endl;
    }

}
