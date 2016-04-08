/*
 * config.cpp
 *
 *  Created on: 2016年3月16日
 *      Author: Administrator
 */
#include <iostream>
#include <stdio.h>
#include "config.hpp"

using namespace hawrk;

bool CConfig::FileExist(const char* filename)
{
	LOG(INFO)<<" file exist begin"<<endl;
	FILE *fp = NULL;
	if(NULL == (fp = fopen(filename,"r")))
	{
		LOG(ERROR)<<"file not exist!!"<<endl;
		return false;
	}
	return true;
}

bool CConfig::ReadConf(const char* filename,StrStrMap& outmap)
{
	char szline[MAXSTRLEN] = {0};

	FILE *fp = NULL;
	if(NULL == (fp = fopen(filename,"r")))
	{
		LOG(ERROR)<<"file not exist!!"<<endl;

		return false;
	}

	while(NULL != fgets(szline,sizeof(szline),fp))
	{
		char szkey[100] = {0};
		char szvalue[MAXSTRLEN] = {0};

		//跳过注释行
		if(IsNeedSkip(szline))
			continue;

		//去掉回车换行
		int len = strlen(szline);
		if(szline[len - 1] == '\n')
		{
			szline[len-1] =0;
		}
		//取值
		if(ParserLine(szline, szkey, szvalue) <0)
		{
			fclose(fp);
			return false;
		}
		outmap.insert(make_pair(szkey,szvalue));

	}
	//转换成key=value格式以方便日志查看  ---hawrk debug H_DEBUG
#ifdef H_DEBUG
	string outstr;
	Map2Str(outmap,outstr);
	LOG(INFO)<<" get config key&value ["<<outstr<<"]"<<endl;
#endif

	return true;
}

bool CConfig::ReadConfByKey(const char* filename,const char* key,char* value)
{
	//LOG(INFO)<<"read config by key"<<endl;

	char szline[MAXSTRLEN] = {0};

	FILE *fp = NULL;
	if(NULL == (fp = fopen(filename,"r")))
	{
		LOG(ERROR)<<"file not exist!!"<<endl;

		return false;
	}

	while(NULL != fgets(szline,sizeof(szline),fp))
	{
		char szkey[100] = {0};
		char szvalue[MAXSTRLEN] = {0};

		//LOG(INFO)<<" 1szline = "<<szline<<endl;
		//跳过注释
		if(IsNeedSkip(szline))
			continue;

		//LOG(INFO)<<"szline = ["<<szline<<"]"<<endl;
		//去掉回车换行
		int len = strlen(szline);
		if(szline[len - 1] == '\n')
		{
			szline[len-1] =0;
		}
#ifdef H_DEBUG
		LOG(INFO)<<"szline  data = ["<<szline<<"]"<<endl;
#endif
		if(ParserLine(szline, szkey, szvalue) <0)
		{
			fclose(fp);
			return false;
		}

		//LOG(INFO)<<"szkey = "<<szkey<<"szvalue = ["<<szvalue<<"]"<<endl;
		if(strcmp(key,szkey) == 0)
		{
			fclose(fp);
			strcpy(value,szvalue);
			LOG(INFO)<<"get config value:["<<value<<"] by key :["<<key<<"]"<<endl;
			return true;
		}
	}
	LOG(INFO)<<" no value for key:["<<key<<"]"<<endl;

	fclose(fp);
	return false;
}




