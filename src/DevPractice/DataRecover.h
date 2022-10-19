#pragma once


#include <set>
#include <string>
#include <iosfwd>
#include <fstream>

//CAN数据分隔符
const int MAX_CAN_FIELD_NUM = 28;
static int g_arrCANDelimiter[MAX_CAN_FIELD_NUM] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x0B, 0x0C, \
    0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,  \
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F };

const int MAX_DATA_LEN = 8;  //数据的最大长度（字节数）
const int CANID_MAX_LEN = 8;  //CANID 最大8个字节
static const unsigned int DBID_BaseData = 2;  //普通数据量的表所在的库

const int Motorola_Order = 0;  //摩托罗拉字节序
const int Intel_Order = 1;     //英特尔字节序


typedef struct {
    string strSignalName;      //信号名
    int iIndexInCSV;           //标签在CSV标题栏的位置
    long long llSignalValue;   //信号值   
}CANSignalItem;

typedef struct
{
    long long llTimestamp;   //采集时刻
    long long llCANID;  //00F9--->249    
    list <CANSignalItem> signals;
}CANSignalInfo;

typedef map<string, string> CANDataMap;  //对应文件里的每一行数据(first: 1655782434890_00F9_8_     second: 0101012121012101)
typedef map<string, CANSignalInfo> CANSignalsMap;  //文件中每一行数据包含的信号信息

//CAN信号的配置信息
typedef struct
{
    long long llCANID;    //所属的CANID
    string strSignalName; //信号名
    int iStartBit;  //起始位
    int iBitWidth;  //位宽 

    int iByteOrder; //字节序(0代表Motorola格式，1代表Inter格式)
    int iPrecision; //精度
    long lOffset;   //偏移量

    int iIndexInCSV;  //该信号名在csv标题头上的位置（从1开始，0固定为“时间”栏）
}CANSignalCfg;

typedef map<long long, list<CANSignalCfg> > CANSignalCfgMAP;  //CAN信号的配置信息（用于解析信号）


#define LOG_DEBUG(...)    printf(##__VA_ARGS__)
#define LOG_INFO( ...)     printf(##__VA_ARGS__)
#define LOG_WARNING(...)  printf(##__VA_ARGS__)
#define LOG_ERROR(...)    printf(##__VA_ARGS__)
#define LOG_FATAL(...)    printf(##__VA_ARGS__)

#define LY_LOG_DEBUG(g_LogHandle, ...)    printf(##__VA_ARGS__)
#define LY_LOG_INFO(g_LogHandle, ...)     printf(##__VA_ARGS__)
#define LY_LOG_WARNING(g_LogHandle, ...)  printf(##__VA_ARGS__)
#define LY_LOG_ERROR(g_LogHandle, ...)    printf(##__VA_ARGS__)
#define LY_LOG_FATAL(g_LogHandle, ...)    printf(##__VA_ARGS__)

//#define LOG_DEBUG(...) LY_LOG_DEBUG(GetDefaultLogHandle(), ##__VA_ARGS__)
//#define LOG_INFO(...) LY_LOG_INFO (GetDefaultLogHandle(), ##__VA_ARGS__)
//#define LOG_WARNING(...) LY_LOG_WARNING(GetDefaultLogHandle(), ##__VA_ARGS__)
//#define LOG_ERROR(...) LY_LOG_ERROR(GetDefaultLogHandle(), ##__VA_ARGS__)
//#define LOG_FATAL(...) LY_LOG_FATAL(GetDefaultLogHandle(), ##__VA_ARGS__)

class DataRecover
{
private:
    CANSignalsMap m_mapCANSignals;
    list<string> m_listCSVTitle; //CSV的标题栏

public:

    int doRecover()
    {
        CANDataMap mapCAN;
        Recover("./canlog", mapCAN);
        Parse(mapCAN);
        WriteCSV("./canlog.csv");

        return 0;
    }

    int Recover(const char* pFileName, CANDataMap& mapCAN)
    {
        FILE* fp = fopen(pFileName, "rb");
        if (NULL == fp) {
            printf("open file:[%s] failed!\n", pFileName);
            return -1;
        }

        char buffer[512] = { 0 };

        string strFileds[MAX_CAN_FIELD_NUM];  //string类型的数组，存储一行所有的Field内容
        long long millseconds = 0;  //当前行的时间，毫秒

        int iDelimiterPos = 1;   //分隔符位置（数组下标）
        bool bNeedUpdateFiled = true;  //需要更新域
        unsigned int nLineNo = 0;

        while (NULL != fgets(buffer, sizeof(buffer), fp)) { //fgets遇到\n停止，然后会在后面增加一个\0
            if ('\n' == buffer[0]) {
                printf( "line is empty!\n");
                continue;
            }

            string strBuffer(buffer, sizeof(buffer));
            if (string::npos != strBuffer.rfind("\r\n"))
            {
                printf("Can file format is invalid!\n");
                fclose(fp);
                return -1;
            }

            printf("Current LineNo[%d]!\n", ++nLineNo);

            //SOH
            if (g_arrCANDelimiter[0] == buffer[0]) {
                bNeedUpdateFiled = true;
                continue;
            }
            else {
                char* pGuard = buffer;    //哨兵  
                char* pTemp = NULL;
                string strKey;
                string strValue;

                if (bNeedUpdateFiled) { //需要更新field里的值
                    int i = 1;
                    for (; i <= 3; i++) {  //至少三个分隔符号
                        pTemp = strchr(pGuard, g_arrCANDelimiter[i]);
                        if (NULL == pTemp) {
                            printf( "lineCont:[%s] can't find delimiter:[%02x],pos:[%d]\n", buffer, g_arrCANDelimiter[i], i);
                            fclose(fp);
                            return -1;
                        }

                        int iLength = pTemp - pGuard;
                        if (iLength <= 0) {
                            printf( "iLength=[%d] is invalid!\n", iLength);
                            fclose(fp);
                            return -1;
                        }

                        strFileds[i - 1].assign(pGuard, iLength);
                        if (1 == i) {
                            if (13 != iLength) {   //第一个域是毫秒时间，13位长度   
                                printf( "millseconds is invalid! %s\n", buffer);
                                fclose(fp);
                                return -1;
                            }
                            millseconds = atoll(strFileds[i - 1].c_str());
                        }

                        strKey += strFileds[i - 1] + "_";  //写入map的key
                        pGuard = pTemp + 1;
                    }

                    int iDataLen = atoi(strFileds[2].c_str());  //数据长度
                    if (3 + iDataLen >= MAX_CAN_FIELD_NUM - 1) {
                        printf( "iDataLen:[%d] is out of range\n", iDataLen);
                        fclose(fp);
                        return -1;
                    }

                    //后续iDataLen个分隔符(最后一个分隔符为'\n')
                    for (int j = 0; j < iDataLen; j++) {
                        int iDelimiter = -1;
                        if (j == iDataLen - 1) {  //最后一个分隔符
                            iDelimiter = '\n';
                        }
                        else {
                            iDelimiter = g_arrCANDelimiter[i + j];
                        }
                        iDelimiterPos = i + j;  //包括最后一个分隔符'\n'

                        pTemp = strchr(pGuard, iDelimiter);
                        if (NULL == pTemp) {
                            printf( "lineCont:[%s] can't find delimiter:[%#x],pos:[%d]\n", buffer, iDelimiter, i + j);
                            fclose(fp);
                            return -1;
                        }

                        strFileds[i + j - 1].assign(pGuard, pTemp - pGuard);
                        strValue += strFileds[i + j - 1];   //写入map的value
                        pGuard = pTemp + 1;
                    }

                    //Key末尾加上行号,否则key可能不唯一
                    strKey += to_string(nLineNo);
                    mapCAN.insert(CANDataMap::value_type(strKey, strValue));
                    LOG_INFO("Current LineNo[%d], mapCAN.size[%d], strKey[%s], strValue[%s]\n", nLineNo, mapCAN.size(), strKey.c_str(), strValue.c_str());
                    bNeedUpdateFiled = false;  //Field个数已统计完成
                }
                else {
                    int iPrePos = 0;  //匹配到的数据的下标
                    for (int k = 1; k <= iDelimiterPos; k++) {
                        int iDelimiter = -1;
                        if (k == iDelimiterPos) {  //最后一个分隔符
                            iDelimiter = '\n';
                        }
                        else {
                            iDelimiter = g_arrCANDelimiter[k];
                        }

                        pTemp = strchr(pGuard, iDelimiter);
                        if (NULL != pTemp) {
                            int iLength = pTemp - pGuard;
                            //iLength为0,说明第一个字节就是iDelimiter
                            if (iLength < 0) {
                                printf("nLineNo[%d], iLength2=[%d] is invalid!, pTemp[%s], pGuard[%s], iDelimiter[%0x]\n",
                                    nLineNo, iLength, pTemp, pGuard, iDelimiter);
                                fclose(fp);
                                return -1;
                            }

                            string tmpFiledValue;
                            tmpFiledValue.assign(pGuard, iLength);
                            if (0 == iPrePos) {
                                if ("0" != tmpFiledValue)
                                {
                                    if (iLength >= 13) {
                                        printf("nLineNo[%d], iLength3=[%d] is invalid!, pTemp[%s], pGuard[%s], iDelimiter[%0x]\n",
                                            nLineNo, iLength, pTemp, pGuard, iDelimiter);
                                        fclose(fp);
                                        return -1;
                                    }
                                    millseconds += atoi(tmpFiledValue.c_str());
                                    strFileds[0] = std::to_string(millseconds);
                                }
                            }
                            else {
                                strFileds[iPrePos] = tmpFiledValue;
                            }

                            iPrePos = k;
                            pGuard = pTemp + 1;
                        }
                    }

                    int iDataLen = atoi(strFileds[2].c_str());
                    strKey += strFileds[0] + "_" + strFileds[1] + "_" + strFileds[2] + "_" + to_string(nLineNo);  //写入map的key
                    for (int r = 0; r < iDataLen; r++) {
                        strValue += strFileds[3 + r];   //写入map的value
                    }
                    mapCAN.insert(CANDataMap::value_type(strKey, strValue));
                    LOG_INFO("2Current LineNo[%d], mapCAN.size[%d], strKey[%s], strValue[%s]\n", nLineNo, mapCAN.size(), strKey.c_str(), strValue.c_str());
                }
            }

            memset(buffer, 0, sizeof(buffer));
        }

        fclose(fp);
        return 0;
    }

    bool Parse(CANDataMap& data)
    {
        set<int> allCANID;
        CANSignalCfgMAP mapSignalsCfg;
        string strTmpSQL = "select CAN_ID,SIGNAL_NAME,START_BIT,BIT_WIDTH,BYTE_ORDER,SIGNAL_PRECISION,OFFSET from t_sdc_can_inner_signal where CAN_ID in (";

        CANDataMap::iterator iter;
        for (iter = data.begin(); iter != data.end(); iter++) {
            std::string::size_type pos1 = iter->first.find("_");
            if (std::string::npos == pos1) {
                LY_LOG_ERROR(g_LogHandle, "not found the first _\n");
                return false;
            }

            std::string::size_type pos2 = iter->first.find("_", pos1 + 1);
            if (std::string::npos == pos2) {
                LY_LOG_ERROR(g_LogHandle, "not found the second _\n");
                return false;
            }

            std::string::size_type pos3 = iter->first.find("_", pos2 + 1);
            if (std::string::npos == pos3) {
                LY_LOG_ERROR(g_LogHandle, "not found the third _\n");
                return false;
            }

            string strDataLen = iter->first.substr(pos2 + 1, pos3 - pos2 - 1);
            int iDataLen = stoi(strDataLen);
            if (iDataLen * 2 != iter->second.size()) {
                LY_LOG_ERROR(g_LogHandle, "data is wrong! iDataLen=%d, DataSize(%d) Data(%s)\n", iDataLen * 2, iter->second.size(), iter->second.c_str());
                return false;
            }

            int CANStrLen = pos2 - pos1 - 1;
            string strCANID = iter->first.substr(pos1 + 1, CANStrLen);
            if (0 != CANStrLen % 2 || CANStrLen > 2 * CANID_MAX_LEN) {
                LY_LOG_ERROR(g_LogHandle, "CANStrLen=%d is invalid! %s\n", CANStrLen, strCANID.c_str());
                return false;
            }

            long long llCANID = stoll(strCANID, nullptr, 16);  //16进制：00000387---->903        
            allCANID.insert(llCANID);

            CANSignalInfo can;
            can.llTimestamp = stoll(iter->first.substr(0, pos1));
            can.llCANID = llCANID;
            m_mapCANSignals.insert(CANSignalsMap::value_type(iter->first, std::move(can)));  //信号信息        
        }

        //获取所有CANID对应的信号的配置信息
        //set<int>::iterator it;
        //string strSql = strTmpSQL;
        //for (it = allCANID.begin(); it != allCANID.end(); it++) {
        //    strSql += to_string(*it) + ",";
        //}
        //strSql.replace(strSql.size() - 1, 1, ")");

        //CDBDriver dbDriver;
        //int nRet = dbDriver.ExecuteQuery(DBID_BaseData, strSql.c_str(), strSql.size());
        //if (0 != nRet) {
        //    LY_LOG_ERROR(g_LogHandle, "ExecuteQuery failed(%d).[%s]", nRet, strSql.c_str());
        //    return false;
        //}
        //CDBReader* pReader = dbDriver.GetResultReader();
        //if (NULL == pReader) {
        //    LY_LOG_ERROR(g_LogHandle, "Get DBReader1 failed.");
        //    return false;
        //}

        //unsigned int uValueLen = 0;
        //const char* pValue = NULL;
        //CANSignalCfgMAP::iterator itr;   //迭代器

        //int iPosInCSV = 0;  //标签在CSV标题栏的位置
        //while (pReader->MoveNextRow()) {
        //    CANSignalCfg signalCfg;
        //    pValue = pReader->GetString("SIGNAL_NAME", uValueLen);
        //    if (!(NULL != pValue && uValueLen > 0)) {
        //        LY_LOG_ERROR(g_LogHandle, "SIGNAL_NAME is null. %s", strSql.c_str());
        //        return false;
        //    }
        //    signalCfg.strSignalName = pValue;

        //    signalCfg.llCANID = pReader->GetInt64("CAN_ID");
        //    signalCfg.iStartBit = pReader->GetInt32("START_BIT");
        //    signalCfg.iBitWidth = pReader->GetInt32("BIT_WIDTH");
        //    signalCfg.iByteOrder = pReader->GetInt32("BYTE_ORDER");
        //    signalCfg.iPrecision = pReader->GetInt32("SIGNAL_PRECISION");
        //    signalCfg.lOffset = pReader->GetInt64("OFFSET");
        //    signalCfg.iIndexInCSV = ++iPosInCSV;  //标签在CSV标题栏的位置

        //    itr = mapSignalsCfg.find(signalCfg.llCANID);
        //    if (mapSignalsCfg.end() != itr) {
        //        itr->second.push_back(std::move(signalCfg));
        //    }
        //    else {
        //        list<CANSignalCfg> listCANSignalCfg;
        //        listCANSignalCfg.push_back(std::move(signalCfg));
        //        mapSignalsCfg.insert(CANSignalCfgMAP::value_type(signalCfg.llCANID, listCANSignalCfg));
        //    }

        //    m_listCSVTitle.push_back(pValue);  //标签入队
        //}
        //pReader->CloseResults();

        //CANSignalCfg signalCfg;
        //signalCfg.strSignalName = "TM_XXX";
        //signalCfg.llCANID = 615;
        //signalCfg.iStartBit = 7;
        //signalCfg.iBitWidth = 2;
        //signalCfg.iByteOrder = 0;
        //signalCfg.iPrecision = 0;
        //signalCfg.lOffset = 0;
        //signalCfg.iIndexInCSV = 1;
        list<CANSignalCfg> listCANSignalCfg;
        listCANSignalCfg.push_back({ 615, "TM_XXX", 7, 2, 0, 0, 0, 1 });
        mapSignalsCfg.insert(make_pair(615, listCANSignalCfg));


        listCANSignalCfg.clear();
        listCANSignalCfg.push_back({ 903, "TM_PPOSFAIL", 13, 1, 0, 0, 0, 2});
        listCANSignalCfg.push_back({ 903, "TM_ALIVE_COUNTER_387", 21, 2, 0, 0, 0, 3});
        listCANSignalCfg.push_back({ 903, "TM_SHFT_IN_PARKING", 7, 1, 0, 0, 0, 4 });
        listCANSignalCfg.push_back({ 903, "TM_PPOSAVAL", 12, 1, 0, 0, 0, 5 });
        listCANSignalCfg.push_back({ 903, "TM_CHECKSUM_387", 19, 4, 0, 0, 0, 6 });
        mapSignalsCfg.insert(make_pair(903, listCANSignalCfg));

        LOG_INFO("mapSignalsCfg.size(%d) !!!\n", mapSignalsCfg.size());

        for (auto [CanID, listCANSignals] : mapSignalsCfg)
        {
            LOG_INFO("CanID[%d], listCANSignals.size(%d) !!!\n", CanID, listCANSignals.size());
        }

        //if (mapSignalsCfg.empty()) {
        //    LY_LOG_ERROR(g_LogHandle, "not found a record! %s", strSql.c_str());
        //    return false;
        //}

        //解析CAN信号
        for (iter = data.begin(); iter != data.end(); iter++) {

            CANSignalsMap::iterator it_M = m_mapCANSignals.find(iter->first);
            if (m_mapCANSignals.end() == it_M) {
                LY_LOG_ERROR(g_LogHandle, "not found signal in MAP. first: %s\n", iter->first.c_str());
                return false;
            }
            long long llCANID = it_M->second.llCANID;

            unsigned char szData[MAX_DATA_LEN] = { 0 };
            int iDataLen = iter->second.size() / 2;    //16进制字符串对应的字节

            for (int i = 0; i < iDataLen; i++) {
                szData[i] = stoul(iter->second.substr(i * 2, 2), nullptr, 16);   //获取一个字节                 
            }

            auto itr = mapSignalsCfg.find(llCANID);
            if (mapSignalsCfg.end() == itr) {
                LY_LOG_ERROR(g_LogHandle, "not found signal cfgInfo! llCANID=%lld\n", llCANID);
                return false;
            }

            list<CANSignalCfg>& listCANSignalCfg = itr->second;
            list<CANSignalCfg>::iterator it_L;
            for (it_L = listCANSignalCfg.begin(); it_L != listCANSignalCfg.end(); it_L++) {
                int istartBit = it_L->iStartBit;
                int iBitWidth = it_L->iBitWidth;
                int byteOrder = it_L->iByteOrder;

                int byte_index = istartBit / 8;  //起始字节
                int bit_index = istartBit % 8;  //起始位
                unsigned long long ret_val = 0;

                for (int i = 0; i < iBitWidth; i++) {
                    if (Intel_Order == byteOrder) {
                        ret_val |= ((szData[byte_index] >> bit_index) & 0X01) << i;
                        if (bit_index++ >= 7) {
                            bit_index = 0;
                            byte_index++;
                        }
                    }
                    else if (Motorola_Order == byteOrder) {
                        ret_val |= ((szData[byte_index] >> bit_index) & 0X01) << (iBitWidth - i - 1);
                        if (bit_index == 0) {
                            bit_index = 7;
                            byte_index++;
                        }
                        else {
                            bit_index--;
                        }
                    }
                }

                CANSignalItem item;
                item.strSignalName = it_L->strSignalName;
                item.iIndexInCSV = it_L->iIndexInCSV;
                item.llSignalValue = ret_val; // ret_val * factor - offset
                it_M->second.signals.push_back(std::move(item));
            }

        }

        LY_LOG_INFO(g_LogHandle, "m_mapCANSignals.size()=%d\n", m_mapCANSignals.size());
        return true;

    }

    void WriteCSV(const string& strFileName)
    {
        ofstream ofs(strFileName, std::ios::binary);
        ofs << "时间";

        list<string>::iterator iter;
        for (iter = m_listCSVTitle.begin(); iter != m_listCSVTitle.end(); iter++) {
            ofs << ',' << (*iter);
        }
        ofs << '\n';  //标题栏写完后换行

        for (auto it = m_mapCANSignals.begin(); it != m_mapCANSignals.end(); it++) {

            ofs << it->second.llTimestamp;
            list <CANSignalItem>& item = it->second.signals;
            list <CANSignalItem>::iterator it_L;

            for (it_L = item.begin(); it_L != item.end(); it_L++) {
                if (item.begin() == it_L) { //第一个数据项
                    int iIndexInCSV = it_L->iIndexInCSV;
                    for (int i = 0; i < iIndexInCSV; i++) {
                        ofs << ',';
                    }
                    ofs << it_L->llSignalValue;
                }
                else {
                    ofs << ',' << it_L->llSignalValue;
                }
            }
            ofs << '\n';  //换行

        }

    }

};

void call_DataRecover()
{
    DataRecover objDataRecover;
    objDataRecover.doRecover();
}