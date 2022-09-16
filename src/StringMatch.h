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

class BMMatch
{
private:
    const int maxHashSize_ = 256;
    vector<int> vecList_;


public:
    BMMatch()
    {
        vecList_.resize(maxHashSize_, -1);
    }

    void buildList(const string& strPatternStr)
    {
        int nStart = strPatternStr.size() - 1;
        while (nStart >= 0)
        {
            char tmp = strPatternStr[nStart];
            if (vecList_[tmp] == -1)
            {
                vecList_[tmp] = nStart;
            }

            nStart--;
        }

    }



};
