#pragma once

#include <iostream>

using std::cout;
using std::string;

class StringMatch
{
public:
    StringMatch() = default;
    ~StringMatch() = default;

private:


public:
    void match(const string& strMainString, const string& strTarget)
    {
        if (strMainString.size() < strTarget.size()) return;

        string::size_type length = strTarget.size();
        string::size_type start = 0; string::size_type end = length;

        while (start + end <= strMainString.size())
        {
            string strSub = strMainString.substr(start, end);

            bool bIsEqual = true;
            for (string::size_type i = 0; i < strTarget.size(); ++i)
            {
                if (strSub[i] != strTarget[i])
                {
                    bIsEqual = false;
                    break;
                }
            }

            if (bIsEqual)
            {
                cout << "Equal string start index: " << start << endl;
            }

            start++;
        }

    }
};
