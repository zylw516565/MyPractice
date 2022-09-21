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

    int match(const string& strMaster, const string& strPatternStr, vector<int>& vecBCList)
    {
        if (strMaster.size() < strPatternStr.size()
            || strMaster.empty()
            || strPatternStr.empty()
            || vecBCList.empty()){
            return -1;
        }

        buildList(strPatternStr, vecBCList);

        int nMasterBegin = 0; int nPatternEnd = strPatternStr.size() - 1;
        while (strMaster.size() - nMasterBegin >= strPatternStr.size())
        {
            int j;
            for (j = nPatternEnd; j >= 0; --j)
            {
                if (strPatternStr[j] != strMaster[nMasterBegin + j]) break;
            }

            if (j < 0) {
                return nMasterBegin;
            }

            nMasterBegin = nMasterBegin + j + vecBCList[strMaster[nMasterBegin + j]];

//             int si = j;
//             char cBadCharacter = strMaster[nMasterBegin + j];
//             int xi = vecBCList[cBadCharacter];
//             if (xi == -1)
//             {
//                 nMasterBegin = si - xi;
//             }
//             else
//             {
//                 //TODO:应用好后缀规则?
//             }

        }

    }

    void buildList(const string& strPatternStr, vector<int>& vecBCList)
    {
        vecBCList.resize(maxHashSize_, -1);

        for (int i=0; i < strPatternStr.size(); ++i)
        {
            int nASCII = static_cast<int>(strPatternStr[i]);
            vecBCList[nASCII] = i;
        }
    }

    void generateGS(const string& pattern, vector<int>& suffix, vector<bool>& prefix)
    {
        if (pattern.empty()) {
            return;
        }

        int nPatternLen = pattern.size();
        suffix.resize(nPatternLen, -1);
        prefix.resize(nPatternLen, false);
        for (int i = 0; i < nPatternLen - 1; ++i)  //b[0, i]
        {
            int j = i;  //b[0, i] 从尾部与b[0, m-1]求公共后缀子串
            int k = 0;  //公共后缀子串长度
            while (j >= 0 && pattern[j] == pattern[nPatternLen - 1 - k]) {  // 与b[0, m-1]求公共后缀子串
                --j;
                ++k;
                suffix[k] = j + 1;
            }

            if (j == -1) prefix[k] = true;
        }
    }

private:


};
