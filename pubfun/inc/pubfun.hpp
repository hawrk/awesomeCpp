/*
 * pubfun.hpp
 *
 *  Created on: 2016��3��16��
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
 * Desc:  ���ַ����а�"="������Ϊ�ָ�����ֳ���������ֵ
 * input:
 * output:
 * return:
 */
int ParserLine(char *szData, char *szKey, char *szVal);


/*
 * Desc:�ж��Ƿ�Ϊ���С�ע����(��#��ͷ)����<��ͷ����
 */
bool IsNeedSkip(const char *szLine);



//map ��ʽ ת����string ��ʽ
bool Map2Str(const StrStrMap &inMap, std::string &outStr);

//������ʽƥ��
bool matchRegex(const char* pattern, const char* userString);

#endif /* INCLUDE_PUBFUN_HPP_ */
