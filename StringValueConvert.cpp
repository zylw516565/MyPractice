#include "StringValueConvert.h"

#include <string>
#include <stdlib.h>
#include <iostream>


using std::cout;
using std::endl;
using std::string;

void StringValueConvert::begin()
{
    int i = 42;
    string s = std::to_string(i);

    cout << "s = " << s << endl;

    double d = std::stod(s);
    cout << "d = " << d << endl;

    string s2 = "pi = 3.1415926";
    cout << "s = " << s2 << endl;

    double pi;
    pi = std::stod(s2.substr(s2.find_first_of("+-.0123456789")));
    cout << "pi = " << pi << endl;

    string strPIV2 = "pi = 3.1415926";


    try
    {
        int nPiV2 = std::stoi(strPIV2);
        cout << "nPiV2 = " << nPiV2 << endl;

    }
    catch (const std::exception& e)
    {
        cout << "exception: " << e.what() << endl;
    }

    string strPI = "3.1415926";
    int nPi = std::stoi(strPI);
    cout << "nPi = " << nPi << endl;

    string strPIV3 = "0x9abcde";
    int nPiV3 = std::stoi(strPIV3, 0, 16);

    char cPiV4[128];
    if (_itoa_s(nPiV3, cPiV4, 2) != 0)
        return;

    printf("nPiV3: %0X, %d, %o, %s\n", nPiV3, nPiV3, nPiV3, cPiV4);
    cout << "nPiV3 = " << nPiV3 << endl;

}