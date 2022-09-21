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

        generateBC(strPatternStr, vecBCList);

        vector<int> suffix; vector<bool> prefix;
        generateGS(strPatternStr, suffix, prefix);

        int nMasterBegin = 0; 
        int nPatternEnd = strPatternStr.size() - 1;
        int nPatternSize = strPatternStr.size();
        while (strMaster.size() - nMasterBegin >= strPatternStr.size())
        {
            int j;
            int nGSLen = 0;  //好后缀长度
            for (j = nPatternEnd; j >= 0; --j)
            {
                if (strPatternStr[j] != strMaster[nMasterBegin + j]) break;
                ++nGSLen;
            }

            if (j < 0) {
                return nMasterBegin;
            }

            int bcMoveLen = j + vecBCList[strMaster[nMasterBegin + j]];

            int gsMoveLen = 0;
            if (suffix[nGSLen] != -1){
                gsMoveLen = j - suffix[nGSLen] + 1;
            }
            else
            {
                if (prefix[nGSLen]){
                    gsMoveLen = nPatternSize - nGSLen;
                }
                else
                {
                    gsMoveLen = nPatternSize;
                }
            }

            nMasterBegin = nMasterBegin + (bcMoveLen< gsMoveLen)?bcMoveLen: gsMoveLen;
        }

    }

    //生成坏字符表
    void generateBC(const string& strPatternStr, vector<int>& vecBCList)
    {
        vecBCList.resize(maxHashSize_, -1);

        for (int i=0; i < strPatternStr.size(); ++i)
        {
            int nASCII = static_cast<int>(strPatternStr[i]);
            vecBCList[nASCII] = i;
        }
    }

    //生成好后缀规则
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
