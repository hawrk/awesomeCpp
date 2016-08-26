/*
 * pubfun.hpp
 *
 *  Created on: 2016年3月16日
 *      Author: Administrator
 */

#ifndef INCLUDE_PUBFUN_HPP_
#define INCLUDE_PUBFUN_HPP_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "macro.hpp"
#include <regex.h>
/*
 * Desc:  从字符串中按"="符号做为分隔符拆分出键名及键值
 * input:
 * output:
 * return:
 */
int ParserLine(char *szData, char *szKey, char *szVal);


/*
 * Desc:判断是否为空行、注释行(以#开头)及以<开头的行
 */
bool IsNeedSkip(const char *szLine);



//map 格式 转换成string 格式
bool Map2Str(const StrStrMap &inMap, std::string &outStr);

//正则表达式匹配
bool matchRegex(const char* pattern, const char* userString);

#endif /* INCLUDE_PUBFUN_HPP_ */
