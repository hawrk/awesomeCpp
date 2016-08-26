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


bool matchRegex(const char* pattern, const char* userString)
{
    bool result = false;

    regex_t regex;
    int regexInit = regcomp( &regex, pattern, REG_EXTENDED|REG_NOSUB );
    if( regexInit )
    {
        //Error print : Compile regex failed
    }
    else
    {
        int reti = regexec( &regex, userString, 0, NULL, 0 );
        if( REG_NOERROR != reti )
        {
            //Error print: match failed!
        }
        else
        {
            result = true;
        }
    }
    regfree( &regex );
    return result;
}
