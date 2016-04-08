/*
 * pubfun.cpp
 *
 *  Created on: 2016Äê3ÔÂ16ÈÕ
 *      Author: Administrator
 */

#include "pubfun.hpp"
using namespace std;

int ParserLine(char *szData, char *szKey, char *szVal)
{
    char *pChar = NULL;

    pChar=strchr(szData, '=');
    if(pChar == NULL){
        return -1;
    }
    strncpy(szKey, szData, (pChar-szData));
    strncpy(szVal, pChar+1, strlen(pChar+1));

    szKey[strlen(szKey)] = '\0';
    szVal[strlen(szVal)] = '\0';

    return 0;
}



bool IsNeedSkip(const char *szLine)
{
    bool bRet = false;

    if(szLine!=NULL){
        if(szLine[0] == '#' || szLine[0] == '<' || isspace(szLine[0]))
            bRet = true;
    }
    return bRet;
}



bool Map2Str(const StrStrMap &inMap, string &outStr)
{
    unsigned int iLoopCnt=0;
    StrStrMap::size_type itemNum;
    bool bRet = true;
    outStr = "";

    itemNum = inMap.size();
    StrStrMap::const_iterator it;
    for(it=inMap.begin();it!=inMap.end();it++){
        outStr+=it->first;
        outStr+="=";
        outStr+=it->second;
        if(++iLoopCnt != itemNum){
            outStr+="&";
        }
    }

    return bRet;
}
