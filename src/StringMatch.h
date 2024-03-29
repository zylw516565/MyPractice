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

    int match(const string& strMaster, const string& strPatternStr)
    {
        if (strMaster.size() < strPatternStr.size()
            || strMaster.empty()
            || strPatternStr.empty()
            ){
            return -1;
        }

        vector<int> vecBCList;
        generateBC(strPatternStr, vecBCList);

        vector<int> suffix; vector<bool> prefix;
        generateGS(strPatternStr, suffix, prefix);

        int nMasterBegin = 0; 
        int nPatternEnd = strPatternStr.size() - 1;
        int nMasterSize = strMaster.size(); int nPatternSize = strPatternStr.size();
        while (nMasterSize - nMasterBegin >= nPatternSize)
        {
            int j;
            for (j = nPatternEnd; j >= 0; --j)
            {
                if (strPatternStr[j] != strMaster[nMasterBegin + j]) break;
            }

            if (j < 0) {
                return nMasterBegin;
            }

            int bcMoveLen = j - vecBCList[strMaster[nMasterBegin + j]];
            int gsMoveLen = 0;

            int nGSLen = nPatternSize - 1 - j; //好后缀长度
            if (j < nPatternEnd) {  //如果有好后缀
                if (suffix[nGSLen] != -1) { //如果好后缀在模式串中有匹配的字符串
                    gsMoveLen = j - suffix[nGSLen] + 1;
                }
                else
                {
                    gsMoveLen = nPatternSize;

                    for (int r = j+2; r <= nPatternSize - 1; ++r)
                    {
                        if (prefix[nPatternSize - r]) {
                            gsMoveLen = r; 
                            break;
                        }
                    }
                }
            }

            nMasterBegin = nMasterBegin + std::max(bcMoveLen, gsMoveLen);
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

void call_BMMatch()
{
    string strPattern("example");
    string strText("here is a simple example");
    BMMatch objBMMatch;
    int index = objBMMatch.match(strText, strPattern);
    cout << "index: " << index << endl;
}

class KMP
{
public:
    int match(const string& master, const string& pattern)
    {
        if (master.size() < pattern.size()) return -1;

        vector<int> next;
        getNext(pattern, next);

        int masterSize = master.size(); int patternSize = pattern.size();
        int masterBegin = 0;
        while (masterSize - masterBegin >= patternSize)
        {
            int j = 0;
            for (; j < patternSize; ++j)
            {
                if(pattern[j] != master[masterBegin + j]) break;
            }

            if (j == patternSize){
                return masterBegin;
            }

            if(next[j - 1] != -1){
                masterBegin = j - next[j - 1] - 1;
            }
            else{
                masterBegin = j - next[j - 1];
            }
        }

    }

    int matchNice(const string& master, const string& pattern)
    {
        if (master.size() < pattern.size()) return -1;

        vector<int> next;
        getNext(pattern, next);

        int i = 0;
        int j = 0;
        while (i < master.size() && j < pattern.size())
        {
            if (j == -1 || master[i] == pattern[j])
            {
                i++;
                j++;
            }
            else
                j = next[j];
        }

        if (j == pattern.size())
        {
            return i - j;
        }
        else
            return -1;
    }

private:
    void getNext(const string& pattern, vector<int>& next)
    {
        next.resize(pattern.size());
        next[0] = -1;
        int i = 0, j = -1;
        while (i < pattern.size())
        {
            if (j == -1 || pattern[i] == pattern[j])
            {
                ++i;
                ++j;
                next[i] = j;
            }
            else
                j = next[j];
        }
    }

};

void call_KMPMatch()
{
    string strPattern("abababca");
    string strText("ababababca");
    KMP objKMP;
    int index = objKMP.match(strText, strPattern);
    cout << "index: " << index << endl;

    index = objKMP.matchNice(strText, strPattern);
    cout << "index: " << index << endl;
}

const int TrieNodeMaxSize = 26;

class TrieTree
{
public:

    struct TrieNode
    {
        char data_;
        bool isEndingChar = false;
        vector<shared_ptr<TrieNode>> children;

        TrieNode(const char data)
        {
            data_ = data;
            children.resize(TrieNodeMaxSize);
        }
    };

    TrieTree()
    :root_(make_shared<TrieNode>('/'))
    {
    }

    //向TrieTree插入一个字符串
    void insert(const string& target)
    {
        if (target.empty()) return;

        auto p = root_;
        for (const auto& t : target)
        {
            char index = t - 'a';
            if (p->children[index] == nullptr)
            {
                auto newNode(make_shared<TrieNode>(t));
                p->children[index] = newNode;
            }

            p = p->children[index];
        }

        p->isEndingChar = true;
    }

    //在Trie树中查找一个字符串
    bool find(const string& pattern)
    {
        if (pattern.empty())
            return false;

        auto p = root_;
        for (const auto& sub : pattern)
        {
            char index = sub - 'a';
            if (p->children[index] == nullptr)
                return false;

            p = p->children[index];
        }

        if (!p->isEndingChar)
            return false;
        else
            return true;
    }

private:
    shared_ptr<TrieNode> root_;

};

void call_TrieTree()
{
    TrieTree objTrieTree;
    bool bFind = objTrieTree.find("hello");
    cout << "objTrieTree.find(hello): " << bFind << endl;

    objTrieTree.insert("hello");
    objTrieTree.insert("how");
    objTrieTree.insert("hi");
    objTrieTree.insert("her");

    objTrieTree.insert("so");
    objTrieTree.insert("see");

    bFind = objTrieTree.find("hello");
    cout << "objTrieTree.find(hello): " << bFind << endl;

    bFind = objTrieTree.find("hel");
    cout << "objTrieTree.find(hel): " << bFind << endl;

    bFind = objTrieTree.find("how");
    cout << "objTrieTree.find(how): " << bFind << endl;

    bFind = objTrieTree.find("se");
    cout << "objTrieTree.find(se): " << bFind << endl;

}